// Ignore favicon.ico requests

// Node JS Server (running on the Raspberry Pi)
var serverIP = '192.168.254.101';
var serverPort = 8000;

// require is like #include in Arduino/C
var http = require('http');

// Create a WebServer.  What should it do when a request is received?
var server = http.createServer(function (request, response) {
  // This code runs when our WebServer receives a request from a WebClient/Browser
  console.log("Request: " + request.url);
  if (request.url == "/favicon.ico") {
	var respStr = "(not found)";	
	console.log("Response: " + respStr);
	response.writeHead(404, {"Content-Type": "text/plain"});
	response.end(respStr);
  }
  else {
    var respStr = "Hello World, says NodeJS Server.";
    console.log("Response: " + respStr);
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end(respStr);
  }
});

// Start listening for http requests
server.listen(serverPort, serverIP);
console.log("Server running on the Pi at " + serverIP + ":" + serverPort);
