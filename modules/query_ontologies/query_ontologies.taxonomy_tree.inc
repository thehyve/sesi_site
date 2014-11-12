<?php

/**
 * Returns the taxonomy tree for a given variable in JSON format
 * The tree is rendered using aciTree javascript library. The 
 * definition in hook_menu tells drupal to render this output as JSON.
 * 
 * @param type $variable_node            Variablenode
 * @return The tree that is to be rendered. 
 * @see query_ontologies_menu()
 * @see http://plugins.jquery.com/aciTree/
 */
function query_ontologies_variable_taxonomy($variable_node, $selectedIds = "" ) {
    // Retrieve the taxonomy for the variable
    $wrapper = entity_metadata_wrapper('node', $variable_node);
    $taxonomy = $wrapper->field_taxonomy->value();

    if (!$taxonomy) {
        return array();
    }

    // Selected IDs
    if( $selectedIds ) {
        $selectedIds = explode(",", $selectedIds);
    } else {
        $selectedIds = array();
    }
    
    // Find a tree from this taxonomy
    $tree = _query_ontologies_taxonomy_get_nested_tree($taxonomy->vid);
    
    // Convert it into aciTree format
    $aciTree = _query_ontologies_convert_to_aciTree_format( $tree, $selectedIds  );
    
    return $aciTree;
}

/**
 * Returns a nested tree for a set of terms or a taxonomy tree
 * @param type $vid_or_terms
 * @param type $max_depth
 * @param type $parent
 * @param type $parents_index
 * @param type $depth
 * @return type 
 */
function _query_ontologies_taxonomy_get_nested_tree($vid_or_terms = array(), $max_depth = NULL, $parent = 0, $parents_index = array(), $depth = 0) {
    if (!is_array($vid_or_terms)) {
        $vid_or_terms = taxonomy_get_tree($vid_or_terms);
    }
    foreach ($vid_or_terms as $term) {
        foreach ($term->parents as $term_parent) {
            if ($term_parent == $parent) {
                $return[$term->tid] = $term;
            } else {
                $parents_index[$term_parent][$term->tid] = $term;
            }
        }
    }
    foreach ($return as &$term) {
        if (isset($parents_index[$term->tid]) && (is_null($max_depth) || $depth < $max_depth)) {
            $term->children = _query_ontologies_taxonomy_get_nested_tree($parents_index[$term->tid], $max_depth, $term->tid, $parents_index, $depth + 1);
        }
    }
    return $return;
}

/**
 * Converts a nested taxonomy tree to the format that the aciTree component expects
 * @param array $tree    Nested taxonomy tree
 * @return array         Array with the given tree in the aciTree format
 * @see _query_ontologies_taxonomy_get_nested_tree()
 * @see http://acoderinsights.ro/en/aciTree-tree-view-with-jQuery
 */
function _query_ontologies_convert_to_aciTree_format($tree, $selectedIds ) {
    // Start with the root node
    $aciTree = array();
    
    if( count( $tree ) > 0 ) {
        foreach( $tree as $child ) {
            $aciTree[] = _query_ontologies_create_aciTree_node( $child, $selectedIds );
        }
    }
    
    return $aciTree;
}

function _query_ontologies_create_aciTree_node( $node, $selectedIds = array() ) {
    $hasChildren = property_exists( $node, "children" ) && count( $node->children ) > 0;
    $selected = in_array( $node->tid, $selectedIds );
    $children = array();
    
    if( $hasChildren ) {
        foreach( $node->children as $child ) {
            $children[] = _query_ontologies_create_aciTree_node( $child, $selectedIds );
        }
    }
    
    return array(
        "id" => $node->tid,
        "label" => $node->name,
        "open" => false,
        "inode" => $hasChildren,
        "checkbox" => true,
        "checked" => $selected,
        "branch" => $hasChildren ? $children : null,
    );
}