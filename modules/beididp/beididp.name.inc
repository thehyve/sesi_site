<?php
/**
 * @file
 * Functions for creating and deleting user names and eID authnames.
 */

/**
 * Create a username.
 *
 * Use the citizen's first and last name (as stored on the eID).
 * If this name is already taken, then add a numeric suffix.
 *
 * @param string $first_name
 *   First name of the citizen
 * @param string $last_name
 *   Last name of the citizen
 *
 * @return string
 *   Concatenated string
 */
function beididp_name_nick($first_name, $last_name) {
  $name = preg_replace('/\W/', '', $first_name . $last_name);
  $nick = $name;
  $suffix = 1;

  while (beididp_user_exists($nick)) {
    $nick = $name . $suffix++;
  }
  return $nick;
}


/**
 * Check if a certain user name already exists.
 *
 * @param string $name
 *   User name to be checked
 *
 * @return bool
 *   TRUE if a user name is already in the database
 */
function beididp_user_exists($name) {
  return db_query(
    'SELECT 1 FROM {users} WHERE name = :name',
    array(':name' => $name))
    ->fetchColumn();
}

/**
 * Check if a certain eID identity (authname) already exists.
 *
 * @param string $eidentity
 *   EID IDP URL (authname) to be checked
 *
 * @return bool
 *   TRUE if an eID identity is already in the database
 */
function beididp_authname_exists($eidentity) {
  return db_query(
    "SELECT 1 FROM {authmap} WHERE authname = :authname AND module = 'beididp'",
    array(':authname' => $eidentity))
    ->fetchField();
}

/**
 * Retrieve an eID identity from the database.
 *
 * @param int $uid
 *   User ID
 * @param int $aid
 *   Authname ID
 *
 * @return string
 *   EID IDP URL (eID identity) 
 */
function beididp_authname_get($uid, $aid) {
  return db_query(
    "SELECT authname FROM {authmap} WHERE uid = :uid AND aid = :aid AND module = 'beididp'",
    array(':uid' => $uid, ':aid' => $aid))
    ->fetchField();
}

/**
 * Retrieve all eID identities of a user from the database.
 *
 * @param int $uid
 *   User ID
 *
 * @return DatabaseStatementInterface
 *   A prepared statement object
 */
function beididp_authname_all($uid) {
  return db_query(
    "SELECT * FROM {authmap} WHERE uid = :uid AND module = 'beididp'",
    array(':uid' => $uid));
}

/**
 * Store an eID identity in the database.
 *
 * @param string $eidentity
 *   EID IDP URL (authname)
 * @param int $uid
 *   User ID 
 *
 * @return bool
 *   TRUE if stored successfully
 */
function beididp_authname_store($eidentity, $uid) {
  $record = array(
    'uid' => $uid,
    'authname' => $eidentity,
    'module' => 'beididp',
  );
  return drupal_write_record('authmap', $record);
}

/**
 * Delete an eID identity from the database.
 *
 * @param int $uid
 *   User ID
 * @param int $aid
 *   Authname ID
 *
 * @return bool
 *   TRUE if deleted successfully
 */
function beididp_authname_del($uid, $aid) {
  return db_delete('authmap')
    ->condition('uid', $uid)
    ->condition('aid', $aid)
    ->condition('module', 'beididp')
    ->execute();
}
