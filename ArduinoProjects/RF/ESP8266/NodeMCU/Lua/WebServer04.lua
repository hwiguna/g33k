-- One time Wifi setup --
wifi.setmode(wifi.STATION)
wifi.sta.config ( "WIFI_SSID" , "PASSWORD" )  
print(wifi.sta.getip())

--------------------------------------------------

-- I/O configuration --
dataPin=0 -- SER
latchPin=1 -- RCLK
clockPin=2 -- SRCLK
gpio.mode(dataPin,gpio.OUTPUT)
gpio.mode(latchPin,gpio.OUTPUT)
gpio.mode(clockPin,gpio.OUTPUT)

-- Initialize all to LOW --
gpio.write(dataPin,gpio.LOW)
gpio.write(latchPin,gpio.LOW)
gpio.write(clockPin,gpio.LOW)

function shiftOut(dataPin, clockPin, latchPin, bitz)
 gpio.write(latchPin,gpio.LOW) -- Don't reflect changes to LED (yet...)
 for b=1,8 do
  gpio.write(clockPin,gpio.LOW)

  if (string.sub(bitz, b,b) == "0") then
   gpio.write(dataPin,gpio.HIGH)
  else
   gpio.write(dataPin,gpio.LOW)
  end

  gpio.write(clockPin,gpio.HIGH)
 end
 
 gpio.write(latchPin,gpio.HIGH) -- Transfer to LED
end

digits={"11111100", "01100000", "11011010", "11110010", "01100110", "10110110", "10111110", "11100000", "11111110", "11110110"}

-- Testing --
print(digits[1])
bits = digits[1]
shiftOut(dataPin, clockPin, latchPin, bits)

-----------------------------------

-- LUA Webserver --
srv=net.createServer(net.TCP)

srv:listen(80,function(conn)

  conn:on("receive",function(conn,payload)
    print(payload)
    bitz="?"
    if string.len(payload)>=6 then
     if string.sub(payload,6,8) == "dig" then
      index = tonumber(string.sub(payload,9,9))
      bitz = tostring(digits[index+1])
      shiftOut(dataPin, clockPin, latchPin, bitz)
     end 
    end

    reply = "Sent to Shift Register: " .. bitz 
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

print(wifi.sta.getip())
