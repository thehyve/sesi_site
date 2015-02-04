<?php
/**
 * @file
 * sesi_moderation.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function sesi_moderation_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:access authoring options of article content'
  $permissions['node:community:access authoring options of article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of community_document content'
  $permissions['node:community:access authoring options of community_document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of data_access_request_form content'
  $permissions['node:community:access authoring options of data_access_request_form content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of dataset content'
  $permissions['node:community:access authoring options of dataset content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of event content'
  $permissions['node:community:access authoring options of event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of study content'
  $permissions['node:community:access authoring options of study content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of study_variable_attributes content'
  $permissions['node:community:access authoring options of study_variable_attributes content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access authoring options of variable content'
  $permissions['node:community:access authoring options of variable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of article content'
  $permissions['node:community:access publishing options of article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of community_document content'
  $permissions['node:community:access publishing options of community_document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of data_access_request_form content'
  $permissions['node:community:access publishing options of data_access_request_form content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of dataset content'
  $permissions['node:community:access publishing options of dataset content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of event content'
  $permissions['node:community:access publishing options of event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of study content'
  $permissions['node:community:access publishing options of study content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of study_variable_attributes content'
  $permissions['node:community:access publishing options of study_variable_attributes content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access publishing options of variable content'
  $permissions['node:community:access publishing options of variable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of article content'
  $permissions['node:community:access revisions options of article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of community_document content'
  $permissions['node:community:access revisions options of community_document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of data_access_request_form content'
  $permissions['node:community:access revisions options of data_access_request_form content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of dataset content'
  $permissions['node:community:access revisions options of dataset content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of event content'
  $permissions['node:community:access revisions options of event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of study content'
  $permissions['node:community:access revisions options of study content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of study_variable_attributes content'
  $permissions['node:community:access revisions options of study_variable_attributes content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:access revisions options of variable content'
  $permissions['node:community:access revisions options of variable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished article content'
  $permissions['node:community:view any unpublished article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished community_document content'
  $permissions['node:community:view any unpublished community_document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished data_access_request_form content'
  $permissions['node:community:view any unpublished data_access_request_form content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished dataset content'
  $permissions['node:community:view any unpublished dataset content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished event content'
  $permissions['node:community:view any unpublished event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished study content'
  $permissions['node:community:view any unpublished study content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished study_variable_attributes content'
  $permissions['node:community:view any unpublished study_variable_attributes content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:community:view any unpublished variable content'
  $permissions['node:community:view any unpublished variable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:default_community:access authoring options of article content'
  $permissions['node:default_community:access authoring options of article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of community_document content'
  $permissions['node:default_community:access authoring options of community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of data_access_request_form content'
  $permissions['node:default_community:access authoring options of data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of dataset content'
  $permissions['node:default_community:access authoring options of dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of event content'
  $permissions['node:default_community:access authoring options of event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of study content'
  $permissions['node:default_community:access authoring options of study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of study_variable_attributes content'
  $permissions['node:default_community:access authoring options of study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access authoring options of variable content'
  $permissions['node:default_community:access authoring options of variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of article content'
  $permissions['node:default_community:access publishing options of article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of community_document content'
  $permissions['node:default_community:access publishing options of community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of data_access_request_form content'
  $permissions['node:default_community:access publishing options of data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of dataset content'
  $permissions['node:default_community:access publishing options of dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of event content'
  $permissions['node:default_community:access publishing options of event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of study content'
  $permissions['node:default_community:access publishing options of study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of study_variable_attributes content'
  $permissions['node:default_community:access publishing options of study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access publishing options of variable content'
  $permissions['node:default_community:access publishing options of variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of article content'
  $permissions['node:default_community:access revisions options of article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of community_document content'
  $permissions['node:default_community:access revisions options of community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of data_access_request_form content'
  $permissions['node:default_community:access revisions options of data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of dataset content'
  $permissions['node:default_community:access revisions options of dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of event content'
  $permissions['node:default_community:access revisions options of event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of study content'
  $permissions['node:default_community:access revisions options of study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of study_variable_attributes content'
  $permissions['node:default_community:access revisions options of study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:access revisions options of variable content'
  $permissions['node:default_community:access revisions options of variable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished article content'
  $permissions['node:default_community:view any unpublished article content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished community_document content'
  $permissions['node:default_community:view any unpublished community_document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished data_access_request_form content'
  $permissions['node:default_community:view any unpublished data_access_request_form content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished dataset content'
  $permissions['node:default_community:view any unpublished dataset content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished event content'
  $permissions['node:default_community:view any unpublished event content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished study content'
  $permissions['node:default_community:view any unpublished study content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished study_variable_attributes content'
  $permissions['node:default_community:view any unpublished study_variable_attributes content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:default_community:view any unpublished variable content'
  $permissions['node:default_community:view any unpublished variable content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
