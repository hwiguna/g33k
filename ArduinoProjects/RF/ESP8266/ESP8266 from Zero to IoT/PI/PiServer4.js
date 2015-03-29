// Pass request from first ESP to second ESP

// Node JS Server (running on the Raspberry Pi)
var serverIP = '192.168.254.101';
var serverPort = 8000;

// require is like #include in Arduino/C
var http = require('http');

// Create a WebServer.  What should it do when a request is received?
var server = http.createServer(function (request, response) {
  // This code runs when our WebServer receives a request from a WebClient/Browser
  console.log("Request: " + request.url);
  var theUrl = require('url').parse(request.url);
  if (theUrl.href.indexOf("/set?v=") == 0) {
    console.log("Request: " + request.url);
  
	var pair = theUrl.query;
    console.log("Response: " + pair);
    response.writeHead(200, {"Content-Type": "text/plain"});
	response.end(pair);
  
	// -- Send request to second ESP --
	var options = {
	  host: '192.168.254.106',
	  path: '/set?' + pair
	}
	callback = function(response) {
	  var str = '';
	  response.on('data', function(chunk) { str += chunk; });
	}
	http.request(options, callback).end();
  }
});

// Start listening for http requests
server.listen(serverPort, serverIP);
console.log("Server running at " + serverIP + ":" + serverPort);
