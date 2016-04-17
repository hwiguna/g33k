// PCF8574 WebServer, listens for /inline?state=
// Hari Wiguna, 2016

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Declare and set these two variables here or in an include file
//const byte credentialCount = 2; //IMPORTANT! Change this to match how many credentials you have!
//const char* credentials[] =
//{
//  "ssid1","pwd1",
//  "ssid2","pwd2"
//};
#include "C:\Users\hwiguna\Documents\Creds\creds.txt"

const byte bufMax = 20;
char ssid[bufMax];
char password[bufMax];

ESP8266WebServer server(80);

void ScanWiFi()
{
  bool found = false;
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; (i < n) && !found; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.print((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "* ");
      delay(10);

      char foundssid[bufMax];
      WiFi.SSID(i).toCharArray(foundssid, bufMax);

      for (byte i = 0; i < credentialCount; i++)
      {
        if ( strcmp( foundssid, credentials[i*2]) == 0)
        {
          Serial.print("<-- MATCH");
          strcpy(ssid, credentials[i*2]);
          strcpy(password, credentials[i*2 + 1]);
          found = true;
          exit;
        }
      }
      Serial.println();
    }
  }
  Serial.println("");
}

//------------------------------------
#include <Wire.h>

int mode = 0;
uint8_t error, address, curVal, val;

void LedRefresh(uint8 addr)
{
  Wire.beginTransmission(addr);
  Wire.write(~val);
  error = Wire.endTransmission();
}

void SetLeds(int num)
{
  val = num & 0xFF;
  LedRefresh(address);
  
  val = num >> 8;
  LedRefresh(address + 1);
}

//------------------------------------
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  Serial.begin(115200);

  ScanWiFi(); 
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);


  //=== PCF8574 Specific code ===
  server.on("/inline", [](){
    String state = server.arg("state");
    int num = state.toInt();
    String out = String(num);
    server.send(200, "text/plain", out);
    SetLeds(num);
  });
  //=== PCF8574 Specific code ===


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  //--- LED ---
  //Wire.begin(); // Arduino needs (SDA=A4,SCL=A5)
  Wire.begin(0, 2); // ESP8266 needs (SDA=GPIO0,SCL=GPIO2)
  address = 0x20;
}

void loop(void){
  server.handleClient();
}
