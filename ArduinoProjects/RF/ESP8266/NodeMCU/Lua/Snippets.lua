-- Two dashes starts a comment

-- from Jankop
-- http://www.esp8266.com/viewtopic.php?f=24&t=826&p=4718#p4686
tmr.alarm(1,1000, 1, function() if wifi.sta.getip()==nil then print(" Wait to IP address!") else print("New IP address is "..wifi.sta.getip()) tmr.stop(1) end end)

s = "123"
print(string.sub(s,2,2))
print(digits[tonumber(string.sub(s,2,2))])

a = 1
b = 2
c = a + b
print (c)

node.restart()
print(wifi.sta.getip()) -- Print IP Address
print(node.heap()) 	-- Print Available Memory

print(wifi.sta.getip())
wifi.setmode(wifi.STATION)
wifi.sta.config ( "WIFI_SSID" , "PASSWORD" )  
print(wifi.sta.getip())

-- I/O --
led=9
gpio.mode(led,gpio.OUTPUT)
gpio.write(led,gpio.LOW)
gpio.write(led,gpio.HIGH)

-- LUA Web Client --
conn = net.createConnection( net.TCP, false)
conn:on("receive", function(c, payload) print(payload) end)
conn:connect(80,"115.239.210.27")
conn:send("GET / HTTP/1.1\r\n\r\n")

-- LUA Web Client --
conn = net.createConnection( net.TCP, false)
conn:on("receive", function(c, payload) print(payload) end)
conn:connect(80,"www.baidu.com")
conn:send("GET / HTTP/1.1\r\n\r\n")

-- LUA Web Client with DNS lookup --
address = 'unknown'
conn = net.createConnection( net.TCP, 0)
conn:on("receive", function(c, payload) print(payload) end)
conn.dns(conn, "thawing-depths-8215.herokuapp.com", function(conn, ip) print(ip) address=ip end)
print(address)
conn:connect(80,address)
conn:send("GET / HTTP/1.1\r\nHost: thawing-depths-8215.herokuapp.com\r\n\r\n")

-- File List --
l = file.list();
for k,v in pairs(l) do
  print("name:"..k..", size:"..v)
end

-- Print File Content --
filename = 'blink.lua'
txt = ''
file.open(filename,"r")
repeat
  line = file.readline()
  if (line~=nil) then txt = txt .. line end
until line==nil
file.close()
print(txt)



print(node.heap()) 	-- Print Available Memory

-- One time ESP Setup --
wifi.setmode(wifi.STATION)
wifi.sta.config ( "WIFI_SSID" , "PASSWORD" )  
print(wifi.sta.getip())

-- Blink using timer alarm --
timerId = 0 -- we have seven timers! 0..6
dly = 500 -- milliseconds
ledPin = 4 -- 4=GPIO2 https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en#gpio-new-table--build-20141219-and-later
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0
tmr.stop(timerId)
tmr.alarm( timerId, dly, 1, function() 
  ledState = 1 - ledState;
  gpio.write(ledPin, ledState)
end)



























dofile("webserver.lua")	-- Launch Program --

print(wifi.sta.getip())
--0.0.0.0
wifi.setmode(wifi.STATION)
wifi.sta.config("SSID","password")
print(wifi.sta.getip())
--192.168.18.110


file.remove("door.lua")
file.open("door.lua","w")
file.writeline([[srv=net.createServer(net.TCP) srv:listen(80,function(conn)]])
file.writeline([[conn:on("receive",function(conn,payload)]])
file.writeline([[print(node.heap())]])
file.writeline([[door="open"]])
file.writeline([[if gpio.read(8)==1 then door="OPEN" else door="CLOSED" end]])
file.writeline([[conn:send("<h1> The door is " .. door ..".</h1>")]])
file.writeline([[end)]])
file.writeline([[conn:on("sent",function(conn) conn:close() end)]])
file.writeline([[end)]])
file.close()


file.remove("door.lua")
file.open("door.lua","w")
file.writeline([[srv=net.createServer(net.TCP) srv:listen(80,function(conn)]])
file.writeline([[conn:on("receive",function(conn,payload)]])
file.writeline([[print(node.heap())]])
file.writeline([[door="open"]])
file.writeline([[if gpio.read(9)==1 then door="OPEn" else door="CLOSEd" end]])
file.writeline([[conn:send("<h1> The door is " .. door ..".</h1>")]])
file.writeline([[end)]])
file.writeline([[conn:on("sent",function(conn) conn:close() end)]])
file.writeline([[end)]])
file.close()

node.restart()
dofile("door.lua")

print(gpio.mode(9,gpio.INPUT))
print(gpio.read(9))

C:\Users\hwiguna\Documents\Git\g33k\ArduinoProjects\RF\ESP8266\NodeMCU\Lua\door.lua.txt

gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then door="OPEn" else door="CLOSEd" end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)
-------------------------

tmr.stop()
dly = 1000
isOn = false
led = 9
gpio.mode(led,gpio.OUTPUT)
tmr.alarm( dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(led,gpio.HIGH)
  else
    gpio.write(led,gpio.LOW)
  end
end)

gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then door="OPEn" else door="CLOSEd" end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)

------------------

tmr.stop()

gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then
      door="OPEn" gpio.write(led,gpio.HIGH)
    else
      door="CLOSEd" gpio.write(led,gpio.LOW)
    end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)

dly = 1000
isOn = false
led = 9
gpio.mode(led,gpio.OUTPUT)
tmr.alarm( dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(led,gpio.HIGH)
  else
    gpio.write(led,gpio.LOW)
  end
end)





dly = 1000000
led = 9
gpio.mode(led,gpio.OUTPUT)
repeat
  gpio.write(led,gpio.HIGH)
  tmr.delay( dly )
  gpio.write(led,gpio.LOW)
  tmr.delay( dly )
until false



gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then door="OPEn" else door="CLOSEd" end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)





gpio.mode(8,gpio.INPUT)
srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
  conn:on("receive",function(conn,payload)
    print(node.heap())
    door="open"
    if gpio.read(8)==1 then door="OPEn" else door="CLOSEd" end
    conn:send("<h1> The door is " .. door ..".</h1>")
  end)
  conn:on("sent",function(conn)
    conn:close()
  end)
end)

dly = 1000000
led = 9
gpio.mode(led,gpio.OUTPUT)
repeat
  gpio.write(led,gpio.HIGH)
  tmr.delay( dly )
  gpio.write(led,gpio.LOW)
  tmr.delay( dly )
until false


dly = 1000
isOn = false
led = 9
gpio.mode(led,gpio.OUTPUT)
tmr.alarm( dly, 1, function() 
  isOn = not isOn
  if isOn then
    gpio.write(led,gpio.HIGH)
  else
    gpio.write(led,gpio.LOW)
  end
end


------------------------
	  $.ajax({
	    dataType: "json",
		url: "/a",
		data: data,
		success: function(data, status, xhr) { $("#DataFromESP").html("status:" + status);},
		fail: function(xhr, status, errStr) {
		  $("#DataFromESP").html("err:" + errStr);
		}
	  });
	  
//	  $.getJSON("192.168.254.100:8080", function(data) {
//	    alert(data);
//	  });


-- Saving data --
a = 7
b = 8

fname = "data.lua"
file.open(fname,"w")
file.writeline("a="..a)
file.writeline("b="..b)
file.close()

file.open(fname,"r")
repeat
 line=file.readline()
 pcall(loadstring(line))
until (line == nil)
file.close()

print(a)
print(b)





-- Writing data to a file --
function Saver(fname)
 file.open(fname,"w")
 file.writeline("a="..a)
 file.writeline("b="..b)
 file.writeline("c=\""..c.."\"")
 file.close()
end


-- Sample Program --
a=7
b=8
c="Hello"
Saver("data.lua")

node.restart()

print(a)
print(b)
print(c)


-- Reading data from a file --
function Loadr(fname)
 file.open(fname,"r")
 repeat
  line = file.readline()
  if line ~= nil then pcall(loadstring(line)) end
 until line == nil
 file.close()
end

Loadr("data.lua")
print(a)
print(b)
print(c)

--------------------------------------
-- Sample variables --
a=7
b=8
c="Hello"

-- Write data to a file --
file.open("data.lua","w")
file.writeline("a="..a)
file.writeline("b="..b)
file.writeline("c=\""..c.."\"")
file.close()

-- Restart --
node.restart()

-- All gone! --
print(a)
print(b)
print(c)

-- Read data from a file --
-- pcall(loadstring(x)) executes the string as if we typed it! -- 
file.open("data.lua","r")
repeat
 line = file.readline()
 if line ~= nil then pcall(loadstring(line)) end
until line == nil
file.close()

-- We're back! --
Loadr("data.lua")
print(a)
print(b)
print(c)
