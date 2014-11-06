// Initialize namespace
if( typeof Sesi == 'undefined' ) 
    Sesi = {};

if( typeof Sesi.QueryOntologies == 'undefined' ) 
    Sesi.QueryOntologies = {};

if( typeof Sesi.QueryOntologies.TaxonomyTree == 'undefined' )
    Sesi.QueryOntologies.TaxonomyTree = {};

(function ($) {
    if( !Sesi.QueryOntologies.TaxonomyTree.init ) {
        // Initialize a taxonomy tree
        Sesi.QueryOntologies.TaxonomyTree.init = function () {
            // init the tree
            var tree = $('#taxonomy_query_tree');
            var form = tree.parents( "form" ).first();
            
            if( tree.length > 0 ) {
                tree.aciTree({
                    ajax: {
                        url: tree.data( 'url' )
                    },
                    checkbox: true
                });

                tree.on('acitree', function(event, api, item, eventName, options) {
                    switch( eventName ) {
                        case "checked":
                            Sesi.QueryOntologies.TaxonomyTree.markChecked(item, api, form, true);
                            break;
                        case "unchecked":
                            Sesi.QueryOntologies.TaxonomyTree.markChecked(item, api, form, false);
                            break;
                    }
                });

            }
        };

        // Marks an item in the taxonomy tree and its descendants as checked
        // or not checked, depending on the parameter
        Sesi.QueryOntologies.TaxonomyTree.markChecked = function( item, api, form, checked, recursive ) {
            if( typeof checked == 'undefined' )
                checked = true;

            if( typeof recursive == 'undefined' )
                recursive = true;

            var id = api.getId(item);

            if( checked ) {
                // Add a hidden input field to mark this item selected
                // if the item doesn't exist yet
                if( $( '#term_selected_' + id ).length == 0 ) {
                    form.append( 
                        $( '<input type="hidden" />' ).attr( "name", "terms[]" ).attr( "id", "term_selected_" + id ).val( id )
                    );
                }            
            } else {
                // Remove the hidden input field if it exists
                $( '#term_selected_' + id ).remove();
            }

            // Also do the same to all descendants
            if( recursive ) {
                var children = api.children(item, true, true);
                console.log( "children", item, children );
                for( i = 0; i < children.length; i++) {
                    Sesi.QueryOntologies.TaxonomyTree.markChecked( $(children.get(i)), api, form, checked, false );
                }
            }
        };

        // (de)select all elements in the taxonomy tree    
        // If no argument is given, all elements are selected
        Sesi.QueryOntologies.TaxonomyTree.selectAll = function(checked) {
            if( typeof checked == 'undefined' )
                checked = true;

            // Retrieve a reference to the tree api
            var taxonomyTree = $( Sesi.QueryOntologies.selectors.taxonomyTree );
            var treeApi = taxonomyTree.aciTree('api');

            // Loop through all items and (de)select all items
            var allItems = treeApi.children( null, true );

            for( i = 0; i < allItems.length; i++ ) {
                if( checked ) 
                    treeApi.check( allItems.eq(i) );
                else
                    treeApi.uncheck( allItems.eq(i) );
            }
        }
    }

}(jQuery)); 

