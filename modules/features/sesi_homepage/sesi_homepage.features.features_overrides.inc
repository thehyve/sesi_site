<?php
/**
 * @file
 * sesi_homepage.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_homepage_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.news.display|default|display_options|filters|type"] = array(
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'value' => array(
      'article' => 'article',
      'community_document' => 'community_document',
      'dataset' => 'dataset',
      'event' => 'event',
      'study' => 'study',
        'community' => 'community',
    ),
  );

 return $overrides;
}
