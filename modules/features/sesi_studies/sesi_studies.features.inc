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
