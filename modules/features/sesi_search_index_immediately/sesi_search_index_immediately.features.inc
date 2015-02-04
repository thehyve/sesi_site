<?php
/**
 * @file
 * sesi_search_index_immediately.features.inc
 */

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_search_index_immediately_default_search_api_index_alter(&$data) {
  if (isset($data['dataset_index'])) {
    $data['dataset_index']->options['index_directly'] = 1; /* WAS: 0 */
  }
  if (isset($data['fields_description_index'])) {
    $data['fields_description_index']->options['index_directly'] = 1; /* WAS: 0 */
  }
  if (isset($data['studies_index'])) {
    $data['studies_index']->options['index_directly'] = 1; /* WAS: 0 */
  }
  if (isset($data['variable_index'])) {
    $data['variable_index']->options['index_directly'] = 1; /* WAS: 0 */
  }
}
