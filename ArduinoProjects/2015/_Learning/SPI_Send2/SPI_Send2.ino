/*
 The circuit:
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

Signal on scope:
- Left is later in time!
- Right happens first!
- LSB is sent first. Use SPISettings() to change it
- Default behavior is mode0, clock is normally low (CPOL=0) data should be sampled on clock rising edge (CHPA0)

*/

#include <SPI.h>

const int slaveSelectPin = 10;
int count = 0;

void setup() {
  pinMode (slaveSelectPin, OUTPUT); // set the slaveSelectPin as an output
  SPI.begin(); // initialize SPI
//  SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down the master a bit
}

void loop() {  // take the SS pin low to select the chip:
  //count++; if (count>255) count=0;
  
  //digitalWrite(slaveSelectPin, LOW); // LOW = Hey, SPI slave, PAY ATTENTION to me, your master!
  SPI.transfer('H'); // Send something else
  SPI.transfer('\n'); // Send something else
  //SPI.transfer(count); // Send something
  //digitalWrite(slaveSelectPin, HIGH); // HIGH= You can ignore me now, I'm going to talk to other slaves!
  delay(1000);
}
