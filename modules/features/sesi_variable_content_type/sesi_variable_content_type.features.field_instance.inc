<?php
/**
 * @file
 * sesi_variable_content_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_variable_content_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-variable-field_validate_categories'
  $field_instances['node-variable-field_validate_categories'] = array(
    'bundle' => 'variable',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '<br>Validate all the values against categories list',
    'display' => array(
      'banner_area' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 31,
      ),
      'footer_area' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'left_area' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'right_area' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'display_label' => 'Validate categories',
    'entity_type' => 'node',
    'field_name' => 'field_validate_categories',
    'label' => 'Validate categories',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 105,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<br>Validate all the values against categories list');
  t('Validate categories');

  return $field_instances;
}
