

// Written by Nick Gammon
// January 2011

#include <SPI.h>

void setup (void)
{
}


void loop (void)
{

  
  digitalWrite(SS, HIGH);  // ensure SS stays high

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  //delay (1000);  // 5 seconds delay to start logic analyser.

  char c;
  
  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10
  
  // send test string
  for (const char * p = "Fab" ; c = *p; p++)
    SPI.transfer (c);

 // disable Slave Select
 digitalWrite(SS, HIGH);

 // turn SPI hardware off
 SPI.end ();
 
 while (1);  //loop
}
