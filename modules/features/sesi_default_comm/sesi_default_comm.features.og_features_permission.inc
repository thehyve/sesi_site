<?php
/**
 * @file
 * sesi_default_comm.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function sesi_default_comm_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create community_document content'
  $permissions['node:community:create community_document content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
