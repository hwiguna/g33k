-- Check to see if we have our WiFi credentials setup yet --
print(wifi.sta.getip()) -- nil means we have not set WiFi up

-- Execute these two lines (with proper SSID and password) --
wifi.setmode(wifi.STATION)
wifi.sta.config( "Firefly24" , "Buckbeak&Stu" ) 

-- Then check again --
print(wifi.sta.getip())
