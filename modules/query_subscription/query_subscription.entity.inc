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
   * This method returns the differences for this subscription if a check is due and they are significant.. If this subscription is not
   * yet due to be checked returns NULL silently. If differences are found the subscription's timestamp is updated and the
   * new result is stored. If the structure of the query was changed since the last run, the stored result and timestamp
   * is updated but no changes are reported.
   *
   * @return array
   */
  public function significantDifferences() {
    if(!$this->needsUpdate()) return array();

    $new_result = $this->results();

    if(is_null($this->updated) || is_null($this->last_result)) {
      $this->update();
      return NULL;
    }

    $old_result = $this->old_results();

    if(count(array_filter($old_result, function($a) {return !is_array($a);})) !== 0) {
      // stored result is in an older format
      $this->update();
      return NULL;
    }

    if($this->resultStructureChanged($old_result['_all'], $new_result['_all'])) {
      $this->update();
      return NULL;
    }

    $change = array();

    $change['studies_removed'] = array_diff_key($old_result, $new_result);
    $change['studies_added'] = array_diff_key($new_result, $old_result);
    $significant = !empty($change['studies_added']) or !empty($change['studies_removed']);

    foreach(array_keys($old_result['_all']['_matched']) as $term) {
      $old = $old_result['_all']['_matched'][$term];
      $new = $new_result['_all']['_matched'][$term];
      $significant |= abs($old - $new) > $old * $this->threshold;
      if($significant) break;
    }

    $change['old_matched'] = $old_matched = $old_result['_all']['_matched']['_all'];
    $change['new_matched'] = $new_matched = $new_result['_all']['_matched']['_all'];

    if(isset($old_result['_all']['_matched']['_cardinality'])) {
      $change['old_cardinality'] = $old_cardinality = $old_result['_all']['_matched']['_cardinality'];
      $change['new_cardinality'] = $new_cardinality = $new_result['_all']['_matched']['_cardinality'];
    }

    if(!$significant) {
      // Don't update the stored result, we want to compare against it again the next time.
      return NULL;
    }

    $this->update();
    return $change;
  }

  /**
   * Helper function to tell if both argument arrays have the same keys
   * @param $first
   * @param $second
   * @return bool
   */
  function sameKeys($first, $second) {
    return is_array($first) and is_array($second) and
      count(array_diff_key($first, $second)) === 0 and
      count(array_diff_key($second, $first)) === 0;
  }

  function resultStructureChanged($old, $new) {
    if(!$this->sameKeys($old, $new)) {
      return TRUE;
    }
    foreach($old as $variable => $terms) {
      if(!$this->sameKeys($old[$variable], $new[$variable])) {
        return TRUE;
      }
    }
    return FALSE;
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
    $ret['dataset'] = node_load($query->dataset_id);
    if(isset($ret['dataset']->field_expiration_date['und'][0]['value'])) {
      $ret['dataset_expiration_date'] = new DateTime($ret['dataset']->field_expiration_date['und'][0]['value']);
      //$ret['connectors'] = $ret['terms'] = array();
    } else {
      $ret['dataset_expiration_date'] = null;
      // Accessing this on an expired dataset generates an error message
      //$ret['connectors'] = self::id_map(mica_connector_query_multiple($query->dataset_id));
      $ret['terms'] = mica_query_term_query($query);
    }
    /*$ret['connectors'] =*/ $ret['terms'] = array();
    if (is_null($ret['dataset_expiration_date'])) {
      // Accessing this on an expired dataset generates an error message
      //$ret['connectors'] = self::id_map(mica_connector_query_multiple($query->dataset_id));
      $ret['terms'] = mica_query_term_query($query);
    }

    //$ret['studies'] = array();
    //foreach($ret['connectors'] as $connid => $conn) {
    //  $ret['studies'][$connid] = node_load($conn->study_id);
    //}

    $ret['term_variables'] = array();
    foreach ($ret['terms'] as $tid => $term) {
      $ret['term_variables'][$tid] = node_load($term->variable_id);
    }
    $ret['cross_variable'] = node_load($query->cross_variable_id);

    $ret['categories'] = array();
    if ($ret['cross_variable']) {
      foreach (entity_metadata_wrapper('node', $ret['cross_variable'])->field_variable_categories->value() as $cat) {
        $ret['categories'][$cat['name']] = $cat['label'];
      }
    }

    return $ret;
  }

  static function study_for_connection_id($connId) {
    $connection = node_load($connId);
    return node_load($connection->study_id);
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
