<?php
/**
 * @file
 * sesi_contact_form.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sesi_contact_form_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'comment-comment_node_contact-comment_body'
  $field_instances['comment-comment_node_contact-comment_body'] = array(
    'bundle' => 'comment_node_contact',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Comment');

  return $field_instances;
}
