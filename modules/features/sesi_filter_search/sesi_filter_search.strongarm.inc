<?php
/**
 * @file
 * sesi_filter_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_filter_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'og_filter_search' => 'og_filter_search',
    'user' => 'user',
    'advanced_help' => 0,
    'ds_search' => 0,
    'node' => 0,
  );
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'og_filter_search';
  $export['search_default_module'] = $strongarm;

  return $export;
}
