(function ($) {

  function fixToolbarHeight(event) {
    var toolbarHeight = $('#toolbar').height();
    if(toolbarHeight !== null) {
      $('#navbar').css('top', toolbarHeight+'px');
    }
  }

  $().ready(function() {
    if($('#toolbar').length) {
      fixToolbarHeight(null);
      $(window).resize(fixToolbarHeight);
    }
  });

})(jQuery);
