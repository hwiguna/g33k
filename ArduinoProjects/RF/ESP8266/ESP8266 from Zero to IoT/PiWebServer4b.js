// Pass request from first ESP to second ESP

var config = require('./config');

// Node JS Server (running on the Raspberry Pi)
var serverIP = config.serverIP;
var serverPort = config.serverPort;

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
	  host: config.clientIPs[1],
	  path: '/set?' + pair
	}
	callback = function(response) {
	  var str = '';
	  response.on('data', function(chunk) { str += chunk; });
	}
	http.request(options, callback).end();

	// -- Send request to Third ESP --
	options.host = config.clientIPs[2];
	http.request(options, callback).end();

	}
});

// Start listening for http requests
server.listen(serverPort, serverIP);
console.log("Server running at " + serverIP + ":" + serverPort);
