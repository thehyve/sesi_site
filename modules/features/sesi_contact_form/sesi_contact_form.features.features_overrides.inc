<?php
/**
 * @file
 * sesi_contact_form.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_contact_form_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.create contact content.roles|network administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.create contact content.roles|network reviewer"]["DELETED"] = TRUE;
  $overrides["user_permission.delete any contact content.roles|network reviewer"]["DELETED"] = TRUE;
  $overrides["user_permission.delete own contact content.roles|network administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.delete own contact content.roles|network reviewer"]["DELETED"] = TRUE;
  $overrides["user_permission.edit any contact content.roles|network administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.edit any contact content.roles|network reviewer"]["DELETED"] = TRUE;
  $overrides["user_permission.edit own contact content.roles|network administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.edit own contact content.roles|network reviewer"]["DELETED"] = TRUE;

 return $overrides;
}
