<?php
/**
 * @file
 * sesi_menu_links.features.inc
 */

/**
 * Implements hook_default_fe_block_settings_alter().
 */
function sesi_menu_links_default_fe_block_settings_alter(&$data) {
  if (isset($data['system-main-menu'])) {
    $data['system-main-menu']['title'] = '<none>'; /* WAS: '' */
  }
}

/**
 * Implements hook_menu_default_menu_links_alter().
 */
function sesi_menu_links_menu_default_menu_links_alter(&$data) {
  if (isset($data['main-menu:node/4'])) {
    $data['main-menu:node/4']['parent_path'] = 'node/4'; /* WAS: '' */
    $data['main-menu:node/4']['weight'] = -50; /* WAS: -40 */
  }
  if (isset($data['main-menu:sitemap'])) {
    $data['main-menu:sitemap']['weight'] = -49; /* WAS: 0 */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function sesi_menu_links_views_default_views_alter(&$data) {
  if (isset($data['variable_search'])) {
    $data['variable_search']->display['page']->display_options['access'] = array(
      'type' => 'role',
      'role' => array(
        3 => 3,
        2 => 2,
        4 => 4,
        7 => 7,
        9 => 9,
        10 => 10,
        8 => 8,
        5 => 5,
        6 => 6,
      ),
    ); /* WAS: '' */
    $data['variable_search']->display['page']->display_options['defaults']['access'] = FALSE; /* WAS: '' */
  }
}
