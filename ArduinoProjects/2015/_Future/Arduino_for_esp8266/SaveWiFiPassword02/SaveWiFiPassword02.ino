// Save Password to EEPROM
// by Hari Wiguna, 2015
//
// My motivation for writing this sketch is so I could share my
// ESP8266 sketches without including my SSID and password in them.
//
// How it works:
// Enter your SSID/password in this sketch and do not distribute it.
// You don't even have to save it if you don't want to.
// Upload it to the ESP 
// Instructions:
// Modify the ssid string below, upload to the ESP.
// This data will remain there even if we turn off the power.
// Data is in reserved area of the ESP so uploading other sketches will not affect this data.
// Data will remain there until we erase it.

#include <EEPROM.h>

char ssid[] = "----------";
char password[] = "---------";
int addr = 0;

char ssid2[50];
char password2[50];

void Save(char str[])
{
  EEPROM.begin(512);
  int len = strlen(str);
  for (int i = 0; i <= len; i++)
  {
    Serial.print(addr+i);
    Serial.print(" <- ");
    byte c = (i<len) ? str[i] : 0; 
    Serial.println(c);
    EEPROM.write(addr+i, c);
  }
  EEPROM.commit();
  
  addr += (len + 1); // Skip saved data
}

void Load(char str[])
{
  EEPROM.begin(512);

  for (int i = 0; (addr+i) < 512; i++)
  {
    str[i] = EEPROM.read(addr+i);
    Serial.print(addr+i);
    Serial.print(" -> ");
    Serial.println(str[i], HEX);
    
    if (str[i]==0) {
      addr += (i+1); // Skip loaded data
      break;
    }
  }
  
  Serial.println();
  Serial.print("str=");
  Serial.println(str);
}

void setup()
{
  Serial.begin(115200);

  Save(ssid);
  Save(password);
  
  delay(1000);
  
  addr = 0;
  Load(ssid2);
  Load(password2);
  
  Serial.println();
  Serial.print("ssid2=");
  Serial.println(ssid2);
  Serial.print("password2=");
  Serial.println(password2);
}

void loop()
{
}
