<?php
/**
 * @file
 * sesi_default_community.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function sesi_default_community_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'uid' => 1,
  'title' => 'GLOBAL',
  'log' => '',
  'status' => 1,
  'comment' => 1,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => 'ae66294b-03d9-4b93-a1dc-a5cde811a39c',
  'type' => 'default_community',
  'language' => 'en',
  'created' => 1415100709,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '36aa942a-6f7e-40e3-b95b-7a11a2e919c4',
  'revision_uid' => 0,
  'body' => array(
    'en' => array(
      0 => array(
        'value' => '<p>Global community.&nbsp;</p>
',
        'summary' => '',
        'format' => 'filtered_html',
        'safe_value' => '<p>Global community. </p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'group_access' => array(
    'und' => array(
      0 => array(
        'value' => 1,
      ),
    ),
  ),
  'group_group' => array(
    'und' => array(
      0 => array(
        'value' => 1,
      ),
    ),
  ),
  'group_register' => array(
    'und' => array(
      0 => array(
        'value' => 1,
      ),
    ),
  ),
  'rdf_mapping' => array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
  ),
  'cid' => 0,
  'last_comment_name' => NULL,
  'last_comment_uid' => 1,
  'comment_count' => 0,
  'print_display' => 1,
  'print_display_comment' => 0,
  'print_display_urllist' => 1,
  'name' => 'mica',
  'picture' => 0,
  'data' => 'b:0;',
  'date' => '2014-11-04 12:31:49 +0100',
);
  return $nodes;
}
