
(function($) {
  Drupal.behaviors.custom_field_js_form = {
    attach: function(context, settings) {
        
        // Get selected value from validate categories field
        var selectedVar = $("input[type='radio'][name='field_validate_categories[und]']:checked").val();        
        
        // Enable/Disable Vocabulary URL based on selected var
        disableVocabularyURLField(selectedVar);
        
        // Enable/Disable Vocabulary URL based on selected var if value changed
        // trigged by value changes in validate categories field
        $("input[type='radio'][name='field_validate_categories[und]']").click(function(){
           disableVocabularyURLField ($(this).attr('value'));  
        });
            
        /**
         * To disable vocabulary url field when 
         * @returns {undefined}
         */
        function disableVocabularyURLField (selected) {
            if (selected=='1') {
                $('.field-name-field-vocabulary-url input').attr('disabled', 
                  'disabled');
            } else {
                $('.field-name-field-vocabulary-url input').removeAttr('disabled');
            }
        } // end of function
    
    } // end of attach
  };
})(jQuery);

