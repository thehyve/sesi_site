// Initialize namespace
if( typeof Sesi == 'undefined' ) 
    Sesi = {};

if( typeof Sesi.QueryInterface == 'undefined' ) 
    Sesi.QueryInterface = {};

// Using the closure to map jQuery to $.
(function ($) {
    Sesi.QueryInterface.selectors = {
        variables: '#variables',
        fullTextInput: '.form-item-fulltext-search input',
        taxonomyTree: '#taxonomy_tree'
    }

    /**
     * Filter the list of available variables, based on the fulltextsearch
     * as well as on the selected terms in the tree
     */
    Sesi.QueryInterface.filter = function() {
        var fullTextInput = $( Sesi.QueryInterface.selectors.fullTextInput );
        var taxonomyTree = $( Sesi.QueryInterface.selectors.taxonomyTree );

        // Retrieve the fulltext search value
        var val = $.trim(fullTextInput.val()).replace(/ +/g, ' ').toLowerCase();

        var $rows = $( Sesi.QueryInterface.selectors.variables ).find('tbody tr');
        var classPattern = /variable_[0-9]+/;

        // Retrieve the selected term s
        var treeApi = taxonomyTree.aciTree('api');
        var allItems = treeApi.children( null, true );
        var selectedTerms = treeApi.checkboxes( allItems, true );
        
        // If no selection has been made, return immediately for performance reasons
        if( val == "" && allItems.length == selectedTerms.length ) {
            $rows.show();
            return;
        }

        // Retrieve IDs for those selected terms
        var selectedTermIds = $.map( selectedTerms, function(el,idx) { 
            return $(el).data( 'itemData.aciTree' ).id; 
        } );

        // All variables have 2 rows, with the same class ('variable-...')
        // We should show (combinations of) rows if both of these conditions holds
        //  - the text in the fulltext search box is present
        //  - on of the selected taxonomy terms is present
        var classesToShowBasedOnFullText = $rows.map(function() {
            // First check whether this row contains the text
            var text = $(this).text().replace(/\s+/g, ' ').toLowerCase();

            // If not, return
            if( text.indexOf(val) == -1 )
                return null;

            // Now we know that both conditions hold. We will now
            // return the class that matches the pattern
            var classList = $(this).attr('class').split(/\s+/);
            for(var i = 0; i < classList.length; i++) {
                if( classPattern.test(classList[i]) )
                    return classList[i];
            }

            return null;
        });

        var classesToShowBasedOnTaxonomy = $rows.map(function() {
            // Now check for the matching taxonomy terms 
            var taxonomyHiddenFields = $(this).find( "input.hidden-taxonomy-id" );
            var matchingTaxonomies = taxonomyHiddenFields.filter(function() {
                return jQuery.inArray( $(this).val(), selectedTermIds ) > -1;
            });

            // If none of the taxonomies match, return
            if( matchingTaxonomies.length == 0 )
                return null;

            // Now we know that both conditions hold. We will now
            // return the class that matches the pattern
            var classList = $(this).attr('class').split(/\s+/);
            for(var i = 0; i < classList.length; i++) {
                if( classPattern.test(classList[i]) )
                    return classList[i];
            }

            return null;
        });


        // Create a unique list, without null values
        var classesToShow = $.unique( 
            classesToShowBasedOnFullText.get().filter(function(n) {
                return classesToShowBasedOnTaxonomy.get().indexOf(n) != -1
            })
        );

        // Show all rows matching these classes
        if( classesToShow.length > 0 ) {
            var selector = "." + classesToShow.join( ", ." );
            $rows.hide().filter(selector).show()
        } else {
            $rows.hide();
        }
    }

    function changeLookAndFeelFullTextSearch() {
        if ($('form .input-prepend').length > 0) return;

        var searchDiv = $('.form-item-fulltext-search');

        var label = searchDiv.find("label");
        var input = searchDiv.find("input");

        input.wrap('<div class="input-prepend" />');
        input.before('<span class="add-on"><i class="icon-search"></i></span>');
        input.attr('placeholder', $.trim(label.html()));

        label.hide();
    }   

    function enableFilter( input, table ) {
        input.keyup(function() { Sesi.QueryInterface.filter() } );
    }

    Drupal.behaviors.query_interface_filter_variables = {
        attach: function (context, settings) {
            changeLookAndFeelFullTextSearch();
            enableFilter( $( Sesi.QueryInterface.selectors.fullTextInput ), $( Sesi.QueryInterface.selectors.variables ) );
        }
    };

}(jQuery));