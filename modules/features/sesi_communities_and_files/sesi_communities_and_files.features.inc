<?php
/**
 * @file
 * sesi_communities_and_files.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_communities_and_files_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function sesi_communities_and_files_node_info() {
  $items = array(
    'community' => array(
      'name' => t('Community'),
      'base' => 'node_content',
      'description' => t('CMI Community'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'community_document' => array(
      'name' => t('Community document'),
      'base' => 'node_content',
      'description' => t('CMI Community document'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
