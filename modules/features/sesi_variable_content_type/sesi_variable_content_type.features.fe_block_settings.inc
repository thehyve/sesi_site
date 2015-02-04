<?php
/**
 * @file
 * sesi_variable_content_type.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_variable_content_type_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['facetapi-1ICH2fsssLrKuMzDRkhCg6MzDn3uKJmS'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '1ICH2fsssLrKuMzDRkhCg6MzDn3uKJmS',
    'module' => 'facetapi',
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
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => 60,
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

  return $export;
}
