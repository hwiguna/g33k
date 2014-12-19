-- First test, blink an X-10 device --
-- I/O configuration ESP-01 --
gpio0=8 -- GPIO 0 is lua 8
gpio2=9 -- GPIO 2 is lua 9
offBtn=gpio0
 onBtn=gpio2
gpio.mode(offBtn,gpio.OUTPUT)
gpio.mode( onBtn,gpio.OUTPUT)
-- Initialize all to LOW --
gpio.write(offBtn,gpio.LOW)
gpio.write( onBtn,gpio.LOW)
-- Try blinking first --
dly=4000
isOn=false
tmr.stop(0)
tmr.stop(1)
tmr.alarm(0, dly, 1, function()
  isOn = not isOn
  --print(isOn)
  if isOn then
    gpio.write( onBtn,gpio.HIGH)
  else
    gpio.write(offBtn,gpio.HIGH)
  end
 tmr.alarm(1, 500, 0, function ()
  gpio.write( onBtn,gpio.LOW)
  gpio.write(offBtn,gpio.LOW)
  --print("done")
 end)
end)