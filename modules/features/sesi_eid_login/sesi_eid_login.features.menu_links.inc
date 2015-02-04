<?php
/**
 * @file
 * sesi_eid_login.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_eid_login_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/config/beididp
  $menu_links['management:admin/config/beididp'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/beididp',
    'router_path' => 'admin/config/beididp',
    'link_title' => 'Belgian eID IDP',
    'options' => array(
      'attributes' => array(
        'title' => 'Setting for the Belgian eID Identity Provider',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Belgian eID IDP');


  return $menu_links;
}
