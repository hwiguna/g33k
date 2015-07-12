// Save Password to EEPROM
// by Hari Wiguna, 2015
//
// Instructions:
// Modify the ssid string below, upload to the ESP.
// This data will remain there even if we turn off the power.
// Data is in reserved area of the ESP so uploading other sketches will not affect this data.
// Data will remain there until we erase it.

#include <EEPROM.h>

char ssid[] = "Firefly24";

void setup()
{
  EEPROM.begin(512);

  for (int i = 0; i < sizeof(ssid); i++)
  {
    EEPROM.write(i, ssid[i]);
  }
  
  EEPROM.commit();
}

void loop()
{
}
