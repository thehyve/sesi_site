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
  $strongarm->name = 'og_email_admin_pending_body';
  $strongarm->value = array(
    'value' => '<p>Dear [group:author:name],</p>
    
    <p>User \'[account:name]\' requests membership for group \'[group:title]\' in [group:url].</p>
    <p>
    	============<br>
    	User Details<br>
    	============<br>
    	User ID: [account:id]<br>
        User Unique ID: [account:uuid]<br>
    	User Name: [account:name]<br>
		Account Status: [account:status]<br>
		First Name: [account:profile-main:field_profile_first_name]<br>
		Last Name: [account:profile-main:field-profile-last-name]<br>
		Institution: [account:profile-main:field-profile-institution]<br>
		Departement: [account:profile-main:field-profile-department]<br>
		Telephone: [account:profile-main:field-profile-telephone]<br>
    	Real Name: [account:realname]<br>
    	Email: [account:mail]<br>
    </p>
    <hr>    
    <p>Please check:
    People in group page:<br>
    [site:url]?q=group/node/[group:nid]/admin/people</p>
    <p>Edit membership in group page: <br>
    [site:url]?q=group/node/[group:nid]/admin/people/edit-membership/[og-membership:id]&destination=group/node/[group:nid]/admin/people</p>
    ',
    'format' => 'filtered_html',
  );
  $export['og_email_admin_pending_body'] = $strongarm;

  return $export;
}
