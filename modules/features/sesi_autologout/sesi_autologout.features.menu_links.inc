<?php
/**
 * @file
 * sesi_autologout.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_autologout_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/config/people/autologout
  $menu_links['management:admin/config/people/autologout'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/people/autologout',
    'router_path' => 'admin/config/people/autologout',
    'link_title' => 'Auto Logout',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer Auto Logout settings.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config/people',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Auto Logout');


  return $menu_links;
}
