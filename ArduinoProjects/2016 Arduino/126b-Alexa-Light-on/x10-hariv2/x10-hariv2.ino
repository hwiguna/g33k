#include <X10Firecracker.h>

void setup()
{
  X10.init( 0, 2, 5 );
}


void Test()
{
  X10.sendCmd( hcA, 1, cmdOn );
  delay(1000);
  
  X10.sendCmd( hcA, 1, cmdOff );
  delay(1000);
}

void loop()
{
  Test();
}
