<?php
/**
 * @file
 * sesi_og_email.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sesi_og_email_default_rules_configuration() {
  $items = array();
  $items['rules_user_membership_approved'] = entity_import('rules_config', '{ "rules_user_membership_approved" : {
      "LABEL" : "User membership approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "variable_email", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "variable_email_mail" : {
            "to" : "[account:mail]",
            "variable" : "og_email_member_active_[mail_part]",
            "language" : "default"
          }
        }
      ]
    }
  }');
  return $items;
}
