<?php
/**
 * @file
 * sesi_dataset_access_form.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sesi_dataset_access_form_default_rules_configuration() {
  $items = array();
  $items['og_email_rules_send_dataset_request_email'] = entity_import('rules_config', '{ "og_email_rules_send_dataset_request_email" : {
      "LABEL" : "Send Dataset Access Form",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "og", "rules", "pet" ],
      "ON" : { "node_insert--data_access_request_form" : { "bundle" : "data_access_request_form" } },
      "IF" : [ { "og_entity_is_group_content" : { "entity" : [ "node" ] } } ],
      "DO" : [
        { "og_get_managers" : {
            "USING" : { "group_content" : [ "node" ] },
            "PROVIDE" : { "group_managers" : { "group_managers" : "List of group managers" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "group_managers" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "drupal_message" : { "message" : [ "list-item:mail" ], "type" : [ "" ] } },
              { "pet_action_send_pet" : {
                  "pet_name" : "data_request_access_email_",
                  "to_text" : [ "list-item:mail" ],
                  "to_account" : [ "" ],
                  "account_subs" : [ "" ],
                  "node_subs" : [ "" ]
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
