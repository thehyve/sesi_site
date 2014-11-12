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
                // Initialize the tree
                tree.aciTree({
                    ajax: {
                        url: tree.data( 'url' )
                    },
                    checkbox: true,

                    // our custom filter/search
                    filterHook: function(item, search, regexp) {
                        if (search.length) {
                            // match the item
                            return regexp.test(String(this.getLabel(item)));
                        } else {
                            // empty search, all matches
                            return true;
                        }
                    }
                });
                
                // Make sure that all selections are taken into account when 
                // the form is submitted
                form.on( "submit", function(e) {
                    // Retrieve the selected term s
                    var treeApi = tree.aciTree('api');
                    var allItems = treeApi.children( null, true );
                    var selectedTerms = treeApi.checkboxes( allItems, true );

                    // Add an hidden input for all selected items
                    $.each( selectedTerms, function(idx, el) { 
                        // Only use the checkboxes 'fully selected'
                        if( treeApi.isTristate( $(el) ) )
                            return;

                        var data = treeApi.itemData( $(el) );
                        if( data.id ) {
                            var id = data.id;
                            form.append( 
                                $( '<input type="hidden" />' ).attr( "name", "terms[]" ).attr( "id", "term_selected_" + id ).val( id )
                            ); 
                        }
                    });

                    return true;
                });

                // Initialize filtering the tree
                var treeApi = tree.aciTree('api');
                var lastSearch = '';

                $('#edit-filter').keyup(function() {
                    // Don't search if nothing has changed in the search term
                    if ($(this).val() == lastSearch) {
                        return;
                    }
                    lastSearch = $(this).val();

                    // Start filtering
                    treeApi.filter(null, {
                        search: $(this).val(),
                        success: function(item, options) {
                            if (!options.first) {
                                alert('No results found!');
                            }
                        }
                    });
                });
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

