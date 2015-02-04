<?php
/**
 * @file
 * sesi_user_profile_fields.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_user_profile_fields_field_default_field_instances_alter(&$data) {
  if (isset($data['profile2-main-field_profile_first_name'])) {
    $data['profile2-main-field_profile_first_name']['widget']['weight'] = 2; /* WAS: 1 */
  }
  if (isset($data['profile2-main-field_profile_last_name'])) {
    $data['profile2-main-field_profile_last_name']['widget']['weight'] = 3; /* WAS: 2 */
  }
}
