<?php
/**
 * @file
 * sesi_communities_and_files.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function sesi_communities_and_files_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:add user'
  $permissions['node:community:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:administer group'
  $permissions['node:community:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:approve and deny subscription'
  $permissions['node:community:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:create community_document content'
  $permissions['node:community:create community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:create dataset content'
  $permissions['node:community:create dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete any community_document content'
  $permissions['node:community:delete any community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete any dataset content'
  $permissions['node:community:delete any dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete own community_document content'
  $permissions['node:community:delete own community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete own dataset content'
  $permissions['node:community:delete own dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:manage members'
  $permissions['node:community:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:manage permissions'
  $permissions['node:community:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:manage roles'
  $permissions['node:community:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:subscribe'
  $permissions['node:community:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:community:subscribe without approval'
  $permissions['node:community:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:unsubscribe'
  $permissions['node:community:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any community_document content'
  $permissions['node:community:update any community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update any dataset content'
  $permissions['node:community:update any dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update group'
  $permissions['node:community:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:update own community_document content'
  $permissions['node:community:update own community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update own dataset content'
  $permissions['node:community:update own dataset content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
