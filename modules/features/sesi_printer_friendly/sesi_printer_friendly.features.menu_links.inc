<?php
/**
 * @file
 * sesi_printer_friendly.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_printer_friendly_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/config/user-interface/print
  $menu_links['management:admin/config/user-interface/print'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/user-interface/print',
    'router_path' => 'admin/config/user-interface/print',
    'link_title' => 'Printer, email and PDF versions',
    'options' => array(
      'attributes' => array(
        'title' => 'Adds a printer-friendly version link to content and administrative pages.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/config/user-interface',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Printer, email and PDF versions');


  return $menu_links;
}
