<?php


function _query_subscription_email($uid, $changes) {
  $user = user_load($uid);
  if(empty($user)) {
    watchdog('query_subscription', 'Attempting to send notification mail non-existing user, uid @uid', array('@uid' => $uid), WATCHDOG_WARNING);
    return;
  }
  drupal_mail('query_subscription', 'notification', $user->mail, $user->language, array('user' => $user, 'changes' => $changes));
}


// implements hook_mail. What kind of monkey thought it was a good design to require constructing the message subject/body in a callback?!
function query_subscription_mail($key, &$message, $params) {
  if ($key !== 'notification') return;

  $user = $params['user'];
  $changes = $params['changes'];

  // translate to appropriate user's language and html escape function
  $ht = function($txt) use ($user) {
    // php 5.3, so there is no ENT_SUBSTITUTE, ENT_HTML401
    return htmlspecialchars(t($txt, array(), array('langcode' => $user->language)), ENT_QUOTES);
  };

  // html escape function
  $e = function($txt) {
    // php 5.3, so there is no ENT_SUBSTITUTE, ENT_HTML401
    return htmlspecialchars($txt, ENT_QUOTES);
  };

  // Build html containing tables with data on what changed
  $data = '';
  foreach($changes as $change) {
    $subscription = $change['subscription'];
    $query = $subscription->query();
    $descriptors = $change['descriptors'];

    $variable_names = array('_all' => $ht('total'), 'total' => $ht('total'), '_matched' => $ht('matched'));
    foreach ($descriptors['term_variables'] as $tid => $var) {
      $variable_names[$tid] = $e($var->title);
    }

    $query_url = $e(call_user_func_array('url', entity_uri('mica_query', $query)));
    $query_name = $e($query->name) ? : $ht("unnamed query");
    $dataset_name = $e($descriptors['dataset']->title);
    $prevdate = $e($subscription->updated()->format("d-m-Y"));

    // we cannot use stylesheets in html mail, as many webmail systems such as gmail don't support it.
    $th = "th style='text-align: left'";
    $td = "td style='padding: 0 .2em'";

    // The per-query header
    $data .= "<div style='margin: 1em 0 1em -.2em'><table>\n" .
      "  <tr><$th>{$ht('Query')}:</th><$td><a href=\"$query_url\">$query_name</a></td></tr>\n" .
      "  <tr><$th>{$ht('Dataset')}:</th><$td>$dataset_name</td></tr>\n" .
      "  <tr><$th>{$ht('Previous check date')}:</th><$td>$prevdate</td></tr>\n" .
      "</table></div><br>\n\n";

    $th = "th style='padding: .2em .5em'";
    $td = "td style='padding: .2em .5em; text-align: center'";

    // The changes for this query
    $data .= "<div style='margin: 1em 0 2em -.2em'><table>\n" .
      "<tr><$th>{$ht('Study')}</th><$th>{$ht('Variable')}</th><$th>{$ht('Cross Category')}</th><$th>{$ht('Old value')}</th><$th>{$ht('New value')}</th></tr>\n";
    foreach ($change['differences'] as $difference) {

      $study_name = $e($descriptors['studies'][$difference['connection']]->title);
      $variable_name = $e($variable_names[$difference['term']]);
      $old = $difference['old_value'];
      $new = $difference['new_value'];

      if ($difference['category'] === '_all') {
        $cross = '&nbsp;';
      } else {
        $cross_name = $descriptors['cross_variable']->title;
        $cross = $e("{$cross_name} = {$difference['category']}");
      }

      $data .= "<tr><$td>$study_name</td><$td>$variable_name</td><$td>$cross</td><$td>$old</td><$td>$new</td></tr>\n";
    }
    $data .= "</table></div><br>\n\n";

  }

  $subscriptions_url = 'http://localhost:7880/mica/?q=node/590/queries';

  $body = <<<EOF
<h1 style="font-size: 120%">CMI data update notification</h1>

<p>You have asked to be notified of changes in saved queries at CMI. The following changes have been found:</p>

!data

<p style="font-size: small"><a href="@subscriptions_url">View update notification settings</a></p>
EOF;


  $message['subject'] = t('CMI data update notification', array(), array('langcode' => $user->language));
  $message['body'] = t($body, array('!data' => $data, '@subscriptions_url' => $subscriptions_url), array('langcode' => $user->language));
  //$message['headers']['Content-Type'] = 'text/html; charset=UTF-8';

  //drupal_mail('query_subscription', 'notification', $user->mail, $user->language, $params);
}
