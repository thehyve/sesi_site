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
  'language' => 'und',
  'created' => 1415100709,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '36aa942a-6f7e-40e3-b95b-7a11a2e919c4',
  'revision_uid' => 0,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>Global Community.</p>
',
        'summary' => '',
        'format' => 'full_html',
        'safe_value' => '<p>Global Community.</p>
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
        'value' => 0,
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
  'picture' => 24,
  'data' => 'a:8:{s:5:"block";a:1:{s:8:"facetapi";a:46:{s:32:"a9LyUTOi1ffLzGTcQwh9xp8oRxCMeEKL";i:1;s:32:"awsaDlbzLwJuMcc68Z1Cf44LPAE8qXvc";i:1;s:32:"yA10jWhmiIxzbT1U06UOjm0CUcDpxcGq";i:1;s:32:"FRpHLnXH2QiUI7INyX15rV1ArZFUqSVh";i:1;s:32:"0Z4Ng4Ow36mLFVauhkPTJsv3nbDscCqj";i:1;s:32:"BxBx4CCHJOF008uP8gP1P0Ufgl541lEB";i:1;s:32:"oy34mXN1nxJL14Ut9ROdWqeRVEb48MjO";i:1;s:32:"TJAdc3wctJPQpY8BNihzClvpTTQHHOgi";i:1;s:32:"47KkgRkzgzY3GtmwWAHPRJeNpEGG6kLB";i:1;s:32:"veXBzdn9ld2b1QgqOG5E41eaj3tTkfqn";i:1;s:32:"2Mbw7FQjUohNsRdrLGPaX8SmsIIHGVSm";i:1;s:32:"UXQ7up5z8qtveA4ycXIY6NwLzLCby59I";i:1;s:32:"mq7MQYR1vElyxwLiucoVgd7bbSNoqusp";i:1;s:32:"oess7amOGLJ04KmUoKpUTzCNH0E20Bfk";i:1;s:32:"16q0DNBcFkVkFcJUhUJH7pdSs241UkS1";i:1;s:32:"eMZ7bL3ztSLP1awFXyiZtAZWHGIbsHk0";i:1;s:32:"bpv9CQJVwWZBA3J6nCH1UaaqlGFgCXZK";i:1;s:32:"sX8HQmvpLoksLI0rE4GqoVE1enpKyvHG";i:1;s:32:"Y2jUzmF8fK49hirSqsFb2077JN52TV83";i:1;s:32:"z0XiAO0D3Qin2ZDiDHx7IM2EzCursZc0";i:1;s:32:"XJUIzu1AA9SWO0c5RW7h7OIyJgACkiWA";i:1;s:32:"QxCe8fex6KpZTv7XN2DbAyx1BFXM5x9X";i:1;s:32:"1Uf8V0ASOkzjorT704EFxCx7kE0ntRLp";i:1;s:32:"OI5JoX61IF2G6w9TdOrS35Pn5r0mVPs0";i:1;s:32:"6tZH3VkoxMw4fmXJEk42Ct31RR37ET3C";i:1;s:32:"GH9lIqQBZkB15cKnWp0A1o2hsuNoVXy7";i:1;s:32:"1vPgYmVUltQDloo7E1KZ4hgvNEVqyx5p";i:1;s:32:"gbuUXtAXGOlsHY3buymRJDIRz8EmpueE";i:1;s:32:"Sn1YMwE54HNNg8AgxcSDTLelHLvDVLpE";i:1;s:32:"rIfS1oiHpBpZRnRjW1YjPfvtnkYAxMb5";i:1;s:32:"Zq7PpSDHZ7yiyMfUDGNq4AmUj9KR9QqU";i:1;s:32:"Lko0oF1TugEiAYfekUKzcEUjmMcYAjNX";i:1;s:32:"kuAauH4ZwcBENFQB682Gr8wNAIYSJ7IQ";i:1;s:32:"VtHarua11sVKjupu3NEeogm7P9Txjrjr";i:1;s:32:"XOuc1fKZWeI0Uq79bg0Jdk1Cqxynufjr";i:1;s:32:"fABDbsrHZSBHP8P34Ami6Kqo9b8SnD3U";i:1;s:32:"wG4i5Lu6TfAPWV3WRN8xbZRBpOQ0U6Tr";i:1;s:32:"AgeiuCPy9CAzCV3oCgPVkiNiOV7Z8IGd";i:1;s:32:"j8cx4BRyhJAVkkeH1zEnJhsuW2ARmpfT";i:1;s:32:"wuuSJH4Ls8avr4WWA0JVv1zbxqMLyc0e";i:1;s:32:"1PcMpiSpS9dUnvLtvgib9Q3VpCBnk2fn";i:1;s:32:"08VHfUt1FcDbNNN3e8e3ALFkgkOraV0P";i:1;s:32:"X0CsULWYGsOH1YEFmPaiNGrjbwq91ucq";i:1;s:32:"0YXGz425IAVYG5aKshpTRxgUyOmVnrkk";i:1;s:32:"XtBh4Jt1W0fjb2GI0lgUrvAvFOdk88A5";i:1;s:32:"yQQDQrXg6ob0w2HdpiMXRpDZo6qTXyXR";i:1;}}s:16:"ckeditor_default";s:1:"t";s:20:"ckeditor_show_toggle";s:1:"t";s:14:"ckeditor_width";s:4:"100%";s:13:"ckeditor_lang";s:2:"en";s:18:"ckeditor_auto_lang";s:1:"t";s:7:"contact";i:1;s:18:"htmlmail_plaintext";i:0;}',
  'date' => '2014-11-04 12:31:49 +0100',
);
  return $nodes;
}
