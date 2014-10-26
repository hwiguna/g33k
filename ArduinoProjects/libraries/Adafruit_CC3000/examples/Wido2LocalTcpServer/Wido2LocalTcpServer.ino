/*************************************************** 
 * This is an example for the DFRobot WiDo - Wifi Integrated IoT lite sensor and control node
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

This example create a local TCP client for you to contact with local server
To get local server tool: 
https://github.com/Lauren-ED209/Wido-OpenSource-IOT-Node/blob/master/Tools/USR-TCP232-Test.exe

Application:
*local wifi control for robots
*private cloud data collection like connecting to Raspberry pi

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
#define TIMEOUT_MS  2000

void setup(){
  
  Serial.begin(115200);
  /* Initialise the module */
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
  
  Serial.println(F("Connecting Router/AP"));
  if (!WiDo.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
  
  Serial.println(F("Router/AP Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!WiDo.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  
}

void loop(){
  
  static Adafruit_CC3000_Client tcpClient;
  static unsigned long heartRate = millis();
  
  if(!tcpClient.connected()){
    Serial.println("Try to connect the Local Server");
    tcpClient.close();
    
    /* Set the target ip address and connection port */
    uint32_t ip = WiDo.IP2U32(192,168,0,134);
    tcpClient = WiDo.connectTCP(ip, 4000);
    
    if(!tcpClient.connected()){
      Serial.println(F("Couldn't connect to server! Make sure TCP Test Tool is running on the server."));
      while(1);
    }
  }
  else if(millis() - heartRate > 1000){
    heartRate = millis();  // Update time stamp of the microcontroller system
    
    char clientString[30];
    sprintf(clientString, "%s%d%s", "Wido heartRate: ",heartRate/1000," s\r\n");
    
    Serial.println(clientString);
    tcpClient.fastrprintln(clientString);

  }
  
  /* Read data until either the connection is closed, or the timeout is reached. */ 
  unsigned long lastRead = millis();
  while (tcpClient.connected() && (millis() - lastRead < TIMEOUT_MS)) {
    while (tcpClient.available()) {
      char c = tcpClient.read();
      Serial.print(c);
      lastRead = millis();
      
      // Disable sending message for a moment
      heartRate = millis();
    }
  }
}
