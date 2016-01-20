#ifndef PAGE_EXAMPLE_H
#define PAGE_EXAMPLE_H
//
//   The EXAMPLE PAGE
//

const char PAGE_example[] PROGMEM = R"=====(
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <h1>ESP8266 WiFi Thermometer</h1>     

  <table width="400">
    <tr><td align="center"><div id="mydynamicdata" style="font-size:96" >?</div> </td><td align="center"><div id="myHumidity" style="font-size:96" >?</div></td></tr>
    <tr><td align="center">Temperature</td><td align="center">Humidity</td></tr>
  </table>
  
  <script>
		window.onload = function ()
		{
			load("style.css","css", function() 
			{
				load("microajax.js","js", function() 
				{
						setValues("/admin/filldynamicdata");  //-- this function calls the function on the ESP      
				});
			});
		}
		function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



   </script>

)=====";
#endif


void filldynamicdata()
{     

  //--- READ TEMPERATURE ---
  int f = dht.readTemperature(true);
  Serial.print(F("Temperature = ")); Serial.println(f, DEC);

  String values ="";
  values += "mydynamicdata|" + (String) f + "|div\n";   // Build a string, like this:  ID|VALUE|TYPE

  //--- READ HUMIDITY ---
  int h = dht.readHumidity();
  Serial.print(F("Humidity = ")); Serial.println(h, DEC);

  values += "myHumidity|" + (String) h + "|div\n";   // Build a string, like this:  ID|VALUE|TYPE
  server.send ( 200, "text/plain", values);   
}

void processExample()
{        
    if (server.args() > 0 )  // Are there any POST/GET Fields ? 
    {
       for ( uint8_t i = 0; i < server.args(); i++ ) {  // Iterate through the fields
            if (server.argName(i) == "firstname") 
            {
                 // Your processing for the transmitted form-variable 
                 String fName = server.arg(i);
            }
        }
    }
    server.send ( 200, "text/html", PAGE_example  ); 
}
