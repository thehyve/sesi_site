// Initialize namespace
if( typeof Sesi == 'undefined' ) 
    Sesi = {};

if( typeof Sesi.QueryInterface == 'undefined' ) 
    Sesi.QueryInterface = {};

(function ($) {

    // Make sure that the taxonomy tree is loaded
    Drupal.behaviors.query_interface_taxonomy_tree = {
        attach: function (context, settings) {
            // init the tree
            var tree = $('#taxonomy_tree');
            if( tree.length > 0 ) {
                tree.aciTree({
                    ajax: {
                        url: tree.data( 'url' )
                    },
                    checkbox: true
                });

                // Enable filtering on selected terms
                tree.on('acitree', function(event, api, item, eventName, options) {
                    if( eventName == 'checked' || eventName == 'unchecked' ) {
                        Sesi.QueryInterface.filter();
                    }
                });
            }
        }
    };

    // Initialize TaxonomyTree namespace
    if( typeof Sesi.QueryInterface.TaxonomyTree == 'undefined' )
        Sesi.QueryInterface.TaxonomyTree = {};

    // (de)select all elements in the taxonomy tree    
    // If no argument is given, all elements are selected
    Sesi.QueryInterface.TaxonomyTree.selectAll = function(checked) {
        if( typeof checked == 'undefined' )
            checked = true;

        // Retrieve a reference to the tree api
        var taxonomyTree = $( Sesi.QueryInterface.selectors.taxonomyTree );
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

}(jQuery)); 

