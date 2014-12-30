<?php
/**
 * @file
 * sesi_menu_links.features.inc
 */

/**
 * Implements hook_menu_default_menu_links_alter().
 */
function sesi_menu_links_menu_default_menu_links_alter(&$data) {
  if (isset($data['main-menu:communities'])) {
    unset($data['main-menu:communities']);
  }
  if (isset($data['main-menu:datasets'])) {
    $data['main-menu:datasets']['weight'] = -49; /* WAS: -47 */
  }
  if (isset($data['main-menu:node/4'])) {
    $data['main-menu:node/4']['has_children'] = 0; /* WAS: 1 */
    $data['main-menu:node/4']['parent_path'] = 'node/4'; /* WAS: '' */
    $data['main-menu:node/4']['weight'] = -50; /* WAS: -40 */
  }
  if (isset($data['main-menu:sitemap'])) {
    $data['main-menu:sitemap']['weight'] = -49; /* WAS: 0 */
  }
  if (isset($data['main-menu:studies'])) {
    $data['main-menu:studies']['weight'] = -50; /* WAS: -49 */
  }
  if (isset($data['main-menu:variable-search'])) {
    $data['main-menu:variable-search']['weight'] = -48; /* WAS: -46 */
  }
}
