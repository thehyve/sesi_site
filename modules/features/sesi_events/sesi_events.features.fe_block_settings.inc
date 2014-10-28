<?php
/**
 * @file
 * sesi_events.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_events_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['panels_mini-sesi_homepage_registered'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'sesi_homepage_registered',
    'module' => 'panels_mini',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'mica_subtheme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => -43,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['panels_mini-sesi_homepage_unregistered'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'sesi_homepage_unregistered',
    'module' => 'panels_mini',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'anonymous user' => 1,
    ),
    'themes' => array(
      'mica_subtheme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => -44,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
