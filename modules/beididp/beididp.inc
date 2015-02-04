<?php
/**
 * @file
 * Various functions
 *
 * This file is largely based upon Drupal OpenID core and provides the
 * the actual authentication functionalities
 */

/**
 * OpenID extensions
 */
define('BEIDIDP_NS_AX', 'http://openid.net/srv/ax/1.0');

define('BEIDIDP_NS_PAPE', 'http://specs.openid.net/extensions/pape/1.0');
define('BEIDIDP_PAPE_MFP', 'http://schemas.openid.net/pape/policies/2007/06/multi-factor-physical');
define('BEIDIDP_PAPE_PR', 'http://schemas.openid.net/pape/policies/2007/06/phishing-resistant');

module_load_include('module', 'openid');
module_load_include('inc', 'openid');

module_load_include('inc', 'beididp', 'beididp.nrn');
module_load_include('inc', 'beididp', 'beididp.name');

/**
 * The initial step of OpenID authentication.
 *
 * This is responsible for the following:
 *  - Perform discovery on the claimed OpenID.
 *  - If possible, create an association with the Provider's endpoint.
 *  - Create the authentication request.
 *  - Perform the appropriate redirect.
 *
 * @param string $return_to
 *   The endpoint to return to from the OpenID Provider
 * @param array $form_values
 *   Login form values
 */
function beididp_begin($return_to = '', $form_values = array()) {
  drupal_session_start();

  $idp = variable_get_value('beididp_idp_url');
  $idp = openid_normalize($idp);

  $services = beididp_discovery($idp);
  if (empty($services)) {
    form_set_error('openid_identifier', t('Not a valid eID IDP service.'));
    watchdog('beididp', 'No services discovered on IDP @idp',
      array('@idp' => $idp), WATCHDOG_ERROR);
    return;
  }

  if (isset($services[0]['types']) && is_array($services[0]['types']) && in_array(OPENID_NS_2_0 . '/server', $services[0]['types'])) {
    // Store discovered info in the users' session.
    $_SESSION['beididp']['service']['uri'] = $services[0]['uri'];
    $_SESSION['beididp']['service']['version'] = 2;
    $_SESSION['beididp']['claimed_id'] = $idp;

    // Store login form values so we can pass them to user_authenticate
    $_SESSION['beididp']['user_login_values'] = $form_values;

    $op_endpoint = $services[0]['uri'];
    $assoc_handle = beididp_association($op_endpoint);

    $claimed_id = $identity = OPENID_NS_2_0 . '/identifier_select';
    $authn_request = beididp_authentication_request($claimed_id, $identity, $return_to, $assoc_handle);

    openid_redirect($op_endpoint, $authn_request);
  }
  else {
    form_set_error('openid_identifier', t('Not a valid eID service.'));
    watchdog('beididp', 'Error in service type from IDP @idp)',
      array('@idp' => $idp), WATCHDOG_ERROR);
  }
}


/**
 * Completes OpenID authentication.
 *
 * Validates returned data from the Belgian eID IDP / OpenID Provider.
 *
 * @return array
 *   Response values for further processing with
 *   $response['status'] set to one of 'success', 'failed' or 'cancel'.
 */
function beididp_complete() {
  $response = _openid_response();

  // Default to failed response.
  $response['status'] = 'failed';

  if (isset($_SESSION['beididp']['service']['uri']) && isset($_SESSION['beididp']['claimed_id'])) {
    $service = $_SESSION['beididp']['service'];
    $claimed_id = $_SESSION['beididp']['claimed_id'];
    unset($_SESSION['beididp']['service']);
    unset($_SESSION['beididp']['claimed_id']);
  }
  else {
    watchdog('beididp', 'Session variables beididp not set', array(), WATCHDOG_WARNING);
    return $response;
  }

  if (!isset($response['openid.mode'])) {
    watchdog('beididp', 'Response mode not set', array(), WATCHDOG_ERROR);
    return $response;
  }

  if ($response['openid.mode'] == 'cancel') {
    watchdog('beididp', 'Cancel response received (claimed ID = @id)',
      array('@id' => $claimed_id), WATCHDOG_WARNING);
    $response['status'] = 'cancel';

    return $response;
  }

  if (!beididp_verify_assertion($service, $response)) {
    watchdog('beididp', 'Assertion could not be verified (claimed ID = @id)',
      array('@id' => $claimed_id), WATCHDOG_ERROR);
    return $response;
  }

  $response['openid.claimed_id'] = openid_normalize($response['openid.claimed_id']);

  // If the returned Claimed Identifier is different from the one sent
  // to the OpenID Provider, we need to perform discovery.
  if ($response['openid.claimed_id'] != $claimed_id) {
    $services = beididp_discovery($response['openid.claimed_id']);
    $uris = array();

    foreach ($services as $discovered) {
      if (in_array(OPENID_NS_2_0 . '/server', $discovered['types']) || in_array(OPENID_NS_2_0 . '/signon', $discovered['types'])) {
        $uris[] = $discovered['uri'];
      }
    }

    if (!in_array($service['uri'], $uris)) {
      watchdog('beididp', 'Received ID @recv does not match claimed ID @id',
        array('@id' => $claimed_id, '@recv' => $response['openid.claimed_id']),
        WATCHDOG_ERROR);

      return $response;
    }
  }
  else {
    $response['openid.claimed_id'] = $claimed_id;
  }

  $response['status'] = 'success';

  // Optionally hash the claimed_id (since it contains Rijksregister Nummer).
  if (variable_get_value('beididp_beididp_hash_claimed_id') && isset($response['openid.claimed_id'])) {
    $response['openid.claimed_id'] = beididp_hash_rrn($response['openid.claimed_id']);
  }
  return $response;
}


/**
 * Perform discovery on a claimed ID to determine the OpenID provider endpoint.
 *
 * @param string $claimed_id
 *   The OpenID URL to perform discovery on.
 *
 * @return array
 *   Array of services discovered (including endpoint URI etc).
 */
function beididp_discovery($claimed_id) {
  $services = array();
  $url = @parse_url($claimed_id);

  if ($url['scheme'] === 'https') {
    $xrds = _openid_xrds_discovery($claimed_id);

    if (!isset($xrds) || empty($xrds)) {
      watchdog('beididp', 'No services discovered for @id',
        array('@id' => $claimed_id), WATCHDOG_ERROR);
    }
    $services = $xrds['services'];
  }
  else {
    drupal_set_message(t('Discovery scheme is not https'), 'error');
    watchdog('beididp', 'Discovery scheme is not in https for @id',
        array('@id' => $claimed_id), WATCHDOG_ERROR);
  }
  return $services;
}


/**
 * Get a recent association handle for an IDP.
 *
 * @param string $endpoint
 *   URL of the eID IDP endpoint.
 *
 * @return string
 *   Association handle or empty string.
 */
function beididp_assoc_recent($endpoint) {
  // Delete old associations.
  db_delete('beididp_association')
    ->where('created + expires_in < :time', array(':time' => REQUEST_TIME))
    ->execute();

  return db_query(
    "SELECT assoc_handle FROM {beididp_association} WHERE idp_endpoint_uri = :endpoint",
    array(':endpoint' => $endpoint))
    ->fetchColumn();
}

/**
 * Store IDP association.
 *
 * @param string $uri
 *   eID IDP endpoint.
 * @param array $response
 *   Array with association response of the eID IDP.
 */
function beididp_assoc_store($uri, $response) {
  db_insert('beididp_association')
    ->fields(array(
      'idp_endpoint_uri' => $uri,
      'session_type' => $response['session_type'],
      'assoc_handle' => $response['assoc_handle'],
      'assoc_type' => $response['assoc_type'],
      'expires_in' => $response['expires_in'],
      'mac_key' => $response['mac_key'],
      'created' => REQUEST_TIME,
    ))
    ->execute();
}

/**
 * Get association.
 *
 * @param string $endpoint
 *   EID IDP endpoint.
 * @param string $handle
 *   EID IDP association handle.
 *
 * @return DatabaseStatementInterface 
 *   Association object
 */
function beididp_assoc_get($endpoint, $handle) {
  return db_query(
    "SELECT * FROM {beididp_association} WHERE idp_endpoint_uri = :endpoint AND assoc_handle = :handle",
    array(':endpoint' => $endpoint, ':handle' => $handle))
    ->fetchObject();
}

/**
 * Delete IDP association.
 *
 * @param string $endpoint
 *   EID IDP endpoint.
 * @param string $handle
 *   Handle of the association.
 */
function beididp_assoc_del($endpoint, $handle) {
  db_delete('beididp_association')
    ->condition('idp_endpoint_uri', $endpoint)
    ->condition('assoc_handle', $handle)
    ->execute();
}
 
/**
 * POST a form url encoded HTTP request.
 *
 * @param string $url
 *   URL to POST the message to.
 * @param string $request
 *   Request to post.
 *
 * @return object
 *   Result of the request.
 */
function beididp_http_post($url, $request) {
  $message = _openid_encode_message(_openid_create_message($request));

  $options = array(
    'headers' => array('Content-Type' => 'application/x-www-form-urlencoded; charset=utf-8'),
    'method' => 'POST',
    'data' => $message,
  );
  return drupal_http_request($url, $options);
}

/**
 * Attempt to create a shared secret with the OpenID Provider.
 *
 * @param string $op_endpoint
 *   URL of the OpenID Provider endpoint.
 *
 * @return string
 *   The association handle.
 */
function beididp_association($op_endpoint) {
  $handle = beididp_assoc_recent($op_endpoint);

  if (empty($handle)) {
    $mod = OPENID_DH_DEFAULT_MOD;
    $gen = OPENID_DH_DEFAULT_GEN;
    $r = _openid_dh_rand($mod);
    $private = _openid_math_add($r, 1);
    $public = _openid_math_powmod($gen, $private, $mod);

    // If there is no existing association, then request one.
    $request = openid_association_request($public);
    $result = beididp_http_post($op_endpoint, $request);

    if (isset($result->error)) {
      return FALSE;
    }

    $response = _openid_parse_message($result->data);
    if (isset($response['mode']) && $response['mode'] == 'error') {
      return FALSE;
    }

    if ($response['session_type'] == 'DH-SHA1') {
      $spub = _openid_dh_base64_to_long($response['dh_server_public']);
      $enc_mac_key = base64_decode($response['enc_mac_key']);
      $shared = bcpowmod($spub, $private, $mod);
      $response['mac_key'] = base64_encode(_openid_dh_xorsecret($shared, $enc_mac_key));
    }
    beididp_assoc_store($op_endpoint, $response);
    $handle = $response['assoc_handle'];
  }
  return $handle;
}

/**
 * Authenticate a user or attempt registration.
 *
 * @param array $response
 *   Response values from the OpenID Provider.
 */
function beididp_authentication($response) {

  $identity = $response['openid.claimed_id'];
  $account = user_external_load($identity);
  $created = FALSE;
  
  
  if (isset($account->uid)) {
    
    // ----------------------------------------
    // Log user in when it's verified Mica user      
    // ----------------------------------------

    $verify = variable_get('user_email_verification', TRUE);
    if ($verify) {
      $verify = !variable_get_value('beididp_no_mail_verify');
    }

    if (!$verify || $account->login) {
      $state['values']['name'] = $account->name;
      user_login_name_validate(array(), $state);

      if (!form_get_errors()) {
        $form_state['uid'] = $account->uid;
        user_login_submit(array(), $form_state);
      }
    }
    else {
      drupal_set_message(t('You must validate your email address for this account before logging in via eID'));
    }
  }
  elseif (variable_get('user_register', USER_REGISTER_VISITORS)) {
    
    // ----------------------------------------
    // When user with eID is a new register, register him/her automatically as
    // Mica user and also automatically logged in  
    // ----------------------------------------
      
    $module = 'beididp';
      
    $ax_values = openid_extract_namespace($response, BEIDIDP_NS_AX, 'ax', TRUE);
    $nick = beididp_name_nick($ax_values['value.fname'], $ax_values['value.lname']);
    $pass = user_password();

    $userinfo = array(
      'name' => $nick,
      'pass' => user_password(),
      'init' => $nick,
      'status' => 1,
      'access' => REQUEST_TIME
    );   

    $account = user_save(drupal_anonymous_user(), $userinfo);
    
    // Terminate if an error occurred during user_save().
    if (!$account) {
      drupal_set_message(t("Error saving user account."), 'error');
      return;
    }
    
    user_set_authmaps($account, array("authname_$module" => $identity ));
    
    drupal_set_message(t('You must change your email address for future logins. Your current temporary password is: @pass ', array('@pass' => $pass)));
    
    $created = TRUE;
    
    // Log user in.
    $form_state['uid'] = $account->uid;
    user_login_submit(array(), $form_state);
    unset($_GET['destination']);
      
  }
  else {
    drupal_set_message(t('Only site administrators can create new user accounts.'), 'error');
  }
  
  drupal_goto();

}
  
/**
 * Authentication request.
 *
 * @param string $claimed_id
 *   Claimed ID.
 * @param string $identity
 *   Identity.
 * @param string $return_to
 *   URL to return to after authentication on the IDP.
 * @param string $assoc_handle
 *   Association handle.
 */
function beididp_authentication_request($claimed_id, $identity, $return_to = '', $assoc_handle = '') {
  global $language;
  $lang_name = $language->language;

  $request = array(
    'openid.ns' => OPENID_NS_2_0,
    'openid.ns.ui' => 'http://specs.openid.net/extensions/ui/1.0',
    'openid.ns.ax' => BEIDIDP_NS_AX,
    'openid.ns.pape' => BEIDIDP_NS_PAPE,
    'openid.mode' => 'checkid_setup',
    'openid.identity' => $identity,
    'openid.claimed_id' => $claimed_id,
    'openid.assoc_handle' => $assoc_handle,
    'openid.return_to' => $return_to,
    'openid.realm' => url('', array('absolute' => TRUE)),
    'openid.ui.lang' => $lang_name . '-BE',
    'openid.ax.mode' => 'fetch_request',
    'openid.ax.type.fname' => 'http://axschema.org/namePerson/first',
    'openid.ax.type.lname' => 'http://axschema.org/namePerson/last',
    'openid.ax.type.mname' => 'http://axschema.org/namePerson/middle',
    'openid.ax.required' => 'fname,lname',
    'openid.ax.if_available' => 'mname',
    'openid.pape.preferred_auth_policies' => BEIDIDP_PAPE_MFP . ' ' . BEIDIDP_PAPE_PR,
  );
  return $request;
}

/**
 * Attempt to verify the response received from the OpenID Provider.
 *
 * @param string $service
 *   The OpenID Provider URL.
 * @param array $response
 *   Array of response values from the provider.
 *
 * @return bool
 *   Boolean
 */
function beididp_verify_assertion($service, $response) {
  $valid = FALSE;
  $association = FALSE;
  $op_endpoint = $service['uri'];

  if (!beididp_verify_assertion_nonce($op_endpoint, $response)) {
    return FALSE;
  }

  if (!beididp_verify_assertion_pape($response)) {
    return FALSE;
  }

  if (!openid_verify_assertion_return_url($op_endpoint, $response)) {
    watchdog('beididp', 'Return_to URL @url assertion failed',
      array('@url' => $response['openid.return_to']), WATCHDOG_ERROR);
    return FALSE;
  }

  // If the OP returned a openid.invalidate_handle, we have to proceed with
  // direct verification: ignore the openid.assoc_handle, even if present.
  if (!empty($response['openid.assoc_handle']) && empty($response['openid.invalidate_handle'])) {
    $association = beididp_assoc_get($op_endpoint, $response['openid.assoc_handle']);
  }

  if ($association && isset($association->session_type)) {
    $valid = openid_verify_assertion_signature($service, $association, $response);
    if (!$valid) {
      watchdog('beididp', 'Invalid association signature (handle = @handle)',
        array('@handle' => $response['openid.assoc_handle']),
        WATCHDOG_ERROR);
    }
  }
  else {
    // The verification requests contain all the fields from the response,
    // except openid.mode.
    $request = $response;
    $request['openid.mode'] = 'check_authentication';

    $result = beididp_http_post($op_endpoint, $request);

    if (!isset($result->error)) {
      $response = _openid_parse_message($result->data);
      if (drupal_strtolower(trim($response['is_valid'])) == 'true') {
        $valid = TRUE;
        if (!empty($response['invalidate_handle'])) {
          // This association handle has expired on the OP side, remove it.
          beididp_assoc_del($op_endpoint, $response['invalidate_handle']);
        }
      }
      else {
        watchdog('beididp', 'Association error @code @err (claimed id @id)',
          array('@err' => $result->error, '@code' => $result->code,
            '@id' => $response['openid.claimed_id']), WATCHDOG_ERROR);
        $valid = FALSE;
      }
    }
  }

  // Additional checks.
  if ($valid) {
    $results = module_invoke_all('beididp_verify_assert', $response);
    if ((!empty($results)) && in_array(FALSE, $results)) {
      watchdog('beididp', 'Additional verification failed (claimed id @id)',
        array('@id' => $response['openid.claimed_id']), WATCHDOG_ERROR);
      $valid = FALSE;
    }
  }
  return $valid;
}


/**
 * Record that this nonce was used.
 *
 * @param string $nonce
 *   The nonce.
 * @param string $uri
 *   EID identity URL.
 * @param int $expires
 *   Timestamp when nonce should expire.
 */
function beididp_nonce_store($nonce, $uri, $expires) {
  $record = array(
    'idp_endpoint_uri' => $uri,
    'nonce' => $nonce,
    'expires' => $expires,
  );
  drupal_write_record('beididp_nonce', $record);
}

/**
 * Count the number of times a nonce is used.
 * If the number > 1, then it is probably a replay attack.
 *
 * @param string $nonce
 *   The nonce.
 * @param string $url
 *   EID identity URL.
 */
function beididp_nonce_count($nonce, $url) {
  return db_query(
    "SELECT COUNT(*) FROM {beididp_nonce} WHERE nonce = :nonce AND idp_endpoint_uri = :uri",
    array(':nonce' => $nonce, ':uri' => $url))
    ->fetchColumn();
}

/**
 * Delete expired nonces.
 *
 * @return int
 *   Number of nonces deleted.
 */
function beididp_nonce_purge() {
  return db_delete('beididp_nonce')
    ->condition('expires', REQUEST_TIME, '<')
    ->execute();
}

/**
 * Verify nonce.
 *
 * @param array $service
 *   Service
 * @param array $response
 *   OpenID response
 *
 * @return bool
 *   Boolean
 */
function beididp_verify_assertion_nonce($service, $response) {
  $nonce = $response['openid.response_nonce'];

  if (preg_match('/^(\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2}):(\d{2})Z/', $nonce, $matches)) {
    list(, $year, $month, $day, $hour, $minutes, $seconds) = $matches;
    $nonce_stamp = gmmktime($hour, $minutes, $seconds, $month, $day, $year);
  }
  else {
    watchdog('beididp', 'Nonce from @endpoint rejected because it is not correctly formatted, nonce: @nonce.',
      array('@endpoint' => $service, '@nonce' => $nonce), WATCHDOG_ERROR);
    return FALSE;
  }

  // A nonce with a timestamp too far in the past or future will already have
  // been removed and cannot be checked for single use anymore.
  $time = time();
  $expiry = 900;
  if ($nonce_stamp <= $time - $expiry || $nonce_stamp >= $time + $expiry) {
    watchdog('beididp', 'Nonce received from @endpoint is out of range (time difference: @intervals). Check possible clock skew.',
      array('@endpoint' => $service, '@interval' => $time - $nonce_stamp), WATCHDOG_ERROR);
    return FALSE;
  }

  beididp_nonce_store($nonce, $service, $nonce_stamp + $expiry);
  if (beididp_nonce_count($nonce, $service) == 1) {
    return TRUE;
  }
  else {
    watchdog('beididp', 'Nonce replay attempt blocked from @ip, service: @service, nonce: @nonce.',
      array('@ip' => ip_address(), '@service' => $service, '@nonce' => $nonce), WATCHDOG_CRITICAL);
    return FALSE;
  }
}

/**
 * Verify PAPE in response.
 *
 * @param array $response
 *   IDP Response
 *
 * @return bool
 *   Bool
 */
function beididp_verify_assertion_pape($response) {
  $pape = openid_extract_namespace($response, BEIDIDP_NS_PAPE, 'pape', TRUE);
  if (!empty($pape)) {
    $policies = explode(' ', $pape['auth_policies']);

    if (in_array(BEIDIDP_PAPE_MFP, $policies, TRUE) && in_array(BEIDIDP_PAPE_PR, $policies, TRUE)) {
      return TRUE;
    }
  }
  watchdog('beididp_pape', 'PAPE policies not supported (claimed id @id)',
    array('@id' => $response['openid.claimed_id']), WATCHDOG_ERROR);
  return FALSE;
}
