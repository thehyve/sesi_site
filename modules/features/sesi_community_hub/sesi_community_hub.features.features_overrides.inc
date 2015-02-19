<?php
/**
 * @file
 * sesi_community_hub.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_community_hub_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.og_content_draft_.display|panel_pane_1|display_options|defaults|filter_groups"] = FALSE;
  $overrides["views_view.og_content_draft_.display|panel_pane_1|display_options|defaults|filters"] = FALSE;
  $overrides["views_view.og_content_draft_.display|panel_pane_1|display_options|filters"] = array(
    'status' => array(
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'value' => 1,
    ),
    'group_type' => array(
      'id' => 'group_type',
      'table' => 'og_membership',
      'field' => 'group_type',
      'relationship' => 'og_membership_rel',
      'value' => array(
        'node' => 'node',
      ),
    ),
    'type' => array(
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'value' => array(
        'article' => 'article',
        'community_document' => 'community_document',
        'dataset' => 'dataset',
        'event' => 'event',
        'study' => 'study',
      ),
    ),
  );
  $overrides["views_view.og_content_draft_.display|panel_pane_2|display_options|filters|type"] = array(
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'value' => array(
      'article' => 'article',
      'community_document' => 'community_document',
      'dataset' => 'dataset',
      'event' => 'event',
      'study' => 'study',
    ),
  );

 return $overrides;
}
