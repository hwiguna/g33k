// Phone and FOB Car lock for Jay
// v1 - First stab after talking to J. #a0 = lock, #a1 = unlock.

#include <SoftwareSerial.h>
char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(7, 8);

//-- Preferences --
int fobLockPin = 4; // Connected to the FOB receiver. Hi = Lock
int fobUnlockPin = 5; // Connected to the FOB receiver. Hi = Unlock
int relayLockPin = 10; // Connected to the Door lock relay.
int relayUnlockPin = 11; // Connected to the door Unlock relay.
int relayDelay = 1000; // How long the relay pins should be held High before brought back down to low

void setup()
{
  Serial.begin(19200);

  // set up the digital pins to control
  pinMode(fobLockPin, INPUT);
  pinMode(fobUnlockPin, INPUT);
  pinMode(relayLockPin, OUTPUT);
  pinMode(relayUnlockPin, OUTPUT);

  //-- Default relay pins to low --
  digitalWrite(relayLockPin, LOW);
  digitalWrite(relayUnlockPin, LOW);

  // wake up the GSM shield
  SIM900power();
  SIM900.begin(19200);
  delay(20000);  // give time to log on to network.
  SIM900.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
  Serial.println("Ready...");
}

void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(7000);
}

void loop()
{
  //-- Check FOB Receiver --
  if ( digitalRead(fobLockPin) == HIGH ) ToggleRelay(relayLockPin);
  if ( digitalRead(fobUnlockPin) == HIGH ) ToggleRelay(relayUnlockPin);
  
  //-- Check Phone --
  //If a character comes in from the cellular module...
  if (SIM900.available() > 0)
  {
    inchar = SIM900.read();
    if (inchar == '#')
    {
      delay(10);

      inchar = SIM900.read();
      if (inchar == 'a')
      {
        delay(10);
        inchar = SIM900.read();
        if (inchar == '0')
        {
          ToggleRelay(relayLockPin);
        }
        else if (inchar == '1')
        {
          ToggleRelay(relayUnlockPin);
        }
        delay(10);
      }
    }
  }
}

void ToggleRelay(int relayPin)
{
  digitalWrite(relayPin, HIGH);
  delay(relayDelay);
  digitalWrite(relayPin, LOW);
  delay(1000); // Ignore further inputs (from fob or phone) for one second
}

