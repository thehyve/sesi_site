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
  $overrides["menu_links.main-menu:node/4.parent_path"]["DELETED"] = TRUE;
  $overrides["menu_links.main-menu:node/4.weight"] = -40;

  // Exported overrides for: views_view
  $overrides["views_view.variable_search.display|page|display_options|access"] = array(
    'type' => 'role',
    'role' => array(
      3 => 3,
      2 => 2,
      4 => 4,
      7 => 7,
      9 => 9,
      10 => 10,
      8 => 8,
      5 => 5,
      6 => 6,
    ),
  );
  $overrides["views_view.variable_search.display|page|display_options|defaults|access"] = FALSE;

 return $overrides;
}
