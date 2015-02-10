<?php

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
    $origin = $form_state[ "build_info" ][ "args" ][3];
    
    // Update the form action to make sure not to add the (empty) query term again
    $form[ "#action" ] = url( "mica/ajax/node/" . $dataset_node->nid . "/queries/" . $query->id . "/term/" . $query_term->id . "/edit");
    
    // Update the cancel button to point to the edit query screen
    $form[ "actions" ][ "cancel" ][ "#href" ] = _mica_query_url($dataset_node, $query, $origin);
    
    $form['actions']['origin'] = array(
        '#type' => 'hidden',
        '#name' => 'origin',
        '#value' => $origin,
    );
    
    return $form;
}

/**
 * Page to display the edit query term form in a modal dialog. 
 * This is separate from the normal method so we can set the origin 
 * properly. See SESIDEV-78
 * @param $js
 * @param $node
 * @param $query
 * @param $term
 */
function query_interface_query_term_edit_modal_page($js = NULL, $node, $query, $term, $cross_variable = NULL) {
  if ($js) {
    $impl = $term->termImpl();
    $title = t('Edit !term', array('!term' => $impl->getFieldName()));
    $origin = "edit";
    query_interface_modal_form_term_render($title, 'mica_datasets_query_term_edit_form', $node, $query, $term, $origin, $cross_variable);
  }
  else {
    // fallback to plain page
    return query_interface_query_term_edit_page($node, $query, $term, $cross_variable);
  }
}

/**
 * Page to display the edit query term form. This is separate from the normal
 * method so we can set the origin properly. See SESIDEV-78
 * @param $node
 * @param $query
 * @param $term
 */
function query_interface_query_term_edit_page($node, $query, $term, $cross_variable = NULL) {
  $impl = $term->termImpl();
  drupal_set_title(
    t('!title -- Edit !term in !query',
      array(
        '!title' => $node->title,
        '!query' => $query->name,
        '!term' => $impl->getFieldName()
      )
    )
  );
  $origin = "edit";
  return drupal_get_form('mica_datasets_query_term_edit_form', $node, $query, $term, $origin, $cross_variable);
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

    if($variable->title === variable_get_value('mica_query_patients_cardinality_variable')) {
        // This variable may not be queried on.
        form_set_error('variables', t('Invalid variable, the specified variable cannot be queried on.'));
        $cmd = array(ctools_modal_command_dismiss(), ctools_ajax_command_submit("#mica-query-edit-form"));
        print ajax_render($cmd);
        return NULL;
    }

    // Mark the term as being added but not yet saved. We will delete 
    // this term again when it is shown on screen without being saved.
    // That could happen if the user clicks 'cancel' or closes the screen
    if( !array_key_exists( "options", $values ) ) 
        $values[ 'options' ] = array();
    
    $values[ "options" ][ "isSavedByUser" ] = false;
    
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
    $form = query_interface_query_term_edit_modal_page($js, $node, $query, $term, $cross_variable);
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
    
    // Make sure the form parameters are saved as well (SESIDEV-91)
    $query = $form_state['build_info']['args'][1];
    query_interface_store_query_parameters( $query, $form_state );
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

/**
 * Delete query terms that have not been saved by the user. That could
 * happen if the user closes the popup or clicks cancel, without saving the
 * term.
 * @param type $query 
 */
function query_interface_cleanupTerms( $query ) {
    if( !$query ) {
        return;
    }
    
  // Loop through terms and see which terms are saved by the user. If not
  // delete these terms
  $originalTerms = mica_query_term_query($query);
  
  if( !$originalTerms )
      return;
  
  foreach( $originalTerms as $term ) {
      if( $term->options && array_key_exists( "isSavedByUser", $term->options ) && !$term->options[ "isSavedByUser" ] ) {
          // Delete the query
          if (is_numeric($term->id)) {
              // delete term
              $term->delete();
          } else {
              MicaDatasetQueryManager::getCache($query)->deleteTerm($term);
          }
      }
  }    
}

/**
 * Renders the form identified by $form_id in a modal dialog, with provided title. 
 * Additional arguments are added to the $form_state.
 * 
 * This implementation differs from the original mica_core_modal_form_render 
 * method in that it submits a parent form if form_state[ 'submit_parent_form' ]
 * is given. The value of that variable is used as a selector for the form to submit
 * 
 * @see mica_core_modal_form_render
 * @param $title
 * @param $form_id
 */
function query_interface_modal_form_term_render($title, $form_id) {
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');

  $args = func_get_args();
  // Remove $title and $form_id from the arguments.
  array_shift($args);
  array_shift($args);
  $form_state = array(
    'ajax' => TRUE,
    'title' => $title,
  );
  $form_state['build_info']['args'] = $args;

  $commands = ctools_modal_form_wrapper($form_id, $form_state);

  // If cancelling or complete, return to the activity.
  if (!empty($form_state['complete'])) {
    $commands = array();
    $commands[] = ctools_modal_command_dismiss();
    
    if (!empty($form_state['submit_parent_form'])) {
      $commands[] = ctools_ajax_command_submit($form_state['submit_parent_form']);
    }
    elseif (!empty($form_state['redirect'])) {
      $commands[] = ctools_ajax_command_redirect($form_state['redirect']);
    }
  }
  elseif (!empty($form_state['cancel'])) {
    $commands = array();
    $commands[] = ctools_modal_command_dismiss();
  }

  print ajax_render($commands);
}

/**
 * Store query parameters (name, description) from the form state
 * 
 * Can be used when e.g. adding or deleting a term
 * @param type $query
 * @param type $form_state 
 */
function query_interface_store_query_parameters( $query, $form_state ) {
      $query->name = check_plain($form_state['values']['name']);
      $query->description = $form_state['values']['description'];
      
      if( !array_key_exists( 'cross-variable', $form_state[ 'values' ] ) || $form_state['values']['cross-variable'] == '-1' ) {
        $query->cross_variable_id = NULL;
      } else {
          $query->cross_variable_id = $form_state['values']['cross-variable'];
      }

      if (MicaDatasetQueryManager::isCached($query)) {
        // then save all and remove from cache
        MicaDatasetQueryManager::save($query);
      }
      else {
        // save query
        $query->save();
      }
          
    
}