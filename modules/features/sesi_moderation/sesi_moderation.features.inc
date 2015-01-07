<?php
/**
 * @file
 * sesi_moderation.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function sesi_moderation_user_default_permissions_alter(&$data) {
  if (isset($data['moderate content from draft to needs_review'])) {
    $data['moderate content from draft to needs_review']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['moderate content from needs_review to draft'])) {
    $data['moderate content from needs_review to draft']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['moderate content from needs_review to published'])) {
    $data['moderate content from needs_review to published']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['view moderation history'])) {
    $data['view moderation history']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['view moderation messages'])) {
    $data['view moderation messages']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
}
