<?php
/**
 * @file
 * sesi_site_map.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_site_map_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:sitemap
  $menu_links['main-menu:sitemap'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site Map',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'node/4',
  );
  // Exported menu link: management:admin/config/search/sitemap
  $menu_links['management:admin/config/search/sitemap'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/search/sitemap',
    'router_path' => 'admin/config/search/sitemap',
    'link_title' => 'Site map',
    'options' => array(
      'attributes' => array(
        'title' => 'Control what should be displayed on the site map.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config/search',
  );
  // Exported menu link: management:admin/config/system/site-information
  $menu_links['management:admin/config/system/site-information'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/site-information',
    'router_path' => 'admin/config/system/site-information',
    'link_title' => 'Site information',
    'options' => array(
      'attributes' => array(
        'title' => 'Change site name, e-mail address, slogan, default front page, and number of posts per page, error pages.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -20,
    'parent_path' => 'admin/config/system',
  );
  // Exported menu link: navigation:sitemap
  $menu_links['navigation:sitemap'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site map',
    'options' => array(
      'attributes' => array(
        'title' => 'Display a site map with RSS feeds.',
      ),
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site Map');
  t('Site information');
  t('Site map');


  return $menu_links;
}
