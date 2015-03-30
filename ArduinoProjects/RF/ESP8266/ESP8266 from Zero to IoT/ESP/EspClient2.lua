-- When switch value changes, send it to server --

function SendWebRequest_UponSwitchStateChange()
	-- Include shared configuration settings --
	require "config"

	-- Check WiFi connection --
	print("ESP IPAddress: " .. wifi.sta.getip())

	-- Setup GPIO --
	switchPin = 3 -- GPIO0
	gpio.mode(switchPin,gpio.INPUT)
	ledPin = 4 -- 3=GPIO00, 4=GPIO2
	gpio.mode(ledPin,gpio.OUTPUT)

	-- Setup variables --
	timerId = 0
	dly=100
	lastSwitchValue = 1 -- Set to 1 so initial state won't send a web request

	-- Check Switch periodically and send Web Request when switch changes state
	tmr.alarm( timerId, dly, 1, function() 
	  switchValue = gpio.read( switchPin )
	  if (switchValue ~= lastSwitchValue) then
		print("memory=" .. node.heap())
		print("switchValue=" .. switchValue)
		gpio.write(ledPin,switchValue)

		print("Sending request to " .. config.serverIP.. "/" .. config.serverPort)
		conn=net.createConnection(net.TCP, false) 
		--conn:on("receive", function(conn, pl) print(pl) end)
		conn:connect(config.serverPort, config.serverIP)
		conn:send("GET /set?v=" .. switchValue .. " HTTP/1.1\r\n" .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")

		lastSwitchValue = switchValue;
	  end
	end)
end

SendWebRequest_UponSwitchStateChange()
