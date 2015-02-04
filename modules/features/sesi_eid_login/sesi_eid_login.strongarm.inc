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
  $strongarm->name = 'beididp_hash_claimed_id';
  $strongarm->value = 1;
  $export['beididp_hash_claimed_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'beididp_https_required';
  $strongarm->value = 0;
  $export['beididp_https_required'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'beididp_idp_url';
  $strongarm->value = 'https://eidfake.be:18443/eid-idp/endpoints/openid/auth-ident';
  $export['beididp_idp_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'beididp_no_mail_verify';
  $strongarm->value = 1;
  $export['beididp_no_mail_verify'] = $strongarm;

  return $export;
}
