-- Auto shut off --
io0 = 3 -- pull down during bootup to burn firmware
io2 = 4 -- Don't pull low on bootup
gpio.mode(io2,gpio.OUTPUT)
gpio.write(io2, 1)

print("Hello...")

timerId = 0 -- we have seven timers! 0..6
dly = 1000 -- milliseconds
kount = 3
tmr.alarm( timerId, dly, 1, function() 
  print(kount)
  if kount < 0 then
    print("Bye")
    kount = 3
    gpio.write(io2, 0)
  end
  kount = kount - 1
end)