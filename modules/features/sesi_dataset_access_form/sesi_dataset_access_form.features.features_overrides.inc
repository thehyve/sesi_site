<?php
/**
 * @file
 * sesi_dataset_access_form.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_dataset_access_form_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.datasets.display|default|display_options|access|perm"] = 'update group';

 return $overrides;
}
