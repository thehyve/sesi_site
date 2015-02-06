<?php
/**
 * @file
 * sesi_vocabulary.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_vocabulary_field_default_field_instances_alter(&$data) {
  if (isset($data['node-variable-field_vocabulary_url'])) {
    $data['node-variable-field_vocabulary_url']['widget']['weight'] = 106; /* WAS: 62 */
  }
}
