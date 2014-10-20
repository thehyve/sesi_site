<?php
define( "QUERY_INTERFACE_TAXONOMY_ROOT_NODE", -1 );

/**
 * Returns the taxonomy tree for a given dataset in JSON format
 * The tree is rendered using aciTree javascript library. The 
 * definition in hook_menu tells drupal to render this output as JSON.
 * 
 * @param type $dataset_node            Dataset node
 * @return The tree that is to be rendered. 
 * @see query_interface_menu()
 * @see http://plugins.jquery.com/aciTree/
 */
function query_interface_taxonomy_tree($dataset_node) {
    // Retrieve a list of all variables
    $variables = mica_dataset_dataset_variables($dataset_node->nid);
    
    // Retrieve all taxonomies for all nodes
    $taxonomies = _query_interface_get_multiple_variables_taxonomies( $variables );
    
    // Create a tree from those nodes
    // Issues: - multiple parents: A -> B -> C and X -> C, what to show, what to select?
    $tree = _query_interface_create_tree_from_taxonomies( $taxonomies );
    
    return _query_interface_convert_to_aciTree_format( $tree );
    //return unserialize( 'a:3:{i:0;a:7:{s:2:"id";i:1;s:5:"label";s:5:"Brand";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:35:{i:0;a:5:{s:2:"id";i:2;s:5:"label";s:5:"Acura";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:1;a:5:{s:2:"id";i:3;s:5:"label";s:4:"Audi";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:2;a:5:{s:2:"id";i:4;s:5:"label";s:3:"BMW";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:3;a:5:{s:2:"id";i:5;s:5:"label";s:5:"Buick";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:4;a:5:{s:2:"id";i:6;s:5:"label";s:8:"Cadillac";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:5;a:5:{s:2:"id";i:7;s:5:"label";s:9:"Chevrolet";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:6;a:5:{s:2:"id";i:8;s:5:"label";s:8:"Chrysler";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:7;a:5:{s:2:"id";i:9;s:5:"label";s:5:"Dodge";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:8;a:5:{s:2:"id";i:10;s:5:"label";s:4:"Fiat";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:9;a:5:{s:2:"id";i:11;s:5:"label";s:6:"Fisker";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:10;a:5:{s:2:"id";i:12;s:5:"label";s:4:"Ford";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:11;a:5:{s:2:"id";i:13;s:5:"label";s:3:"GMC";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:12;a:5:{s:2:"id";i:14;s:5:"label";s:5:"Honda";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:13;a:5:{s:2:"id";i:15;s:5:"label";s:7:"Hyundai";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:14;a:5:{s:2:"id";i:16;s:5:"label";s:8:"Infiniti";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:15;a:5:{s:2:"id";i:17;s:5:"label";s:6:"Jaguar";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:16;a:5:{s:2:"id";i:18;s:5:"label";s:4:"Jeep";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:17;a:5:{s:2:"id";i:19;s:5:"label";s:3:"Kia";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:18;a:5:{s:2:"id";i:20;s:5:"label";s:10:"Land Rover";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:19;a:5:{s:2:"id";i:21;s:5:"label";s:5:"Lexus";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:20;a:5:{s:2:"id";i:22;s:5:"label";s:7:"Lincoln";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:21;a:5:{s:2:"id";i:23;s:5:"label";s:5:"Mazda";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:22;a:5:{s:2:"id";i:24;s:5:"label";s:8:"Mercedes";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:23;a:5:{s:2:"id";i:25;s:5:"label";s:4:"MINI";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:24;a:5:{s:2:"id";i:26;s:5:"label";s:10:"Mitsubishi";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:25;a:5:{s:2:"id";i:27;s:5:"label";s:6:"Nissan";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:26;a:5:{s:2:"id";i:28;s:5:"label";s:7:"Porsche";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:27;a:5:{s:2:"id";i:29;s:5:"label";s:3:"Ram";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:28;a:5:{s:2:"id";i:30;s:5:"label";s:5:"Scion";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:29;a:5:{s:2:"id";i:31;s:5:"label";s:5:"Smart";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:30;a:5:{s:2:"id";i:32;s:5:"label";s:6:"Subaru";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:31;a:5:{s:2:"id";i:33;s:5:"label";s:5:"Tesla";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:32;a:5:{s:2:"id";i:34;s:5:"label";s:6:"Toyota";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:33;a:5:{s:2:"id";i:35;s:5:"label";s:10:"Volkswagen";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:34;a:5:{s:2:"id";i:36;s:5:"label";s:5:"Volvo";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}i:1;a:7:{s:2:"id";i:47;s:5:"label";s:33:"Comfort Convenience Entertainment";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:4:{i:0;a:7:{s:2:"id";i:48;s:5:"label";s:18:"Convenient Control";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:8:{i:0;a:5:{s:2:"id";i:49;s:5:"label";s:15:"Gesture control";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:1;a:5:{s:2:"id";i:50;s:5:"label";s:20:"Voice command system";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:2;a:5:{s:2:"id";i:51;s:5:"label";s:34:"Fully reconfigurable gauge cluster";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:3;a:5:{s:2:"id";i:52;s:5:"label";s:24:"Electronic parking brake";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:4;a:5:{s:2:"id";i:53;s:5:"label";s:26:"Shift by wire transmission";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:5;a:5:{s:2:"id";i:54;s:5:"label";s:28:"Push-button keyless ignition";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:6;a:5:{s:2:"id";i:55;s:5:"label";s:14:"Remote starter";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:7;a:5:{s:2:"id";i:56;s:5:"label";s:25:"Driver information system";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}i:1;a:7:{s:2:"id";i:57;s:5:"label";s:7:"Comfort";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:6:{i:0;a:5:{s:2:"id";i:58;s:5:"label";s:25:"Automatic climate control";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:1;a:5:{s:2:"id";i:59;s:5:"label";s:21:"Smart climate control";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:2;a:5:{s:2:"id";i:60;s:5:"label";s:31:"Dual/multi zone climate control";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:3;a:5:{s:2:"id";i:61;s:5:"label";s:25:"Ambient interior lighting";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:4;a:5:{s:2:"id";i:62;s:5:"label";s:12:"Active glass";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:5;a:5:{s:2:"id";i:63;s:5:"label";s:7:"Sunroof";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}i:2;a:7:{s:2:"id";i:64;s:5:"label";s:13:"Connected Car";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:10:{i:0;a:5:{s:2:"id";i:65;s:5:"label";s:23:"Built-in navigation aid";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:1;a:5:{s:2:"id";i:66;s:5:"label";s:26:"Navigation with path guide";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:2;a:5:{s:2:"id";i:67;s:5:"label";s:21:"Healthcare monitoring";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:3;a:5:{s:2:"id";i:68;s:5:"label";s:27:"Wireless phone charging mat";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:4;a:5:{s:2:"id";i:69;s:5:"label";s:18:"Remote diagnostics";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:5;a:5:{s:2:"id";i:70;s:5:"label";s:37:"Access and control with mobile device";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:6;a:5:{s:2:"id";i:71;s:5:"label";s:9:"Bluetooth";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:7;a:5:{s:2:"id";i:72;s:5:"label";s:34:"Dashboard display runs mobile apps";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:8;a:5:{s:2:"id";i:73;s:5:"label";s:30:"Live advisor/concierge service";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:9;a:5:{s:2:"id";i:74;s:5:"label";s:13:"Wi-Fi hotspot";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}i:3;a:7:{s:2:"id";i:75;s:5:"label";s:13:"Entertainment";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:1;s:5:"radio";b:0;s:6:"branch";a:8:{i:0;a:5:{s:2:"id";i:76;s:5:"label";s:24:"Passenger display screen";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:1;a:5:{s:2:"id";i:77;s:5:"label";s:9:"CD player";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:2;a:5:{s:2:"id";i:78;s:5:"label";s:8:"HD radio";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:3;a:5:{s:2:"id";i:79;s:5:"label";s:15:"Satellite radio";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:4;a:5:{s:2:"id";i:80;s:5:"label";s:37:"Smartphone/MP3 player connection port";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:5;a:5:{s:2:"id";i:81;s:5:"label";s:20:"Premium audio system";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:6;a:5:{s:2:"id";i:82;s:5:"label";s:43:"Rear seat displays for entertainment system";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}i:7;a:5:{s:2:"id";i:83;s:5:"label";s:22:"Rear seat USB charging";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}}}i:2;a:7:{s:2:"id";i:84;s:5:"label";s:20:"Fuel Hybrid Electric";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:0;s:5:"radio";b:0;s:6:"branch";a:1:{i:0;a:7:{s:2:"id";i:92;s:5:"label";s:12:"Fuel Economy";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:0;s:5:"radio";b:0;s:6:"branch";a:1:{i:0;a:7:{s:2:"id";i:99;s:5:"label";s:20:"Fuel-Saving Features";s:5:"inode";b:1;s:4:"open";b:1;s:8:"checkbox";b:0;s:5:"radio";b:0;s:6:"branch";a:1:{i:0;a:5:{s:2:"id";i:100;s:5:"label";s:17:"Start-stop system";s:5:"inode";b:0;s:8:"checkbox";b:1;s:5:"radio";b:0;}}}}}}}}');
}

/**
 * Returns a list of taxonomies for a list of variables
 * The list is composed of all values selected in fields within the 'domains' group
 * in all variables. The list doesn't contain duplicates
 * @param $variables    Array of Variable Node objects to return taxonomies for
 * @return Array        Unique list of taxonomies selected on the given variables.
 */
function _query_interface_get_multiple_variables_taxonomies($variables) {
    $taxonomies = array();
    
    foreach( $variables as $variable ) {
        $wrapper = entity_metadata_wrapper( 'node', $variable );
        foreach( _query_interface_get_taxonomies( $wrapper ) as $taxonomy ) {
            // Add to the list and guarantee uniqueness. Uniqueness
            // if defined by the tid property
            if( !array_key_exists( $taxonomy->tid, $taxonomies ) ) {
                $taxonomies[$taxonomy->tid] = $taxonomy;
            }
        }
    }
    
    return array_values($taxonomies);
}

/**
 * Creates a single tree from a list of taxonomy nodes.
 * 
 * @param type $taxonomies
 * @return type 
 */
function _query_interface_create_tree_from_taxonomies($taxonomyNodes) {
    $tree = _query_interface_initialize_tree();
    
    foreach( $taxonomyNodes as $node ) {
        _query_interface_add_taxonomy_node_to_tree($node, $tree);
    }
    
    return $tree;
}

/**
 * Create an empty taxonomy tree to add other items to
 * @return type 
 */
function _query_interface_initialize_tree() {
    $root = new stdClass();
    $root->tid = QUERY_INTERFACE_TAXONOMY_ROOT_NODE;
    $root->name = "Root";
    
    return array( QUERY_INTERFACE_TAXONOMY_ROOT_NODE => $root );
}

/**
 * Adds a taxonomy node to an existing tree
 * @param type $taxonomy
 * @param type $tree 
 */
function _query_interface_add_taxonomy_node_to_tree( $taxonomyNode, &$tree ) {
    // Make sure that all parants of the node are added to the 
    // tree already.
    $parents = taxonomy_get_parents( $taxonomyNode->tid );
    
    // Add the parents of this node first
    if( count( $parents ) > 0 ) {
        foreach( $parents as $parent ) {
            if( !array_key_exists( $parent->tid, $tree ) ) {
                _query_interface_add_taxonomy_node_to_tree($parent, $tree);
            }
        }
    } else {
        $parent = NULL;
    }
    
    // Add the node itself, if not yet present
    if( !array_key_exists( $taxonomyNode->tid, $tree ) ) {
        $tree[ $taxonomyNode->tid ] = $taxonomyNode;
    }
    
    // Add the node as child for each parent
    if( count( $parents ) > 0 ) {
        foreach( $parents as $parent ) {
            _query_interface_add_node_as_child( $taxonomyNode, $parent->tid, $tree );
        }
    } else {
        _query_interface_add_node_as_child( $taxonomyNode, QUERY_INTERFACE_TAXONOMY_ROOT_NODE, $tree );
    }
 
    return $tree;
}

/**
 * Add a node to a parent
 * @param type $taxonomyNode    Node to be added
 * @param type $tid             Tid of the parent taxonomy term
 * @param type $tree            Tree to alter
 */
function _query_interface_add_node_as_child( $taxonomyNode, $tid, &$tree ) {
    if( !array_key_exists( $tid, $tree ) )
        throw new Exception( "Parent tid does not exist in the given tree!" );
    
    if( !property_exists( $tree[ $tid ], "children" ) ) {
        $tree[ $tid ]->children = array();
    }
    
    if( !in_array( $taxonomyNode->tid, $tree[ $tid ]->children ) ) {
        $tree[ $tid ]->children[] = $taxonomyNode->tid;
    }
    
    return $tree;
}

/**
 * Converts a taxonomy tree to the format that the aciTree component expects
 * @param array $tree    Array with all taxonomy nodes
 * @return array         Array with the given tree in the aciTree format
 * @see _query_interface_create_tree_from_taxonomies()
 * @see http://acoderinsights.ro/en/aciTree-tree-view-with-jQuery
 */
function _query_interface_convert_to_aciTree_format($tree) {
    // Start with the root node
    $aciTree = array();
    
    if( count( $tree ) > 0 ) {
        foreach( $tree[ QUERY_INTERFACE_TAXONOMY_ROOT_NODE ]->children as $child_tid ) {
            $aciTree[] = _query_interface_create_aciTree_node( $tree[ $child_tid ], $tree );
        }
    }
    
    return $aciTree;
}

function _query_interface_create_aciTree_node( $node, $tree ) {
    $hasChildren = property_exists( $node, "children" ) && count( $node->children ) > 0;
    $children = array();
    
    if( $hasChildren ) {
        foreach( $node->children as $child_tid ) {
            $children[] = _query_interface_create_aciTree_node( $tree[ $child_tid ], $tree );
        }
    }
    
    return array(
        "id" => $node->tid,
        "label" => $node->name,
        "open" => false,
        "inode" => $hasChildren,
        "checkbox" => true,
        "checked" => true,
        "branch" => $hasChildren ? $children : null,
    );
}

/**
 * Returns a list of selected taxonomies for the given variable.
 * The list is composed of all values selected in fields within the 'domains' group.
 * @param $variableWrapper  Entity_Metadata_Wrapper around a variable node
 */
function _query_interface_get_taxonomies($variableWrapper) {
    // Determine which fields belong to the domains group.
    $fields = _query_interface_get_domain_fields();

    // Find the values on those fields
    $taxonomies = array();
    foreach ($fields as $fieldName) {
        $selectedTaxonomies = $variableWrapper->{$fieldName}->value();

        if ($selectedTaxonomies) {
            $taxonomies = array_merge($taxonomies, $selectedTaxonomies);
        }
    }

    return $taxonomies;
}

/**
 * Returns a list of field names for all fields within the 'domains' group for variables
 */
function _query_interface_get_domain_fields() {
    $groups = field_group_info_groups("node", "variable", "form");

    // Consistency check
    if (!array_key_exists("group_dimensions", $groups) || !property_exists($groups["group_dimensions"], "children")) {
        return array();
    }

    return $groups["group_dimensions"]->children;
}

