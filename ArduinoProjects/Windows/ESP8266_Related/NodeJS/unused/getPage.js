//-- Get page --
var http = require('http');

var options = {
	  host: "192.168.254.110",
	  port: 80,
	  path: '',
	  method: 'GET'
	};
	
	http.get( options, function(response) {
	  console.log("got response: " + response.statusCode);
	  
	  var body = ''
	  response.on('data', function(d) { body += d});
	  
	  response.on('end', function() { 
	    console.log("BODY: " + body)
	  });
	});
	
console.log("End of program");	