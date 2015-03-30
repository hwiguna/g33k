-- When switch value changes, send it to server
-- DO NOT USE THIS VERSION!!!  Use latest version of EspClientx.lua.
--
-- Lesson learned from this version:
-- When variables go out of scope, NodeMCU EVENTUALLY does garbage collection, causing unpredictable failure.
-- In future versions, I encapsulate everything in a function so all variables remain alive for the life of the function.

require "config"

-- Check ESP --
print(wifi.sta.getip())
print(node.heap())

-- NodeMCU WebClient
serverIP = config.serverIP -- Raspberry Pi IP Address
serverPort = config.serverPort -- Raspberry Pi Port
conn=net.createConnection(net.TCP, false) 
conn:on("receive", function(conn, pl) print(pl) end)
conn:connect(serverPort, serverIP)

print("Will send requests to " .. serverIP .. "/" .. serverPort )

-- Setup GPIO --
switchPin = 3 -- GPIO0
gpio.mode(switchPin,gpio.INPUT)
ledPin = 4 -- 3=GPIO00, 4=GPIO2
gpio.mode(ledPin,gpio.OUTPUT)

-- Setup variables --
lastSwitchValue = -1
timerId = 0
dly=100

-- Check Switch periodically and send Web Request when switch changes state
tmr.alarm( timerId, dly, 1, function() 
  switchValue = gpio.read( switchPin )
  if (switchValue ~= lastSwitchValue) then
    print("switchValue=" .. switchValue)
    gpio.write(ledPin,switchValue)
    conn:send("GET /set?v=" .. switchValue .. " HTTP/1.1\r\n" .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")
    lastSwitchValue = switchValue;
  end
end)
