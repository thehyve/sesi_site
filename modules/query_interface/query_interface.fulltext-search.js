// Using the closure to map jQuery to $.
(function ($) {
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

    function enableSearch( input, table ) {
        var $rows = table.find('tbody tr');
        var classPattern = /variable_[0-9]+/;

        input.keyup(function() {
            var val = $.trim($(this).val()).replace(/ +/g, ' ').toLowerCase();

            if( val == "" ) {
                $rows.show();
                return;
            }

            // All variables have 2 rows, with the same class ('variable-...')
            // We should search in both rows and if the term is found in one
            // of both rows, we should show both
            var classesToShow = $rows.map(function() {
                // First check whether this row contains the text
                var text = $(this).text().replace(/\s+/g, ' ').toLowerCase();
                
                if( text.indexOf(val) > -1 ) {
                    // If so, return the class that matches the pattern
                    var classList = $(this).attr('class').split(/\s+/);
                    for(var i = 0; i < classList.length; i++) {
                        if( classPattern.test(classList[i]) )
                            return classList[i];
                    }
                    
                    return null;
                } else {
                    // Otherwise, return null
                    return null;
                }
            });
            
            // Create a unique list, without null values
            classesToShow = $.unique( classesToShow );

            // Show all rows matching these classes
            var selector = "." + classesToShow.get().join( ", ." );
            $rows.hide().filter(selector).show()
        });
    }

    Drupal.behaviors.query_interface_fulltext_search = {
        attach: function (context, settings) {
            changeLookAndFeelFullTextSearch();
            enableSearch( $('.form-item-fulltext-search input'), $('#variables') );
        }
    };

}(jQuery));