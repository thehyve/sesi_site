<?php
/**
 * @file
 * sesi_variable_ontologies.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_variable_ontologies_field_default_field_instances_alter(&$data) {
  if (isset($data['node-variable-field_taxonomy'])) {
    $data['node-variable-field_taxonomy']['widget']['weight'] = 109; /* WAS: 64 */
  }
}
