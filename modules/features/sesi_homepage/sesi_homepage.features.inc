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
 * Implements hook_views_default_views_alter().
 */
function sesi_homepage_views_default_views_alter(&$data) {
  if (isset($data['news'])) {
    $data['news']->display['default']->display_options['filters']['type'] = array(
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'value' => array(
        'article' => 'article',
        'community_document' => 'community_document',
        'dataset' => 'dataset',
        'event' => 'event',
        'study' => 'study',
          'community' => 'community',
      ),
    ); /* WAS: '' */
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
