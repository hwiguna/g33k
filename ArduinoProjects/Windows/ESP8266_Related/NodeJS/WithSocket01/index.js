$(function () {
    var socket = io();

    $('#sendBtn').click(function (event) {
        socket.emit('chat message', $('#m').val());
        $('#m').val('');
    });

    $('#led1OnBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', {led:'1', ip:'192.168.254.106'});
    });

    $('#led1OffBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', {led:'0', ip:'192.168.254.106'});
    });
	
    $('#led2OnBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', {led:'1', ip:'192.168.254.110'});
    });

    $('#led2OffBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', {led:'0', ip:'192.168.254.110'});
    });

    socket.on('chat message', function (msg) {
        $('#messages').append($('<li>').text(msg));
    });

    $("#ClearButton").click(function () {
        $("#DataFromESP").html("");
        $("#LEDState").html("");
    });

    $("#ReadSwitchButton").click(function () {
        $.getJSON("/a", function (result) {
            $.each(result, function (i, field) {
                $("#DataFromESP").append(field + " ");
            });
        });
    });
});