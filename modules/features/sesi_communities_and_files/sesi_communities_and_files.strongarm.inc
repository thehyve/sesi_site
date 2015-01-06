<?php
/**
 * @file
 * sesi_communities_and_files.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_communities_and_files_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_article';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_community_document';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_community_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_event';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__community';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__community'] = $strongarm;

  return $export;
}
