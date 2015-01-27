-- Turn on GPIO 0 --
powerPin = 3 -- 3=GPIO0
gpio.mode(powerPin,gpio.OUTPUT)
gpio.write(powerPin,1)


-- Auto Turn-off in 4 seconds --
timerId = 0 -- we have seven timers! 0..6
dly = 4000 -- milliseconds
tmr.alarm( timerId, dly, 0, function() 
  gpio.write(powerPin,0)
end)
