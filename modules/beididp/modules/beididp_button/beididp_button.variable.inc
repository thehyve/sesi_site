<?php
/**
 * @file
 * Variable API module. Definition for variables.
 */

/**
 * Implements hook_variable_info().
 */
function beididp_button_variable_info($options) {
  $variables['beididp_button_hide_up_fields'] = array(
    'type' => 'boolean',
    'title' => t('Hide username and password fields'),
    'default' => FALSE,
    'description' => t('Hide username and password fields of login forms.'),
    'group' => 'beididp',
    'localize' => FALSE,
  );
  return $variables;
}
