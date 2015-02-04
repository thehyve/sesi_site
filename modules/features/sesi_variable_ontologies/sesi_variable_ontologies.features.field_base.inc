<?php
/**
 * @file
 * sesi_variable_ontologies.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function sesi_variable_ontologies_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_taxonomy'
  $field_bases['field_taxonomy'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_taxonomy',
    'foreign keys' => array(
      'taxonomy_vocabulary' => array(
        'columns' => array(
          'target_id' => 'vid',
        ),
        'table' => 'taxonomy_vocabulary',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'property' => 'name',
          'type' => 'property',
        ),
        'target_bundles' => array(),
      ),
      'target_type' => 'taxonomy_vocabulary',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
