$(function () {
    var socket = io();

    $('#sendBtn').click(function (event) {
        socket.emit('chat message', $('#m').val());
        $('#m').val('');
    });

    $('#ledOnBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', '1');
    });

    $('#ledOffBtn').click(function (event) {
        console.log('ledBtn clicked');
        socket.emit('led message', '0');
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