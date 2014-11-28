<?php
/**
 * @file
 * sesi_homepage.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function sesi_homepage_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'uid' => 0,
  'title' => 'Mica',
  'log' => '',
  'status' => 1,
  'comment' => 1,
  'promote' => 0,
  'sticky' => 0,
  'vuuid' => '43ae4b4d-a64e-44c1-bbd7-384dee1736d0',
  'type' => 'page',
  'language' => 'und',
  'created' => 1415707515,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '95005024-b4f6-4c95-bc64-65a02af04633',
  'revision_uid' => 1,
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<div class="field-item even" property="content:encoded"><div class="home-panel">
	<div id="upper-container">
		<h1>CMI <span>- Center for Medical Innovation vzw</span></h1>
	</div>
	<div id="navcontainer">
		<ul>
			<li><a href="#"><i class="flaticon-medicine13"></i>Our Missions</a></li>
			<li><a href="#"><i class="flaticon-adn1"></i> Flemish Biobank</a></li>
			<li><a href="#"><i class="flaticon-molecules1"></i> Translational Research</a></li>
			<li><a href="#"><i class="flaticon-conference2"></i> For Donors</a></li>
			<li><a href="#"><span class="flaticon-medical55"></span> Catalogues</a></li>
		</ul>	
	</div>
</div>
<br>',
        'summary' => '',
        'format' => 'bootstrap',
        'safe_value' => '<div class="field-item even" property="content:encoded"><div class="home-panel">
	<div id="upper-container">
		<h1>CMI <span>- Center for Medical Innovation vzw</span></h1>
	</div>
	<div id="navcontainer">
		<ul>
			<li><a href="#"><i class="flaticon-medicine13"></i>Our Missions</a></li>
			<li><a href="#"><i class="flaticon-adn1"></i> Flemish Biobank</a></li>
			<li><a href="#"><i class="flaticon-molecules1"></i> Translational Research</a></li>
			<li><a href="#"><i class="flaticon-conference2"></i> For Donors</a></li>
			<li><a href="#"><span class="flaticon-medical55"></span> Catalogues</a></li>
		</ul>	
	</div>
</div>
<br>',
        'safe_summary' => '',
      ),
    ),
  ),
  'title_field' => array(
    'und' => array(
      0 => array(
        'value' => 'Mica',
        'format' => NULL,
        'safe_value' => 'Mica',
      ),
    ),
  ),
  'rdf_mapping' => array(
    'rdftype' => array(
      0 => 'foaf:Document',
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
  'last_comment_uid' => 0,
  'comment_count' => 0,
  'print_display' => 1,
  'print_display_comment' => 0,
  'print_display_urllist' => 1,
  'name' => '',
  'picture' => 0,
  'data' => NULL,
  'date' => '2014-11-11 13:05:15 +0100',
);
  return $nodes;
}
