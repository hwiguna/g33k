var app = require('express')();
var http = require('http');
var httpServer = http.Server(app);
var io = require('socket.io')(httpServer);

var ESP1Address = '192.168.254.106';
var ESP2Address = '192.168.254.110';

app.get('/', function (req, res) {
    //res.send('<h1>hello world</h>');
    res.sendFile(__dirname + '/index.html');
});

app.get('/index.css', function (req, res) { res.sendFile(__dirname + '/index.css'); });
app.get('/index.js', function (req, res) { res.sendFile(__dirname + '/index.js'); });

app.get('/api/1', function (req, res) {
    res.send('<h1>API hit</h>');
    //res.sendFile(__dirname + '/index.html');
    io.emit('chat message', 'API says released');
	SetDataOnESP('0', '192.168.254.110');
});

app.get('/api/0', function (req, res) {
    res.send('<h1>API hit</h>');
    //res.sendFile(__dirname + '/index.html');
    io.emit('chat message', 'API says PRESSED');
	SetDataOnESP('1', '192.168.254.110');
});

io.on('connection', function (socket) {
    console.log('a user connected to socket io');
    //socket.broadcast.emit('hi');

    socket.on('disconnect', function () {
        console.log('user disconnected');
    });
    socket.on('chat message', function (msg) {
        console.log('message: ' + msg);
        io.emit('chat message', msg);
    });

    socket.on('led message', function (ledState) {
        console.log('node js got the led message click. ledstate=' + ledState.ip);
        SetDataOnESP(ledState.led, ledState.ip);
    });
});

httpServer.listen(3000, function () {
    console.log('listening on *:3000');
});

//setInterval( blinkNow, 1000);

function blinkNow() {
    console.log('blink fires');
    io.emit('chat message', 'beep');
}

function SetDataOnESP(ledState, deviceIP) {
    console.log('server.js got the led message click');
    var options = {
        host: deviceIP,
        port: 80,
        path: '/set?b=' + ledState,
        method: 'GET',
        headers: { 'Content-Type': 'text/html' }
    };

    http.get(options, function (resp) {
        console.log('received response');
        var output = '';
        resp.on('data', function (chunk) {
            output += chunk;
        });

        resp.on('end', function () {
            console.log(output);
        });

        resp.on('error', function (e) {
            console.log("Got error: " + e);
        });
    });
}