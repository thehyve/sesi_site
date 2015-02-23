<?php
/**
 * @file
 * sesi_contacts_configuration.features.inc
 */

/**
 * Implements hook_field_default_field_bases_alter().
 */
function sesi_contacts_configuration_field_default_field_bases_alter(&$data) {
  if (isset($data['field_daco'])) {
    $data['field_daco']['field_permissions']['type'] = 2; /* WAS: 0 */
    $data['field_daco']['settings']['field_description_infos']['field_description_label'] = ''; /* WAS: '' */
    $data['field_daco']['settings']['field_description_infos']['field_description_value_type'] = 'boolean'; /* WAS: '' */
    $data['field_daco']['settings']['profile2_private'] = FALSE; /* WAS: '' */
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_contacts_configuration_field_default_field_instances_alter(&$data) {
  if (isset($data['node-contact-field_daco'])) {
    $data['node-contact-field_daco']['display_label'] = ''; /* WAS: '' */
  }
}
