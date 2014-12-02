<?php
/**
 * @file
 * sesi_notify_expirations.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_notify_expirations_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'og_membership-og_membership_type_default-field_expiration_date'
  $field_instances['og_membership-og_membership_type_default-field_expiration_date'] = array(
    'bundle' => 'og_membership_type_default',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 2,
      ),
    ),
    'display_label' => '',
    'entity_type' => 'og_membership',
    'field_name' => 'field_expiration_date',
    'label' => 'Expiration date',
    'required' => 0,
    'settings' => array(
      'default_value' => '',
      'default_value2' => '',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'og_membership-og_membership_type_default-field_mail_sent'
  $field_instances['og_membership-og_membership_type_default-field_mail_sent'] = array(
    'bundle' => 'og_membership_type_default',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
    ),
    'display_label' => 'Mail sent',
    'entity_type' => 'og_membership',
    'field_name' => 'field_mail_sent',
    'label' => 'Mail sent',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 6,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Expiration date');
  t('Mail sent');

  return $field_instances;
}
