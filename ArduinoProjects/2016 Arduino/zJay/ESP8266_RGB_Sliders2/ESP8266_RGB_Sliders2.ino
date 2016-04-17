// ESP8266 RGB Sliders
// by Hari Wiguna, 2016 for Jay!

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h" // See https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md#file-system-object-spiffs

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

int redPin = 2;
int greenPin = 0;
int bluePin = 3; // RX

ESP8266WebServer server(80);

//void handleRoot() {
//  server.send(200, "text/plain", "hello from esp8266!");
//}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void SetColor(String colorArg, int colorPin)
{
  String valStr = server.arg(colorArg);
  if (valStr.length() > 0) {
    Serial.print( colorArg + "=");
    Serial.println(valStr);
    analogWrite(colorPin, valStr.toInt());
  }
}

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

  // Wait a bit before scanning again
  delay(5000);
}


void setup(void) {
  Serial.begin(115200);
  
  analogWriteRange(255); // instead of the ESP8266 default of 1023
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
  //-- SPIFFS --
  Serial.print("SPIFFS begin=");
  Serial.println(SPIFFS.begin());

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

  server.on("/test", []() {
    server.send(200, "text/plain", "ESP Server is working :-)");
  });

  server.serveStatic("/", SPIFFS, "/index.htm"); //1=url, 3=in data

  server.on("/set", []() {
    SetColor("r", redPin);
    SetColor("g", greenPin);
    SetColor("b", bluePin);
    server.send(200, "text/plain", "RGB called");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void) {
  server.handleClient();
}
