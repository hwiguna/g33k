-- from http://www.esp8266.com/viewtopic.php?f=18&t=628
function wait_wifi()
  count = count + 1
  --print("Waiting for WiFi .." .. count)
  gpio.write(led,gpio.LOW)
  wifi_ip = wifi.sta.getip()
  if wifi_ip == nil and count < 20 then
    tmr.alarm(0, 1000,0,wait_wifi)
  elseif count >= 20 then
    wifi_connected = false
    --print("Wifi connect timed out.")
  else
    wifi_connected = true
    --print("Got IP "..wifi_ip.."\n")
    gpio.write(led,gpio.HIGH)
    dofile("WorldWideTX.lua")
  end
end

-- Wait for WiFi --
count=0
wait_wifi()