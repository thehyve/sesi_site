<?php
/**
 * @file
 * sesi_vocabulary.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_vocabulary_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-variable-field_vocabulary_url'
  $field_instances['node-variable-field_vocabulary_url'] = array(
    'bundle' => 'variable',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'banner_area' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 28,
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
    'display_label' => '',
    'entity_type' => 'node',
    'field_name' => 'field_vocabulary_url',
    'label' => 'Vocabulary URL',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 106,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Vocabulary URL');

  return $field_instances;
}
