<?php
/**
 * @file
 * sesi_variable_search_wildcards.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_variable_search_wildcards_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_variable_search_wildcards_default_search_api_index_alter(&$data) {
  if (isset($data['variable_index'])) {
    $data['variable_index']->options['processors']['search_api_case_ignore']['weight'] = 0; /* WAS: 0 */
    $data['variable_index']->options['processors']['search_api_html_filter']['weight'] = 10; /* WAS: 10 */
    $data['variable_index']->options['processors']['search_api_tokenizer']['settings']['spaces'] = '[^\\p{L}\\p{N}?*^\']'; /* WAS: '[^\\p{L}\\p{N}^\']' */
    $data['variable_index']->options['processors']['search_api_tokenizer']['weight'] = 20; /* WAS: 20 */
    $data['variable_index']->options['processors']['sesi_wildcard'] = array(
      'status' => 1,
      'weight' => 50,
      'settings' => array(),
    ); /* WAS: '' */
  }
}
