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
            if( is_array( $selectedTaxonomies ) ) {
                $taxonomies = array_merge($taxonomies, $selectedTaxonomies);
            } else {
                $taxonomies[] = $selectedTaxonomies;
            }
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

