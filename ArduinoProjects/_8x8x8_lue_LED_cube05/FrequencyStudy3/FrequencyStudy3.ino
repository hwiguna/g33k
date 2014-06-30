//-- Ports --
int led0 = 11;
int led1 = 13;

//-- Timing preferences --
int whole = 20; // 20ms is the TOTAL time we allow to update ALL 8 layers.
int part1 = whole/8; // each layer would be on for this long.
int part7 = whole-part1; // and be off this long while we update the other 7 layers.

//-- Layer counter --
uint8_t z = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led0, OUTPUT);     
  pinMode(led1, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  Study2();
  delay(part1);
}

void Study2()
{
  //-- Turn off previous layer --
  if (z==0) digitalWrite(led0, LOW);
  if (z==1) digitalWrite(led1, LOW);

  //-- Compute new layer --
  z++; if (z>=8) z=0;

  //-- Turn on new layer (will stay on till next time timer fires) --
  if (z==0) digitalWrite(led0, HIGH);
  if (z==1) digitalWrite(led1, HIGH);
}

