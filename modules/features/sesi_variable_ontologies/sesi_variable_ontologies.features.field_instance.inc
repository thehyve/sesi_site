<?php
/**
 * @file
 * sesi_variable_ontologies.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_variable_ontologies_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-variable-field_taxonomy'
  $field_instances['node-variable-field_taxonomy'] = array(
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
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 30,
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
    'entity_type' => 'node',
    'field_name' => 'field_taxonomy',
    'label' => 'Taxonomy',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 109,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Taxonomy');

  return $field_instances;
}
