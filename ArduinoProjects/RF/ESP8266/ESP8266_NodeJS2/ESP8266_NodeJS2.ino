#define SSID "[WiFi Access Point Name]"
#define PASS "[WiFi Password]"
#define SERVER_IP "?.?.?.?.?"

#include "Credentials.h"
#include<stdlib.h>
#include <SoftwareSerial.h>

#define digitalPin 4
#define analogPin A0

int prevDigitalVal;
String OK = "\r\nOK\r\n";

SoftwareSerial monitor(10, 11); // RX, TX

void setup()
{
  //-- Allow me to switch serial port from uploading sketch and communicating with the ESP8266 --
  delay(1000);

  //-- Setup I/O pins --
  pinMode(digitalPin,INPUT_PULLUP);

  //-- Setup Software Serial for debugging --
  monitor.begin(9600);
  monitor.println("*** NodeJS Client ***");
  
  //-- Setup Serial for ESP8266 --
  Serial.begin(9600);
  Serial.setTimeout(5000);

  //-- Setup ESP8266 --
  if (InitESP8266())
    ConnectToWiFi();
}

void loop()
{
  int digitalVal = digitalRead( digitalPin );
  if (digitalVal != prevDigitalVal) {
    SendData( digitalVal );
    prevDigitalVal = digitalVal;
  }
}

//--------------------------------------------------

boolean InitESP8266()
{
  boolean success = false;
  
//  if (Send("AT", OK)) // ESP8266, are you there?
//    if (Send("AT+CWMODE=1")) // 1=Client, 2=Access Point, 3=Client & AP.  Returns either "OK" or "no change"
//      success = true;
  SendThenListen("AT+RST", "ready"); // Reset, wait for "ready"
  SendThenListen("AT", OK); // ESP8266, are you there?
  SendThenListen("AT+CWMODE=1", OK); // 1=Client, 2=Access Point, 3=Client & AP.  Returns either "OK" or "no change"
  SendThenListen("AT+CIPMUX=0", OK);  // 0=Single Channel, 1=Multi Channel
  SendThenListen("AT+CIPMODE=0", OK); // 0=Received data will be sent to serial port as +IPD,conn, len.  1=plain data stream

  success = true;
  return success;
}

boolean ConnectToWiFi()
{
  boolean success = false;
  
  //-- Build Command string to connect to WiFi --
  String cmd="AT+CWJAP=\""; // AT+CWJAP=quote
  cmd += SSID;
  cmd += "\",\""; // quote, comma, quote
  cmd += PASS;
  cmd += "\"";    // quote
  SendThenListen(cmd, OK);

  //-- Display ESP8266's IP Address --
  SendThenListen("AT+CIFSR", OK);
  
  success = true;
  return success;
}

boolean Send(String command)
{
  Debug("SEND: ", command);
  Serial.println(command);
  return true;
}

boolean Send(String command, char* waitForString)
{
  boolean success = false;
  
  Debug("SEND... ", command);
  Serial.println(command);
  if (Serial.find(waitForString)) {
    Debug(String(waitForString)," received");
    success = true;
  }
  else
    Debug(String(waitForString)," NOT received!");
  
  return success;
}

void Debug(String label, String value )
{
  monitor.print(label);
  monitor.println(value);
}

String Listen(String waitForStr)
{
  unsigned long listeningTimeout = millis() + 5000;
  String returnStr;
  
  while (millis() < listeningTimeout)
  {
    while (Serial.available()) {
      char inChar = (char)Serial.read(); // get the new byte:
      returnStr += inChar; // add it to the inputString:
    }
    
    if (returnStr.indexOf(waitForStr) != -1)
      break;
  }
  return returnStr;
}

void SendThenListen(String command, String waitFor)
{
  Send(command);
  Debug( "RECEIVED: ", Listen(waitFor) );
}

void SendData(int value)
{
  //-- Start TCP communication with server --
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += SERVER_IP;
  cmd += "\",80";
  SendThenListen(cmd, OK);
  
  //-- Build the GET request --
  cmd = "GET /a.htm";
  cmd += "?d=";
  cmd += value;
  cmd += "\r\n\r\n"; // TCP packet ends with two CRLFs
  
  //-- Tell ESP8266 the length of the request that we want to send, followed by actual request --
  String request = "AT+CIPSEND=" + String(cmd.length());
  SendThenListen(request, ">"); // IMPORTANT!!! Do not send the actual request string until ESP8266 sends ">"
  delay(1000);
  SendThenListen(cmd, OK);
}
