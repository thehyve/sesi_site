<?php
/**
 * @file
 * Variable API module. Definition for variables
 */

/**
 * Callback for user mail variables.
 *
 * @param array $variable
 *   Variables
 * @param array $options
 *   Options
 *
 * @return string 
 *   Subject or body text
 */
function beididp_mail_mail_default($variable, $options) {
  $name = substr($variable['name'], strlen('beididp_mail_'));
  $language = $options['language'];
  return _user_mail_text($name, $language, array(), FALSE);
}

/**
 * Implements hook_variable_info().
 */
function beididp_mail_variable_info($options) {
  $variables['beididp_mail_register_no_approval_required_[mail_part]'] = array(
    'title' => t('Welcome, no approval required'),
    'type' => 'mail_text',
    'description' => t('Alternative mail to be sent when a user creates a new account via eID. The default mail can be confusing, because it contains a username and a password.'),
    'group' => 'beididp_mails',
    'localize' => TRUE,
    'repeat' => array(
      'default callback' => 'beididp_mail_mail_default',
    ),
  );

  $variables['beididp_mail_register_pending_approval_[mail_part]'] = array(
    'title' => t('Welcome, awaiting administrator approval'),
    'type' => 'mail_text',
    'description' => t('Alternative mail to be sent when a user creates a new account via eID and admin approval is required. The default mail can be confusing, because it mentions a password.'),
    'group' => 'beididp_mails',
    'localize' => TRUE,
    'repeat' => array(
      'default callback' => 'beididp_mail_mail_default',
    ),
  );

  $variables['beididp_mail_status_activated_[mail_part]'] = array(
    'title' => t('Account activation email'),
    'type' => 'mail_text',
    'description' => t('Alternative mail to be sent when an admin approves a new account that was created with eID. The default mail can be confusing, because it mentions a password.'),
    'group' => 'beididp_mails',
    'localize' => TRUE,
    'repeat' => array(
      'default callback' => 'beididp_mail_mail_default',
    ),
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function beididp_mail_variable_group_info() {
  $groups['beididp_mails'] = array(
    'title' => t('BeidIDP user emails'),
    'description' => t('Alter emails when user registers with eID.'),
    'access' => 'administer beididp',
  );

  return $groups;
}
