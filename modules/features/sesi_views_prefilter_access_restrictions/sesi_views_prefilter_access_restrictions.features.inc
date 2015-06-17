<?php
/**
 * @file
 * sesi_views_prefilter_access_restrictions.features.inc
 */

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_views_prefilter_access_restrictions_default_search_api_index_alter(&$data) {
  if (isset($data['dataset_index'])) {
    $data['dataset_index']->options['fields']['og_group_ref'] = array(
      'type' => 'list<integer>',
      'entity_type' => 'node',
    ); /* WAS: '' */
  }
  if (isset($data['fields_description_index'])) {
    $data['fields_description_index']->options['fields']['og_group_ref'] = array(
      'type' => 'list<integer>',
      'entity_type' => 'node',
    ); /* WAS: '' */
  }
  if (isset($data['studies_index'])) {
    $data['studies_index']->options['fields']['og_group_ref'] = array(
      'type' => 'list<integer>',
      'entity_type' => 'node',
    ); /* WAS: '' */
  }
  if (isset($data['variable_index'])) {
    $data['variable_index']->options['fields']['og_group_ref'] = array(
      'type' => 'list<integer>',
      'entity_type' => 'node',
    ); /* WAS: '' */
  }
}
