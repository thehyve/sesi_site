<?php

/**
 * Recognizes the following options structure:
 * {
 *   categories: [ '1', '2', '3' ],
 *   operator : 'OR'
 * }
 * where
 *   categories is a list of categories names (can be empty or null)
 *   operator is either 'AND' or 'OR' (can be empty or null)
 */
class VocabularyTerm extends AbstractTerm {
    const CODE_SEPARATOR = " - ";
    
  function __construct(MicaDatasetQueryTerm $qt) {
      // In order to avoid many changes in mica tell others that 
      // I'm a categoryterm, as these types of queryterms are hardcoded.
      parent::__construct('CategoryTerm', $qt);
  }
  
  /**
   * Return the selected codes
   */
  function categories() {
      return $this->getSelectedCodes();
  }
  
  function operator() {
    return isset($this->options['operator']) ? $this->options['operator'] : 'OR';
  }  
  
  /**
   * Return a list of selected codes
   * @return type 
   */
  function getSelectedCodes() {
      if( array_key_exists( "codes", $this->options ) && is_array( $this->options[ "codes" ] ) )
          return $this->options['codes'];
      else
          return array();
  }
  
  /**
   * Set a list of selected codes
   * @param type $codes
   */
  function setSelectedCodes($codes = array()) {
    $this->options['codes'] = $codes;
  }      
  
  /**
   * Return the options and make sure that it behaves as a VocabularyTerm
   */
  function getOptions() {
      $options = parent::getOptions();
      $options[ "type" ] = "VocabularyTerm";
      
      return $options;
  }
  
  /**
   * Shows a table with information on the query term. 
   * @return type
   */
  function view() {

    $headers = array('Value');
    $stats = $this->stats();
    foreach ($stats as $study_id => $stat) {
      $headers[] = $this->getStudyName($study_id);
    }

    $row = array(
      array(
        'data' => t('All'),
        'class' => array('active')
      )
    );
    foreach ($stats as $study_id => $stat) {
      $row[] = array(
        'data' => isset($stat['_all']) ? $stat['_all'] : 0,
        'class' => array('active')
      );
    }
    $rows[] = $row;

    return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No studies available')));
  }

  function form($form, &$form_state) {
    $form['inverted'] = array(
      '#title' => t('Operator'),
      '#type' => 'select',
      '#options' => array('in' => 'in', 'notin' => 'not in'),
      '#default_value' => $this->isInverted() ? 'notin' : 'in',
    );

    $form['valuecontainer']['fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => 'Values with autocomplete',
    );

    // For now we only support a single selected code in the frontend
    // But we want to support an autocomplete. For that, we need the variable id
    $variableId = $form_state[ "build_info" ][ "args" ][ 2 ]->variable_id;
    
    $default_value = implode(" ", $this->getSelectedCodes());
    $form['valuecontainer']['fieldset']['value'] = array(
      '#type' => 'textfield',
      '#default_value' => $default_value,
      '#autocomplete_path' => 'sesi/variable/' . $variableId . '/suggest'
    );
    
    return $form;
  }

  // No validation for now
  function validate($form, &$form_state) {

  }

  function submit($form, &$form_state) {
    $selection = trim($form_state['values']['value']);
    $inverted = $form_state['values']['inverted'];

    if (strcmp($selection, '') == 0) {
      $selection = array();
    }
    else {
      $selection = explode(" ", $selection);
      foreach ($selection as $key => $value) {
        $selection[$key] = drupal_strtolower($value);
      }
    }

    $this->setInverted($inverted == 'notin');
    $this->setSelectedCodes($selection);
  }
  
  function toString() {
    $str = parent::toString();
    if (count($this->categories()) > 0) {
      switch ($this->operator()) {
        case 'AND':
          $str .= $this->isInverted() ? ' is not ' : ' is ';
          break;
        default:
          $str .= $this->isInverted() ? ' not in ' : ' in ';
          break;
      }
      $str .= '(' . implode(', ', $this->categories()) . ')';
    }
    return $str;
  }
  
  function checkStats() {
    $stats = $this->stats();
    foreach ($stats as $study_id => $stat) {
      if (isset($stat['_all']) && $stat['_all'] != 0) {
        return TRUE;
      }
    }
    return FALSE;
  }

  function asFilter() {
    return $this->asFilterCategoric();
  }
}
