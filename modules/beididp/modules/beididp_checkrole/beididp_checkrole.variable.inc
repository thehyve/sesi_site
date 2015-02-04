<?php

/**
 * @file
 * Variable API module. Definition for variables.
 */

/**
 * Implements hook_variable_info().
 */
function beididp_checkrole_variable_info($options) {
  $variables['beididp_required_role'] = array(
    'type' => 'options',
    'title' => t('Roles that require eID authentication'),
    'default' => array(),
    'options callback' => '_beididp_checkrole_user_roles_options', 
    'description' => t('Check roles that require eID authentication. Users within these roles will only be able to log in using their eID.'),
    'group' => 'beididp',
    'localize' => FALSE,
  );
  return $variables;
}

/**
 * Callback for roles.
 */
function _beididp_checkrole_user_roles_options($variable, $options) {
  return user_roles(TRUE);
}
