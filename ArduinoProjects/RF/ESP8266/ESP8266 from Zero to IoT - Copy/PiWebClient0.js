// Node JS WebClient

var options = {
  host: '192.168.254.106',
  path: '/set?' + ledValue
}

callback = function(response) {
  var str = '';
  response.on('data', function(chunk) { str += chunk; });
}

http.request(options, callback).end();
