// Initialize namespace
if( typeof Sesi == 'undefined' ) 
    Sesi = {};

if( typeof Sesi.QueryInterface == 'undefined' ) 
    Sesi.QueryInterface = {};

// Using the closure to map jQuery to $.
(function ($) {
    // Moves a column from a table to another position
    jQuery.moveColumn = function (table, from, to) {
        jQuery.moveColumns( table, from, from, to );
    }

    // Moves multiple columns from a table to another position
    jQuery.moveColumns = function (table, start, end, to) {
        var rows = jQuery('tr', table);
        var cols;
        rows.each(function() {
            cols = jQuery(this).children('th, td');
            
            var originalCells = cols.slice(start, end + 1).detach();
            
            // Inserting data to the end of a row
            // must be handled differently
            if( to >= cols.length - originalCells.length ) {
                originalCells.appendTo($(this));
            } else {
                originalCells.insertBefore(cols.eq(to));
            }
        });
    }

    /**
     * Moves a column from the table, including underlying columns
     * to another position in the table.
     * from indicates the 0-based number of the column to move. It counts columns
     * in the header (thead). If the column has a colspan, multiple columns 
     * underneath are moved.
     * 
     * All rows in the tbody are assumed to have the same number of cells.
     */
    function moveColumn( table, from, to ) {
        // Find number of columns
        var headers = table.find( "thead th" )
        var numColumns = headers.length;

        // Count the number of columns underneath
        var colspans = [];
        headers.each(function() {
            var colspan = $(this).attr( "colspan" )
            colspans.push( colspan ? parseInt( colspan ) : 1 );
        });

        // Move the header column itself
        $.moveColumn( table.find( "thead" ), from, to );
        
        // Move the columns underneath. For that, compute the range to move
        var startCol = 0;
        for( i = 0; i < from; i++ ) {
            startCol += colspans[i];
        }
        var endCol = startCol + colspans[from] - 1;

        // Also compute the place where to put the cells back. This depends
        // on the colspan.
        var toCol = 0;
        for( i = 0; i < to; i++ ) {
            // For putting back the cells, the original position is to be
            // disregarded, because the cells are removed from the dom, before
            // putting them back.
            if( i != from )
                toCol += colspans[i];
        }
        
        $.moveColumns( table.find( "tbody" ), startCol, endCol, toCol );
    }

    function changeLookAndFeelQueryResultsScreen() {
        var table = $( "#result-wrapper .query-table" );
        
        // If no table is found, or the table has been changed
        // already, return immediately
        if( table.length == 0 || table.data( "sesi-changed" ) ) 
            return;
        
        // Find number of columns
        var headers = table.find( "thead th" )
        var numColumns = headers.length;

        // The column 'mathced' is last but should be the first column (after headers)
        moveColumn( table, numColumns - 1, 1 );

        // The column 'total' is first (after headers) but should be the last column
        // Please note, because the last column has been moved to the start already
        // we use the third column now
        moveColumn( table, 2, numColumns );

        // Please note: a totals row is only present if multiple studies are 
        // used.
        var dataRows = table.find( "tbody tr" );
        if( dataRows.length > 1 ) {
            // The first row (with totals) must have a green background
            var totalsRow = dataRows.last();
            totalsRow.find( "td" ).css( "background-color", "#dff0d8" );

            // We have to check whether the table is crossed with another variable.
            // If that is the case, 'totals' column have a colspan > 1. In that
            // case, there is a 'cross'-row in the tbody as well.
            var totalColspan = table.find( "thead tr th" ).eq(1).attr( "colspan" );
            var crossed = !!totalColspan;
            
            if( !crossed )
                totalColspan = 1;
            else
                totalColspan = parseInt(totalColspan);

            // The top left (data) cell, with the grand total should be with bold font weight
            totalsRow.find( "td" ).slice(1, 1 + totalColspan).css( "font-weight", "bold" );

            // The row 'totals' should be the first row (after a cross-row, if it exists)
            if( crossed ) {
                table.find( "tbody tr:first-child" ).after( totalsRow.detach() );
            } else {
                table.find( "tbody" ).prepend( totalsRow.detach() );
            }
        }
        
        // There must be labels underneath the table
        // The columns must have a colspan just like the ones in the header
        var colspans = [];
        headers.each(function() {
            var colspan = $(this).attr( "colspan" )
            colspans.push( colspan ? parseInt( colspan ) : 1 );
        });

        var tr = $( '<tr>' ).addClass( "query-result-labels" );
        
        // Add an empty cell underneath the study column
        tr.append( $( "<td>" ) );

        // Below the column 'matched', there must be the label "Matching all criteria"
        tr.append( $( "<td>" ).attr( "colspan", colspans[1] ).text( "Matching all criteria" ) );

        // Below the other columns, there should be "Totals for specific criteria" (only once, spanning all other columns)
        // The colspan for this column should be enough to span all data columns
        var remainingColspan = 0;
        for( i = 2; i < headers.length - 1; i++ ) {
            remainingColspan += colspans[i];
        }
        tr.append( $( "<td>" ).attr( "colspan", remainingColspan ).text( "Totals for specific criteria" ) );
        
        // Below the column 'total', there must be the label "Total sample set size"
        tr.append( $( "<td>" ).attr( "colspan", colspans[ colspans.length - 1 ] ).text( "Total sample set size" ) );
        
        // Add the row to the table
        table.find( "tbody" ).append( tr );

        // Mark the table as being processed, to prevent it to be processed twice
        table.data( "sesi-changed", true );
    }

    Drupal.behaviors.query_interface_results_screen = {
        attach: function (context, settings) {
            changeLookAndFeelQueryResultsScreen();
        }
    };

}(jQuery));