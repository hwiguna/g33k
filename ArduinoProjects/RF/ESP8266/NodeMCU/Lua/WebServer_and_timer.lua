-- LUA Blink using timer alarm --
dly = 500
isOn = false
led = 9
gpio.mode(led,gpio.OUTPUT)

-- LUA Webserver to report I/O pin status --
gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    print(payload)
	
	-- 123456789012
	-- GET /set?b=1 HTTP/1.1 --
	command = string.sub(payload, 6,8) -- Get characters 6,7, and 8
	
	if (command == "set") then
		sentValue = string.sub(payload, 12,12) -- Get the 12th character
		print("sent value=" .. sentValue)
		if (sentValue=="0") then
		  ledValue = gpio.LOW
		else
		  ledValue = gpio.HIGH
		end
		gpio.write(led, ledValue)
		
		reply = "{ \"led\":\"" .. tostring(ledValue) .. "\" }"
	else
		switchValue = gpio.read(8)
		reply = "{ \"btn\":\"" .. tostring(switchValue) .. "\" }"
	end
	
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



-- Blink using timer alarm --
dly = 200
isOn = false
led = 9
gpio.mode(led,gpio.OUTPUT)
tmr.stop() -- There's only one timer, so make sure it's stopped before we start this one.
tmr.alarm( dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(led,gpio.HIGH)
  else
    gpio.write(led,gpio.LOW)
  end
end)


-- Webserver to report I/O pin status --
gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then
      door="open"
    else
      door="CLOSED"
    end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)
