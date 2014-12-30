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
 * Implements hook_views_api().
 */
function sesi_communities_and_files_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_communities_and_files_field_default_field_instances_alter(&$data) {
  if (isset($data['og_membership-og_membership_type_default-field_mail_sent'])) {
    $data['og_membership-og_membership_type_default-field_mail_sent']['required'] = 0; /* WAS: 1 */
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function sesi_communities_and_files_strongarm_alter(&$data) {
  if (isset($data['content_access_dataset'])) {
    $data['content_access_dataset']->value['priority'] = -1; /* WAS: '' */
  }
  if (isset($data['content_access_variable'])) {
    $data['content_access_variable']->value['priority'] = -1; /* WAS: '' */
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
