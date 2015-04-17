<?php
/**
 * @file
 * sesi_variable_search_wildcards.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_variable_search_wildcards_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.variable_index.options|processors|search_api_case_ignore|weight"] = 0;
  $overrides["search_api_index.variable_index.options|processors|search_api_html_filter|weight"] = 10;
  $overrides["search_api_index.variable_index.options|processors|search_api_tokenizer|settings|spaces"] = '[^\\p{L}\\p{N}?*^\']';
  $overrides["search_api_index.variable_index.options|processors|search_api_tokenizer|weight"] = 20;
  $overrides["search_api_index.variable_index.options|processors|sesi_wildcard"] = array(
    'status' => 1,
    'weight' => 50,
    'settings' => array(),
  );

  // Exported overrides for: views_view
  $overrides["views_view.variable_search.display|default|display_options|filters|search_api_views_fulltext|expose|description"] = 'use * and ? wildcards to search for partial words';

 return $overrides;
}
