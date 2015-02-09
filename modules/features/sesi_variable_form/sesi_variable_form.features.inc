<?php
/**
 * @file
 * sesi_variable_form.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_variable_form_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_variable_form_field_default_field_instances_alter(&$data) {
  if (isset($data['node-variable-field_dataset'])) {
    $data['node-variable-field_dataset']['widget']['weight'] = 110; /* WAS: 2 */
  }
  if (isset($data['node-variable-field_repeatable'])) {
    $data['node-variable-field_repeatable']['description'] = '<br>Can this variable have multiple values?'; /* WAS: 'Can this variable have multiple values?' */
    $data['node-variable-field_repeatable']['widget']['weight'] = 107; /* WAS: 1 */
  }
  if (isset($data['node-variable-field_unit'])) {
    $data['node-variable-field_unit']['widget']['weight'] = 108; /* WAS: 0 */
  }
  if (isset($data['node-variable-og_group_ref'])) {
    $data['node-variable-og_group_ref']['widget']['weight'] = 80; /* WAS: 63 */
  }
}
