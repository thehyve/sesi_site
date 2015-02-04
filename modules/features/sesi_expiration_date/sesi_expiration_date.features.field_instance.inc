<?php
/**
 * @file
 * sesi_expiration_date.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_expiration_date_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-dataset-field_expiration_date'
  $field_instances['node-dataset-field_expiration_date'] = array(
    'bundle' => 'dataset',
    'deleted' => 0,
    'description' => 'Date until when this dataset can be used',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'display_label' => 'Expiration date',
    'entity_type' => 'node',
    'field_name' => 'field_expiration_date',
    'label' => 'Expiration date',
    'required' => 0,
    'settings' => array(
      'default_value' => '',
      'default_value2' => '',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 11,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Date until when this dataset can be used');
  t('Expiration date');

  return $field_instances;
}
