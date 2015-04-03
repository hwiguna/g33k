--== LUA WebServer ==--
-- responds to:
-- /set?v=1 to turn on led
-- /set?v=0 to turn off led
-- /get returns button state

function EspServer()
	-- Configuration --
	serverPort = 80
	print("ESP listening at " .. wifi.sta.getip() .. ":" .. serverPort )

	-- I/O Pin constants --
	switchPin = 3 -- GPIO0
	ledPin = 4 -- GPIO2

	-- Setup I/O pins --
	gpio.mode(switchPin,gpio.INPUT)
	gpio.mode(ledPin,gpio.OUTPUT)

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
			gpio.write(ledPin, receivedValue)
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

EspServer()
