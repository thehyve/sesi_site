<?php

class QuerySubscription extends Entity {

  public $id = NULL;
  public $query_id = NULL;
  public $poll_interval = self::WEEKLY;
  public $threshold = 0.05;
  public $updated = NULL;
  public $last_result = NULL;

  private $cached_results = NULL;

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
    if(is_null($id) || $id === false) return NULL;
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

  public function threshold() {
    return $this->threshold * 100;
  }

  public function interval() {
    switch($this->poll_interval) {
      case self::ALWAYS:
        return t('always');
      case self::DAILY:
        return t('daily');
      case self::WEEKLY:
        return t('weekly');
      case self::MONTHLY:
        return t('monthly');
      default:
        throw new Exception("Unknown poll_interval value: {$this->poll_interval}, must be in range 1-3. Subscription id {$this->id}.");
    }
  }

  public function updated() {
    $d = new DateTime();
    $d->setTimestamp($this->updated);
    return $d;
  }

  private function needsUpdate() {
    if(is_null($this->updated)) return true;
    switch($this->poll_interval) {
      case self::ALWAYS:
        return true;
      case self::DAILY:
        return $this->updated < time() - 60*60*24;
      case self::WEEKLY:
        return $this-> updated < time() - 60*60*24*7;
      case self::MONTHLY:
        return $this-> updated < time() - 60*60*24*30;
      default:
        throw new Exception("Unknown poll_interval value: {$this->poll_interval}, must be in range 1-3. Subscription id {$this->id}.");
    }
  }

  private function update() {
    $this->updated = time();
    $this->last_result = serialize($this->results());
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

    $new_result = $this->results();

    if(is_null($this->updated) || is_null($this->last_result)) {
      $this->update($new_result);
      return array();
    }

    $old_result = $this->old_results();

    $changes = array();
    $structurechanged = ! $this->recursiveCompare($old_result, $new_result, array('connection', 'term', 'category'), $changes);

    $over_threshold = false;
    foreach($changes as $change) {
      $max_diff = $change['old_value'] * $this->threshold;
      if (abs($change['new_value'] - $change['old_value']) > $max_diff) {
        $over_threshold = true;
        break;
      }
    }
    if (!$over_threshold) {
      $changes = array();
    }

    $changes = array_filter($changes, function($c) {return $c['connection'] != '_matched_sum';});

    if($structurechanged || !empty($changes)) {
      $this->update();
    }

    if($structurechanged) {
      return array();
    } else {
      return $changes;
    }
  }

  /**
   * Recursively compare two arrays. Any differences are reported in &$changed. $names must contain a list of names that
   * are used as keys in &$changed elements to indicate each level of the array. Recursion will stop if the end of
   * $names is reached.
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
  private function recursiveCompare($old, $new, $names, &$changed, $path = array()) {
    if (!is_array($old) || !is_array($new) || count($names) == 0) {
      if ($new != $old) {
        $changed[] = $path + array('old_value' => $old, 'new_value' => $new);
      }
    } else {
      $keyname = array_shift($names);
      if (count($old) != count($new)) return false;
      foreach ($old as $key => $old_value) {
        if (!isset($new[$key])) return false;
        $ret = $this->recursiveCompare($old_value, $new[$key], $names, $changed, $path + array($keyname => $key));
        if (!$ret) return false;
      }
    }
    return true;
  }

  /**
   * This method packs all data structures related to this subscription and its query into a handy package so that e.g.
   * the name of variables and of the study can be found easily.
   *
   * @return array
   */
  public function descriptors() {
    $query = $this->query();

    $ret = array();
    $ret['connectors'] = self::id_map(mica_connector_query_multiple($query->dataset_id));
    $ret['terms'] = mica_query_term_query($query);
    $ret['dataset'] = node_load($query->dataset_id);
    $ret['dataset_expiration_date'] = null;
    try {
      $expiration_date = $ret['dataset']->field_expiration_date['und'][0]['value'];
      if(!empty($expiration_date)) {
        $ret['dataset_expiration_date'] = new DateTime($expiration_date);
      }
    } catch(Exception $e) {
      // leave dataset_expiration_date null
    }

    $ret['studies'] = array();
    foreach($ret['connectors'] as $connid => $conn) {
      $ret['studies'][$connid] = node_load($conn->study_id);
    }

    $ret['term_variables'] = array();
    foreach ($ret['terms'] as $tid => $term) {
      $ret['term_variables'][$tid] = node_load($term->variable_id);
    }
    $ret['cross_variable'] = node_load($query->cross_variable_id);

//    $categories = array('_all' => 'total', 'total' => 'total', '_matched' => 'matched');
    $ret['categories'] = array();
    if ($ret['cross_variable']) {
      foreach (entity_metadata_wrapper('node', $ret['cross_variable'])->field_variable_categories->value() as $cat) {
        $ret['categories'][$cat['name']] = $cat['label'];
      }
    }

    return $ret;
  }

  /**
   * Query the current results for this subscription's query. The results are cached. To clear the cache, pass
   * array('clear_cache') as argument.
   *
   * @param array $options
   * @return array
   */
  public function results($options = array()) {
    if(in_array('clear_cache', $options)) {
      $this->cached_results = NULL;
    }

    if(is_null($this->cached_results)) {
      $res = query_subscription_query_result($this->query());
      $res['_matched_sum'] = array_sum(array_map(function($a) {return $a['_matched']['_all'];}, $res));
      $this->cached_results = $res;
    }
    return $this->cached_results;
  }

  public function old_results() {
    return unserialize($this->last_result);
  }

  private static function id_map($arr) {
    $ret = array();
    foreach($arr as $item) {
      $ret[$item->id] = $item;
    }
    return $ret;
  }

}
