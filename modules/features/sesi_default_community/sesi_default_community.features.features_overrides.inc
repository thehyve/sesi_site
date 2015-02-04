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

  // Exported overrides for: og_features_permission
  $overrides["og_features_permission.node:default_community:create community_document content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:delete any variable content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:delete own community_document content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:delete own dataset content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:delete own event content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:delete own variable content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:update own community_document content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:update own dataset content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:update own event content.roles|member"]["DELETED"] = TRUE;
  $overrides["og_features_permission.node:default_community:update own variable content.roles|member"]["DELETED"] = TRUE;

 return $overrides;
}
