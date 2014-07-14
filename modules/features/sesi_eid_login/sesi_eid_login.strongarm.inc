<?php
/**
 * @file
 * sesi_eid_login.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_eid_login_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = '2';
  $export['user_register'] = $strongarm;

  return $export;
}
