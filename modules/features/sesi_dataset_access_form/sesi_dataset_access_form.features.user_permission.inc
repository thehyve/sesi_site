<?php
/**
 * @file
 * sesi_dataset_access_form.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sesi_dataset_access_form_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer previewable email templates'.
  $permissions['administer previewable email templates'] = array(
    'name' => 'administer previewable email templates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pet',
  );

  // Exported permission: 'use previewable email templates'.
  $permissions['use previewable email templates'] = array(
    'name' => 'use previewable email templates',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'pet',
  );

  return $permissions;
}
