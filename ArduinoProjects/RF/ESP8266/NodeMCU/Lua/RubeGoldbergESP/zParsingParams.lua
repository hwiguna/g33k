-- Split --
payload="GET /101,102,103,104,23 HTTP/1.1"
ips = string.sub(payload,6, string.len(payload)-9)
for w in string.gmatch(ips, "%d+") do
 print(w)
end

-- Get first number --
payload="GET /101,102,103,104,23  HTTP/1.1"
for i=1,6 do
 if string.sub(payload,6,6)~=" " then
  digitBegin=string.find(payload,"/")+1
  digitEnd=string.find(payload, ",", digitBegin)
  if digitEnd==nil then digitEnd=string.find(payload, " ", digitBegin) end
  if digitEnd~=nil then
   nextGuy = string.sub(payload, digitBegin, digitEnd-1)
   payload = "GET /" .. string.sub(payload, digitEnd + 1)
   print("Send " .. payload .. " to " .. nextGuy )
  end
 end
end


-- Turn it into a function --
function parsePayload(payload)
   digitBegin=string.find(payload,"/")+1
   digitEnd=string.find(payload, ",", digitBegin)
   if digitEnd==nil then digitEnd=string.find(payload, " ", digitBegin) end
   if digitEnd~=nil then
    nextGuy = "192.168.254." .. string.sub(payload, digitBegin, digitEnd-1)
    payload = "GET /" .. string.sub(payload, digitEnd + 1)
    --print("Send " .. payload .. " to " .. nextGuy )
   end
 return payload
end

payload="GET /101,102,103,104,23  HTTP/1.1"
for i=1,6 do
 if string.sub(payload,6,6)~=" " then
  payload = parsePayload(payload)
  print("Send " .. payload .. " to " .. nextGuy )
 end
end

-- Test --
payload="101,102,103,104,23,"
for i=1,6 do
 payload = parsePayload(payload)
 if string.len(payload) > 0 then
  print("Send " .. payload .. " to " .. nextGuy )
 end
end



--- Simpler version? ---
function parsePayload(payload)
 digitEnd=string.find(payload, ",")
 if digitEnd ~= nil then
  nextGuy = "192.168.254." .. string.sub(payload, 1, digitEnd-1)
  payload = string.sub(payload, digitEnd + 1)
 end
 return payload
end

-- I/O --
led=9
gpio.mode(led,gpio.OUTPUT)
gpio.write(led,gpio.HIGH)

-- LUA Webserver --
srv=net.createServer(net.TCP)

srv:listen(80,function(conn)

  conn:on("receive",function(conn,payload)
    gpio.write(led,gpio.LOW) -- Turn on LED as soon as we get request
    
    if string.sub(payload,6,6)~=" " then
	 ips = string.sub(payload, 6, string.find(payload," ",6)-1)
	 print("ips=" .. ips)
     payload = parsePayload( ips )
     reply = "Sent " .. payload .. " to " .. nextGuy
    else
     reply = "Done!"
    end

    payloadLen = string.len(reply)
    conn:send("HTTP/1.1 200 OK\r\n")
    conn:send("Content-Length:" .. tostring(payloadLen) .. "\r\n")
    conn:send("Connection:close\r\n\r\n")
    conn:send(reply)
	
	-- LUA Web Client --
    client = net.createConnection( net.TCP, false)
    client:on("receive", function(c, payload) print("REPLIED: " .. payload) end)
    client:connect(80,nextGuy)
    client:send("GET /" .. payload .. " HTTP/1.1\r\n\r\n")

    gpio.write(led,gpio.HIGH) -- Turn off LED when we're done
  end)

  conn:on("sent",function(conn)
    conn:close()
  end)
end)
