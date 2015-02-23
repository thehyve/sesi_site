<?php
/**
 * @file
 * sesi_contacts_configuration.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_contacts_configuration_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_daco.field_permissions|type"] = 2;
  $overrides["field_base.field_daco.settings|field_description_infos|field_description_label"] = '';
  $overrides["field_base.field_daco.settings|field_description_infos|field_description_value_type"] = 'boolean';
  $overrides["field_base.field_daco.settings|profile2_private"] = FALSE;

  // Exported overrides for: field_instance
  $overrides["field_instance.node-contact-field_daco.display_label"] = '';

 return $overrides;
}
