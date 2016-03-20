// ESP8266 RGB Sliders
// by Hari Wiguna, 2016 for Jay!

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h" // See https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md#file-system-object-spiffs

const char* ssid = "Firefly24";
const char* password = "------";

int redPin = 2;
int greenPin = 0;
int bluePin = 3; // RX

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

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

void setup(void) {
  Serial.begin(115200);
  
  analogWriteRange(255); // instead of the ESP8266 default of 1023
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
  //-- SPIFFS --
  Serial.print("SPIFFS begin=");
  Serial.println(SPIFFS.begin());

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

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.serveStatic("/index.htm", SPIFFS, "/index.htm"); //1=url, 3=in data

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
