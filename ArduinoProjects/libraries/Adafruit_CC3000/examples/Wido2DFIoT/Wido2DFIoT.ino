/*************************************************** 
 * This is an example for the DFRobot WiDo - WIFI Integrated IoT lite sensor and control node
 * 
 * Designed specifically to work with the DFRobot WiDo products:
 * 
 * 
 * The main library is forked from Adafruit
 * 
 * Written by Lauren
 * BSD license, all text above must be included in any redistribution
 * 
 ****************************************************/
 
 /*

This example create a TCP client to work with DFRobot Chinese local community IoT service
Login DFRobot Chinese IoT Service:
http://www.dfrobot.com.cn/community

*/
 
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

#define WiDo_IRQ   7
#define WiDo_VBAT  5
#define WiDo_CS    10

Adafruit_CC3000 WiDo = Adafruit_CC3000(WiDo_CS, WiDo_IRQ, WiDo_VBAT,
SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "myNetwork"           // cannot be longer than 32 characters!
#define WLAN_PASS       "myPassword"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define TOKEN           "7dafd269e271c9bcd0b69f61c3ff6af4"  //attach your own token generated from the DFRobot community website

// To get the full feature of CC3000 library from Adafruit, please comment the define command below
// #define CC3000_TINY_DRIVER    // saving the flash memory space for leonardo

#define TIMEOUT_MS      2000

void setup(){

  Serial.begin(115200);
  Serial.println(F("Hello, Wido!\n")); 

  /* Initialise the module and test the hardware connection */
  Serial.println(F("\nInitialising the CC3000 ..."));
  if (!WiDo.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }

  /* NOTE: Secure connections are not available in 'Tiny' mode!
   By default connectToAP will retry indefinitely, however you can pass an
   optional maximum number of retries (greater than zero) as the fourth parameter.
   */
  if (!WiDo.connectToAP(WLAN_SSID,WLAN_PASS,WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.println(F("Connected!"));

  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!WiDo.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  
}


void loop(){
  static Adafruit_CC3000_Client IoTclient;

  if(IoTclient.connected()){
    //Convert LM35 sensor reading to degrees
    int sensValue = analogRead(0) *0.0048828125 * 100;
    
    char clientString[50];
    sprintf(clientString,"%s%s%s%d%s","GET /data?token=",TOKEN,"&param=",sensValue," HTTP/1.1");
    Serial.println(clientString);
    
    // attach the token to the IOT Server and Upload the sensor dataIoTclient
    IoTclient.fastrprintln(clientString);
    
    IoTclient.fastrprint(F("\r\n"));
    IoTclient.fastrprint(F("\r\n"));
    
    Serial.println();
//    Serial.println("Upload data to the IoT Server");

    /* Read data until either the connection is closed, or the idle timeout is reached. */
    unsigned long lastRead = millis();
    while (IoTclient.connected() && (millis() - lastRead < TIMEOUT_MS)) {
      while (IoTclient.available()) {
        char c = IoTclient.read();
        Serial.print(c);
        lastRead = millis();
      }
    }
    IoTclient.close();
  }
  else{
    // Config the Host IP and DFRobot community IoT service port
    // Data Upload service PORT:  8124
    // Real time controling service PORT: 9120
    uint32_t ip = WiDo.IP2U32(182,254,130,180);
    IoTclient = WiDo.connectTCP(ip,8124);
    Serial.println("Connecting IoT Server...");
  }
  
  delay(5000);

}


