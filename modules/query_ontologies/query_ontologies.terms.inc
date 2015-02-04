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
      $ids = $this->getSelectedTermIds();
      
      if( count( $ids ) == 0 ) 
          return array();
      
      // Retrieve the variable and its taxonomy
      $variable = $this->getVariable();
      $wrapper = entity_metadata_wrapper('node', $variable);
      $taxonomy = $wrapper->field_taxonomy->value();

      if (!$taxonomy) {
        return array();
      }

      $terms = taxonomy_term_load_multiple( $ids );
      
      $codes = array();
      
      foreach( $terms as $term ) {
          $name = $term->name;
          
          // Retrieve the code from the title
          $separatorLocation = strpos( $name, self::CODE_SEPARATOR );
          
          if( $separatorLocation > 0 ) {
              $codes[] = trim( substr( $name, 0, $separatorLocation ) );
          }
      }
      
      return $codes;
  }
  
  function operator() {
    return isset($this->options['operator']) ? $this->options['operator'] : 'OR';
  }  
  
  /**
   * Return a list of selected IDs
   * @return type 
   */
  function getSelectedTermIds() {
      if( array_key_exists( "termIds", $this->options ) && is_array( $this->options[ "termIds" ] ) )
          return $this->options['termIds'];
      else
          return array();
  }
  
  /**
   * Set a list of selected term IDs
   * @param type $termIds 
   */
  function setSelectedTermIds($termIds = array()) {
    $this->options['termIds'] = $termIds;
  }      
  
  /**
   * Return the options and make sure that it behaves as an OntologyTerm
   */
  function getOptions() {
      $options = parent::getOptions();
      $options[ "type" ] = "OntologyTerm";
      
      return $options;
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
    
    // Determine the dataset ID as it is needed to retrieve the taxonomy
    $dataset = $form_state[ "build_info" ][ "args" ][ 0 ];
    
    $dataset_id = $dataset->nid;
    
    $uri = "sesi/node/" . $dataset_id . "/variable/" . $this->getVariable()->nid . "/variabletaxonomy";
    $taxonomyUrl = url($uri);
    $selectedIds = $this->getSelectedTermIds();
    $default_value = ''; // implode(" ", $this->match());
    
    $treeMarkup = "<div id='taxonomy_query_tree' style='min-height: 120px; max-height: 400px; overflow: auto; ' class='aciTree' data-selected-ids='" . implode( ',', $selectedIds ) . "' data-url='" . htmlspecialchars( $taxonomyUrl ). "'></div>";
    $initScript = '<script type="text/javascript">jQuery(function () { 
        Sesi.QueryOntologies.TaxonomyTree.init(); 
    });</script>';
    
    $form['valuecontainer']['fieldset']['filter'] = array(
        '#type' => 'textfield',
        '#title' => t('Filter tree')
    );

    $form['valuecontainer']['fieldset']['value'] = array(
        '#markup' => $treeMarkup . $initScript,
    );
    

    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciPlugin.min.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.dom.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.core.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.selectable.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.checkbox.js');
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/aciTree/js/jquery.aciTree.utils.js');
    drupal_add_css(drupal_get_path('module', 'query_interface') . '/aciTree/css/aciTree.css');
    
    // Add custom interface scripts. 
    drupal_add_js(drupal_get_path('module', 'query_ontologies') . '/query_ontologies.taxonomy_tree.js');
    
    return $form;
  }

  // No validation for now
  function validate($form, &$form_state) {

  }

  function submit($form, &$form_state) {
    if( array_key_exists( 'terms', $form_state[ 'input' ] ) ) {
        $selection = $form_state['input']['terms'];
    } else {
        $selection = array();
    }
    
    $inverted = $form_state['values']['inverted'];

    $this->setInverted($inverted == 'notin');
    $this->setSelectedTermIds($selection);
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
