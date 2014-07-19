<?php
/**
 * @file
 * sesi_user_registration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_user_registration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
