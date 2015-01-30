<?php

/**
 * Variable definition
 */

/**
 * Implements hook_variable_group_info()
 */
function og_email_variable_group_info() {
  // Group for variable that have no group
  $groups['og_email'] = array(
    'title' => t('OG Email'),
    'description' => t("Emails used in Organic Groups."),
  );
  return $groups;
}

/**
 * Implements hook_variable_info().
 */
function og_email_variable_info($options) {
  $variable = array();

  $variable['og_email_member_active_[mail_part]'] = array(
    'title' => t('OG member subscribe (Active, Member)'),
    'type' => 'mail_html',
    'description' => t('Template for the OG email sent out to new group members when their membership request has been approved.'),
    'children' => array(
      'og_email_member_active_subject' => array(
        'default' => 'Your membership request was approved for \'[group:title]\'',
      ),
      'og_email_member_active_body' => array(
        'default' => '<p>[account:name],</p><p>You are now a member in the group \'[group:title]\' located at [group:url]</p>'
      ),
    ),
    'group' => 'og_email',
  );

  $variable['og_email_admin_active_[mail_part]'] = array(
    'title' => t('OG member subscribe (Active, Admin)'),
    'type' => 'mail_html',
    'description' => t('Template for the OG email sent out to group owners when a new member has joined.'),
    'children' => array(
      'og_email_admin_active_subject' => array(
        'default' => '[account:name] joined [group:title]',
      ),
      'og_email_admin_active_body' => array(
        'default' => '<p>[group:author:name],</p><p>[account:name] joined [group:title] in [group:url]</p>'
      ),
    ),
    'group' => 'og_email',
  );

  $variable['og_email_member_pending_[mail_part]'] = array(
    'title' => t('OG member subscribe (Pending, Member)'),
    'type' => 'mail_html',
    'description' => t('Template for the OG email sent out to new group members when their membership request has been sent for approval.'),
    'children' => array(
      'og_email_member_pending_subject' => array(
        'default' => 'Your membership request for \'[group:title]\'',
      ),
      'og_email_member_pending_body' => array(
        'default' => '<p>[account:name],</p><p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>'
      ),
    ),
    'group' => 'og_email',
  );

  $variable['og_email_admin_pending_[mail_part]'] = array(
    'title' => t('OG member subscribe (Pending, Admin)'),
    'type' => 'mail_html',
    'description' => t('Template for the OG email sent out to group owners when a new membership request is pending.'),
    'children' => array(
      'og_email_admin_pending_subject' => array(
        'default' => '[account:name] membership request [group:title]',
      ),
      'og_email_admin_pending_body' => array(
        'default' => '<p>[group:author:name]</p><p>[account:name] requests membership for group \'[group:title]\' in [group:url].</p><p>[og_membership:og-membership-request]</p>'
      ),
    ),
    'group' => 'og_email',
  );

  $variable['og_email_new_content_[mail_part]'] = array(
    'title' => t('OG new content notification'),
    'type' => 'mail_html',
    'description' => t('Template for the OG email sent out to group members when a new group content is posted.'),
    'children' => array(
      'og_email_new_content_subject' => array(
        'default' => 'New post in group',
      ),
      'og_email_new_content_body' => array(
        'default' => '<p>Hello [list-item:name],</p><p>There is a new post called [node:title] that belongs to one of the groups you are subscribed to.</p><p>[site:name]</p>'
      ),
    ),
    'group' => 'og_email',
  );

  return $variable;
}