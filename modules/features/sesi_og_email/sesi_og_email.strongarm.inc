<?php
/**
 * @file
 * sesi_og_email.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_og_email_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_active_body';
  $strongarm->value = array(
    'value' => '<p>Dear [group:author:name],</p>

<p>User \'[account:name]\' joined [group:title] in [group:url]</p>
<p>
============<br>
User Details<br>
============<br>
User ID: [account:uid]<br>
User Unique ID: [account:uuid]<br>
User Name: [account:name]<br>
Account Status: [account:status]<br>
Email: [account:mail]<br>
</p>
<hr> 
Edit account: [account:edit-url]
<hr>
Team [site:name]<br>
[site:url]


',
    'format' => 'filtered_html',
  );
  $export['og_email_admin_active_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_active_subject';
  $strongarm->value = 'User [account:name] joined community [group:title]';
  $export['og_email_admin_active_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_pending_body';
  $strongarm->value = array(
    'value' => '<p>Dear [group:author:name],</p>
    
<p>User \'[account:name]\' requests membership for group \'[group:title]\' in [group:url].</p>
<p>
============<br>
User Details<br>
============<br>
User ID: [account:uid]<br>
User Unique ID: [account:uuid]<br>
User Name: [account:name]<br>
Account Status: [account:status]<br>
First Name: [account:profile-main:field_profile_first_name]<br>
Last Name: [account:profile-main:field_profile_last_name]<br>
Institution: [account:profile-main:field_profile_institution]<br>
Department: [account:profile-main:field_profile_department]<br>
Telephone: [account:profile-main:field_profile_telephone]<br>
Email: [account:mail]<br>
</p>
<p>Please check:
People in group page:<br>
[site:url]?q=group/node/[group:nid]/admin/people</p>
<p>Edit membership in group page: <br>
[site:url]?q=group/node/[group:nid]/admin/people/edit-membership/[og-membership:id]&destination=group/node/[group:nid]/admin/people</p>
<br>
<hr>
Team [site:name]<br>
[site:url]',
    'format' => 'filtered_html',
  );
  $export['og_email_admin_pending_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_pending_subject';
  $strongarm->value = 'User [account:name] requests membership for [group:title]';
  $export['og_email_admin_pending_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_active_body';
  $strongarm->value = array(
    'value' => '<p>Dear [account:name],</p>

<p>
You are now a member in the group \'[group:title]\' located at [group:url]<br>
Your membership will expire on [og-membership:field_expiration_date] (if applicable).
</p>

<hr>
Team [site:name]<br>
[site:url]',
    'format' => 'filtered_html',
  );
  $export['og_email_member_active_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_active_subject';
  $strongarm->value = 'Your membership request was approved for \'[group:title]\'';
  $export['og_email_member_active_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_pending_body';
  $strongarm->value = array(
    'value' => '<p>Dear [account:name],</p>
<p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>

<hr>
Team [site:name]<br>
[site:url]',
    'format' => 'filtered_html',
  );
  $export['og_email_member_pending_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_pending_subject';
  $strongarm->value = 'Your membership request for community \'[group:title]\'';
  $export['og_email_member_pending_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_new_content_body';
  $strongarm->value = array(
    'value' => '<p>Hello [list-item:name],</p>

<p>There is a new post called [node:title] that belongs to one of the groups you are subscribed to.</p>

<hr>
Team [site:name]<br>
[site:url]',
    'format' => 'filtered_html',
  );
  $export['og_email_new_content_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_new_content_subject';
  $strongarm->value = 'New post in group';
  $export['og_email_new_content_subject'] = $strongarm;

  return $export;
}
