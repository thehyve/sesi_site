<?php
/**
 * @file
 * sesi_homepage.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_homepage_default_fe_block_settings() {
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
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => -51,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
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
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => -50,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => -52,
      ),
      'seven' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-navigation'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'navigation',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => 2,
    ),
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
        'weight' => -39,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-news-recent_news'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'news-recent_news',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
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
        'weight' => -38,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
