<?php
/**
 * @file
 * sesi_studies.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_studies_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.content_access_study.value|priority"] = -1;

  // Exported overrides for: views_view
  $overrides["views_view.studies_search.display|default|display_options|query|options|search_api_bypass_access"] = 1;

 return $overrides;
}
