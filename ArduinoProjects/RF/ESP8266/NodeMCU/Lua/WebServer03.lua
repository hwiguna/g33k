-- LUA Webserver --
srv=net.createServer(net.TCP)

srv:listen(80,function(conn)

  conn:on("receive",function(conn,payload)

    forArduino = string.sub(payload, 6, 9) -- LUA substring is inclusive on both ends
    print(forArduino .. "\r\n")

    reply = "Sent to Arduino: " .. forArduino
    payloadLen = string.len(reply)
    conn:send("HTTP/1.1 200 OK\r\n")
    conn:send("Content-Length:" .. tostring(payloadLen) .. "\r\n")
    conn:send("Connection:close\r\n\r\n")
    conn:send(reply)
  end)

  conn:on("sent",function(conn)
    conn:close()
  end)
end)
