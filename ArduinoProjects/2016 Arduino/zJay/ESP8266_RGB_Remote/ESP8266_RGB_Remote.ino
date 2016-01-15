// ESP8266 RGB Remote
// by Hari Wiguna, 2016

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int redPin = 2;
int greenPin = 2; // CHANGE THIS!!!
int bluePin = 2; // CHANGE THIS!!!

const char *ssid = "ESP AP";
const char *password = "password"; // CHANGE THIS!!!

String rv = "255";
String gv = "255";
String bv = "255";

String pageHtml = "";

ESP8266WebServer server(80);

void BuildPage()
{
  pageHtml =
    "<h1>ESP8266 RGB Remote</h1>"
    "<form method='get'>"
    "<table>"
    "<tr><td>Red: </td><td><input type='text' name='r' value=" + rv + "></td></tr>"
    "<tr><td>Green: </td><td><input type='text' name='g' value=" + gv + "><td></tr>"
    "<tr><td>Blue: </td><td><input type='text' name='b' value=" + bv + "><td></tr>"
    "</table><input type='submit' value='Submit'>"
    "</form>";
}

void handleRoot() {
  rv = server.arg("r"); Serial.print("red="); Serial.println(rv);
  gv = server.arg("g"); Serial.print("greeen="); Serial.println(gv);
  bv = server.arg("b"); Serial.print("blue="); Serial.println(bv);

  int ri = rv.toInt();
  int gi = gv.toInt();
  int bi = bv.toInt();
  analogWrite(redPin,ri);
  analogWrite(greenPin,gi);
  analogWrite(bluePin,bi);
  
  BuildPage();
  server.send(200, "text/html", pageHtml);
}

void setup() {
  BuildPage();
  delay(1000);
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
