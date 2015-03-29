-- Read Pushbutton --
buttonPin = 3 -- 3=GPIO00, 4=GPIO2
gpio.mode(buttonPin,gpio.INPUT)

timerId = 0 -- we have seven timers! 0..6
dly = 100 -- milliseconds
ledPin = 4 -- 3=GPIO00, 4=GPIO2
gpio.mode(ledPin,gpio.OUTPUT)
tmr.alarm( timerId, dly, 1, function() 
  ledState = gpio.read(buttonPin)
  gpio.write(ledPin, ledState)
end)