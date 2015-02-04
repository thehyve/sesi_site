<?php
/**
 * @file
 * sesi_user_profile_fields.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_user_profile_fields_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.profile2-main-field_profile_first_name.widget|weight"] = 2;
  $overrides["field_instance.profile2-main-field_profile_last_name.widget|weight"] = 3;

 return $overrides;
}
