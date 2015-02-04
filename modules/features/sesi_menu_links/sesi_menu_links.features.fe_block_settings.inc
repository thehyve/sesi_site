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

  $export['mica_bootstrap_config-bootstrap-login'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'bootstrap-login',
    'module' => 'mica_bootstrap_config',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'mica_subtheme',
        'weight' => 10,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-main-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

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
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => 5,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  return $export;
}
