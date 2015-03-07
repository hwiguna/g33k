io2 = 4
gpio.mode(io2,gpio.OUTPUT)
gpio.write(io2, 0)
function Transmit()
  gpio.write(io2, 0 ) -- ON
  conn = net.createConnection( net.TCP, false)
  conn:on("receive", function(c, payload) 
    print(payload)
    gpio.write(io2, 1 ) -- off
  end)
  conn:connect(8000,"192.168.254.125")
  conn:send("GET /bip1 HTTP/1.1\r\n\r\n")
end
print("Ready to Transmit!")
Transmit()