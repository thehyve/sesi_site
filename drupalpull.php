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

/*
 * Set a default value of 0 ('no') for the required field_validate_past_date on variables. If the field does not
 * exist for an existing variable that will cause errors.
 */
function fix_default_on_variable_past_date_field() {

  $variables = db_query("select n.nid, n.vid from {node} n left join {field_data_field_validate_past_date} f
                            on n.nid = f.entity_id
                            where n.type = 'variable'
                              and f.field_validate_past_date_value is NULL")
    ->fetchAllKeyed();

  watchdog('sesi_variable_form', "Setting default value of 0 for field_validate_past_date on @c variables",
    array('@c' => count($variables)), WATCHDOG_INFO);

  foreach ($variables as $nid => $vid) {
    $fields = array(
      'entity_type' => 'node',
      'bundle' => 'variable',
      'deleted' => 0,
      'entity_id' => $nid,
      'revision_id' => $vid,
      'language' => LANGUAGE_NONE,
      'delta' => 0,
      'field_validate_past_date_value' => 0,
    );
    db_insert('field_data_field_validate_past_date')
      ->fields($fields)
      ->execute();
    db_insert('field_revision_field_validate_past_date')
      ->fields($fields)
      ->execute();
  }
}


print  "DRUPALPULL.PHP";

// Apply a fix for the validate_past_date field

fix_default_on_variable_past_date_field();

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
