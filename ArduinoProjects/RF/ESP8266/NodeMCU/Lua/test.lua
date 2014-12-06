-- Two dashes starts a comment
node.restart()
print(wifi.sta.getip()) -- Print IP Address
print(node.heap()) 		-- Print Available Memory

print(wifi.sta.getip())
wifi.setmode(wifi.STATION)
wifi.sta.config ( "WIFI_SSID" , "PASSWORD" )  
print(wifi.sta.getip())


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


-- Blink using timer alarm --
dly = 200 -- milliseconds
ledPin = 9
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0 -- gpio.HIGH=1, gpio.LOW=0
tmr.stop() -- There's only one timer, so make sure it's stopped before we start this one.
tmr.alarm( dly, 1, function() 
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
