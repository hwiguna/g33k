//AT+RST
//AT+CWMODE=1
//AT+CWJAP="Firefly24","password"
//AT+CIPSTART="TCP","184.168.46.67",80
//
//  cmd = "GET /status HTTP/1.0\r\nHost: ";
//  cmd += HOST;
//  cmd += "\r\n\r\n";
// 
//  Serial.print("AT+CIPSEND=");
//  Serial.println(cmd.length());
  
  
  
#include <SoftwareSerial.h>
#define SSID "Firefly24"        //your wifi ssid here
#define PASS "password"  //your wifi wep key here
 
#define DST_IP "184.168.46.67" // www.dontpaniclabs.com
#define HOST "www.dontpaniclabs.com"
 
SoftwareSerial dbgSerial(10, 11); // RX, TX
 
char myChar;
 
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
 
  //blink led13 to indicate power up
  for(int i = 0; i<15; i++)
  {
   digitalWrite(13,HIGH);
   delay(50);
   digitalWrite(13,LOW);
   delay(50);
  }
 
  // Open serial communications for WiFi module:
  Serial.begin(9600); // tried: 115200, 74880, 57600, 9600
  // Set time to wait for response strings to be found
  Serial.setTimeout(5000);
 
  //Open software serial for debugging - must use serial to usb (FTDI) adapter
  //dbgSerial.begin(19200); //can't be faster than 19200 for softserial
  dbgSerial.begin(19200);   //38400 softserial works fine for me
  
//  dbgSerial.println("ESP8266 TEST");
//  delay(1000);
//  Serial.println("AT+RST");    
//  delay(100);
//  while (Serial.available()) {
//    myChar = Serial.read();
//    delay(25);
//    dbgSerial.print(myChar);
//  }
// delay(1000);
      
  dbgSerial.println("ESP8266 Demo");
  delay(100);
  
  //test if the module is ready
  Serial.println("AT+RST");    
  if(Serial.find("ready"))
  {
    dbgSerial.println("Module is ready");
    delay(1000);
    //connect to the wifi
    boolean connected=false;
    for(int i=0;i<5;i++)
    {
      if(connectWiFi())
      {
        connected = true;
        break;
      }
    }
    if (!connected)
    {
      //die
      while(1);
    }
 
    delay(5000);
    //set the single connection mode
    Serial.println("AT+CIPMUX=0");
  }
  else
  {
    dbgSerial.println("Module didn't respond.");
    delay(100);
   
    //serial loop mode for diag
    while(1){
      while (dbgSerial.available()) {
        myChar = dbgSerial.read();
        Serial.print(myChar);
      }
 
      while (Serial.available()) {
        myChar = Serial.read();
        delay(25);
        dbgSerial.print(myChar);
      }
    }
  }
}
 
void loop()
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Serial.println(cmd);
  dbgSerial.println(cmd);
  if(Serial.find("Error")) return;
  cmd = "GET /status HTTP/1.0\r\nHost: ";
  cmd += HOST;
  cmd += "\r\n\r\n";
 
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">"))
  {
    dbgSerial.print(">");
  }
  else
  {
    Serial.println("AT+CIPCLOSE");
    dbgSerial.println("connect timeout");
    delay(1000);
    return;
  }
 
  Serial.print(cmd);
 
  delay(500);
  //Serial.find("+IPD");
  while (Serial.available())
  {
   char c = Serial.read();
   dbgSerial.write(c);
   if(c=='\r') dbgSerial.print('\n');
   delay(50);
  }
 
 dbgSerial.println();
 dbgSerial.println("====");
 delay(1000);
}
 
 
boolean connectWiFi()
{
  Serial.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  dbgSerial.println(cmd);
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("OK"))
  {
    dbgSerial.println("OK, Connected to WiFi.");
    return true;
  }
  else
  {
    dbgSerial.println("Can not connect to the WiFi.");
    return false;
  }            
}
