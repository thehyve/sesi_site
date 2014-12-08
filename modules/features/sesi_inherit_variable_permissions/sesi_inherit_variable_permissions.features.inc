<?php
/**
 * @file
 * sesi_inherit_variable_permissions.features.inc
 */

/**
 * Implements hook_field_group_info_alter().
 */
function sesi_inherit_variable_permissions_field_group_info_alter(&$data) {
  if (isset($data['group_dataset_inheritance|node|dataset|form'])) {
    $data['group_dataset_inheritance|node|dataset|form']->data['children']['1'] = 'field_inherit_permissions'; /* WAS: '' */
    $data['group_dataset_inheritance|node|dataset|form']->data['weight'] = 8; /* WAS: 9 */
  }
}
