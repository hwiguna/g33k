
-- I/O configuration --
dataPin=6 -- was 0 (GPIO 12)
latchPin=7 -- was 1 (GPIO 13)
clockPin=5 -- 2 was (GPIO 14)
gpio.mode(dataPin,gpio.OUTPUT)
gpio.mode(latchPin,gpio.OUTPUT)
gpio.mode(clockPin,gpio.OUTPUT)

-- Initialize all to LOW --
gpio.write(dataPin,gpio.LOW)
gpio.write(latchPin,gpio.LOW)
gpio.write(clockPin,gpio.LOW)

function shiftOut(dataPin, clockPin, latchPin, bits)
 gpio.write(latchPin,gpio.LOW) -- Don't reflect changes to LED (yet...)
 for b=1,8 do
  gpio.write(clockPin,gpio.LOW)

  if (string.sub(bits, b,b) == "0") then
   gpio.write(dataPin,gpio.HIGH)
  else
   gpio.write(dataPin,gpio.LOW)
  end

  gpio.write(clockPin,gpio.HIGH)
 end
 
 gpio.write(latchPin,gpio.HIGH) -- Transfer to LED
end

digits={"11111100", "01100000", "11011010", "11110010", "01100110", "10110110", "10111110", "11100000", "11111110", "11110110"}

-- Try one --
frame=1
print(digits[frame])

-- Count up every 200ms --
tmr.stop(0)
tmr.alarm(0, 200,1, function()
 bits = digits[ frame ]
 frame=frame+1
 if frame>10 then 
  frame=1
  print(node.heap())
 end
 shiftOut(dataPin, clockPin, latchPin, bits)
end)

