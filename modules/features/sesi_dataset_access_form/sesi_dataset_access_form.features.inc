<?php
/**
 * @file
 * sesi_dataset_access_form.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sesi_dataset_access_form_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function sesi_dataset_access_form_node_info() {
  $items = array(
    'data_access_request_form' => array(
      'name' => t('Data Access Request Form'),
      'base' => 'node_content',
      'description' => t('Request for data access form '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_pet().
 */
function sesi_dataset_access_form_default_pet() {
  $items = array();
  $items['pet_data_access_request'] = entity_import('pet', '{
    "name" : "pet_data_access_request",
    "title" : "pet_data_access_request",
    "subject" : "CMI Request for Access to Dataset",
    "mail_body" : "Request for access to samples and data to following:\\r\\n========================================\\r\\nQuery URI: __QUERY_URI__\\r\\nDataset: __DATASET__\\r\\nMessage:\\r\\n__MESSAGE__\\r\\n\\r\\nUser Details:\\r\\n==========\\r\\nUser Unique ID: [current-user:uuid]\\r\\nUser Name: [current-user:name]\\r\\nAccount Status: [current-user:status]\\r\\nFirst Name: [current-user:profile-main:field_profile_first_name]\\r\\nLast Name: [current-user:profile-main:field-profile-last-name]\\r\\nInstitution: [current-user:profile-main:field-profile-institution]\\r\\nDepartement: [current-user:profile-main:field-profile-department]\\r\\nTelephone: [current-user:profile-main:field-profile-telephone]\\r\\nReal Name: [current-user:realname]\\r\\nE-mail: [current-user:mail]\\r\\nActive Membership: [current-user:og_user_node]\\r\\n\\r\\n",
    "mail_body_plain" : null,
    "send_plain" : "0",
    "from_override" : "",
    "cc_default" : "",
    "bcc_default" : "",
    "recipient_callback" : "",
    "rdf_mapping" : []
  }');
  return $items;
}
