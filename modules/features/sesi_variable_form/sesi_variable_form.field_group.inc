<?php
/**
 * @file
 * sesi_variable_form.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sesi_variable_form_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_variable_details|node|variable|form';
  $field_group->group_name = 'group_variable_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'variable';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_general_info';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '10',
    'children' => array(
      0 => 'field_dataset',
      1 => 'field_repeatable',
      2 => 'field_unit',
      3 => 'field_value_type',
      4 => 'field_vocabulary_url',
      5 => 'field_taxonomy',
      6 => 'field_validate_categories',
      7 => 'field_validate_min',
      8 => 'field_validate_max',
      9 => 'field_validate_past_date',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-variable-details field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_variable_details|node|variable|form'] = $field_group;

  return $export;
}
