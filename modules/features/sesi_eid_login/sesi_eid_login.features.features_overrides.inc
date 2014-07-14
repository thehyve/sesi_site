<?php
/**
 * @file
 * sesi_eid_login.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_eid_login_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.logintoboggan_confirm_email_at_registration.value"] = 1;

 return $overrides;
}
