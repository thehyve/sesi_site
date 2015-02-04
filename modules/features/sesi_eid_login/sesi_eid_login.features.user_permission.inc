<?php
/**
 * @file
 * sesi_eid_login.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sesi_eid_login_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer beididp'.
  $permissions['administer beididp'] = array(
    'name' => 'administer beididp',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'beididp',
  );

  return $permissions;
}
