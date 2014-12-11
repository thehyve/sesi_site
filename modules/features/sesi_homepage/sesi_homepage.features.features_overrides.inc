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

  // Exported overrides for: variable
  $overrides["variable.uuid_features_entity_node.value|page"] = 'page';

 return $overrides;
}
