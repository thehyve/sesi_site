<?php
/**
 * @file
 * sesi_homepage.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_homepage_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sesi_homepage_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_strongarm_alter().
 */
function sesi_homepage_strongarm_alter(&$data) {
  if (isset($data['uuid_features_entity_node'])) {
    $data['uuid_features_entity_node']->value['page'] = 'page'; /* WAS: 0 */
  }
}

/**
 * Implements hook_node_info().
 */
function sesi_homepage_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
