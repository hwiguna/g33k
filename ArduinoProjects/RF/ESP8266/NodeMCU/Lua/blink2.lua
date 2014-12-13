-- Blink using timer alarm --
dly = 1000 -- miliseconds
isOn = false

led = 8 -- 8=GPIO 00, 9=GPIO 02
gpio.mode(led,gpio.OUTPUT)

tmr.stop(0) -- There are now 0..7 timers!!!
tmr.alarm(0, dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(led,gpio.HIGH)
  else
    gpio.write(led,gpio.LOW)
  end
end)