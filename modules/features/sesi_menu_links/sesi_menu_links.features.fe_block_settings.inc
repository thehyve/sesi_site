<?php
/**
 * @file
 * sesi_menu_links.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_menu_links_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['system-user-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'user-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'administrator' => 3,
      'authenticated user' => 2,
      'consortium administrator' => 4,
      'data access committee officer' => 7,
      'dataset administrator' => 9,
      'dataset reviewer' => 10,
      'researcher' => 8,
      'study administrator' => 5,
      'study reviewer' => 6,
    ),
    'themes' => array(
      'mica_subtheme' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => 5,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  return $export;
}
