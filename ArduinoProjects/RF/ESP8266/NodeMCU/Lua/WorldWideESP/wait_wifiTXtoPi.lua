led=4 -- GPIO02
gpio.mode(led,gpio.OUTPUT)
gpio.write(led,gpio.LOW) -- LED ON
tmr.stop(0)
tmr.stop(1)
serverIP = "192.168.254.125"

function Transmit()
  conn = net.createConnection( net.TCP, 0)
  print("Transmitting to nodeJS at " .. serverIP)
  
  conn:on("receive", function(c, payload) 
    print(payload)
    gpio.write(led,gpio.HIGH) -- LED OFF
    print("closing connection")
    conn:close()
  end)

  conn:on("connection",function(conn) 
    print("Connected")

    conn:send("GET / HTTP/1.1\r\n")
    conn:send("Host: " .. serverIP .. ":8000\r\n") 
    conn:send("Connection: close\r\n") 	
    conn:send("Accept: */*\r\n") 
    conn:send("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n")
    conn:send("\r\n")
   end)

  conn:on("disconnection", function(c)
    print("Got disconnection...")
  end)
  conn:on("sent", function(c)
    print("sent!")
  end)

  conn:connect(8000,serverIP)
end

-- from http://www.esp8266.com/viewtopic.php?f=18&t=628
function wait_wifi()
  count = count + 1
  print("Waiting for WiFi .." .. count)
  wifi_ip = wifi.sta.getip()
  if wifi_ip == nil and count < 20 then
    tmr.alarm(0, 1000,0,wait_wifi)
  elseif count >= 20 then
    wifi_connected = false
    print("Wifi connect timed out.")
  else
    wifi_connected = true
    print("Got IP "..wifi_ip.."\n")
	--tmr.alarm(1, 2000, 0, function()
      Transmit()
	--end)
  end
end

-- Wait for WiFi --
count=0
wait_wifi()