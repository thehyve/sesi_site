<?php
/**
 * @file
 * sesi_default_community.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_default_community_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_bases_alter().		
 */		
function sesi_default_community_field_default_field_bases_alter(&$data) {		
  if (isset($data['og_group_ref'])) {		
    $data['og_group_ref']['field_permissions']['type'] = 2; /* WAS: 0 */		
  }		
}		


/**
 * Implements hook_node_info().
 */
function sesi_default_community_node_info() {
  $items = array(
    'default_community' => array(
      'name' => t('Default Community'),
      'base' => 'node_content',
      'description' => t('This organic group is a default organic group that collects all global content types (global datasets, news, events, documents) that are viewable to all Mica registered users. Registered users will be automatically subscribed to this organic group. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
