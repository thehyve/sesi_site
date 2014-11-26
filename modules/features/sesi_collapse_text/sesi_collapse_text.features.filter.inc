<?php
/**
 * @file
 * sesi_collapse_text.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function sesi_collapse_text_filter_default_formats() {
  $formats = array();

  // Exported format: Bootstrap.
  $formats['bootstrap'] = array(
    'format' => 'bootstrap',
    'name' => 'Bootstrap',
    'cache' => 1,
    'status' => 1,
    'weight' => 30,
    'filters' => array(
      'collapse_text_filter' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'form' => 1,
          'default_title' => 'Click here to expand or collapse this section',
        ),
      ),
    ),
  );

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_url' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_html' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => -43,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(),
      ),
      'collapse_text_filter' => array(
        'weight' => -41,
        'status' => 1,
        'settings' => array(
          'form' => 1,
          'default_title' => 'Click here to expand or collapse this section',
        ),
      ),
    ),
  );

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 1,
    'filters' => array(
      'filter_url' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(),
      ),
      'collapse_text_filter' => array(
        'weight' => -41,
        'status' => 1,
        'settings' => array(
          'form' => 1,
          'default_title' => 'Click here to expand or collapse this section',
        ),
      ),
    ),
  );

  // Exported format: Plain text.
  $formats['plain_text'] = array(
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => 10,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_autop' => array(
        'weight' => -43,
        'status' => 1,
        'settings' => array(),
      ),
      'collapse_text_filter' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(
          'form' => 1,
          'default_title' => 'Click here to expand or collapse this section',
        ),
      ),
    ),
  );

  return $formats;
}
