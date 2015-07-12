// Read Password from EEPROM
// by Hari Wiguna, 2015
//
// Instructions:
// Use SaveWiFiPassword to save your password to ESP EEPROM

#include <EEPROM.h>

char ssid[100];

void setup()
{
  Serial.begin(115200); // Open COM port for debugging

  EEPROM.begin(512);

  for (int address = 0; address < sizeof(ssid); address++)
  {
    ssid[address] = EEPROM.read(address);
    Serial.print(address);
    Serial.print("=");
    Serial.println(ssid[address], HEX);
  }
  
  Serial.println();
  Serial.println("ssid=");
  Serial.println(ssid);
}

void loop()
{
}
