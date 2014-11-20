<?php
/**
 * @file
 * sesi_my_queries_screen.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_my_queries_screen_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-my_queries-block_1'] = array(
    'cache' => -1,
    'delta' => 'my_queries-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'mica_subtheme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'mica_subtheme',
        'weight' => 0,
      ),
    ),
  );

  return $export;
}
