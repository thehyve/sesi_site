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
  $overrides["variable.og_email_admin_pending_body.value|value"] = '<p>Dear [group:author:name]</p>
  
  <p>[account:name] requests membership for group \'[group:title]\' in [group:url].</p>
  
  <p>Please check:
  People in group page:<br>
  [site:url]?q=group/node/[group:nid]/admin/people</p>
  <p>Edit membership in group page: <br>
  [site:url]?q=group/node/[group:nid]/admin/people/edit-membership/[og-membership:id]&destination=group/node/[group:nid]/admin/people</p>
  ';

 return $overrides;
}
