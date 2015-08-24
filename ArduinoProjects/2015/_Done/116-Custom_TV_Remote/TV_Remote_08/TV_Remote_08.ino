// v01 - Blink using direct port manipulation
// v02 - read button using direct port manipulation
// v03 - Blink n times based on which button is pressed
// v04 - Read buttons using interrupt instead of polling in loop()
// v05 - Sleep
// v06 - Mode Switch (Program vs Normal use)
// v07 - Merge in IR library
// v08 - It WORKS! Mode switch works, can record, save to EEPROM and recall IR code after power been removed!  Still many bugs.

#include <avr/sleep.h>

#include <IRLib.h>
//#include <IRLibMatch.h>
//#include <IRLibRData.h>
//#include <IRLibTimer.h>

#include <EEPROM.h>

#include "ButtonInfo.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// pressedButton Values (NOT I/O pin index)
#define BTN_POWER 2
#define BTN_CHANNEL_UP 4
#define BTN_CHANNEL_DOWN 5
#define BTN_VOLUME_UP 18
#define BTN_VOLUME_DOWN 6
#define BTN_CENTER 8
#define BTN_UP 7
#define BTN_DOWN 12
#define BTN_LEFT 10
#define BTN_RIGHT 9

volatile byte pressedButton = 0; // 0=None
bool wasProgramming = false; volatile bool isProgramming = false;
byte lastPressedButton = 0; // 0=None
//volatile bool isTransmitting = false;

int RECV_PIN = 11;
IRrecv My_Receiver(RECV_PIN);
IRsend irSender;
IRdecode My_Decoder;

// Storage for the recorded code
IRTYPES codeType;          // The type of code
unsigned long codeValue;   // The data bits if type is not raw
int codeBits;              // The length of the code in bits

ButtonInfo ButtonInfos[23];

void setup() {
  /*
  Legend:
   - = don't touch
   n/a = not applicable (does not exists)
   Rst = Reset
   Xtl = Crystal/Oscillator
         +-------------------------------++-------------------------------++-------------------------------+
   PORTx |          P O R T [C]          ||          P O R T [B]          ||          P O R T [D]          |
         +-------------------------------++-------------------------------++-------------------------------+
  PCMSKx |         P C M S K  [1]        ||         P C M S K  [0]        ||         P C M S K [2]         |
         +-------------------------------++-------------------------------++-------------------------------+
  PCINTx |n/a|I14|I13|I12|I11|I10| I9| I8|| I7| I6| I5| I4| I3| I2| I1| I0||I23|I22|I21|I20|I19|I18|I17|I16|
         +-------------------------------++-------------------------------++-------------------------------+
    PINx |PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0||PB7|PB6|PB5|PB4|PB3|PB2|PB1|PB0||PD7|PD6|PD5|PD4|PD3|PD2|PD1|PD0|
         +-------------------------------++-------------------------------++-------------------------------+
  Arduino|n/a|Rst| A5| A4| A3| A2| A1| A0||Xtl|Xtl|D13|D12|D11|D10| D9| D8|| D7| D6| D5| D4| D3| D2| D1| D0|
         +-------------------------------++-------------------------------++-------------------------------+
    Info |n/a| - |   |   |   |vUp|Pgm|Bzz|| - | - | - |Dwn|iRx|Lft|Rgt|Ctr|| Up|vDn|cDn|cUp|iTx|Pwr| RX| TX|
         +-------------------------------++-------------------------------++-------------------------------+
  Output?| - | - | 0 | 0 | 0 | 0 | 0 | 1 || - | - | - | 0 | 0 | 0 | 0 | 0 || 0 | 0 | 0 | 0 | 1 | 0 | - | - |
         +-------------------------------++-------------------------------++-------------------------------+
  */
  cli(); // turn off interrupt while we setup ports and interrupts

  DDRD  &= B00001011; // CLEAR input pin bits. Leave IRt, RX, and TX alone
  DDRD  |= B00001000; // SET output pin bit for IRt(IR Transmit)
  PORTD |= B11110100; // SET pullups on input pins
  PCMSK2 = 0xFF - _BV(PCINT19) - _BV(PCINT17) - _BV(PCINT16); // Listen to interrupts: PCINT18..23 (on D2..D7)
  //  cbi(PCMSK2, PCINT16);
  //  cbi(PCMSK2, PCINT17);
  //  sbi(PCMSK2, PCINT18);
  //  cbi(PCMSK2, PCINT19);
  //  sbi(PCMSK2, PCINT20);
  //  sbi(PCMSK2, PCINT21);
  //  sbi(PCMSK2, PCINT22);
  //  sbi(PCMSK2, PCINT23);

  DDRB  &= B11100000; // CLEAR input pin bits. Leave highest three bits alone
  PORTB |= B00010111; // SET pullups on D8..D13, except D11,D13
  PCMSK0 |= _BV(PCINT0) + _BV(PCINT1) + _BV(PCINT2) + _BV(PCINT4); // Listen to interrupts: PCINT0..PCINT4 (on D8..D13)

  DDRC  &= B11000001; // CLEAR A5,4,3,2,1 but not 0, and leave high bits alone
  DDRC  |= B00000001; // SET A0 as output (Buzzer)
  PORTC |= B00111110; // pullup on all input pins (even the ones we're not using)
  PCMSK1 |= _BV(PCINT9) + _BV(PCINT10); // listen to interrupt on PC1/A1, PC2/A2

  PCICR |= B00000111; // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2
  //sbi(PCICR, PCIE0);
  //sbi(PCICR, PCIE1);
  //sbi(PCICR, PCIE2); // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2

  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
  //sbi(SREG, SREG_I);

  Serial.begin(9600);

  Blink(1); // Beep once to indicate that we're ready!

  ReadFromEEPROM();

  Serial.println(F("Setup Completed!"));
}

void loop() {
  if (isProgramming != wasProgramming)
  {
    Serial.print(F("Programming mode: "));
    Serial.println(isProgramming, DEC);
    if (isProgramming)
      My_Receiver.enableIRIn(); // Re-enable receiver
    wasProgramming = isProgramming;
  }

  if (isProgramming)
    DoReceive();

  if (pressedButton != 0)
  {
    byte blinkCount = isProgramming ? pressedButton * 2 : pressedButton;

    if (!isProgramming)
      DoSend();

    Blink(blinkCount); // blinkCount
    lastPressedButton = pressedButton;
    pressedButton = 0; // Button press has been handled, we're ready for next button press
  }

  if (!isProgramming)
    sleepNow();
}

void DoSend()
{
  ButtonInfo buttonInfo = ButtonInfos[pressedButton];
  irSender.send(buttonInfo.codeType, buttonInfo.codeValue, 20);
}

void DoReceive()
{
  //WARNING: My_Receiver.GetResults() is a blocking call!  We won't return until after we receive some IR
  if (My_Receiver.GetResults(&My_Decoder)) {
    Serial.println(F("My_Receiver received IR.  Decoding..."));
    My_Decoder.decode();
    Serial.println(F("Decoding COMPLETED!"));
    storeCode();
    Serial.print(F("Saved as button#"));
    Serial.println(lastPressedButton, DEC);
    delay(1000);
    My_Receiver.resume();
  }
}

void storeCode(void) {
  //GotNew = true;
  codeType = My_Decoder.decode_type;
  if (codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    // To store raw codes:
    // Drop first value (gap)
    // As of v1.3 of IRLib global values are already in microseconds rather than ticks
    // They have also been adjusted for overreporting/underreporting of marks and spaces
    //    rawCount = My_Decoder.rawlen - 1;
    //    for (int i = 1; i <= rawCount; i++) {
    //      rawCodes[i - 1] = My_Decoder.rawbuf[i];
    //    };
    //    My_Decoder.DumpResults();
    //    codeType = UNKNOWN;
  }
  else {
    Serial.print(F("Received "));
    Serial.print(Pnames(codeType));
    if (My_Decoder.value == REPEAT) {
      // Don't record a NEC repeat value as that's useless.
      Serial.println(F("repeat; ignoring."));
    }
    else {
      codeValue = My_Decoder.value;
      codeBits = My_Decoder.bits;
    }

    ButtonInfos[lastPressedButton].codeType = codeType;
    ButtonInfos[lastPressedButton].codeValue = codeValue;
    SaveToEEPROM(lastPressedButton, codeType, codeValue);

    Serial.print(F(" Value:0x"));
    Serial.println(My_Decoder.value, HEX);
  }
}

void SaveToEEPROM(byte buttonNumber, IRTYPES codeType, unsigned long codeValue)
{
  int addr = buttonNumber * 5; // IRTYPES is a char, unsigned long is 4 bytes
  EEPROM.put(addr, codeType);
  EEPROM.put(addr + 1, codeValue);
}

void ReadFromEEPROM()
{
  Serial.println(F("EEPROM values:"));
  for (byte i = 0; i < 24; i++)
  {
    int addr = i * 5;
    //char codeType;
    //unsigned long codeValue;
    EEPROM.get(addr, ButtonInfos[i]);
    //EEPROM.get(addr+1, codeValue);
    Serial.print(i, DEC);
    Serial.print(": Type=");
    Serial.print(ButtonInfos[i].codeType, DEC);
    Serial.print(", Value=0x");
    Serial.println(ButtonInfos[i].codeValue, HEX);
  }
}

void DoSend_Samsung()
{
  switch (pressedButton)
  {
    case BTN_POWER: irSender.send(NECX, 0xE0E040BF, 20); break;
    case BTN_CHANNEL_UP: irSender.send(NECX, 0xE0E048B7, 20); break;
    case BTN_CHANNEL_DOWN: irSender.send(NECX, 0xE0E008F7, 20); break;
    case BTN_VOLUME_UP: irSender.send(NECX, 0xE0E0E01F, 20); break;
    case BTN_VOLUME_DOWN: irSender.send(NECX, 0xE0E0D02F, 20); break;
    case BTN_CENTER: irSender.send(NECX, 0xE0E016E9, 20); break;
    case BTN_UP: irSender.send(NECX, 0xE0E006F9, 20); break;
    case BTN_DOWN: irSender.send(NECX, 0xE0E08679, 20); break;
    case BTN_LEFT: irSender.send(NECX, 0xE0E0A659, 20); break;
    case BTN_RIGHT: irSender.send(NECX, 0xE0E046B9, 20); break;
  }
}

void DoSend_LG()
{
  switch (pressedButton)
  {
    case BTN_POWER: irSender.send(NEC, 0x20DF10EF, 20); break;
    case BTN_CHANNEL_UP: irSender.send(NEC, 0x20DF00FF, 20); break;
    case BTN_CHANNEL_DOWN: irSender.send(NEC, 0x20DF807F, 20); break;
    case BTN_VOLUME_UP: irSender.send(NEC, 0x20DF40BF, 20); break;
    case BTN_VOLUME_DOWN: irSender.send(NEC, 0x20DFC03F, 20); break;
    case BTN_CENTER: irSender.send(NEC, 0x20DF22DD, 20); break;
    case BTN_UP: irSender.send(NEC, 0x20DF02FD, 20); break;
    case BTN_DOWN: irSender.send(NEC, 0x20DF827D, 20); break;
    case BTN_LEFT: irSender.send(NEC, 0x20DFE01F, 20); break;
    case BTN_RIGHT: irSender.send(NEC, 0x20DF609F, 20); break;
  }
}

void sleepNow()
{
  delay(2000); // Allow serial to print stuff before sleeping
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // pick sleep mode to use
  sleep_enable(); // set SE bit
  sleep_mode(); // actually go to sleep!
}

// enabled interrupt X fires ISR(Interrupt Service Routine) Y: PCIE0>PCINT0_vect, PCIE1>PCINT1_vect, PCIE2>PCINT2_vect
ISR(PCINT0_vect)
{
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles

  if (pressedButton == 0)
  {
    for (byte i = 0; i < 6; i++) // PCINT0 is for PORTB, only bits 0..5 are used. 6,7 are used by Arduino Crystal.
    {
      if ((PINB & _BV(i)) == 0) {// If bit is low, that button is pressed
        pressedButton = 8 + i;
        break;
      }
    }
  }

  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

ISR(PCINT2_vect)
{
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles

  if (pressedButton == 0)
  {
    byte bits = PIND;
    for (byte i = 2; i < 8; i++) // PCINT2 is for PORT D, we ignore RX&TX
    {
      if ((DDRD & _BV(i)) == 0 && (bits & _BV(i)) == 0) // If bit an INPUT and its value is low, that button is pressed
      {
        pressedButton = i;
        break;
      }
    }
  }

  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

ISR(PCINT1_vect)
{
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles

  byte bits = PINC;
  isProgramming = (bits & _BV(PC1)) == 0; // PCINT1 is for PORT C, we only need to watch for bit 1 (Pgm)

  if (pressedButton == 0)
  {
    for (byte i = 1; i < 6; i++) // PCINT1 is for PORT C, we ignore buzzer on A0
    {
      if ((DDRC & _BV(i)) == 0 && (bits & _BV(i)) == 0) // If bit an INPUT and its value is low, that button is pressed
      {
        pressedButton = 16 + i;
        break;
      }
    }
  }

  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void Blink(byte n)
{
  for (byte i = 0; i < n; i++) {
    sbi(PORTC, PC0);  // Beep on
    delay(50);
    cbi(PORTC, PC0);  // Beep off
    delay(250);
  }
}
