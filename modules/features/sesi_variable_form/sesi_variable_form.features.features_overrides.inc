<?php
/**
 * @file
 * sesi_variable_form.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_variable_form_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-variable-field_dataset.widget|weight"] = 75;
  $overrides["field_instance.node-variable-field_repeatable.description"] = '<br>Can this variable have multiple values?';
  $overrides["field_instance.node-variable-field_repeatable.widget|weight"] = 75;
  $overrides["field_instance.node-variable-field_taxonomy.widget|weight"] = 75;
  $overrides["field_instance.node-variable-field_unit.widget|weight"] = 75;
  $overrides["field_instance.node-variable-field_vocabulary_url.widget|weight"] = 75;
  $overrides["field_instance.node-variable-og_group_ref.widget|weight"] = 80;

 return $overrides;
}
