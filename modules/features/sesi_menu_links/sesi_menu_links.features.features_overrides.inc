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
  $overrides["menu_links.main-menu:communities.main-menu:communities"]["DELETED"] = TRUE;
  $overrides["menu_links.main-menu:datasets.weight"] = -49;
  $overrides["menu_links.main-menu:node/4.has_children"] = 0;
  $overrides["menu_links.main-menu:node/4.parent_path"] = 'node/4';
  $overrides["menu_links.main-menu:node/4.weight"] = -50;
  $overrides["menu_links.main-menu:sitemap.weight"] = -49;
  $overrides["menu_links.main-menu:studies.weight"] = -50;
  $overrides["menu_links.main-menu:variable-search.weight"] = -48;

 return $overrides;
}
