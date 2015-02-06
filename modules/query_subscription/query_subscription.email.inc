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

  // format link as html anchor with translation
  $l = function($txt, $link) use ($user) {
    return l($txt, $link, array('language' => $user->language, 'absolute' => true));
  };

  // Build html containing tables with data on what changed
  /*
   * Todo: group queries by dataset. Per-dataset information such as new/removed studies or expirations should only be
   * shown once instead of for every query affected. The $changes array already has this grouping but we don't do
   * anything with it now.
   */
  $datasets_html = '';
  $datasets_expired_html = '';
  $datasets_expired = array();
  foreach($changes as $dschanges) foreach($dschanges as $change) {
    $data = '';
    $subscription = $change['subscription'];
    $query = $subscription->query();
    // Emails are only sent if the structure of the query has not changed, so descriptors for old and new values are the same.
    $descriptors = $subscription->descriptors();

    $expiration_date = $old_matching = $new_matching = $old_cardinality = $new_cardinality = null;
    $studies_added_links = $studies_removed_links = array();
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
      $differences = $change['differences'];

      $old_matching = $e($differences['old_matched']);
      $new_matching = $e($differences['new_matched']);

      if(isset($differences['old_cardinality'])) {
        $old_cardinality = $e($differences['old_cardinality']);
        $new_cardinality = $e($differences['new_cardinality']);
      }

      foreach($differences['studies_added'] as $conn_id) {
        $study = QuerySubscription::study_for_connection_id($conn_id);
        $studies_added_links[] = $l($study->title, 'node/'.$study->nid);
      }
      foreach($differences['studies_removed'] as $conn_id) {
        $study = QuerySubscription::study_for_connection_id($conn_id);
        $studies_removed_links[] = $l($study->title, 'node/'.$study->nid);
      }
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
      if(count($studies_added_links) > 0) {
        $studies_list = implode('<br>', $studies_added_links);
        $data .= "  <tr><$th>{$ht('New Studies')}:</th><$td>$studies_list</td></tr>\n";
      }
      if(count($studies_removed_links) > 0) {
        $studies_list = implode('<br>', $studies_removed_links);
        $data .= "  <tr><$th>{$ht('Removed Studies')}:</th><$td>$studies_list</td></tr>\n";
      }

    } else {
      $data .= "<tr><$th>{$ht('Expiration date')}:</th><$td>$expiration_date</td>\n";
    }
    $data .= "</table></div><br>\n\n";

    if($expired) {
      $datasets_expired_html .= $data;
      continue;
    }

    $th = "th style='text-align: left'";
    $td = "td style='padding: 0 1em; text-align: center'";
    $italic = function($txt) {return "<span style='font-style: italic;'>$txt</span>";};

    // changes in values
    $data .= "<div style='margin: .5em 0 1em -1em'><table>\n" .
      "  <tr><$th></th><$td>{$italic($prevdate)}</td><$td>{$italic($ht('Now'))}</td></tr>\n";

    $cross_ids = array_diff(array_keys($change['old_values']['_all']['_matched']), array('_all', '_cardinality'));
    if(empty($cross_ids)) {
      $old = $old_matching;
      $new = $new_matching;
    } else {
      $olds = $news = array();
      foreach($change['old_values']['_all']['_matched'] as $cross_cat => $value) {
        if(in_array($cross_cat, array('_all', '_cardinality'))) continue;
        $cross_label = $descriptors['categories'][$cross_cat];
        $olds[] = $e("\"$cross_label\" ({$cross_cat}): $value");
      }
      $olds[] = $ht("Total").": $old_matching";
      if(!is_null($old_cardinality)) {
        $olds[] = $ht("No. of Patients").": $old_cardinality";
      }
      foreach($change['new_values']['_all']['_matched'] as $cross_cat => $value) {
        if(in_array($cross_cat, array('_all', '_cardinality'))) continue;
        $cross_label = $descriptors['categories'][$cross_cat];
        $news[] = $e("\"$cross_label\" ({$cross_cat}): $value");
      }
      $news[] = $ht("Total").": $new_matching";
      if(!is_null($new_cardinality)) {
        $news[] = $ht("No. of Patients").": $new_cardinality";
      }

      $old = implode('<br>', $olds);
      $new = implode('<br>', $news);
    }

    $data .=
      "  <tr><$th>{$ht('Total Matching Results')}:</th><$td>$old</td><$td>$new</td></tr>\n";

    if(isset($differences['old_cardinality'])) {
      $data .=
        "  <tr><$th>{$ht('Total Matching no. of Patients')}:</th><$td>$old_cardinality</td><$td>$new_cardinality</td></tr>\n";
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
