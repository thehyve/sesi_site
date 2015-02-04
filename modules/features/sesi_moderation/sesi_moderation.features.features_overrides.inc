<?php
/**
 * @file
 * sesi_moderation.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_moderation_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.moderate content from draft to needs_review.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.moderate content from needs_review to draft.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.moderate content from needs_review to published.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.view moderation history.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.view moderation messages.roles|authenticated user"] = 'authenticated user';

 return $overrides;
}
