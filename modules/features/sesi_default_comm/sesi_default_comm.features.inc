<?php
/**
 * @file
 * sesi_default_comm.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_default_comm_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
