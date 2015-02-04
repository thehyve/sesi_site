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
 * Implements hook_og_features_default_permissions_alter().
 */
function sesi_default_community_og_features_default_permissions_alter(&$data) {
  if (isset($data['node:default_community:create community_document content'])) {
    unset($data['node:default_community:create community_document content']['roles']['member']);
  }
  if (isset($data['node:default_community:delete any variable content'])) {
    unset($data['node:default_community:delete any variable content']['roles']['member']);
  }
  if (isset($data['node:default_community:delete own community_document content'])) {
    unset($data['node:default_community:delete own community_document content']['roles']['member']);
  }
  if (isset($data['node:default_community:delete own dataset content'])) {
    unset($data['node:default_community:delete own dataset content']['roles']['member']);
  }
  if (isset($data['node:default_community:delete own event content'])) {
    unset($data['node:default_community:delete own event content']['roles']['member']);
  }
  if (isset($data['node:default_community:delete own variable content'])) {
    unset($data['node:default_community:delete own variable content']['roles']['member']);
  }
  if (isset($data['node:default_community:update own community_document content'])) {
    unset($data['node:default_community:update own community_document content']['roles']['member']);
  }
  if (isset($data['node:default_community:update own dataset content'])) {
    unset($data['node:default_community:update own dataset content']['roles']['member']);
  }
  if (isset($data['node:default_community:update own event content'])) {
    unset($data['node:default_community:update own event content']['roles']['member']);
  }
  if (isset($data['node:default_community:update own variable content'])) {
    unset($data['node:default_community:update own variable content']['roles']['member']);
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
