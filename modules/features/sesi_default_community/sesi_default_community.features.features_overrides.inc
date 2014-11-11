<?php
/**
 * @file
 * sesi_default_community.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_default_community_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.og_group_ref.field_permissions"] = array(
    'type' => 0,
  );
  $overrides["field_base.og_group_ref.settings|field_description_infos"] = array(
    'field_description' => 0,
    'field_description_body' => '',
    'field_description_label' => '',
    'field_description_value_type' => 'text',
  );
  $overrides["field_base.og_group_ref.settings|handler_settings|behaviors|views-select-list"] = array(
    'status' => 0,
  );
  $overrides["field_base.og_group_ref.settings|handler_settings|sort"] = array(
    'type' => 'none',
  );
  $overrides["field_base.og_group_ref.settings|handler_settings|target_bundles|community"] = 'community';
  $overrides["field_base.og_group_ref.settings|handler_settings|target_bundles|default_community"] = 'default_community';
  $overrides["field_base.og_group_ref.settings|profile2_private"] = FALSE;

 return $overrides;
}
