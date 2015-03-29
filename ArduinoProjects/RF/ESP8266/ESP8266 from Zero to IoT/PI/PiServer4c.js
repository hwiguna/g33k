// Pass request from first ESP to second ESP

var config = require('./config');

// Node JS Server (running on the Raspberry Pi)
var serverIP = config.serverIP;
var serverPort = config.serverPort;

// require is like #include in Arduino/C
var http = require('http');

// Create a WebServer.  What should it do when a request is received?
var server = http.createServer( function (request, response) {
	// This code runs when our WebServer receives a request from a WebClient/Browser
	console.log("Request: " + request.url);
	var theUrl = require('url').parse(request.url);

	if (theUrl.href.indexOf("/set?v=") == 0) {
		var param = theUrl.query;
		//-- Do something --
		SendToESP( config.clientIPs[1], '/set?' + param);
		SendToESP( config.clientIPs[2], '/set?' + param);

		//-- Send response to client --
		response.writeHead(200, {"Content-Type": "text/plain"});
		response.end(param + " processed!");
	}
	else
	{
		var respStr = "Unknown command: " + request.url;	
		console.log("Response: " + respStr);
		response.writeHead(404, {"Content-Type": "text/plain"});
		response.end(respStr);
	}
});

function SendToESP( clientIP, request )
{
	console.log("SendToESP: " + clientIP + request);

	var options = {
	  host: clientIP,
	  path: request
	}
	callback = function(response) {
	  var str = '';
	  response.on('data', function(chunk) { str += chunk; });
	}
	http.request(options, callback).end();
}

// Start listening for http requests
server.listen(serverPort, serverIP);
console.log("Server running at " + serverIP + ":" + serverPort);
