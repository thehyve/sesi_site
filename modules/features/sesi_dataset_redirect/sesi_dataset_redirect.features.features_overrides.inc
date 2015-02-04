<?php
/**
 * @file
 * sesi_dataset_redirect.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_dataset_redirect_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.community_by_dataset.display|page|display_options|path"] = 'community_by_dataset';
  $overrides["views_view.datasets.display|page|display_options|defaults|fields"] = FALSE;
  $overrides["views_view.datasets.display|page|display_options|fields"] = array(
    'nid' => array(
      'id' => 'nid',
      'table' => 'search_api_index_dataset_index',
      'field' => 'nid',
      'exclude' => TRUE,
      'link_to_entity' => 0,
    ),
    'title' => array(
      'id' => 'title',
      'table' => 'search_api_index_dataset_index',
      'field' => 'title',
      'label' => 'Name',
      'alter' => array(
        'make_link' => TRUE,
        'path' => 'userflow/[nid]',
      ),
      'link_to_entity' => 0,
    ),
    'field_dataset_type' => array(
      'id' => 'field_dataset_type',
      'table' => 'search_api_index_dataset_index',
      'field' => 'field_dataset_type',
      'label' => 'Type',
    ),
    'body' => array(
      'id' => 'body',
      'table' => 'search_api_index_dataset_index',
      'field' => 'body',
      'label' => 'Description',
      'alter' => array(
        'max_length' => 200,
        'trim' => TRUE,
        'html' => TRUE,
      ),
      'type' => 'text_summary_or_trimmed',
      'settings' => array(
        'trim_length' => 600,
      ),
    ),
  );

 return $overrides;
}
