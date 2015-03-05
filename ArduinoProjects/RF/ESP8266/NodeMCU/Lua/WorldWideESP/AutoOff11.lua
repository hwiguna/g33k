-- Auto shut off --
io0 = 3 -- pull down during bootup to burn firmware
io2 = 4 -- Don't pull low on bootup
gpio.mode(io2,gpio.OUTPUT)
gpio.write(io2, 0)

print("Hello...")

timerId = 0 -- we have seven timers! 0..6
dly = 500 -- milliseconds
kount = 5
tmr.alarm( timerId, dly, 1, function() 
  print(kount)
  gpio.write(io2, kount % 2)
  if kount < 0 then
    tmr.stop(timerId)
    print("Bye")
    node.dsleep(0,1)
  end
  kount = kount - 1
end)
