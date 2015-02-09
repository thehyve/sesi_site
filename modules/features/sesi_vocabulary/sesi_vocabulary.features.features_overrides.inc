<?php
/**
 * @file
 * sesi_vocabulary.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_vocabulary_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-variable-field_vocabulary_url.widget|weight"] = 106;

 return $overrides;
}
