-- Setup feedback LED --
beepPin = 4 -- GPIO 02
gpio.mode(beepPin, gpio.OUTPUT)

-- Beep Transmitter --
function Transmit()
  gpio.write(beepPin, 0 ) -- ON
  conn = net.createConnection( net.TCP, false)
  conn:on("receive", function(c, payload) 
    print(payload)
    gpio.write(beepPin, 1 ) -- off
  end)
  conn:connect(80,"192.168.254.100")
  conn:send("GET /bip1 HTTP/1.1\r\n\r\n")
end

Transmit()
tmr.alarm(0, 2000, 1, Transmit)

