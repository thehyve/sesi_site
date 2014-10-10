<?php
/**
 * @file
 * sesi_contact_form.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function sesi_contact_form_user_default_permissions_alter(&$data) {
  if (isset($data['create contact content'])) {
    unset($data['create contact content']['roles']['network administrator']);
    unset($data['create contact content']['roles']['network reviewer']);
  }
  if (isset($data['delete any contact content'])) {
    unset($data['delete any contact content']['roles']['network reviewer']);
  }
  if (isset($data['delete own contact content'])) {
    unset($data['delete own contact content']['roles']['network administrator']);
    unset($data['delete own contact content']['roles']['network reviewer']);
  }
  if (isset($data['edit any contact content'])) {
    unset($data['edit any contact content']['roles']['network administrator']);
    unset($data['edit any contact content']['roles']['network reviewer']);
  }
  if (isset($data['edit own contact content'])) {
    unset($data['edit own contact content']['roles']['network administrator']);
    unset($data['edit own contact content']['roles']['network reviewer']);
  }
}
