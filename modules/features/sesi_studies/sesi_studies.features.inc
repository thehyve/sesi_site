<?php
/**
 * @file
 * sesi_studies.features.inc
 */

/**
 * Implements hook_strongarm_alter().
 */
function sesi_studies_strongarm_alter(&$data) {
  if (isset($data['content_access_study'])) {
    $data['content_access_study']->value['priority'] = -1; /* WAS: '' */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function sesi_studies_views_default_views_alter(&$data) {
  if (isset($data['studies_search'])) {
    $data['studies_search']->display['default']->display_options['query']['options']['search_api_bypass_access'] = 1; /* WAS: '' */
  }
}
