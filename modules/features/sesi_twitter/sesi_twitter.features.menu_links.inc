<?php
/**
 * @file
 * sesi_twitter.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_twitter_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/config/services/twitter
  $menu_links['management:admin/config/services/twitter'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/services/twitter',
    'router_path' => 'admin/config/services/twitter',
    'link_title' => 'Twitter',
    'options' => array(
      'attributes' => array(
        'title' => 'Twitter accounts and settings.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config/services',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Twitter');


  return $menu_links;
}
