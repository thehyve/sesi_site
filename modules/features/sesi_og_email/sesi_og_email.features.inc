<?php
/**
 * @file
 * sesi_og_email.features.inc
 */

/**
 * Implements hook_strongarm_alter().
 */
function sesi_og_email_strongarm_alter(&$data) {
  if (isset($data['og_email_admin_pending_body'])) {
    $data['og_email_admin_pending_body']->value['value'] = '<p>Dear [group:author:name]</p>
    
    <p>[account:name] requests membership for group \'[group:title]\' in [group:url].</p>
    
    <p>Please check:
    People in group page:<br>
    [site:url]?q=group/node/[group:nid]/admin/people</p>
    <p>Edit membership in group page: <br>
    [site:url]?q=group/node/[group:nid]/admin/people/edit-membership/[og-membership:id]&destination=group/node/[group:nid]/admin/people</p>
    '; /* WAS: '<p>[group:author:name]</p>
    
    <p>[account:name] requests membership for group \'[group:title]\' in [group:url].</p>
    
    <p>&nbsp;</p>
    
    <p>&nbsp;</p>
    
    <p>&nbsp;</p>
    ' */
  }
}
