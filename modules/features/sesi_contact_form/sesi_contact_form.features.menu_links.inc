<?php
/**
 * @file
 * sesi_contact_form.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sesi_contact_form_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/structure/contact
  $menu_links['management:admin/structure/contact'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/contact',
    'router_path' => 'admin/structure/contact',
    'link_title' => 'Contact form',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a system contact form and set up categories for the form to use.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/structure',
  );
  // Exported menu link: navigation:contact
  $menu_links['navigation:contact'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: navigation:node/add/contact
  $menu_links['navigation:node/add/contact'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/contact',
    'router_path' => 'node/add/contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => 'How to contact a person in an institution.',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'node/add',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Contact');
  t('Contact form');


  return $menu_links;
}
