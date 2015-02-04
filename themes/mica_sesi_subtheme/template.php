<?php


/**
 * Implements hook_bootstrap_based_theme().
 */
function mica_subtheme_bootstrap_based_theme() {
  return array('mica_subtheme' => TRUE);
}

/**
 * Check if we need to show page title or not.
 * 
 * Implements hook_process_page().
 */
function mica_subtheme_process_page(&$variables) {
    if (!isset($variables['node'])) {
        return;
    }
    
    if ($variables['node']->type != 'page') {
        return;
    }
         
    if(drupal_is_front_page()) {
        $variables['title'] = NULL;         
    }
}
