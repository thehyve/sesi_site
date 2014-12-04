<?php
/**
 * @file
 * sesi_default_community.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function sesi_default_community_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:default_community:subscribe without approval'
  $permissions['node:default_community:subscribe without approval'] = array(
    'roles' => array(),
  );

  return $permissions;
}
