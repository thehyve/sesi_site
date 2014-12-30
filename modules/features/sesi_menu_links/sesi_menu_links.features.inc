<?php
/**
 * @file
 * sesi_menu_links.features.inc
 */

/**
 * Implements hook_menu_default_menu_links_alter().
 */
function sesi_menu_links_menu_default_menu_links_alter(&$data) {
  if (isset($data['main-menu:sitemap'])) {
    $data['main-menu:sitemap']['weight'] = -49; /* WAS: 0 */
  }
}
