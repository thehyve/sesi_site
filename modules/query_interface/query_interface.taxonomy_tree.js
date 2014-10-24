// Using the closure to map jQuery to $.
(function ($) {
    Drupal.behaviors.query_interface_taxonomy_tree = {
        attach: function (context, settings) {
            // init the tree
            var tree = jQuery('#taxonomy_tree');
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

}(jQuery)); 

