<?php

/**
 * @file
 * Provides the admin callback functionalities
 */

/**
 * Form constructor for the migrate admin form.
 *
 * @see beididp_migrate_form_validate()
 * @see beididp_migrate_form_submit()
 * @ingroup forms
 */
function beididp_migrate_form() {
  $idps = beididp_migrate_current_idps();

  // Turn flat list into key/value array for <select>
  $options = array();
  foreach ($idps as $idp) {
    $options[$idp] = $idp;
  }

  $form['beididp_migrate_old'] = array(
    '#type' => 'select',
    '#title' => t('Current IDPs'),
    '#description' => t('List of currently used IDPs.'),
    '#options' => $options,
  );

  $form['beididp_migrate_new'] = array(
    '#type' => 'textfield',
    '#title' => t('New IDP'),
    '#description' => t('URL of the new IDP.'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Update'));

  return $form;
}


/**
 * Form validation handler for beididp_migrate_form().
 */
function beididp_migrate_form_validate($form, &$form_state) {
  $idp = $form_state['values']['beididp_migrate_new'];

  if (!valid_url($idp)) {
    form_set_error('beididp_migrate_new', t('Please enter a valid URL'));
  }
  else {
    $url = parse_url($idp);
    if (!($url['scheme'] === 'https')) {
      form_set_error('beididp_migrate_new', t('HTTPS required'));
    }
  }
}

/**
 * Form submission handler for beididp_migrate_form().
 */
function beididp_migrate_form_submit($form, &$form_state) {
  $old_idp = $form_state['values']['beididp_migrate_old'];
  $new_idp = $form_state['values']['beididp_migrate_new'];

  if (beididp_migrate_update_idp($old_idp, $new_idp)) {
    drupal_set_message(t('Updated %old to %new', array("%old" => $old_idp, "%new" => $new_idp)));
  }
}
