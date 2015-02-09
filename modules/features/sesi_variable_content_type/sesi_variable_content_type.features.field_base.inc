<?php
/**
 * @file
 * sesi_variable_content_type.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function sesi_variable_content_type_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_validate_categories'
  $field_bases['field_validate_categories'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_validate_categories',
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
        0 => 'No',
        1 => 'Yes',
      ),
      'allowed_values_function' => '',
      'field_description_infos' => array(
        'field_description' => 0,
        'field_description_body' => 'Validate categories',
        'field_description_label' => 'Validate categories',
        'field_description_value_type' => 'boolean',
      ),
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
