<?php
/**
 * @file
 * sesi_wildcard_content_search.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function sesi_wildcard_content_search_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.dataset_index.options|processors|search_api_case_ignore|weight"] = -50;
  $overrides["search_api_index.dataset_index.options|processors|search_api_html_filter|weight"] = -49;
  $overrides["search_api_index.dataset_index.options|processors|search_api_tokenizer|settings|fields|title"]["DELETED"] = TRUE;
  $overrides["search_api_index.dataset_index.options|processors|search_api_tokenizer|settings|spaces"] = '[^\\p{L}\\p{N}?*^\']';
  $overrides["search_api_index.dataset_index.options|processors|search_api_tokenizer|status"] = 1;
  $overrides["search_api_index.dataset_index.options|processors|search_api_tokenizer|weight"] = -48;
  $overrides["search_api_index.dataset_index.options|processors|sesi_wildcard"] = array(
    'status' => 1,
    'weight' => -47,
    'settings' => array(),
  );
  $overrides["search_api_index.studies_index.options|processors|search_api_case_ignore|weight"] = -50;
  $overrides["search_api_index.studies_index.options|processors|search_api_html_filter|weight"] = -49;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|fields|body:summary"] = TRUE;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|fields|body:value"] = TRUE;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|fields|field_acroym"] = TRUE;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|fields|search_api_aggregation_1"] = TRUE;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|fields|title_field"] = TRUE;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|settings|spaces"] = '[^\\p{L}\\p{N}?*^\']';
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|status"] = 1;
  $overrides["search_api_index.studies_index.options|processors|search_api_tokenizer|weight"] = -48;
  $overrides["search_api_index.studies_index.options|processors|sesi_wildcard"] = array(
    'status' => 1,
    'weight' => -47,
    'settings' => array(),
  );
  $overrides["search_api_index.variable_index.options|processors|search_api_case_ignore|weight"] = 0;
  $overrides["search_api_index.variable_index.options|processors|search_api_html_filter|weight"] = 10;
  $overrides["search_api_index.variable_index.options|processors|search_api_tokenizer|settings|spaces"] = '[^\\p{L}\\p{N}?*^_\']';
  $overrides["search_api_index.variable_index.options|processors|search_api_tokenizer|weight"] = 20;
  $overrides["search_api_index.variable_index.options|processors|sesi_wildcard"] = array(
    'status' => 1,
    'weight' => 50,
    'settings' => array(),
  );

  // Exported overrides for: views_view
  $overrides["views_view.datasets.display|default|display_options|filters|search_api_views_fulltext"] = array(
    'id' => 'search_api_views_fulltext',
    'table' => 'search_api_index_dataset_index',
    'field' => 'search_api_views_fulltext',
    'group' => 1,
    'exposed' => TRUE,
    'expose' => array(
      'operator_id' => 'search_api_views_fulltext_op',
      'label' => 'Search',
      'description' => 'use * and ? wildcards to search for partial words',
      'operator' => 'search_api_views_fulltext_op',
      'identifier' => 'search_api_views_fulltext',
      'remember_roles' => array(
        2 => 2,
        1 => 0,
        3 => 0,
        4 => 0,
        6 => 0,
        5 => 0,
        7 => 0,
        8 => 0,
        10 => 0,
        9 => 0,
      ),
    ),
    'group_info' => array(
      'label' => 'Fulltext search',
      'identifier' => 'search_api_views_fulltext',
      'remember' => FALSE,
      'group_items' => array(
        1 => array(),
        2 => array(),
        3 => array(),
      ),
    ),
    'fields' => array(
      'search_api_aggregation_1' => 'search_api_aggregation_1',
      'body:value' => 'body:value',
      'body:summary' => 'body:summary',
    ),
  );
  $overrides["views_view.datasets.display|default|display_options|filters|type|group"] = 1;
  $overrides["views_view.datasets.display|default|display_options|header|area|content"]["DELETED"] = TRUE;
  $overrides["views_view.studies_search.display|page_1|display_options|filters|search_api_views_fulltext"] = array(
    'id' => 'search_api_views_fulltext',
    'table' => 'search_api_index_studies_index',
    'field' => 'search_api_views_fulltext',
    'exposed' => TRUE,
    'expose' => array(
      'operator_id' => 'search_api_views_fulltext_op',
      'label' => 'Search',
      'description' => 'use * and ? wildcards to search for partial words',
      'operator' => 'search_api_views_fulltext_op',
      'identifier' => 'search_api_views_fulltext',
      'remember_roles' => array(
        2 => 2,
        1 => 0,
        3 => 0,
        4 => 0,
        6 => 0,
        5 => 0,
        7 => 0,
        8 => 0,
        10 => 0,
        9 => 0,
      ),
    ),
    'fields' => array(
      'title_field' => 'title_field',
      'field_acroym' => 'field_acroym',
      'body:value' => 'body:value',
      'body:summary' => 'body:summary',
    ),
  );
  $overrides["views_view.studies_search.display|page_1|display_options|header|area|content"]["DELETED"] = TRUE;
  $overrides["views_view.studies_search.display|page_1|display_options|header|result"]["DELETED"] = TRUE;
  $overrides["views_view.variable_search.display|default|display_options|filters|search_api_views_fulltext|expose|description"] = 'use * and ? wildcards to search for partial words';

 return $overrides;
}
