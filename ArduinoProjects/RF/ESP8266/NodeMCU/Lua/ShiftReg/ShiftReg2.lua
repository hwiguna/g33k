-- I/O configuration --
dataPin=0
latchPin=1
clockPin=2
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

  if (string.sub(bits, b,b) == "1") then
   gpio.write(dataPin,gpio.HIGH)
  else
   gpio.write(dataPin,gpio.LOW)
  end

  gpio.write(clockPin,gpio.HIGH)
 end
 
 gpio.write(latchPin,gpio.HIGH) -- Transfer to LED
end

frame=0

tmr.stop(0)
tmr.alarm(0, 1000,1, function()

if (frame % 2) == 0 then
  bits = "00010010"
else
 bits = "11101101"
end

frame=frame+1

shiftOut(dataPin, clockPin, latchPin, bits)

end)

