<?php
/**
 * @file
 * sesi_filter_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_filter_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
