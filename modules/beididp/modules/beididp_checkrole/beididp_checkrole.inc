<?php

/**
 * @file
 * Provides the admin callback functionalities
 */

module_load_include('inc', 'beididp');

/**
 * Return the roles for a specified user.
 *
 * @param int $uid
 *   User ID.
 *
 * @return array
 *   Array of roles.
 */
function beididp_checkrole_get_roles($uid) {
  global $user;

  $roles = array();

  if (isset($uid) && isset($user)) {
    if ($uid == $user->uid) {
      $roles = $user->roles;
    }
    else {
      $check_user = user_load($uid);
      if ($check_user) {
        $roles = $check_user->roles;
      }
    }
  }
  return $roles;
}

/**
 * Get the IDs of the roles requiring eID to log in.
 *
 * @return array
 *   Array of role ids.
 */
function beididp_checkrole_eid_rids() {
  $rids = array();
  $roles = variable_get_value('beididp_required_role');

  foreach ($roles as $rid => $value) {
    if ($value > 0) {
      $rids[] = $rid;
    }
  }
  return $rids;
}

/**
 * Checks if a user has roles that match eID-only roles.
 *
 * @param array $roles_a
 *   First array of role ids.
 * @param array $roles_b
 *   Second array of role ids.
 * @param int $uid
 *   User ID.
 *
 * @return bool
 *   True if user would be blocked
 */
function beididp_checkrole_block_or_eid($roles_a, $roles_b, $uid) {
  $block = array_intersect($roles_a, $roles_b);
  if (empty($block) || beididp_authname_all($uid)->fetchObject()) {
    return FALSE;
  }
  return TRUE;
}


/**
 * Checks if a user would be locked out when roles are set to requires eID.
 *
 * @param int $uid
 *   The ID of the user.
 * @param array $role_ids
 *   The ids of the roles requiring eID.
 *
 * @return bool
 *   TRUE if drupal user would be locked out
 */
function beididp_checkrole_would_lock_user($uid, $role_ids) {
  if (empty($role_ids)) {
    return FALSE;
  }
  $user_role_ids = array_keys(beididp_checkrole_get_roles($uid));

  return beididp_checkrole_block_or_eid($user_role_ids, $role_ids, $uid);
}

/**
 * Checks if a user would be locked out when eID is deleted.
 *
 * @param int $uid
 *   The ID of the user.
 *
 * @return bool
 *   TRUE if drupal user would be locked out
 */
function beididp_checkrole_would_lock_user_delete($uid) {
  $user_role_ids = array_keys(beididp_checkrole_get_roles($uid));
  $role_ids = beididp_checkrole_eid_rids();

  $block = array_intersect($user_role_ids, $role_ids);

  return !empty($block);
}


/**
 * Checks if a user would be locked out when he gets new roles.
 *
 * @param int $uid
 *   The ID of the user.
 * @param array $new_ids
 *   The ids of the roles the user would get.
 *
 * @return bool
 *   TRUE if drupal user would be locked out
 */
function beididp_checkrole_would_lock_user_new_roles($uid, $new_ids) {
  $user_role_ids = array_keys($new_ids);
  $role_ids = beididp_checkrole_eid_rids();

  return beididp_checkrole_block_or_eid($user_role_ids, $role_ids, $uid);
}
