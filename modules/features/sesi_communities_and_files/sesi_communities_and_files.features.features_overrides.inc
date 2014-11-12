<?php
/**
 * @file
 * sesi_communities_and_files.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_communities_and_files_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.content_access_dataset.value|priority"] = -1;
  $overrides["variable.content_access_variable.value|priority"] = -1;

 return $overrides;
}
