<?php

// implements hook_mail. What kind of monkey thought it was a good design to require constructing the message subject/body in a callback?!
function query_subscription_mail($key, &$message, $params) {
  if ($key !== 'notification') return;

  $user = $params['user'];
  $changes = $params['changes'];

  watchdog('query_subscription', "Sending notification mail to @email (uid @uid)",
    array('@email' => $user->mail, '@uid' => $user->uid), WATCHDOG_INFO);

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

  $l = function($txt, $link) use ($user) {
    return l($txt, $link, array('language' => $user->language, 'absolute' => true));
  };

  // Build html containing tables with data on what changed
  $datasets_html = '';
  $datasets_expired_html = '';
  $datasets_expired = array();
  foreach($changes as $change) {
    $data = '';
    $subscription = $change['subscription'];
    $query = $subscription->query();
    // Emails are only sent if the structure of the query has not changed, so descriptors for old and new values are the same.
    $descriptors = $subscription->descriptors();

    $variable_names = array('_all' => $ht('total'), 'total' => $ht('total'), '_matched' => $ht('matched'));
    foreach ($descriptors['term_variables'] as $tid => $var) {
      $variable_names[$tid] = $e($var->title);
    }

    $expiration_date = $old_matching = $new_matching = null;
    $query_uri = entity_uri('mica_query', $query);
    $query_link = $l($query->name ? : $ht("unnamed query"), $query_uri['path']);
    $dataset_link = $l($descriptors['dataset']->title, 'node/'.$descriptors['dataset']->nid);
    $prevdate = $e($subscription->updated()->format("d-m-Y"));
    $curdate = $e(date('d-m-Y'));
    $expired = $change['expired'];
    if ($expired) {
      $expiration_date = $e($descriptors['dataset_expiration_date']->format('d-m-Y'));
      $datasets_expired[$dataset_link] = 1;
    } else {
      $old_matching = $e($change['old_values']['_matched_sum']);
      $new_matching = $e($change['new_values']['_matched_sum']);
    }

    // we cannot use stylesheets in html mail, as many webmail systems such as gmail don't support it. Use inline styles.
    $th = "th style='text-align: left'";
    $td = "td style='padding: 0 .2em'";

    // The per-query header
    $data .= "<div style='margin: 1em 0 1em -.2em'><table>\n" .
      "  <tr><$th>{$ht('Query')}:</th><$td>$query_link</td></tr>\n" .
      "  <tr><$th>{$ht('Dataset')}:</th><$td>$dataset_link</td></tr>\n" .
      "  <tr><$th>{$ht('Date')}:</th><$td>$curdate</td></tr>\n" .
      "  <tr><$th>{$ht('Previous check date')}:</th><$td>$prevdate</td></tr>\n";
    if (!$expired) {
      $data .=
        "  <tr><$th>{$ht('Total matching results')}:</th><$td>$new_matching</td></tr>\n" .
        "  <tr><$th>{$ht('Previous total matching results')}:</th><$td>$old_matching</td></tr>\n";
    } else {
      $data .= "<tr><$th>{$ht('Expiration date')}:</th><$td>$expiration_date</td>\n";
    }
    $data .= "</table></div><br>\n\n";

    if($expired) {
      $datasets_expired_html .= $data;
      continue;
    }


    $th = "th style='padding: .2em .5em'";
    $td = "td style='padding: .2em .5em; text-align: center'";

    // The changes for this query
    $data .= "<div style='margin: 1em 0 2em -.2em'><table>\n" .
      "<tr><$th>{$ht('Study')}</th><$th>{$ht('Variable')}</th><$th>{$ht('Cross Category')}</th><$th>{$ht('Old value')}</th><$th>{$ht('New value')}</th></tr>\n";
    foreach ($change['differences'] as $difference) {

      $study = $descriptors['studies'][$difference['connection']];
      $study_link = $l($study->title, 'node/'.$study->nid);
      $variable_name = $e($variable_names[$difference['term']]);
      $old = $difference['old_value'];
      $new = $difference['new_value'];

      if ($difference['category'] === '_cardinality') {
        $variable_name .= ' ' . $ht("(no. of donors)");
      }

      if ($difference['category'] === '_all' || $difference['category'] === '_cardinality') {
        $cross = '&nbsp;';
      } else {
        $cross_name = $descriptors['cross_variable']->title;
        $cross_label = $descriptors['categories'][$difference['category']];
        $cross = $e("{$cross_name} = \"$cross_label\" ({$difference['category']})");
      }

      $data .= "<tr><$td>$study_link</td><$td>$variable_name</td><$td>$cross</td><$td>$old</td><$td>$new</td></tr>\n";
    }
    $data .= "</table></div><br>\n\n";

    $datasets_html .= $data;
  }

  $datasets_expired = array_keys($datasets_expired);
  if (count($datasets_expired) > 0) {
    $expired_notice = t(<<<EOF
<p><span style='font-weight: bold; font-size: 105%'>The following datasets have expired.</span>\n
You will no longer receive updates for queries on these datasets. New versions of datasets may be available:</p>\n
EOF
    , array(), array('langcode' => $user->language));
    $expired_notice .= "<ul>\n" . implode('', array_map(function($d) {return "<li>$d</li>\n";}, $datasets_expired)) . "</ul>\n\n";
  } else {
    $expired_notice = '';
  }

  $body = <<<EOF
<h1 style="font-size: 120%">CMI data update notification</h1>

<p>You have asked to be notified of changes in saved queries at CMI. The following changes have been found:</p>

!expired_notice
!data_expired
!data_html

<p style="font-size: 90%">!subscriptions_url</p>

<p style="font-size: 90%">!home_link</p>
EOF;

  $subscriptions_url = $l($ht('View update notification settings'), "my-queries");
  $home_link = $l($ht("CMI home page"), '/');

  $message['subject'] = t('CMI data update notification', array(), array('langcode' => $user->language));
  $message['body'] = t($body,
    array(
      '!expired_notice' => $expired_notice,
      '!data_expired' => $datasets_expired_html,
      '!data_html' => $datasets_html,
      '!subscriptions_url' => $subscriptions_url,
      '!home_link' => $home_link,
    ),
    array('langcode' => $user->language));
}
