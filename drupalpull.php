<?php
#!/usr/bin/env drush
/**
 * Enable a rule on the site.
 */
function drush_rules_enable() {
  $args = func_get_args();
  $rule_name = (!empty($args) && is_array($args)) ? array_shift($args) : '';
  if (empty($rule_name)) {
    return drush_set_error('', 'No rule name given.');
  }

  $rule = rules_config_load($rule_name);
  if (empty($rule)) {
    return drush_set_error('', dt('Could not load rule named "!rule-name".', array('!rule-name' => $rule_name)));
  }

  if (empty($rule->active)) {
    $rule->active = TRUE;
    $rule->save();
    drush_log(dt('The rule "!name" has been enabled.', array('!name' => $rule_name)), 'success');
  }
  else {
    drush_log(dt('The rule "!name" is already enabled.', array('!name' => $rule_name)), 'warning');
  }
}

print  "DRUPALPULL.PHP";

// ACTIVATES DEFAULT RULES

drush_rules_enable('rules_og_email_member_pending');
drush_rules_enable('rules_user_membership_approved');

// CLEAN SEARCH INDEX
drush_search_api_clear();

// SET HOMEPAGE to latest page called Mica
$query = new EntityFieldQuery();
$entities = $query->entityCondition('entity_type', 'node')
  ->propertyCondition('title', 'Mica')
  ->propertyCondition('status', 1)
  ->execute();

print "set new homepage";
if (!empty($entities['node'])) {
  $nid = array_pop(array_keys($entities['node']));
  variable_set("site_frontpage", "node/".$nid);
}
