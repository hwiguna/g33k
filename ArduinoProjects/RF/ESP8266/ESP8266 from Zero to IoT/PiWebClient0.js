// Node JS WebClient

var options = {
  host: '192.168.254.106',		// WebServer to talk to
  path: '/set?' + ledValue		// Command to send to
}

callback = function(response) {
  var str = '';
  response.on('data', function(chunk) { str += chunk; });
}

http.request(options, callback).end();
