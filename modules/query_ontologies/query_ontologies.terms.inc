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
class OntologyTerm extends AbstractTerm {

  function __construct(MicaDatasetQueryTerm $qt) {
    parent::__construct('OntologyTerm', $qt);
  }

  /**
   * Shows a table with information on the query term. However, as we
   * do not want to enumerate all possible ontology terms.
   * @return type
   */
  function view() {
 //    $variable = $this->getVariable();

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
      '#title' => 'Values',
    );

    // TODO: check selected values already at the start
    $taxonomyUrl = url("sesi/variable/" . $this->getVariable()->nid . "/variabletaxonomy");
    $default_value = ''; // implode(" ", $this->match());
    $treeMarkup = "<div id='taxonomy_query_tree' style='min-height: 120px; max-height: 400px; overflow: auto; ' class='aciTree' data-url='" . htmlspecialchars( $taxonomyUrl ). "'></div>";
    $initScript = '<script type="text/javascript">jQuery(function () { 
        Sesi.QueryOntologies.TaxonomyTree.init(); 
    });</script>';
    $form['valuecontainer']['fieldset']['value'] = array(
      '#markup' => $treeMarkup . $initScript,
    );

    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciPlugin.min.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.dom.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.core.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.selectable.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.checkbox.js');
    drupal_add_css(drupal_get_path('module', 'query_interface') . '/aciTree/css/aciTree.css');
    
    // Add custom interface scripts. 
    drupal_add_js(drupal_get_path('module', 'query_ontologies') . '/query_ontologies.taxonomy_tree.js');
    
    return $form;
  }

  // No validation for now
  function validate($form, &$form_state) {

  }

  function submit($form, &$form_state) {
    $selection = $form_state['values']['categories'];
    $inverted = $form_state['values']['inverted'];

    $this->setInverted($inverted == 'notin');
    $this->setCategories($this->formToCategories($selection));
  }

  /**
   * Undoes the categoriesToForm() function
   * @param array $formCategories
   */
  private function formToCategories(array $formCategories) {
    // array_filter will remove all non-selected categories
    // array_keys will return only the array keys
    $selected = array_keys(array_filter($formCategories));
    $categories = array();
    foreach ($selected as $c) {
      $categories[] = substr($c, 2);
    }
    return $categories;
  }

}
