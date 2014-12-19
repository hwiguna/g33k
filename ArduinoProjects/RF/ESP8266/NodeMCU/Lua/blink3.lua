-- Blink using timer alarm --
dly = 1000 -- miliseconds
isOn = false

out0=8
out1=9
gpio.mode(out0,gpio.OUTPUT)
gpio.mode(out1,gpio.OUTPUT)

tmr.stop(0) -- There are now 0..7 timers!!!
tmr.alarm(0, dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(out0,gpio.LOW)
    gpio.write(out1,gpio.HIGH)
  else
    gpio.write(out0,gpio.HIGH)
    gpio.write(out1,gpio.LOW)
  end
end)