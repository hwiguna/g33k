var http = require('http');
http.createServer(function (req, res) {
  console.log('req=' + require('url').parse(req.url).query);
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('ok\n');
}).listen(80, '192.168.254.100');
console.log('Server running at http://192.168.254.100:80/');
