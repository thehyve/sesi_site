<?php
/**
 * @file
 * Functions for validating and hashing National Registry Number.
 */

define('BEIDIDP_PREFIX', 'pUJ122deM0');
define('BEIDIDP_SUFFIX', 'gwct5ZopY7');

/**
 * Hash unique National Registry Number.
 *
 * Storing the NRN without permission of the Privacy Commission may violate 
 * Belgian law. Please consult a legal expert.
 *
 * @param string $plain
 *   NRN in plain text
 *
 * @return string
 *   Hashed NRN
 */
function beididp_hash($plain) {
  // Change these variables in settings.php
  $prefix = variable_get('beididp_hash_prefix', BEIDIDP_PREFIX);
  $suffix = variable_get('beididp_hash_suffix', BEIDIDP_SUFFIX);
  return sha1($prefix . $plain . $suffix);
}

/**
 * Hash the citizen's unique National Registry Number.
 *
 * @param string $claimed_id
 *   URL containing the (unhashed) NRN
 *
 * @return string
 *   URL containing the hashed NRN
 */
function beididp_hash_rrn($claimed_id) {
  $pattern = "/(.+\?)(\d{11})$/";

  if (preg_match($pattern, $claimed_id, $matches) > 0 && is_array($matches) && count($matches) == 3) {
    $hash = $matches[1] . beididp_hash($matches[2]);
  }
  else {
    $hash = beididp_hash($claimed_id);
  }

  return $hash;
}

/**
 * Parse a string and verify if it is a valid NRN.
 *
 * @param string $string
 *   String to be parsed
 *
 * @return string|bool
 *   Numeric string with NRN or FALSE if no valid NRN was found.
 */
function beididp_nrn_parse($string) {
  // Remove punctuation, spaces ...
  $nrn = preg_replace('/\D/', '', $string);

  if (strlen($nrn) != 11) {
    return FALSE;
  }
  list($yr, $month, $day, $count, $check) = sscanf($nrn, '%2d%2d%2d%3d%2d');

  // Basic check, note that month and day can actually be zero.
  if (!checkdate(max($month, 1), max($day, 1), 1900 + $yr)) {
    // Year 1900/2000 only makes a difference for those born on 29 Feb 2000
    if (!($month == 2 && $day == 29 && $yr == 00)) {
      return FALSE;
    }
  }

  // Verify checksum.
  $div = substr($nrn, 0, 9);
  $calc = 97 - round(fmod($div, 97));

  if ($check != $calc) {
    // Perhaps born in or after year 2000
    $calc = 97 - round(fmod('2' . $div, 97));
    if ($check != $calc) {
      return FALSE;
    }
  }
  return $nrn;
}
