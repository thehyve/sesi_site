<?php
/**
 * @file
 * sesi_notify_expirations.features.inc
 */

/**
 * Implements hook_default_pet().
 */
function sesi_notify_expirations_default_pet() {
  $items = array();
  $items['subscription_expiration_mail'] = entity_import('pet', '{
    "name" : "subscription_expiration_mail",
    "title" : "Subscription expiration mail",
    "subject" : "Membership of  __GROUPNAME__  expires within 7 days",
    "mail_body" : "Dear __SALUTATION__ __FIRSTNAME__ __LASTNAME__,\\r\\n\\r\\nWithin the next week your subscription of __GROUPNAME__ will end on __ENDDATE__.\\r\\nIf you need further access please contact the __GROUPNAME__ group administrator (__GROUP_ADM_MAIL__).\\r\\nPlease do not reply to this mail.\\r\\n\\r\\nBest regards,\\r\\nThe [site:name] team",
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
