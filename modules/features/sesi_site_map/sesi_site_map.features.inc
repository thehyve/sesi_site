<?php
/**
 * @file
 * sesi_site_map.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_site_map_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
