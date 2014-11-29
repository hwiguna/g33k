//-- Initialization --
$( function() {
    $("#ClearButton").click( function() {
	  $("#DataFromESP").html("");
	  $("#LEDState").html("");
	});
  
	$("#ReadSwitchButton").click( function() {
	  $.getJSON("/a",function(result){
		$.each(result, function(i, field){
		  $("#DataFromESP").append(field + " ");
		});
	  });
	});

	$("#LedOnButton").click( function() {
	  $.getJSON("/b",function(result){
		$.each(result, function(i, field){
		  $("#LEDState").append(field + " ");
		});
	  });
	});

	$("#LedOffButton").click( function() {
	  $.getJSON("/c",function(result){
		$.each(result, function(i, field){
		  $("#LEDState").append(field + " ");
		});
	  });
	});
  
});