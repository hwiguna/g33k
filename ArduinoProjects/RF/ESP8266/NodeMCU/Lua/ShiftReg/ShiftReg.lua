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

bitsString = "00010010" -- "11101101"
--function shiftOut(dataPin, clockPin, bits)
 gpio.write(latchPin,gpio.LOW) -- Don't reflect changes to LED (yet...)
 for b=1,8 do
  gpio.write(clockPin,gpio.LOW)

  if (string.sub(bitsString, b,b) == "1") then
   gpio.write(dataPin,gpio.HIGH)
  else
   gpio.write(dataPin,gpio.LOW)
  end

  gpio.write(clockPin,gpio.HIGH)
 end
 
 gpio.write(latchPin,gpio.HIGH) -- Transfer to LED
--end
