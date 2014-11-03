<?php

/**
 * Changes the layout of the table on the query results screen
 * Implements hook form_FORM_ID_alter
 * 
 * @param type $form
 * @param type $form_state
 * @param type $form_id 
 */
function query_interface_form_mica_query_run_page_alter(&$form, $form_state, $form_id) {
    drupal_add_js(drupal_get_path('module', 'query_interface') . '/query_interface.results_screen.js');
    return $form;
}
