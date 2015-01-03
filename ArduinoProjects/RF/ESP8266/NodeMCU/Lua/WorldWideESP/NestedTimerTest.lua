-- Beeper --
beepPin = 4 -- GPIO 02
gpio.mode(beepPin, gpio.OUTPUT)

beepCount = 0

function Beep()
 -- Alternatingly turn on/off the beeper each time Beep is called.
 if (beepCount % 2) == 0 then
  gpio.write(beepPin,0) -- ON
 else
  gpio.write(beepPin,1) -- off
 end
 beepCount = beepCount + 1

 if beepCount < 6 then
  tmr.alarm(1, 50, 0, Beep) 
 end
end

function EverySecond()
 print "-"
 beepCount = 0
 tmr.alarm(1, 100, 0, Beep)
end

tmr.alarm(0, 2000, 1, EverySecond)

-----------------------------------------

-- Beeper --
beepPin = 4 -- GPIO 02
gpio.mode(beepPin, gpio.OUTPUT)

beepCount = 0

function Beep()
 gpio.write(beepPin, (beepCount % 2) )
 beepCount = beepCount + 1
 if beepCount < 6 then tmr.alarm(1, 50, 0, Beep) end
end

function Every2Seconds()
 beepCount = 0
 tmr.alarm(1, 100, 0, Beep)
end

tmr.alarm(0, 2000, 1, Every2Seconds)
