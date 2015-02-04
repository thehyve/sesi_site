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
