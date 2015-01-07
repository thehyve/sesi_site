<?php
/**
 * @file
 * sesi_default_community.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_default_community_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.og_group_ref.field_permissions|type"] = 0;

 return $overrides;
}
