<?php

class QuerySubscription extends Entity {

  public $id = NULL;
  public $query_id = NULL;
  public $poll_interval = self::WEEKLY;
  public $threshold = 0.05;
  public $updated = NULL;
  public $last_result = NULL;

  const ALWAYS = 0;  // ALWAYS is not exposed in the UI, just for testing
  const DAILY = 1;
  const WEEKLY = 2;
  const MONTHLY = 3;

  const QS = 'query_subscription';


  public function __construct($arg = array()) {
    if(is_a($arg, 'MicaDatasetQuery')) {
      $arg = array('query_id' => $arg->id);
    }
    if(array_key_exists('query', $arg)) {
      $arg['query_id'] = $arg['query']->id;
      unset($arg['query']);
    }
    if(isset($arg['updated']) && is_object($arg['updated'])) {
      $arg['updated'] = $arg['updated']->getTimestamp();
    }
    parent::__construct($arg, self::QS);
  }

  /**
   * Get a QuerySubscription
   * @param $id Numeric entity ID
   * @return QuerySubscription|null
   */
  public static function get($id) {
    $subscription = entity_load(self::QS, array($id));
    if(empty($subscription)) { return NULL; }
    return array_pop($subscription);
  }

  public static function hasNotification(MicaDatasetQuery $query) {
    $count = db_query("select count(*) from {query_subscription} where query_id = :qid",
      array(':qid' => $query->id))->fetchField();
    return (bool) $count;
  }

  /**
   * @param MicaDatasetQuery $query
   * @return null|QuerySubscription
   */
  public static function getForQuery(MicaDatasetQuery $query) {
    $id = db_query("select id from {query_subscription} where query_id = :qid",
      array(':qid' => $query->id))->fetchField();
    if(is_null($id) || $id === FALSE) return NULL;
    return self::get($id);
  }

  /**
   * @return MicaDatasetQuery
   */
  public function query() {
    // entity_load already caches
    $q = entity_load('mica_query', array($this->query_id));
    if(empty($q)) throw new Exception("mica_query entity for query_subscription not found");
    return array_pop($q);
  }

  public function updated() {
    $d = new DateTime();
    $d->setTimestamp($this->updated);
    return $d;
  }

  private function needsUpdate() {
    if(is_null($this->updated)) return TRUE;
    switch($this->poll_interval) {
      case self::ALWAYS:
        return TRUE;
      case self::DAILY:
        return $this->updated < time() - 60*60*24;
      case self::WEEKLY:
        return $this-> updated < time() - 60*60*24*7;
      case self::MONTHLY:
        return $this-> updated < time() - 60*60*24*30;
      default:
        throw new Exception("Unknown poll_interval value: {$this->poll_interval}, must be in range 1-3");
    }
  }

  private function update($new_result) {
    $this->updated = time();
    $this->last_result = serialize($new_result);
    $this->save();
  }

  /**
   * This method finds any significant differences for this subscription if a check is due. If this subscription is not
   * yet due to be checked returns silently. If differences are found the subscription's timestamp is updated and the
   * new result is stored. If the structure of the query was changed since the last run, the stored result and timestamp
   * is updated but no changes are reported.
   *
   * @return array
   */
  public function significantDifferences() {
    if(!$this->needsUpdate()) return array();

    $new_result = $this->getResults();

    if(is_null($this->updated) || is_null($this->last_result)) {
      $this->update($new_result);
      return array();
    }

    $old_result = unserialize($this->last_result);

    $changes = array();
    $structurechanged = ! $this->_recursiveCompare($old_result, $new_result, array('connection', 'term', 'category'), $changes);

    if($structurechanged || !empty($changes)) {
      $this->update($new_result);
    }

    if($structurechanged) {
      return array();
    } else {
      return $changes;
    }
  }

  /**
   * Recursively compare two arrays. Any differences that exceed $this->threshold are reported in &$changed. $names must
   * contain a list of names that are used as keys in &$changed elements to indicate each level of the array. The depth
   * of the arrays must match the length of $names.
   *
   * The return value (boolean) indicates if the structure of the two arrays matches. If the structure does not match,
   * the function returns FALSE immediately without looking for further differences. If the structure matches returns
   * TRUE. To match, every node in the array tree must have the same set of keys in $old and $new.
   *
   * @param array $old The old values
   * @param array $new The new values
   * @param array $names A list of names for each level of the compared values
   * @param array $changed Array reference that will be filled with arrays describing changes. Each member array has as
   *   keys the names from $names plus 'old_value' and 'new_value'.
   * @param array $path Used internally, do not specify
   * @return bool Whether the structure of $old and $new is the same
   */
  private function _recursiveCompare($old, $new, $names, &$changed, $path = array()) {
    if (count($names) == 0) {
      $diff = $old * $this->threshold;
      if ($new > $old + $diff || $new < $old - $diff) {
        $changed[] = $path + array('old_value' => $old, 'new_value' => $new);
      }
    } else {
      $keyname = array_shift($names);
      if (count($old) != count($new)) return FALSE;
      foreach ($old as $key => $old_value) {
        if (!isset($new[$key])) return FALSE;
        $ret = $this->_recursiveCompare($old_value, $new[$key], $names, $changed, $path + array($keyname => $key));
        if (!$ret) return FALSE;
      }
    }
    return TRUE;
  }

  public function descriptors() {
    $query = $this->query();

    $ret = array();
    $ret['connectors'] = self::id_map(mica_connector_query_multiple($query->dataset_id));
    $ret['terms'] = mica_query_term_query($query);
    $ret['dataset'] = self::metaload($query->dataset_id);

    $ret['studies'] = array();
    foreach($ret['connectors'] as $connid => $conn) {
      $ret['studies'][$connid] = self::metaload($conn->study_id);
    }

    $ret['term_variables'] = array();
    foreach ($ret['terms'] as $tid => $term) {
      $ret['term_variables'][$tid] = self::metaload($term->variable_id);
    }
    $ret['cross_variable'] = self::metaload($query->cross_variable_id);

//    $categories = array('_all' => 'total', 'total' => 'total', '_matched' => 'matched');
    $ret['categories'] = array();
    if ($ret['cross_variable']) {
      foreach (entity_metadata_wrapper('node', $ret['cross_variable'])->field_variable_categories->value() as $cat) {
        $ret['categories'][$cat['name']] = $cat['label'];
      }
    }

    return $ret;
  }

  public function getResults() {
    return query_subscription_query_result($this->query());
  }

  private static function id_map($arr) {
    $ret = array();
    foreach($arr as $item) {
      $ret[$item->id] = $item;
    }
    return $ret;
  }

  private static function metaload($id) {
    //return entity_metadata_wrapper('node', node_load($id));
    return node_load($id);
  }

}
