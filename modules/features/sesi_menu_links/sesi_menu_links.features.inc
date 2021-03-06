<?php
/**
 * @file
 * sesi_menu_links.features.inc
 */

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
