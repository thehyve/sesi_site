<?php
/**
 * @file
 * sesi_community_hub.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sesi_community_hub_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['sesi_og_addcontent-ogaddcontent'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'ogaddcontent',
    'module' => 'sesi_og_addcontent',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 1,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'mica_subtheme' => array(
        'region' => '',
        'status' => 1,
        'theme' => 'mica_subtheme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
