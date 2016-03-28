//  Quick PCF8574 LED test .
//
// Bassed of the PCF8574 demo by Rob Tillaart

#include "PCF8574.h"  //  AUTHOR: Rob Tillaart
#include <Wire.h>

// adjust addresses if needed 
PCF8574 PCF_LED(0x20);  // add leds to lines      (used as output)

void setup()
{
  Serial.begin(115200);
  Serial.println("\nTEST PCF8574\n");
//
//  uint8_t value = PCF_LED.read(3);// for PIR later
//  Serial.print("#38:\t");
//  Serial.println(value);

   
  for (int i=0; i<8; i++)
  {
    PCF_LED.write(i, 1); // set them + , or off on a CA RGB LED
  }
  
}

void loop()
{
  // flip through the RGB led Parts
    for (int i=0; i<3; i++)
  {
    PCF_LED.toggle(i);
    delay(100);
    PCF_LED.toggle(i);
    delay(100);
  }
}
//
// END OF FILE
//
