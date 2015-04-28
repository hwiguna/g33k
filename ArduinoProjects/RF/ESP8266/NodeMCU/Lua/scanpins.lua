-- Many GPIO on ESP-12
dly = 100 -- miliseconds

-- 0 : GPIO 16
-- 1 : GPIO 4
-- 2 : GPIO 5
-- 3 : GPIO 0
-- 4 : GPIO 2
-- 5 : GPIO 14
-- 6 : GPIO 12
-- 7 : GPIO 13
-- 8 : GPIO 15
-- 9 : GPIO 3
-- 0 : GPIO 1
-- 10 : GPIO 9
-- 11 : GPIO 10

-- GPIOs 4,5,0,2, 16,14,12,13 -- 15 must be low :-(
pins = {1,2,3,4, 0,5,6,7, 6,5,0, 4,3,2}
pinIndex = 8+6

for i=1,8 do
  gpio.mode( pins[i], gpio.OUTPUT)
  print(pins[i])
end

tmr.stop(0) -- There are now 0..7 timers!!!
tmr.alarm(0, dly, 1, function() 
  gpio.write( pins[pinIndex],gpio.HIGH)
  pinIndex = pinIndex - 1
  if pinIndex<1 then
    pinIndex=8+6
  end
  gpio.write( pins[pinIndex],gpio.LOW)
end)