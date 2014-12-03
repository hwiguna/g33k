var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

app.get('/', function(req, res) {
  //res.send('<h1>hello world</h>');
  res.sendFile(__dirname + '/index.html');
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
});

http.listen(3000, function() {
  console.log('listening on *:3000');
});

setInterval( blinkNow, 1000);

function blinkNow()
{
  console.log('blink fires');
  io.emit('chat message', 'beep');
}