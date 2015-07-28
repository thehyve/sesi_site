<?php
/**
 * @file
 * sesi_views_prefilter_access_restrictions.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_views_prefilter_access_restrictions_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.dataset_index.options|fields|og_group_ref"] = array(
    'type' => 'list<integer>',
    'entity_type' => 'node',
  );
  $overrides["search_api_index.fields_description_index.options|fields|og_group_ref"] = array(
    'type' => 'list<integer>',
    'entity_type' => 'node',
  );
  $overrides["search_api_index.studies_index.options|fields|og_group_ref"] = array(
    'type' => 'list<integer>',
    'entity_type' => 'node',
  );
  $overrides["search_api_index.variable_index.options|fields|og_group_ref"] = array(
    'type' => 'list<integer>',
    'entity_type' => 'node',
  );

 return $overrides;
}
