<?php
/**
 * @file
 * sesi_my_queries_screen.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_my_queries_screen_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu:my-queries
  $menu_links['user-menu:my-queries'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'my-queries',
    'router_path' => 'my-queries',
    'link_title' => 'My queries',
    'options' => array(
      'attributes' => array(
        'title' => 'Show all your queries',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My queries');


  return $menu_links;
}
