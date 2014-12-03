var app = require('express')();
var http = require('http');
var httpServer = http.Server(app);
var io = require('socket.io')(httpServer);

app.get('/', function(req, res) {
  //res.send('<h1>hello world</h>');
  res.sendFile(__dirname + '/index.html');
});

app.get('/api', function(req, res) {
  res.send('<h1>API hit</h>');
  //res.sendFile(__dirname + '/index.html');
  io.emit('chat message', 'API says hello');
});


io.on('connection', function(socket){
  console.log('a user connected to socket io');
  //socket.broadcast.emit('hi');
  
  socket.on('disconnect', function() {
    console.log('user disconnected');
  });
  socket.on('chat message', function(msg){
    console.log('message: ' + msg);
	io.emit('chat message', msg);
  });
  
  socket.on('led message', function(ledState){
    console.log('node js got the led message click');
	var options = {
	  host: 'www.google.com',
	  port: 80,
	  path: '/',
	  method: 'GET',
	  headers: { 'Content-Type': 'text/html'}
	};
	
	http.get( options, function(resp){
	  console.log('received response');
	  var output = '';
	  resp.on('data', function(chunk) {
		output += chunk;
	  });
	  
	  resp.on('end', function(){
		console.log(output);
	  });
	  
	  resp.on('error', function(e){
		console.log("Got error: " + e);
	  });
	});
  });
});

httpServer.listen(3000, function() {
  console.log('listening on *:3000');
});

//setInterval( blinkNow, 1000);

function blinkNow()
{
  console.log('blink fires');
  io.emit('chat message', 'beep');
}