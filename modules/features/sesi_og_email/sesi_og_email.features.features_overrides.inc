<?php
/**
 * @file
 * sesi_og_email.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_og_email_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.og_email_admin_active_body.value|value"] = '<p>Dear group:author:name],</p>
  
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
  
  
  
  ';
  $overrides["variable.og_email_member_active_body.value|value"] = '<p>Dear [account:name],</p>
  
  <p>You are now a member in the group \'[group:title]\' located at [group:url]</p>
  
  <hr>
  [site:name]<br>
  [site:slogan]<br>
  [site:url]';
  $overrides["variable.og_email_member_pending_body.value|value"] = '<p>Dear [account:name],</p>
  <p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>
  
  <hr>
  [site:name]<br>
  [site:slogan]<br>
  [site:url]';

 return $overrides;
}
