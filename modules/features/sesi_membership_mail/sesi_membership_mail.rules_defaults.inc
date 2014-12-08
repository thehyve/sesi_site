<?php
/**
 * @file
 * sesi_membership_mail.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sesi_membership_mail_default_rules_configuration() {
  $items = array();
  $items['rules_user_membership_approved'] = entity_import('rules_config', '{ "rules_user_membership_approved" : {
      "LABEL" : "User membership approved",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_user_approved" ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Membership approved",
            "message" : "Dear [account:name],\\r\\n\\r\\nYour membership of the group has been approved.\\r\\n\\r\\nthe [site:name] team"
          }
        },
        { "drupal_message" : { "message" : "1. [account:name]\\r\\n2. [account:og-user-node]\\r\\n3. [account:og_user_node]" } }
      ]
    }
  }');
  return $items;
}
