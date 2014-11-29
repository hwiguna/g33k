-- I/O Pin constants --
switchPin = 8
ledPin = 9

-- Setup I/O pins --
gpio.mode(switchPin,gpio.INPUT)
gpio.mode(ledPin,gpio.OUTPUT)

-- LUA Webserver --
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
		gpio.write(ledPin, ledValue)
		
		reply = "{ \"led\":\"" .. tostring(ledValue) .. "\" }"
	else
		switchValue = gpio.read( switchPin )
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
