led=4 -- GPIO02
gpio.mode(led,gpio.OUTPUT)
tmr.stop(0)
tmr.stop(1)

function Transmit()
  gpio.write(led, 0 ) -- ON
  print("Transmitting to nodeJS...")
  conn = net.createConnection( net.TCP, 0)
  conn:on("receive", function(c, payload) 
    print(payload)
    gpio.write(led, 1 ) -- off
  end)

  conn:connect(8000,"192.168.254.125")
  
  conn:send("GET / HTTP/1.1\r\nConnection: keep-alive\r\n")
  conn:send("Host: 192.168.254.125\r\n") 
  conn:send("Accept: */*\r\n") 
  conn:send("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n")
  conn:send("\r\n")
  
  conn:on("sent",function(conn)
                      print("Closing connection")
                      conn:close()
                  end)

  conn:on("disconnection", function(conn)
          print("Got disconnection...")
  end)
end

-- from http://www.esp8266.com/viewtopic.php?f=18&t=628
function wait_wifi()
  count = count + 1
  print("Waiting for WiFi .." .. count)
  gpio.write(led,gpio.LOW)
  wifi_ip = wifi.sta.getip()
  if wifi_ip == nil and count < 20 then
    tmr.alarm(0, 1000,0,wait_wifi)
  elseif count >= 20 then
    wifi_connected = false
    print("Wifi connect timed out.")
  else
    wifi_connected = true
    print("Got IP "..wifi_ip.."\n")
    gpio.write(led,gpio.HIGH)
    
	-- dofile("TXtoPi.lua")
	-- Sending immediately after getting IP is unreliable, so wait a second before sending --
	tmr.alarm(1, 3000, 0, function()
	  Transmit()
	end);
  end
end

-- Wait for WiFi --
count=0
wait_wifi()