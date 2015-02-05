<?php
/**
 * @file
 * Variable API module. Definition for variables.
 */

/**
 * Implements hook_variable_info().
 */
function beididp_variable_info($options) {
  $variables['beididp_idp_url'] = array(
    'type' => 'url',
    'title' => t('eID IDP endpoint'),
    'default' => 'https://www.e-contract.be/eid-idp/endpoints/openid/auth-ident',
    'description' => t('The HTTPS URL to the OpenID endpoint of the Belgian eID Identity Provider.'),
    'group' => 'beididp', 
    'validate callback' => 'beididp_idp_url_validate',
    'localize' => FALSE,
  );
  $variables['beididp_no_mail_verify'] = array(
    'type' => 'boolean',
    'title' => t('No email verification required for eID accounts'),
    'default' => TRUE,
    'description' => t('Never require email verification when a visitor creates a new account using his/her eID-card.'),
    'group' => 'beididp',
    'localize' => FALSE, 
  );
  $variables['beididp_https_required'] = array(
    'type' => 'boolean',
    'title' => t('Require HTTPS on eID login'),
    'default' => TRUE,
    'description' => t('HTTPS must be activated to prevent cookie / session hijacking'),
    'group' => 'beididp',
    'localize' => FALSE,
  );
  $variables['beididp_hash_claimed_id'] = array(
    'type' => 'boolean',
    'title' => t('Apply hash function to BeIDIDP identity'),
    'default' => TRUE,
    'description' => t('Enable this option to hash the unique National Registry Number (part of the BeidIDP Identity) before storing it in the database.'),
    'group' => 'beididp',
    'localize' => FALSE,
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function beididp_variable_group_info() {
  $groups['beididp'] = array(
    'title' => t('BeidIDP settings'),
    'access' => 'administer beididp',
  );

  return $groups;
}

/**
 * Validate BeID URL.
 */
function beididp_idp_url_validate($variable) {
  if (!valid_url($variable['value'])) {
    return t('Please enter a valid URL');
  }
  else {
    $url = parse_url($variable['value']);
    if (!($url['scheme'] === 'https')) {
      return t('HTTPS required');
    }
  }
}
