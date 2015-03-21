-- Check ESP --
print(wifi.sta.getip())
print(node.heap())

-- NodeMCU WebClient
serverIP = "192.168.254.101"
serverPort = 8000
conn=net.createConnection(net.TCP, false) 
conn:on("receive", function(conn, pl) print(pl) end)
conn:connect(serverPort, serverIP)

switchPin = 3 -- GPIO0
gpio.mode(switchPin,gpio.INPUT)

lastSwitchValue = -1
print("Ready!")

timerId = 0
dly=100
tmr.stop(0)
tmr.alarm( timerId, dly, 1, function() 
  switchValue = gpio.read( switchPin )
  if (switchValue ~= lastSwitchValue) then
    print(switchValue)
    conn:send("GET /set?b=" .. switchValue .. " HTTP/1.1\r\n" .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")
    lastSwitchValue = switchValue
  end
end)

