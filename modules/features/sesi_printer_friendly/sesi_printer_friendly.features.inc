<?php
/**
 * @file
 * sesi_printer_friendly.features.inc
 */

/**
 * Implements hook_strongarm_alter().
 */
function sesi_printer_friendly_strongarm_alter(&$data) {
  if (isset($data['print_html_link_pos'])) {
    $data['print_html_link_pos']->value['corner'] = 'corner'; /* WAS: 0 */
  }
  if (isset($data['print_html_show_link'])) {
    $data['print_html_show_link']->value = 2; /* WAS: 1 */
  }
  if (isset($data['print_html_sys_link_visibility'])) {
    $data['print_html_sys_link_visibility']->value = 0; /* WAS: 1 */
  }
  if (isset($data['print_html_windowclose'])) {
    $data['print_html_windowclose']->value = 0; /* WAS: 1 */
  }
}
