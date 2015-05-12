<?php
/**
 * @file
 * sesi_wildcard_content_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_wildcard_content_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_wildcard_content_search_default_search_api_index_alter(&$data) {
  if (isset($data['dataset_index'])) {
    $data['dataset_index']->options['processors']['search_api_case_ignore']['weight'] = -50; /* WAS: 0 */
    $data['dataset_index']->options['processors']['search_api_html_filter']['weight'] = -49; /* WAS: 10 */
    $data['dataset_index']->options['processors']['search_api_tokenizer']['settings']['spaces'] = '[^\\p{L}\\p{N}?*^\']'; /* WAS: '[^\\p{L}\\p{N}^\']' */
    $data['dataset_index']->options['processors']['search_api_tokenizer']['status'] = 1; /* WAS: 0 */
    $data['dataset_index']->options['processors']['search_api_tokenizer']['weight'] = -48; /* WAS: 20 */
    $data['dataset_index']->options['processors']['sesi_wildcard'] = array(
      'status' => 1,
      'weight' => -47,
      'settings' => array(),
    ); /* WAS: '' */
    unset($data['dataset_index']->options['processors']['search_api_tokenizer']['settings']['fields']['title']);
  }
  if (isset($data['studies_index'])) {
    $data['studies_index']->options['processors']['search_api_case_ignore']['weight'] = -50; /* WAS: 0 */
    $data['studies_index']->options['processors']['search_api_html_filter']['weight'] = -49; /* WAS: 10 */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['fields']['body:summary'] = TRUE; /* WAS: '' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['fields']['body:value'] = TRUE; /* WAS: '' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['fields']['field_acroym'] = TRUE; /* WAS: '' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['fields']['search_api_aggregation_1'] = TRUE; /* WAS: '' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['fields']['title_field'] = TRUE; /* WAS: '' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['settings']['spaces'] = '[^\\p{L}\\p{N}?*^\']'; /* WAS: '[^\\p{L}\\p{N}^\']' */
    $data['studies_index']->options['processors']['search_api_tokenizer']['status'] = 1; /* WAS: 0 */
    $data['studies_index']->options['processors']['search_api_tokenizer']['weight'] = -48; /* WAS: 20 */
    $data['studies_index']->options['processors']['sesi_wildcard'] = array(
      'status' => 1,
      'weight' => -47,
      'settings' => array(),
    ); /* WAS: '' */
  }
  if (isset($data['variable_index'])) {
    $data['variable_index']->options['processors']['search_api_case_ignore']['weight'] = 0; /* WAS: 0 */
    $data['variable_index']->options['processors']['search_api_html_filter']['weight'] = 10; /* WAS: 10 */
    $data['variable_index']->options['processors']['search_api_tokenizer']['settings']['spaces'] = '[^\\p{L}\\p{N}?*^_\']'; /* WAS: '[^\\p{L}\\p{N}^\']' */
    $data['variable_index']->options['processors']['search_api_tokenizer']['weight'] = 20; /* WAS: 20 */
    $data['variable_index']->options['processors']['sesi_wildcard'] = array(
      'status' => 1,
      'weight' => 50,
      'settings' => array(),
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function sesi_wildcard_content_search_views_default_views_alter(&$data) {
  if (isset($data['datasets'])) {
    $data['datasets']->display['default']->display_options['filters']['search_api_views_fulltext'] = array(
      'id' => 'search_api_views_fulltext',
      'table' => 'search_api_index_dataset_index',
      'field' => 'search_api_views_fulltext',
      'group' => 1,
      'exposed' => TRUE,
      'expose' => array(
        'operator_id' => 'search_api_views_fulltext_op',
        'label' => 'Search',
        'description' => 'use * and ? wildcards to search for partial words',
        'operator' => 'search_api_views_fulltext_op',
        'identifier' => 'search_api_views_fulltext',
        'remember_roles' => array(
          2 => 2,
          1 => 0,
          3 => 0,
          4 => 0,
          6 => 0,
          5 => 0,
          7 => 0,
          8 => 0,
          10 => 0,
          9 => 0,
        ),
      ),
      'group_info' => array(
        'label' => 'Fulltext search',
        'identifier' => 'search_api_views_fulltext',
        'remember' => FALSE,
        'group_items' => array(
          1 => array(),
          2 => array(),
          3 => array(),
        ),
      ),
      'fields' => array(
        'search_api_aggregation_1' => 'search_api_aggregation_1',
        'body:value' => 'body:value',
        'body:summary' => 'body:summary',
      ),
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['filters']['type']['group'] = 1; /* WAS: '' */
    unset($data['datasets']->display['default']->display_options['header']['area']['content']);
  }
  if (isset($data['studies_search'])) {
    $data['studies_search']->display['page_1']->display_options['filters']['search_api_views_fulltext'] = array(
      'id' => 'search_api_views_fulltext',
      'table' => 'search_api_index_studies_index',
      'field' => 'search_api_views_fulltext',
      'exposed' => TRUE,
      'expose' => array(
        'operator_id' => 'search_api_views_fulltext_op',
        'label' => 'Search',
        'description' => 'use * and ? wildcards to search for partial words',
        'operator' => 'search_api_views_fulltext_op',
        'identifier' => 'search_api_views_fulltext',
        'remember_roles' => array(
          2 => 2,
          1 => 0,
          3 => 0,
          4 => 0,
          6 => 0,
          5 => 0,
          7 => 0,
          8 => 0,
          10 => 0,
          9 => 0,
        ),
      ),
      'fields' => array(
        'title_field' => 'title_field',
        'field_acroym' => 'field_acroym',
        'body:value' => 'body:value',
        'body:summary' => 'body:summary',
      ),
    ); /* WAS: '' */
    unset($data['studies_search']->display['page_1']->display_options['header']['area']['content']);
    unset($data['studies_search']->display['page_1']->display_options['header']['result']);
  }
  if (isset($data['variable_search'])) {
    $data['variable_search']->display['default']->display_options['filters']['search_api_views_fulltext']['expose']['description'] = 'use * and ? wildcards to search for partial words'; /* WAS: '' */
  }
}
