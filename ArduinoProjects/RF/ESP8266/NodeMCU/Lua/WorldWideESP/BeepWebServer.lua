-- Beep Webserver --
srv=net.createServer(net.TCP)

srv:listen(80,function(conn)

 conn:on("receive",function(conn,payload)
  isBeeping = false
  print(payload)
  if string.len(payload)>=6 then
   if string.sub(payload,6,8) == "bip" then
    isBeeping = string.sub(payload,9,9) == "1"
   end 
  end

  reply = "Beep status " .. tostring(isBeeping)
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
