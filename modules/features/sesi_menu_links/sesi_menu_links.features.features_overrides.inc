<?php
/**
 * @file
 * sesi_menu_links.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_menu_links_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: menu_links
  $overrides["menu_links.main-menu:sitemap.weight"] = -49;

 return $overrides;
}
