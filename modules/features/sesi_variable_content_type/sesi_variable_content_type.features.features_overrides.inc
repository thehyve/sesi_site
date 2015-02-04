<?php
/**
 * @file
 * sesi_variable_content_type.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_variable_content_type_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.variable_index.options|fields|field_validate_categories"] = array(
    'type' => 'boolean',
  );

 return $overrides;
}
