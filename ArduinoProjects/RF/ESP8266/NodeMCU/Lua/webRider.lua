function SetupKnightRider()
  -- GPIOs 4,5,0,2, 16,14,12,13 -- 15 must be low :-(
  pins = {1,2,3,4, 0,5,6,7}

  for i=1,8 do
    gpio.mode( pins[i], gpio.OUTPUT)
    print(pins[i])
  end

  tmr.stop(0) -- There are now 0..7 timers!!!
end
	
--== LUA WebServer ==--
-- responds to:
-- /set?v=1 to turn on led
-- /set?v=0 to turn off led
-- /get returns button state

function EspServer()
	-- Configuration --
	serverPort = 80
	print("ESP listening at " .. wifi.sta.getip() .. ":" .. serverPort )


	-- LUA Webserver --
	srv=net.createServer(net.TCP)

	srv:listen(serverPort,function(conn)

	  conn:on("receive",function(conn,payload)
		--print(node.heap())
		--print(payload)
		
		-- 123456789012
		-- GET /set?v=1 HTTP/1.1 --
		command = string.sub(payload, 6,8) -- Get characters 6,7, and 8

		if command == "set" then
			receivedValue = string.sub(payload, 12,12) -- Get the 12th character
			print("Received value=" .. receivedValue)
			if receivedValue==1 then
 			  pins = {1,2,3,4, 0,5,6,7, 6,5,0, 4,3,2}
              dly = 100 -- miliseconds
			  tmr.alarm(0, dly, 1, function() 
			    pinIndex = 8+6
  			    gpio.write(pins[pinIndex],gpio.HIGH)
  			    pinIndex = pinIndex - 1
  			    if pinIndex<1 then
    		     	pinIndex=8+6
  			    end
  			    gpio.write( pins[pinIndex],gpio.LOW)
			  end)
			else
			  for i=1,8 do
				gpio.write( pins[i],gpio.HIGH)
			  end
              tmr.stop(0) -- There are now 0..7 timers!!!
			end
			reply = "{ \"led\":\"" .. tostring(receivedValue) .. "\" }"
			status = "HTTP/1.1 200 OK\r\n"
		elseif command == "get" then
			switchValue = gpio.read( switchPin )
			reply = "{ \"btn\":\"" .. tostring(switchValue) .. "\" }"
			status = "HTTP/1.1 200 OK\r\n"
		else
			reply = "{ \"err\":\"" .. command .. "\" }"
			status = "HTTP/1.1 404 Not Found\r\n"
		end
		
		payloadLen = string.len(reply)
		conn:send(status)
		conn:send("Content-Length:" .. tostring(payloadLen) .. "\r\n")
		conn:send("Connection:close\r\n\r\n")
		conn:send(reply)
	  end)

	  conn:on("sent",function(conn)
		conn:close()
	  end)
	end)
end
