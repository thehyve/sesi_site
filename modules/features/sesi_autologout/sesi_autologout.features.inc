<?php
/**
 * @file
 * sesi_autologout.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_autologout_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
