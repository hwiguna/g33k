#define SSID "[WiFi Access Point Name]"
#define PASS "[WiFi Password]"
#define SERVER_IP "?.?.?.?.?"

#include "Credentials.h"
#include<stdlib.h>

#define digitalPin 20
#define analogPin A0

int prevDigitalVal;
String OK = "\r\nOK\r\n";

void setup()
{
  //-- Allow me to switch serial port from uploading sketch and communicating with the ESP8266 --
  //delay(1000);

  //-- Setup I/O pins --
  pinMode(digitalPin,INPUT_PULLUP);

  //-- Setup Software Serial for debugging --
  Serial.begin(9600);
  Serial.println("*** NodeJS Client ***");

  //-- Setup Serial for ESP8266 --
  Serial1.begin(9600);
  Serial1.setTimeout(5000);

  //-- Setup ESP8266 --
  if (InitESP8266())
    ConnectToWiFi();
}

void loop()
{
  int digitalVal = digitalRead( digitalPin );
  if (digitalVal == 0) {
    int analogVal = analogRead(analogPin);
    SendData( digitalVal, analogVal );
    //prevDigitalVal = digitalVal;
  }
}

//--------------------------------------------------

boolean InitESP8266()
{
  boolean success = false;

  //  if (Send("AT", OK)) // ESP8266, are you there?
  //    if (Send("AT+CWMODE=1")) // 1=Client, 2=Access Point, 3=Client & AP.  Returns either "OK" or "no change"
  //      success = true;
  //SendThenListen("AT+RST", "ready"); // Reset, wait for "ready"
  SendThenListen("AT", OK); // ESP8266, are you there?
  SendThenListen("AT+CWMODE=1", OK, "no change"); // 1=Client, 2=Access Point, 3=Client & AP.  Returns either "OK" or "no change"
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
  Serial1.println(command);
  return true;
}

boolean Send(String command, char* waitForString)
{
  boolean success = false;

  Debug("SEND... ", command);
  Serial1.println(command);
  if (Serial1.find(waitForString)) {
    Debug(String(waitForString)," received");
    success = true;
  }
  else
    Debug(String(waitForString)," NOT received!");

  return success;
}

void Debug(String label, String value )
{
  Serial.print(label);
  Serial.println(value);
}

String Listen(String waitForStr, String waitForStr2, boolean *success)
{
  *success = false;
  unsigned long listeningTimeout = millis() + 10000;
  String returnStr;

  while (millis() < listeningTimeout)
  {
    while (Serial1.available()) {
      char inChar = (char)Serial1.read(); // get the new byte:
      returnStr += inChar; // add it to the inputString:
    }

    if (returnStr.indexOf(waitForStr) != -1) {
      *success = true;
      break;
    }

    if (waitForStr2.length() > 0 && returnStr.indexOf(waitForStr2) != -1) {
      *success = true;
      break;
    }
  }
  return returnStr;
}

boolean SendThenListen(String command, String waitFor, String waitFor2)
{
  boolean success;
  Send(command);
  Debug("RECEIVED:", Listen(waitFor, waitFor2, &success));
  return success;
}

boolean SendThenListen(String command, String waitFor)
{
  return SendThenListen(command, waitFor, "");
}

void SendData(int value, int value2)
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
  cmd += "?a=";
  cmd += value2;
  cmd += "\r\n\r\n"; // TCP packet ends with two CRLFs

  //-- Tell ESP8266 the length of the request that we want to send, followed by actual request --
  String request = "AT+CIPSEND=" + String(cmd.length());
  bool success = SendThenListen(request, ">"); // IMPORTANT!!! Do not send the actual request string until ESP8266 sends ">"
  if (success)
    SendThenListen(cmd, OK);
  
  SendThenListen("AT+CIPCLOSE", OK);
}

