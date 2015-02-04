<?php
/**
 * @file
 * sesi_dataset_versioning.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function sesi_dataset_versioning_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_dataset_version'
  $field_bases['field_dataset_version'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dataset_version',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'field_description_infos' => array(
        'field_description' => 0,
        'field_description_body' => '',
        'field_description_label' => '',
        'field_description_value_type' => 'integer',
      ),
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  return $field_bases;
}
