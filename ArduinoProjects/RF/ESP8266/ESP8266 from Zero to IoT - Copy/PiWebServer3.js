// Echo the request back
// /set?b=1 --> b=1

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
  var command = "(none)";
  if (theUrl.href.indexOf("/set?b=") == 0) {
    console.log("Request: " + request.url);
	command = theUrl.query;
  }
  console.log("Response: " + command);
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.end(command);
});

// Start listening for http requests
server.listen(serverPort, serverIP);
console.log("Server running at " + serverIP + ":" + serverPort);
