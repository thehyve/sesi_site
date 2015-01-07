<?php
/**
 * @file
 * sesi_community_hub.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_community_hub_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-article-og_group_ref.settings|behaviors|prepopulate"] = array(
    'status' => 0,
  );
  $overrides["field_instance.node-community_document-og_group_ref.settings|behaviors|prepopulate"] = array(
    'action' => 'none',
    'action_on_edit' => 0,
    'fallback' => 'none',
    'providers' => array(
      'og_context' => 0,
      'token_patterns' => 0,
      'url' => 1,
    ),
    'skip_perm' => 0,
    'status' => 1,
    'token_patterns' => '',
  );
  $overrides["field_instance.node-dataset-og_group_ref.settings|behaviors|prepopulate"] = array(
    'action' => 'none',
    'action_on_edit' => 0,
    'fallback' => 'none',
    'providers' => array(
      'og_context' => 0,
      'token_patterns' => 0,
      'url' => 1,
    ),
    'skip_perm' => 0,
    'status' => 1,
    'token_patterns' => '',
  );

 return $overrides;
}
