<?php
/**
 * @file
 * sesi_printer_friendly.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_printer_friendly_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.print_html_link_pos.value|corner"] = 'corner';
  $overrides["variable.print_html_show_link.value"] = 2;
  $overrides["variable.print_html_sys_link_visibility.value"] = 0;
  $overrides["variable.print_html_windowclose.value"] = 0;

 return $overrides;
}
