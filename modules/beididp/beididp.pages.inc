<?php
/**
 * @file
 * The beididp pages.inc file.
 *
 * This file provides callbacks for different pages used in the beididp module
 */

module_load_include('inc', 'beididp');

/**
 * Menu callback. Process an OpenID authentication.
 */
function beididp_authentication_page() {
  $result = beididp_complete();

  switch ($result['status']) {
    case 'success':
      return beididp_authentication($result);

    case 'failed':
      drupal_set_message(t('BeID login failed.'), 'error');
      break;

    case 'cancel':
      drupal_set_message(t('BeID login cancelled.'));
      break;
  }
  drupal_goto();
}


/**
 * Menu callback. Manage eID identities for the specified user.
 */
function beididp_eid_identities($account) {
  drupal_set_title(check_plain($account->name));

  // Check to see if we got a response.
  $result = beididp_complete();
  if ($result['status'] == 'success') {
    $identity = $result['openid.claimed_id'];

    if (beididp_authname_exists($identity)) {
      drupal_set_message(t('The eID card is already in use on this site.'), 'error');
      watchdog('beididp', 'Could not add @identity for @user, already in use', array('@user' => $account->name, '@identity' => $identity), WATCHDOG_WARNING);
    }
    else {
      if (beididp_authname_store($identity, $account->uid)) {
        drupal_set_message(t('Successfully added @identity', array('@identity' => $identity)));
      }
      else {
        drupal_set_message(t('Error adding @identity', array('@identity' => $identity)), 'error');
      }
    }
  }

  $header = array(t('BeID identity'), t('Operations'));
  $rows = array();

  $result = beididp_authname_all($account->uid);
  while ($identity = $result->fetchObject()) {
    $rows[] = array(
      check_plain($identity->authname),
      l(t('Delete'),
      'user/' . $account->uid . '/beididp/delete/' . $identity->aid),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows));
  if (empty($rows)) {
    $form = drupal_get_form('beididp_eid_add_form');
    $output .= drupal_render($form);
  }
  return $output;
}

/**
 * Form constructor for adding eID identities to an account.
 *
 * @see beididp_eid_add_form_submit()
 * @ingroup forms
 */
function beididp_eid_add_form($form) {
  $form['beid'] = array(
    '#name' => 'beid',
    '#type' => 'submit',
    '#value' => t('Add a BeID identity'),
  );

  return $form;
}

/**
 * Form submission handler for beididp_eid_add_form().
 */
function beididp_eid_add_form_submit($form, &$form_state) {
  $return_to = url('user/' . arg(1) . '/beididp', array('absolute' => TRUE));
  beididp_begin($return_to);
}

/**
 * Form constructor for deleting an eID identity.
 *
 * @see beididp_eid_delete_form_submit()
 * @ingroup forms
 */
function beididp_eid_delete_form($form, $form_state, $account, $aid = 0) {
  $authname = beididp_authname_get($account->uid, $aid);

  return confirm_form(
    array(),
    t('Are you sure you want to delete the BeID %authname for %user ?',
      array('%authname' => $authname, '%user' => $account->name)),
    'user/' . $account->uid . '/beididp');
}

/**
 * Form submission handler for beididp_eid_delete_form().
 */
function beididp_eid_delete_form_submit($form, &$form_state) {
  $uid = $form_state['build_info']['args'][0]->uid;
  $aid = $form_state['build_info']['args'][1];

  if (beididp_authname_del($uid, $aid)) {
    drupal_set_message(t('BeID Identity deleted.'));
  }
  $form_state['redirect'] = 'user/' . $uid . '/beididp';
}
