<?php
/**
 * @file
 * Provides the admin callback functionalities
 */

/**
 * Callbacks for the admin settings.
 */
function beididp_fields_admin($form, &$form_state) {
  $form['attr'] = array(
    '#type' => 'fieldset',
    '#title' => t('Map eID attributes to Drupal user fields'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 0,
  );

  $fields = field_info_instances('user');

  $drupal_profiles = array('');
  foreach ($fields['user'] as $field) {
    $name = $field['field_name'];
    $title = $field['label'];
    $drupal_profiles[$name] = $title;
  }

  $profile_fields = beididp_fields_get_fields();
  foreach ($profile_fields as $item) {
    $form['attr']['beididp_fields_' . $item] = array(
      '#type' => 'select',
      '#title' => check_plain($item),
      '#default_value' => variable_get('beididp_fields_' . $item, ''),
      '#options' => $drupal_profiles,
    );
  }

  return system_settings_form($form);
}
