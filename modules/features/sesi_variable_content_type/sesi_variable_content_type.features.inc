<?php
/**
 * @file
 * sesi_variable_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_variable_content_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_variable_content_type_default_search_api_index_alter(&$data) {
  if (isset($data['variable_index'])) {
    $data['variable_index']->options['fields']['field_validate_categories'] = array(
      'type' => 'boolean',
    ); /* WAS: '' */
  }
}
