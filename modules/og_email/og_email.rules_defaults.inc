<?php

/**
* Implements hook_default_rules_configuration().
*/
function og_email_default_rules_configuration() {
  $items = array();
  $items['rules_og_email_member_active'] = entity_import('rules_config', '{ "rules_og_email_member_active" : {
    "LABEL" : "OG member subscribe (Active, HTML)",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "REQUIRES" : [ "rules", "og" ],
    "ON" : [ "og_user_insert" ],
    "IF" : [
      { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
      { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
    ],
    "DO" : [
      { "variable_add" : {
          "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
          "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
        }
      },
      { "variable_email_mail" : {
          "to" : [ "account:mail" ],
          "variable" : "og_email_member_active_[mail_part]",
          "language" : "default"
        }
      },
      { "variable_email_mail" : {
          "to" : [ "group:author:mail" ],
          "variable" : "og_email_admin_active_[mail_part]",
          "language" : "default"
        }
      }
    ]
  }
}');
  $items['rules_og_email_member_pending'] = entity_import('rules_config', '{ "rules_og_email_member_pending" : {
      "LABEL" : "OG member subscribe (Pending, HTML)",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "variable_email", "og" ],
      "ON" : [ "og_user_insert" ],
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "variable_email_mail" : {
            "to" : [ "account:mail" ],
            "variable" : "og_email_member_pending_[mail_part]",
            "language" : "default"
          }
        },
        { "variable_email_mail" : {
            "to" : [ "group:author:mail" ],
            "variable" : "og_email_admin_pending_[mail_part]",
            "language" : "default"
          }
        }
      ]
    }
  }');

  $items['rules_og_email_new_content'] = entity_import('rules_config', '{ "rules_og_email_new_content" : {
    "LABEL" : "OG new content notification (HTML)",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "REQUIRES" : [ "og", "rules" ],
    "ON" : [ "node_insert" ],
    "IF" : [ { "og_entity_is_group_content" : { "entity" : [ "node" ] } } ],
    "DO" : [
      { "og_get_members" : {
          "USING" : { "group_content" : [ "node" ] },
          "PROVIDE" : { "group_members" : { "group_members" : "List of group members" } }
        }
      },
      { "LOOP" : {
          "USING" : { "list" : [ "group-members" ] },
          "ITEM" : { "list_item" : "Current list item" },
          "DO" : [
            { "variable_email_mail" : {
                "to" : [ "list-item:mail" ],
                "variable" : "og_email_new_content_[mail_part]",
                "language" : "default"
              }
            }
          ]
        }
      }
    ]
  }
}');
  return $items;
}
