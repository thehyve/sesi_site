
(function($) {
  Drupal.behaviors.custom_field_js_form = {
    attach: function(context, settings) {
        
        // Get selected value from validate categories field
        var isValidateCategories = $("input[type='radio'][name='field_validate_categories[und]']:checked").val();        
        
        // Enable/Disable Vocabulary URL based on selected var
        disableVocabularyURLField(isValidateCategories);
        
        // Enable/Disable Vocabulary URL based on selected var if value changed
        // trigged by value changes in validate categories field
        $("input[type='radio'][name='field_validate_categories[und]']").click(function(){
           disableVocabularyURLField ($(this).attr('value'));  
        });
        
        // Get selected value from value type
        var valueType = $('#edit-field-value-type-und').val();
        // Default 
        displayMinMaxFields(valueType);
        $('#edit-field-value-type-und').change(function() {
            displayMinMaxFields($(this).val());
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
                
        /**
         * To display attribute field based on the selected value in the 
         * value type field.
         * @param {type} selected
         * @returns {undefined}
         */
        function displayMinMaxFields(selected) {
            
            if (selected == 'decimal' || selected == 'integer') {
                $('.field-name-field-validate-min').show();
                $('.field-name-field-validate-max').show();
                $('.field-name-field-validate-past-date').hide();
            } else if (selected == 'date' || selected == 'date_time') {
                $('.field-name-field-validate-min').hide();
                $('.field-name-field-validate-max').hide();
                $('.field-name-field-validate-past-date').show();                
            } else {
                $('.field-name-field-validate-min').hide();
                $('.field-name-field-validate-max').hide()
                $('.field-name-field-validate-past-date').hide();
            }
            
        } // end function 
    
    } // end of attach
  };
})(jQuery);

