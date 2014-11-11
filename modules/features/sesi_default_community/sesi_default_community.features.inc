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
    $data['og_group_ref']['field_permissions'] = array(
      'type' => 0,
    ); /* WAS: '' */
    $data['og_group_ref']['settings']['field_description_infos'] = array(
      'field_description' => 0,
      'field_description_body' => '',
      'field_description_label' => '',
      'field_description_value_type' => 'text',
    ); /* WAS: '' */
    $data['og_group_ref']['settings']['handler_settings']['behaviors']['views-select-list'] = array(
      'status' => 0,
    ); /* WAS: '' */
    $data['og_group_ref']['settings']['handler_settings']['sort'] = array(
      'type' => 'none',
    ); /* WAS: '' */
    $data['og_group_ref']['settings']['handler_settings']['target_bundles']['community'] = 'community'; /* WAS: '' */
    $data['og_group_ref']['settings']['handler_settings']['target_bundles']['default_community'] = 'default_community'; /* WAS: '' */
    $data['og_group_ref']['settings']['profile2_private'] = FALSE; /* WAS: '' */
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
