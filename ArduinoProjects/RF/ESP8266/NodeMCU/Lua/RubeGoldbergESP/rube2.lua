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
io0=3
gpio.mode(io0,gpio.INPUT)


led=4
gpio.mode(led,gpio.OUTPUT)
gpio.write(led,gpio.LOW)

-- LUA Webserver --
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)

	conn:on("receive",function(conn,payload)
		if string.find(payload,"favicon.ico") == nil then
			gpio.write(led,gpio.LOW) -- Turn on LED upon valid request (ignore favicon)
			if string.sub(payload,6,6)~=" " then
				ips = string.sub(payload, 6, string.find(payload," ",6)-1)
				--print("ips=" .. ips)
				payload = parsePayload( ips )

				if nextGuy ~= nil then
					-- LUA Web Client --
					client = net.createConnection( net.TCP, false)
					client:on("receive", function(c, payload) r=1 end)
					client:connect(80,nextGuy)
					client:send("GET /" .. payload .. " HTTP/1.1\r\n\r\n")
					reply = "Sent " .. payload .. " to " .. nextGuy
				else
					reply = "No nextGuy!"
				end
			else
				reply = "Done!"
			end
		else
			reply = "favicon ignored"
		end

		payloadLen = string.len(reply)
		conn:send("HTTP/1.1 200 OK\r\n")
		conn:send("Content-Length:" .. tostring(payloadLen) .. "\r\n")
		conn:send("Connection:close\r\n\r\n")
		conn:send(reply)

		gpio.write(led,gpio.HIGH) -- Turn off LED when we're done
	end)

	conn:on("sent",function(conn)
		conn:close()
	end)
end)

--print(wifi.sta.getip() .. " READY!")
gpio.write(led,gpio.HIGH)