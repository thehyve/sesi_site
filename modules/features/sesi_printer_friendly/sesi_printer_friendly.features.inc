<?php
/**
 * @file
 * sesi_printer_friendly.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function sesi_printer_friendly_user_default_permissions_alter(&$data) {
  if (isset($data['access print'])) {
    $data['access print']['roles']['anonymous user'] = 'anonymous user'; /* WAS: '' */
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function sesi_printer_friendly_strongarm_alter(&$data) {
  if (isset($data['print_html_link_pos'])) {
    $data['print_html_link_pos']->value['corner'] = 'corner'; /* WAS: 0 */
  }
  if (isset($data['print_html_node_link_pages'])) {
    $data['print_html_node_link_pages']->value = '<front>'; /* WAS: '' */
  }
  if (isset($data['print_html_show_link'])) {
    $data['print_html_show_link']->value = 2; /* WAS: 1 */
  }
}
