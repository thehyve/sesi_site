<?php
/**
 * @file
 * sesi_inherit_variable_permissions.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_inherit_variable_permissions_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_group
  $overrides["field_group.group_dataset_inheritance|node|dataset|form.data|children|1"] = 'field_inherit_permissions';
  $overrides["field_group.group_dataset_inheritance|node|dataset|form.data|weight"] = 8;

 return $overrides;
}
