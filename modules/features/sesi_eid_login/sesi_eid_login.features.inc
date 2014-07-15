<?php
/**
 * @file
 * sesi_eid_login.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_eid_login_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
