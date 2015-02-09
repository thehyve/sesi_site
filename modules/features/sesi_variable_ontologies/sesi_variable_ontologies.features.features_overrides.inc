<?php
/**
 * @file
 * sesi_variable_ontologies.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_variable_ontologies_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-variable-field_taxonomy.widget|weight"] = 109;

 return $overrides;
}
