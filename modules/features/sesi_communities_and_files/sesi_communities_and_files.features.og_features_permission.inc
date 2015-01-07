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

  // Exported og permission: 'node:community:create study content'
  $permissions['node:community:create study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:create study_variable_attributes content'
  $permissions['node:community:create study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete any study content'
  $permissions['node:community:delete any study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete any study_variable_attributes content'
  $permissions['node:community:delete any study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete own study content'
  $permissions['node:community:delete own study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:delete own study_variable_attributes content'
  $permissions['node:community:delete own study_variable_attributes content'] = array(
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

  // Exported og permission: 'node:community:update any study content'
  $permissions['node:community:update any study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update any study_variable_attributes content'
  $permissions['node:community:update any study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update group'
  $permissions['node:community:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:update own study content'
  $permissions['node:community:update own study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:update own study_variable_attributes content'
  $permissions['node:community:update own study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create study content'
  $permissions['node:default_community:create study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:create study_variable_attributes content'
  $permissions['node:default_community:create study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any study content'
  $permissions['node:default_community:delete any study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete any study_variable_attributes content'
  $permissions['node:default_community:delete any study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own study content'
  $permissions['node:default_community:delete own study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:delete own study_variable_attributes content'
  $permissions['node:default_community:delete own study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any study content'
  $permissions['node:default_community:update any study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update any study_variable_attributes content'
  $permissions['node:default_community:update any study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own study content'
  $permissions['node:default_community:update own study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:update own study_variable_attributes content'
  $permissions['node:default_community:update own study_variable_attributes content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
