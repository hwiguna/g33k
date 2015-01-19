led=4 -- GPIO02
gpio.mode(led,gpio.OUTPUT)

function Transmit()
  gpio.write(led, 0 ) -- ON
  conn = net.createConnection( net.TCP, false)
  conn:on("receive", function(c, payload) 
    print(payload)
    gpio.write(led, 1 ) -- off
  end)
  conn:connect(80,"192.168.254.100")
  conn:send("GET /bip1 HTTP/1.1\r\n\r\n")
end
print("Ready to Transmit!")
Transmit()
tmr.alarm(0, 2000, 1, Transmit)