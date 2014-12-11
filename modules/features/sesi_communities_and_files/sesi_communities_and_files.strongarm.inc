<?php
/**
 * @file
 * sesi_communities_and_files.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_communities_and_files_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_article';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_community_document';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_community_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_event';
  $strongarm->value = array(
    'view_own' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'view' => array(
      0 => 1,
      1 => 2,
      2 => 3,
      3 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__community';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__community'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_active_body';
  $strongarm->value = array(
    'value' => '<p>[group:author:name],</p>

<p>[account:name] joined [group:title] in [group:url]</p>

<p>&nbsp;</p>
',
    'format' => 'filtered_html',
  );
  $export['og_email_admin_active_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_active_subject';
  $strongarm->value = '[account:name] joined [group:title]';
  $export['og_email_admin_active_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_pending_body';
  $strongarm->value = array(
    'value' => '<p>[group:author:name]</p>

<p>[account:name] requests membership for group \'[group:title]\' in [group:url].</p>

<p>&nbsp;</p>

<p>&nbsp;</p>

<p>&nbsp;</p>
',
    'format' => 'filtered_html',
  );
  $export['og_email_admin_pending_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_admin_pending_subject';
  $strongarm->value = '[account:name] membership request [group:title]';
  $export['og_email_admin_pending_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_active_body';
  $strongarm->value = array(
    'value' => '<p>[account:name],</p>

<p>You are now a member in the group \'[group:title]\' located at [group:url]</p>
',
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
    'value' => '<p>[account:name],</p>

<p>Your membership to group \'[group:title]\' located at [group:url] is pending approval.</p>
',
    'format' => 'filtered_html',
  );
  $export['og_email_member_pending_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_member_pending_subject';
  $strongarm->value = 'Your membership request for \'[group:title]\'';
  $export['og_email_member_pending_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_new_content_body';
  $strongarm->value = array(
    'value' => '<p>Hello [list-item:name],</p>

<p>There is a new post called [node:title] that belongs to one of the groups you are subscribed to.</p>

<p>[site:name]</p>
',
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
