-- Blink using timer alarm --
dly = 200 -- milliseconds
ledPin = 9
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0 -- gpio.HIGH=1, gpio.LOW=0
tmr.stop() -- There's only one timer, so make sure it's stopped before we start this one.
tmr.alarm( dly, 1, function() 
  ledState = 1 - ledState;
  gpio.write(ledPin, ledState)
end)
