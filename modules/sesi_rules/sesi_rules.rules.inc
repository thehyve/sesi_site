<?php

/**
 * @file
 * Create a custom rules action for Sesi project
 * For more docs see
 * http://drupalcontrib.org/api/drupal/contributions!rules!rules.api.php/function/hook_rules_action_info/7 (hook_rules_action_info)
 * https://www.drupal.org/node/878880 (Entity type metadata)
 * http://drupal.stackexchange.com/questions/35026/og-group-content-notification-for-group-administrators (OG group content notification for group administrators)
 * http://stackoverflow.com/questions/16742925/how-to-send-an-email-to-drupal-7-organic-groups-role-members (How to send an email to Drupal 7 Organic Groups Role Members?)
 * https://www.drupal.org/node/905580 (Data types for rules)
 * http://drupal.org/node/878928 (Conditions / actions)
 *
 */

/**
 * Implements hook_rules_action_info().
 *
 * Creates a new rule actions and declares any meta-data about actions for Rules in a big, associative, nested array
 *
 */

function sesi_rules_rules_action_info() {

  $actions = array(
    'sesi_rules_action_send_email_to_group_admins' => array(
      'label' => t('Mail to group admins'),
      'group' => t('Sesi'),
      'parameter' => array(
        'organic_group' => array(
          'type' => 'og_membership',
          'label' => t('User'),
          'description' => t('The membership record for the user and the group'),
        ),
      ),
      'provides' => array(
        'membership' => array(
          'type' => 'og_membership',
          'label' => t('The membership record for the user and the group')
        ),
      ),
      'base' => 'sesi_rules_rules_get_admins',
    ),
  );
  return $actions;
}

function sesi_rules_rules_get_admins($membership) {
  if (!isset($membership)) {
    return;
  }

  // Get the profile id of the new member
  $userprofile = array();
  $profile = db_select('profile', 'p');
  $profile->fields('p');
  $profile->condition('p.uid', $membership->etid, '=');
  $profilefound = $profile->execute();
  $userprofile = $profilefound->fetchAssoc();
  
  // Get the group admins of the group
  $admins = array();
  $current_admins = db_select('og_membership', 'om');
  $current_admins->leftjoin('og_users_roles', 'ogur', 'om.etid = ogur.uid');
  $current_admins->fields('om', array('etid'));
  $current_admins->condition('om.gid', $membership->gid);
  $current_admins->condition('om.entity_type', 'user');
  // FOR THIS LINE, YOU'LL NEED TO KNOW THE ROLE ID FROM THE `og_role` TABLE (which is 3 for the community) 
  $current_admins->condition('ogur.rid', 3);
  $current_admins->condition('ogur.gid', $membership->gid);
  
  $result = $current_admins->execute();
  while ($res = $result->fetchAssoc()) {
    $admins[] = $res['etid'];
  }
  // Remove duplicate items.
  $admins = array_keys(array_flip($admins));
  // dsm($admins);
  
  // Now mail the group admins
  foreach ($admins as $admin) {
    rules_invoke_component('rules_mail_group_admins', $admin, $membership->gid, $membership->etid, $userprofile['pid']);
    //rules_invoke_component('rules_mail_group_admins', $admin, $membership->gid, $membership->etid, $userprofile->pid);
  }
  drupal_set_message(t('Membership request sent to community administrators'));
  return;
} 
