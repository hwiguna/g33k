-- Blink using timer alarm --
timerId = 0 -- we have seven timers! 0..6
dly = 500 -- milliseconds
ledPin = 4 -- 3=GPIO00, 4=GPIO2
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0
tmr.alarm( timerId, dly, 1, function() 
  ledState = 1 - ledState;
  gpio.write(ledPin, ledState)
end)