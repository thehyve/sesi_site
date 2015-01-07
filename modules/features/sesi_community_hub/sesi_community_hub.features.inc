<?php
/**
 * @file
 * sesi_community_hub.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_community_hub_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sesi_community_hub_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function sesi_community_hub_field_default_field_instances_alter(&$data) {
  if (isset($data['node-community_document-og_group_ref'])) {
    $data['node-community_document-og_group_ref']['settings']['behaviors']['prepopulate'] = array(
      'action' => 'none',
      'action_on_edit' => 0,
      'fallback' => 'redirect',
      'providers' => array(
        'og_context' => 0,
        'token_patterns' => 0,
        'url' => 1,
      ),
      'skip_perm' => 0,
      'status' => 1,
      'token_patterns' => '',
    ); /* WAS: '' */
  }
  if (isset($data['node-dataset-og_group_ref'])) {
    $data['node-dataset-og_group_ref']['settings']['behaviors']['prepopulate'] = array(
      'action' => 'none',
      'action_on_edit' => 0,
      'fallback' => 'redirect',
      'providers' => array(
        'og_context' => 0,
        'token_patterns' => 0,
        'url' => 1,
      ),
      'skip_perm' => 0,
      'status' => 1,
      'token_patterns' => '',
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_image_default_styles().
 */
function sesi_community_hub_image_default_styles() {
  $styles = array();

  // Exported image style: mini_thumbnail.
  $styles['mini_thumbnail'] = array(
    'name' => 'mini_thumbnail',
    'label' => 'Mini thumbnail',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 40,
          'height' => 40,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
