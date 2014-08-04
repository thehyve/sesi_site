<?php
/**
 * @file
 * sesi_dataset_inheritance.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function sesi_dataset_inheritance_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_dataset_parent'
  $field_bases['field_dataset_parent'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dataset_parent',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'profile2_private' => FALSE,
      'referenceable_types' => array(
        'article' => 0,
        'blog' => 0,
        'contact' => 0,
        'data_access_request' => 0,
        'data_access_review' => 0,
        'data_collection_event' => 0,
        'dataset' => 'dataset',
        'documents' => 0,
        'event' => 0,
        'field_description' => 0,
        'forum' => 0,
        'page' => 0,
        'panel' => 0,
        'population' => 0,
        'project' => 0,
        'publication' => 0,
        'study' => 0,
        'study_variable_attributes' => 0,
        'teleconference' => 0,
        'variable' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
    ),
    'translatable' => 0,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_variable_inherited_flag'
  $field_bases['field_variable_inherited_flag'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_variable_inherited_flag',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
      'field_description_infos' => array(
        'field_description' => 0,
        'field_description_body' => '',
        'field_description_label' => '',
        'field_description_value_type' => 'boolean',
      ),
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
