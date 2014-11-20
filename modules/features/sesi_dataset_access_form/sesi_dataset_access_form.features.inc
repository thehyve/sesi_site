<?php
/**
 * @file
 * sesi_dataset_access_form.features.inc
 */

/**
 * Implements hook_default_pet().
 */
function sesi_dataset_access_form_default_pet() {
  $items = array();
  $items['data_request_access_email_'] = entity_import('pet', '{
    "name" : "data_request_access_email_",
    "title" : "Data Request Access Email ",
    "subject" : "Request for Data Access",
    "mail_body" : "I have interest on this dataset. [webform:email-value]",
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
