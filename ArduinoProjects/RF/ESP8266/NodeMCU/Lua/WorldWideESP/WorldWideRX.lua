-- WorldWideRX.lua --

-- Beeper --
beepPin = 4 -- GPIO 02
gpio.mode(beepPin, gpio.OUTPUT)

beepCount = 0

function Beep()
 gpio.write(beepPin, (beepCount % 2) )
 if beepCount < 5 then tmr.alarm(1, 50, 0, Beep) end
 beepCount = beepCount + 1
end

function Every2Seconds()
 beepCount = 0
 tmr.alarm(1, 100, 0, Beep)
end

--tmr.alarm(0, 2000, 1, Every2Seconds)


-- Beep Webserver --
srv=net.createServer(net.TCP)

srv:listen(80,function(conn)
 conn:on("receive",function(conn,payload)
  isBeeping = false
  print(payload)
  if string.len(payload)>=6 then
   if string.sub(payload,6,8) == "bip" then
    isBeeping = string.sub(payload,9,9) == "1"
    if isBeeping then
	 Every2Seconds() -- Repeating is currently done by transmitter
     -- tmr.alarm(0, 2000, 1, Every2Seconds)
	else
     tmr.stop(0)
	end
   end 
  end

  reply = "Beep status " .. tostring(isBeeping)
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
