<?php
/**
 * @file
 * sesi_easy_social.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sesi_easy_social_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer easy social'.
  $permissions['administer easy social'] = array(
    'name' => 'administer easy social',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'easy_social',
  );

  // Exported permission: 'use easy social wizard'.
  $permissions['use easy social wizard'] = array(
    'name' => 'use easy social wizard',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'easy_social',
  );

  return $permissions;
}
