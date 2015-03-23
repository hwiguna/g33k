-- When switch value changes, send it to server

-- Check ESP --
print(wifi.sta.getip())
print(node.heap())

-- NodeMCU WebClient
serverIP = "192.168.254.125" -- Raspberry Pi IP Address
serverPort = 8000 -- Raspberry Pi Port
conn=net.createConnection(net.TCP, false) 
conn:on("receive", function(conn, pl) print(pl) end)
conn:connect(serverPort, serverIP)

-- Setup GPIO --
switchPin = 3 -- GPIO0
gpio.mode(switchPin,gpio.INPUT)

-- Setup variables --
lastSwitchValue = -1
timerId = 0
dly=100

-- Check Switch periodically and send Web Request when switch changes state
tmr.alarm( timerId, dly, 1, function() 
  switchValue = gpio.read( switchPin )
  if (switchValue ~= lastSwitchValue) then
    conn:send("GET /set?v=" .. switchValue .. " HTTP/1.1\r\n" .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")
    lastSwitchValue = switchValue;
  end
end)
