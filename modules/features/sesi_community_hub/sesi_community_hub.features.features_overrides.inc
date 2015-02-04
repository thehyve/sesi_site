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

 return $overrides;
}
