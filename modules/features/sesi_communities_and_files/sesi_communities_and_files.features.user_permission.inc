<?php
/**
 * @file
 * sesi_communities_and_files.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sesi_communities_and_files_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'og',
  );

  // Exported permission: 'create community content'.
  $permissions['create community content'] = array(
    'name' => 'create community content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create community_document content'.
  $permissions['create community_document content'] = array(
    'name' => 'create community_document content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any community content'.
  $permissions['delete any community content'] = array(
    'name' => 'delete any community content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any community_document content'.
  $permissions['delete any community_document content'] = array(
    'name' => 'delete any community_document content',
    'roles' => array(
      'administrator' => 'administrator',
      'consortium administrator' => 'consortium administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own community content'.
  $permissions['delete own community content'] = array(
    'name' => 'delete own community content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own community_document content'.
  $permissions['delete own community_document content'] = array(
    'name' => 'delete own community_document content',
    'roles' => array(
      'administrator' => 'administrator',
      'consortium administrator' => 'consortium administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any community content'.
  $permissions['edit any community content'] = array(
    'name' => 'edit any community content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any community_document content'.
  $permissions['edit any community_document content'] = array(
    'name' => 'edit any community_document content',
    'roles' => array(
      'administrator' => 'administrator',
      'consortium administrator' => 'consortium administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own community content'.
  $permissions['edit own community content'] = array(
    'name' => 'edit own community content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own community_document content'.
  $permissions['edit own community_document content'] = array(
    'name' => 'edit own community_document content',
    'roles' => array(
      'administrator' => 'administrator',
      'consortium administrator' => 'consortium administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view any unpublished community content'.
  $permissions['view any unpublished community content'] = array(
    'name' => 'view any unpublished community content',
    'roles' => array(),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished community_document content'.
  $permissions['view any unpublished community_document content'] = array(
    'name' => 'view any unpublished community_document content',
    'roles' => array(),
    'module' => 'view_unpublished',
  );

  return $permissions;
}
