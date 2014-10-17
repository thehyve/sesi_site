<?php

/**
 * Registers urls specific for new query interface 
 * Implements hook_menu().
 */
function query_interface_menu() {
    $items = array();
    
    // This URL is used when a new query term is added, but when no term object exists yet
    // The user can access this screen whenever he has access to the query
    $items['sesi/%ctools_js/node/%node/queries/%mica_query/term/%node/add'] = array(
        'title' => 'Edit',
        'access callback' => '_mica_datasets_query_access',
        'access arguments' => array(3, 5, 'update'),
        'page callback' => 'query_interface_add_query_term_modal_page', 
        'page arguments' => array(1, 3, 5, 7, 9),
        'type' => MENU_CALLBACK
    );
    return $items;
}

/**
 * Changes the edit query term form to always submit to the 'edit' url. This
 * prevents the system of saving another query_term, if a new one was created already
 * using the query_interface_add_query_term_modal_page method
 * Implements hook hook_FORM_ID_alter
 * @param array $form
 * @param type $form_state
 * @param type $form_id
 * @return type 
 */
function query_interface_form_mica_datasets_query_term_edit_form_alter(&$form, $form_state, $form_id) {
    $dataset_node = $form_state[ "build_info" ][ "args" ][0];
    $query = $form_state[ "build_info" ][ "args" ][1];
    $query_term = $form_state[ "build_info" ][ "args" ][2];
    
    // Update the form action to make sure not to add the (empty) query term again
    $form[ "#action" ] = url( "mica/ajax/node/" . $dataset_node->nid . "/queries/" . $query->id . "/term/" . $query_term->id . "/edit");
    
    // Update the cancel button to point to the edit query screen
    $form[ "actions" ][ "cancel" ][ "#href" ] = _mica_query_url($dataset_node, $query, "edit");
    
    return $form;
}

/**
 * Shows a screen to specify a query term for a given variable.
 * This method is used as a wrapper around mica_datasets_query_term_edit_modal_page, 
 * as that method needs an already saved query_term object.
 * 
 * @param type $js              ??
 * @param type $node            Dataset node
 * @param type $query           Mica query object
 * @param type $variable        Variable to create a constraint for
 * @param type $cross_variable  (optional) cross variable
 * @see mica_datasets_query_term_edit_modal_page()
 * @see query_interface_menu()
 */
function query_interface_add_query_term_modal_page($js, $node, $query, $variable, $cross_variable = NULL) {
    // Create a term based on the variable
    $values = _query_interface_extract_new_query_term_values($query, $variable);
    if (MicaDatasetQueryManager::isCached($query)) {
        // Add the term. Unfortunately, even though the documentation says so
        // this method doesn't return the new term ID
        $cachedQuery = MicaDatasetQueryManager::getCache($query);
        $cachedQuery->addTerm($values);        
        $termId = $query->id . ':' . count( $cachedQuery->terms );
    } else {
        $termId = mica_query_term_insert($values);
    }    
    
    $term = mica_query_term_load( $termId );
    
    // Call the original method
    $form = mica_datasets_query_term_edit_modal_page($js, $node, $query, $term, $cross_variable);
    return $form;
}

/**
 * Callback for the delete term button on the query screen. 
 * 
 * This method does really delete the term immediately, instead of only 
 * keeping track of deleted terms, as mica does. 
 * @param type $form
 * @param type $form_state
 * @return type 
 */
function query_interface_delete_query_term( &$form, $form_state ) {
    if( !array_key_exists( "triggering_element", $form_state ) || !array_key_exists( "#termid", $form_state[ "triggering_element" ] ) )
        return;
    
    // Determine term ID
    $termId = $form_state[ "triggering_element" ][ "#termid" ];
    mica_query_term_delete($termId);
}

/**
 * Create a new set of values to create a new query term. 
 * @param type $query
 * @param type $variable 
 * @see _mica_query_extract_new_query_term_values
 */
function _query_interface_extract_new_query_term_values( $query, $variable ) {
  $values = array();
  $values['query_id'] = $query->id;
  $values['variable_id'] = $variable->nid;
  $values['weight'] = 0;
  return $values;    
}
