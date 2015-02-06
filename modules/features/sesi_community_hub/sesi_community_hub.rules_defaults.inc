<?php
/**
 * @file
 * sesi_community_hub.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sesi_community_hub_default_rules_configuration() {
  $items = array();
  $items['rules_mail_group_admins'] = entity_import('rules_config', '{ "rules_mail_group_admins" : {
      "LABEL" : "Mail group admins",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "gau" : { "label" : "Group admin user", "type" : "user" },
        "group" : { "label" : "Group node id", "type" : "node" },
        "account" : { "label" : "New member", "type" : "user" },
        "profile" : { "label" : "User profile", "type" : "profile2" }
      },
      "ACTION SET" : [
        { "mail" : {
            "to" : "[gau:mail]",
            "subject" : "New group member [account:name]",
            "message" : "\\u003Cp\\u003EDear [gau:name],\\u003C\\/p\\u003E\\r\\n    \\r\\n\\u003Cp\\u003EUser \\u0027[account:name]\\u0027 requests membership for group \\u0027[group:title]\\u0027 in [group:url].\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\r\\n============\\u003Cbr\\u003E\\r\\nUser Details\\u003Cbr\\u003E\\r\\n============\\u003Cbr\\u003E\\r\\nUser ID: [account:uid]\\u003Cbr\\u003E\\r\\nUser Unique ID: [account:uuid]\\u003Cbr\\u003E\\r\\nUser Name: [account:name]\\u003Cbr\\u003E\\r\\nAccount Status: [account:status]\\u003Cbr\\u003E\\r\\nEmail: [account:mail]\\u003Cbr\\u003E\\r\\nFirst Name: [profile:field_profile_first_name]\\r\\nLast Name: [profile:field_profile_last_name]\\r\\nInstitution: [profile:field-profile-institution]\\r\\nDepartement: [profile:field-profile-department]\\r\\nTelephone: [profile:field-profile-telephone]\\r\\n\\u003C\\/p\\u003E\\r\\n\\u003Chr\\u003E    \\r\\n\\u003Cp\\u003EPlease check:\\r\\nPeople in group page:\\u003Cbr\\u003E\\r\\n[site:url]?q=group\\/node\\/[group:nid]\\/admin\\/people\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EEdit membership in group page: \\u003Cbr\\u003E\\r\\n[site:url]?q=group\\/node\\/[group:nid]\\/admin\\/people\\/edit-membership\\/[og-membership:id]\\u0026destination=group\\/node\\/[group:nid]\\/admin\\/people\\u003C\\/p\\u003E\\r\\n    ",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_test'] = entity_import('rules_config', '{ "rules_test" : {
      "LABEL" : "OG membership mail to group admins",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "custom rule action" ],
      "REQUIRES" : [ "rules", "sesi_rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "og_membership", "value" : [ "og-membership" ] },
            "PROVIDE" : { "variable_added" : { "ogm" : "OG Membership" } }
          }
        },
        { "sesi_rules_action_send_email_to_group_admins" : {
            "USING" : { "organic_group" : [ "ogm" ] },
            "PROVIDE" : { "membership" : { "membership" : "The membership record for the user and the group" } }
          }
        }
      ]
    }
  }');
  return $items;
}
