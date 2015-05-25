//
// One Way Chat
// (Serial LCD connected to an ESP-8266)
// Heavily based on Arduino IDE for ESP's HelloServer example.
// Hari Wiguna, 2015
//
// The display I used was an old NewHaven display:
// http://www.newhavendisplay.com/specs/NHD-0216K3Z-NSRGB-FBW-V3.pdf
//

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "..........";
const char* password = "..........";

String form =
  "<p>"
  "<center>"
  "<h1>Talk to me :-)</h1>"
  "<img src='http://i.imgur.com/qu8lDEu.jpg'>"
  "<form action='msg'><p>Wassup? <input type='text' name='msg' size=50 autofocus> <input type='submit' value='Submit'></form>"
  "</center>";

// HTTP server will listen at port 80
ESP8266WebServer server(80);

void handle_msg() {
  // Send same page so they can send another msg
  server.send(200, "text/html", form);

  // Display msg on LCD
  String msg = server.arg("msg");
  String decodedMsg = msg;
  decodedMsg.replace("+", " ");
  ClearLCD();
  PrintLine1(decodedMsg);
  if (decodedMsg.length() > 16)
    PrintLine2(decodedMsg.substring(16));
}

void InitLCD()
{
  // NewHaven display Contrast
  Serial.write(0xFE);
  Serial.write(0x52);
  Serial.write(40);
  delay(500);

  // NewHaven display brightness
  Serial.write(0xFE);
  Serial.write(0x53);
  Serial.write(8);
  delay(500);

  ClearLCD();
}

void ClearLCD()
{
  // NewHaven display clear screen
  Serial.write(0xFE);
  Serial.write(0x51);
}

void setup(void) {
  Serial.begin(9600);
  delay(500);
  InitLCD();

  // Connect to WiFi network
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  PrintLine1("SSID: " + String(ssid));

  // Set up the endpoints for HTTP server
  //
  // Endpoints can be written as inline functions:
  server.on("/", []() {
    server.send(200, "text/html", form);
  });

  // And as regular external functions:
  server.on("/msg", handle_msg);

  // Start the server
  server.begin();

  //ClearLCD();
  //PrintLine1("WebServer ready!");
  PrintLine2("");
  Serial.print(WiFi.localIP());
}

void loop(void) {
  // check for incomming client connections frequently in the main loop:
  server.handleClient();
}

void PrintLine1(String str)
{
  PrintLine(1, str);
}

void PrintLine2(String str)
{
  PrintLine(2, str);
}

void PrintLine(int line, String str)
{
  if (line == 1) {
    // NewHaven display cursor home
    Serial.write(0xFE);
    Serial.write(0x46);
  }
  else
  {
    // NewHaven display go to line 2
    Serial.write(0xFE);
    Serial.write(0x45);
    Serial.write(0x40);
  }
  Serial.print(str);
}
