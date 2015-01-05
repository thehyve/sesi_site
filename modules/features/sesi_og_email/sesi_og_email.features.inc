<?php
/**
 * @file
 * sesi_og_email.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_og_email_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function sesi_og_email_strongarm_alter(&$data) {
  if (isset($data['og_email_admin_active_body'])) {
    $data['og_email_admin_active_body']->value['value'] = '<p>Dear group:author:name],</p>
    
    <p>User \'[account:name]\' joined [group:title] in [group:url]</p>
    
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
    Edit account: [account:edit-url]
    
    <p>&nbsp;</p>
    
    
    
    '; /* WAS: '<p>[group:author:name],</p>
    
    <p>[account:name] joined [group:title] in [group:url]</p>
    
    <p>&nbsp;</p>
    ' */
  }
  if (isset($data['og_email_member_active_body'])) {
    $data['og_email_member_active_body']->value['value'] = '<p>Dear [account:name],</p>
    
    <p>You are now a member in the group \'[group:title]\' located at [group:url]</p>
    
    <hr>
    [site:name]<br>
    [site:slogan]<br>
    [site:url]'; /* WAS: '<p>[account:name],</p>
    
    <p>You are now a member in the group \'[group:title]\' located at [group:url]</p>
    ' */
  }
  if (isset($data['og_email_member_pending_body'])) {
    $data['og_email_member_pending_body']->value['value'] = '<p>Dear [account:name],</p>
    <p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>
    
    <hr>
    [site:name]<br>
    [site:slogan]<br>
    [site:url]'; /* WAS: '<p>[account:name],</p>
    
    <p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>
    ' */
  }
}
