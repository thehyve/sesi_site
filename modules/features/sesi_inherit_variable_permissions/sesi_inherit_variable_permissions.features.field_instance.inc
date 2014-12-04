<?php
/**
 * @file
 * sesi_inherit_variable_permissions.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_inherit_variable_permissions_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-dataset-field_inherit_permissions'
  $field_instances['node-dataset-field_inherit_permissions'] = array(
    'bundle' => 'dataset',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'display_label' => 'Inherit permissions',
    'entity_type' => 'node',
    'field_name' => 'field_inherit_permissions',
    'label' => 'Inherit permissions',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 9,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Inherit permissions');

  return $field_instances;
}
