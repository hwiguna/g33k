var serverIP = '192.168.254.101';

var email   = require("./node_modules/emailjs/email");
var mailServer  = email.server.connect({
   user:    "hari.wiguna.demo",
   password:"panggung",
   host:    "smtp.gmail.com",
   ssl:     true
});

// Load the http module to create an http server.
var http = require('http');

// Configure our HTTP server to respond with Hello World to all requests.
var server = http.createServer(function (request, response) {
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.end("Hello World\n");

  // send the message and get a callback with an error or details of the message that was sent
  mailServer.send({
     text:    "My bowl is empty! Please feed me.",
     from:    "The Cat <meow@scratch.com>",
     to:      "hwiguna <hwiguna@gmail.com>",
     cc:      "",
     subject: "Hungry"
  }, function(err, message) { console.log(err || message); });

});

// Listen on port 8000, IP defaults to 127.0.0.1
server.listen(8000, serverIP);

// Put a friendly message on the terminal
console.log("Server running at http://192.168.254.101:8000/");
