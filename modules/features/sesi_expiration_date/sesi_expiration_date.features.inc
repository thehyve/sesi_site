<?php
/**
 * @file
 * sesi_expiration_date.features.inc
 */

/**
 * Implements hook_default_search_api_index_alter().
 */
function sesi_expiration_date_default_search_api_index_alter(&$data) {
  if (isset($data['dataset_index'])) {
    $data['dataset_index']->options['fields']['field_expiration_date'] = array(
      'type' => 'date',
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function sesi_expiration_date_views_default_views_alter(&$data) {
  if (isset($data['datasets'])) {
    $data['datasets']->display['default']->display_options['filter_groups'] = array(
      'groups' => array(
        1 => 'AND',
        2 => 'OR',
      ),
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['filters']['field_expiration_date'] = array(
      'id' => 'field_expiration_date',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => '>=',
      'value' => 'now',
      'group' => 2,
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['filters']['field_expiration_date_1'] = array(
      'id' => 'field_expiration_date_1',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => 'empty',
      'group' => 2,
    ); /* WAS: '' */
  }
  if (isset($data['harmonization_datasets'])) {
    $data['harmonization_datasets']->display['default']->display_options['filters']['field_expiration_date'] = array(
      'id' => 'field_expiration_date',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => '>=',
      'value' => 'now',
      'group' => 2,
    ); /* WAS: '' */
    $data['harmonization_datasets']->display['default']->display_options['filters']['field_expiration_date_1'] = array(
      'id' => 'field_expiration_date_1',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => 'empty',
      'group' => 2,
    ); /* WAS: '' */
  }
  if (isset($data['study_datasets'])) {
    $data['study_datasets']->display['default']->display_options['filters']['field_expiration_date'] = array(
      'id' => 'field_expiration_date',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => '>=',
      'value' => 'now',
      'group' => 2,
    ); /* WAS: '' */
    $data['study_datasets']->display['default']->display_options['filters']['field_expiration_date_1'] = array(
      'id' => 'field_expiration_date_1',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_expiration_date',
      'operator' => 'not empty',
      'group' => 2,
    ); /* WAS: '' */
  }
}
