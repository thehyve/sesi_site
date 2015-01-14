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

  // Exported og permission: 'node:default_community:add user'
  $permissions['node:default_community:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:administer group'
  $permissions['node:default_community:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:approve and deny subscription'
  $permissions['node:default_community:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:create article content'
  $permissions['node:default_community:create article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create community_document content'
  $permissions['node:default_community:create community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create data_access_request_form content'
  $permissions['node:default_community:create data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create dataset content'
  $permissions['node:default_community:create dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create event content'
  $permissions['node:default_community:create event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create variable content'
  $permissions['node:default_community:create variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any article content'
  $permissions['node:default_community:delete any article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any community_document content'
  $permissions['node:default_community:delete any community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any data_access_request_form content'
  $permissions['node:default_community:delete any data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any dataset content'
  $permissions['node:default_community:delete any dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any event content'
  $permissions['node:default_community:delete any event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any variable content'
  $permissions['node:default_community:delete any variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own article content'
  $permissions['node:default_community:delete own article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own community_document content'
  $permissions['node:default_community:delete own community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own data_access_request_form content'
  $permissions['node:default_community:delete own data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own dataset content'
  $permissions['node:default_community:delete own dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own event content'
  $permissions['node:default_community:delete own event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own variable content'
  $permissions['node:default_community:delete own variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:email people'
  $permissions['node:default_community:email people'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:manage members'
  $permissions['node:default_community:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:manage permissions'
  $permissions['node:default_community:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:manage roles'
  $permissions['node:default_community:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:subscribe'
  $permissions['node:default_community:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:default_community:subscribe without approval'
  $permissions['node:default_community:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:unsubscribe'
  $permissions['node:default_community:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:default_community:update any article content'
  $permissions['node:default_community:update any article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any community_document content'
  $permissions['node:default_community:update any community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any data_access_request_form content'
  $permissions['node:default_community:update any data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any dataset content'
  $permissions['node:default_community:update any dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any event content'
  $permissions['node:default_community:update any event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any variable content'
  $permissions['node:default_community:update any variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update group'
  $permissions['node:default_community:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:update own article content'
  $permissions['node:default_community:update own article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own community_document content'
  $permissions['node:default_community:update own community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own data_access_request_form content'
  $permissions['node:default_community:update own data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own dataset content'
  $permissions['node:default_community:update own dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own event content'
  $permissions['node:default_community:update own event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own variable content'
  $permissions['node:default_community:update own variable content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
