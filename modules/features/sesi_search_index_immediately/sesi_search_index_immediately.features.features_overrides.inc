<?php
/**
 * @file
 * sesi_search_index_immediately.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_search_index_immediately_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.dataset_index.options|index_directly"] = 1;
  $overrides["search_api_index.fields_description_index.options|index_directly"] = 1;
  $overrides["search_api_index.studies_index.options|index_directly"] = 1;
  $overrides["search_api_index.variable_index.options|index_directly"] = 1;

 return $overrides;
}
