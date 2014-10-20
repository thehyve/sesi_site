// Using the closure to map jQuery to $.
(function ($) {
    Drupal.behaviors.query_interface_taxonomy_tree = {
        attach: function (context, settings) {
            // init the tree
            jQuery('#taxonomy_tree').aciTree({
                ajax: {
                    url: '/mica/sites/all/modules/query_interface/checkbox.json'
                },
                checkbox: true
            });
        }
    };

}(jQuery)); 

