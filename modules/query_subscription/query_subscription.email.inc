<?php


function query_subscription_email($uid, $changes) {
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
    // Emails are only sent if the structure of the query has not changed, so descriptors for old and new values are the same.
    $descriptors = $subscription->descriptors();

    $variable_names = array('_all' => $ht('total'), 'total' => $ht('total'), '_matched' => $ht('matched'));
    foreach ($descriptors['term_variables'] as $tid => $var) {
      $variable_names[$tid] = $e($var->title);
    }

    $query_uri = entity_uri('mica_query', $query);
    $query_link = l($query->name ? : $ht("unnamed query"), $query_uri['path'], array('absolute' => TRUE));
    $dataset_link = l($descriptors['dataset']->title, 'node/'.$descriptors['dataset']->nid, array('absolute' => TRUE));
    $prevdate = $e($subscription->updated()->format("d-m-Y"));
    $curdate = $e(date('d-m-Y'));
    $old_matching = $e(array_sum(array_map(function($a) {return $a['_matched']['_all'];}, $change['old_values'])));
    $new_matching = $e(array_sum(array_map(function($a) {return $a['_matched']['_all'];}, $change['new_values'])));

    // we cannot use stylesheets in html mail, as many webmail systems such as gmail don't support it. Use inline styles.
    $th = "th style='text-align: left'";
    $td = "td style='padding: 0 .2em'";

    // The per-query header
    $data .= "<div style='margin: 1em 0 1em -.2em'><table>\n" .
      "  <tr><$th>{$ht('Query')}:</th><$td>$query_link</td></tr>\n" .
      "  <tr><$th>{$ht('Dataset')}:</th><$td>$dataset_link</td></tr>\n" .
      "  <tr><$th>{$ht('Date')}:</th><$td>$curdate</td></tr>\n" .
      "  <tr><$th>{$ht('Previous check date')}:</th><$td>$prevdate</td></tr>\n" .
      "  <tr><$th>{$ht('Total matching results')}:</th><$td>$new_matching</td></tr>\n" .
      "  <tr><$th>{$ht('Previous total matching results')}:</th><$td>$old_matching</td></tr>\n" .
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
        $cross_label = $descriptors['categories'][$difference['category']];
        $cross = $e("{$cross_name} = \"$cross_label\" ({$difference['category']})");
      }

      $data .= "<tr><$td>$study_name</td><$td>$variable_name</td><$td>$cross</td><$td>$old</td><$td>$new</td></tr>\n";
    }
    $data .= "</table></div><br>\n\n";

  }

  $body = <<<EOF
<h1 style="font-size: 120%">CMI data update notification</h1>

<p>You have asked to be notified of changes in saved queries at CMI. The following changes have been found:</p>

!data

<p style="font-size: 90%">!subscriptions_url</p>

<p style="font-size: 90%">!home_link</p>
EOF;

  // todo: link to user's queries page
  $subscriptions_url = l('View update notification settings', "node/590/queries", array('language' => $user->language, 'absolute' => TRUE));
  $home_link = l("CMI home page", '/', array('language' => $user->language, 'absolute' => TRUE));

  $message['subject'] = t('CMI data update notification', array(), array('langcode' => $user->language));
  $message['body'] = t($body,
    array('!data' => $data, '!subscriptions_url' => $subscriptions_url, '!home_link' => $home_link),
    array('langcode' => $user->language));
}
