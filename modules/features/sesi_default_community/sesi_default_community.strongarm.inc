<?php
/**
 * @file
 * sesi_default_community.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sesi_default_community_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'uuid_features_entity_node';
  $strongarm->value = array(
    'default_community' => 'default_community',
    'article' => 0,
    'page' => 'page',
    'blog' => 0,
    'community' => 0,
    'community_document' => 0,
    'contact' => 0,
    'data_access_request' => 0,
    'data_access_review' => 0,
    'data_collection_event' => 0,
    'dataset' => 0,
    'documents' => 0,
    'event' => 0,
    'field_description' => 0,
    'forum' => 0,
    'panel' => 0,
    'population' => 0,
    'project' => 0,
    'publication' => 0,
    'study' => 0,
    'study_variable_attributes' => 0,
    'teleconference' => 0,
    'variable' => 0,
  );
  $export['uuid_features_entity_node'] = $strongarm;

  return $export;
}
