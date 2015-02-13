-- Setup GPIO2 as output and immediately turn it on --
ledPin = 4 -- 4=GPIO2 https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en#gpio-new-table--build-20141219-and-later
gpio.mode(ledPin,gpio.OUTPUT)
gpio.write(ledPin, 1);

-- In x milliseconds, turn off GPIO2 --
timerId = 0 -- we have seven timers! 0..6
dly = 3000 -- milliseconds
tmr.alarm( timerId, dly, 0, function() 
  gpio.write(ledPin, 0);
end)
