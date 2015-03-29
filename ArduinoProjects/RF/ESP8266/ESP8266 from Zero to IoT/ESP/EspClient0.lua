-- Check ESP --
print(wifi.sta.getip())
print(node.heap())

-- NodeMCU WebClient
serverIP = "192.168.254.101"
serverPort = 8000
conn=net.createConnection(net.TCP, false) 
conn:on("receive", function(conn, pl) print(pl) end)
conn:connect(serverPort, serverIP)
conn:send("GET / HTTP/1.1\r\n" .."Connection: keep-alive\r\nAccept: */*\r\n\r\n")
