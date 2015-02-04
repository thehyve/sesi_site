<?php
/**
 * @file
 * sesi_expiration_date.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_expiration_date_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.dataset_index.options|fields|field_expiration_date"] = array(
    'type' => 'date',
  );

  // Exported overrides for: views_view
  $overrides["views_view.datasets.display|default|display_options|filter_groups"] = array(
    'groups' => array(
      1 => 'AND',
      2 => 'OR',
    ),
  );
  $overrides["views_view.datasets.display|default|display_options|filters|field_expiration_date"] = array(
    'id' => 'field_expiration_date',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => '>=',
    'value' => 'now',
    'group' => 2,
  );
  $overrides["views_view.datasets.display|default|display_options|filters|field_expiration_date_1"] = array(
    'id' => 'field_expiration_date_1',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => 'empty',
    'group' => 2,
  );
  $overrides["views_view.harmonization_datasets.display|default|display_options|filters|field_expiration_date"] = array(
    'id' => 'field_expiration_date',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => '>=',
    'value' => 'now',
    'group' => 2,
  );
  $overrides["views_view.harmonization_datasets.display|default|display_options|filters|field_expiration_date_1"] = array(
    'id' => 'field_expiration_date_1',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => 'empty',
    'group' => 2,
  );
  $overrides["views_view.study_datasets.display|default|display_options|filters|field_expiration_date"] = array(
    'id' => 'field_expiration_date',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => '>=',
    'value' => 'now',
    'group' => 2,
  );
  $overrides["views_view.study_datasets.display|default|display_options|filters|field_expiration_date_1"] = array(
    'id' => 'field_expiration_date_1',
    'table' => 'search_api_index_dataset_index',
    'field' => 'field_expiration_date',
    'operator' => 'not empty',
    'group' => 2,
  );

 return $overrides;
}
