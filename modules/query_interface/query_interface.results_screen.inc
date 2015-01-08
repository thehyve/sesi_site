<?php

/**
 * Changes the layout of the table on the query results screen. In order to 
 * avoid changes in the mica code, everything is changed using javascript and css
 * Implements hook form_FORM_ID_alter
 * 
 * @param type $form
 * @param type $form_state
 * @param type $form_id 
 */
function query_interface_form_mica_query_run_page_alter(&$form, $form_state, $form_id) {
    drupal_add_css(drupal_get_path('module', 'query_interface') . '/query_interface.css');
    
    return $form;
}
