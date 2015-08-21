
// v01 - Blink using direct port manipulation
// v02 - read button using direct port manipulation
// v03 - Blink n times based on which button is pressed
// v04 - Read buttons using interrupt instead of polling in loop()
// v05 - Sleep
// v06 - Mode Switch (Program vs Normal use)
// v07 - Merge in IR library

#include <avr/sleep.h>

#include <IRLib.h>
//#include <IRLibMatch.h>
//#include <IRLibRData.h>
//#include <IRLibTimer.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

volatile bool hit = false;
volatile byte pressedButton= 0; // 0=None
volatile bool isProgramming = false;
byte lastButtonPressed = 0; // 0=None

IRsend irSender;

void setup() {
  cli(); // turn off interrupt while we setup interrupts

       +-------------------------------++-------------------------------++-------------------------------+
 PORTx |          P O R T *C*          ||          P O R T *B*          ||          P O R T *D*          |
       +-------------------------------++-------------------------------++-------------------------------+
PCMSKx |          P C M S K  1         ||          P C M S K  0         ||          P C M S K  2         |
       +-------------------------------++-------------------------------++-------------------------------+
PCINTx | x |I14|I13|I12|I11|I10| I9| I8|| I7| I6| I5| I4| I3| I2| I1| I0||I23|I22|I21|I20|I19|I18|I17|I16|
       +-------------------------------++-------------------------------++-------------------------------+
  PINx |PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0||PB7|PB6|PB5|PB4|PB3|PB2|PB1|PB0||PD7|PD6|PD5|PD4|PD3|PD2|PD1|PD0|
       +-------------------------------++-------------------------------++-------------------------------+
Arduino|         A5| A4| A3| A2| A1| A0||        D13|D12|D11|D10| D9| D8|| D7| D6| D5| D4| D3| D2| D1| D0|
       +-------------------------------++-------------------------------++-------------------------------+
  Info |                       |Pgm|Bzz||        vUp|Dwn|IRr|Lft|Rgt|Ctr|| Up|vDn|cDn|cUp|IRt| Up| RX| TX|
       +-------------------------------++-------------------------------++-------------------------------+
       
  DDRD = B00001001; // D2..D7  as Inputs, leave D3(IRsend), D0..D1 (RX/TX) alone
  DDRB = B00000000; // D8..D13 as inputs, D11 as output
  DDRC = B00000001; // PC0=out, PC1 aka D15/A1 as digital input (mode switch)
  
  PORTD |= B11110100; // pullups on D2, D4..D7
  PORTB |= B00110111; // pullups on D8..D13, except D11
  PORTC |= B00000010; // pullup on PC1

  ClearButtonStates();

  // Listen to interrupts: PCINT0..PCINT3 (on D8..D11)
  PCMSK0 = _BV(PCINT0) + _BV(PCINT1) + _BV(PCINT2) + _BV(PCINT3);
  // Listen to interrupts: PCINT18..23 (on D2..D7)
  PCMSK2 = 0xFF - _BV(PCINT16) - _BV(PCINT17); // All bits HIGH except lowest 2 bits (used by RX & TX)
  PCMSK1 = _BV(PCINT8); // listen to interrupt on PC0/D14/A0

  sbi(PCICR, PCIE0);
  sbi(PCICR, PCIE2); // enable pin change interrupt: PCIE0=PCINT7..0|PCMSK0, PCIE1=PCINT14..8|PCMSK1, PCIE2=PCINT23..16|PCMSK2
  sbi(PCICR, PCIE1);
  
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

void loop() {

  if (hit)
  {
    for (byte i = 0; i < 10; i++)
    {
      if (buttonState[i])
      {
        lastButtonPressed = i+1;
        ClearButtonStates();
        byte blinkCount = isProgramming ? (i+1)*2 : (i+1);
        Blink(blinkCount);

        if (isProgramming)
          DoReceive();
        else
          DoSend();
          
        break;
      }
    }

    hit = false;
  }

  sleepNow();
}

void DoReceive()
{
}

void DoSend()
{
  irSender.send(SONY,0xa8bca, 20);
}

void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // pick sleep mode to use
  sleep_enable(); // set SE bit
  sleep_mode(); // actually go to sleep!
}

void ClearButtonStates()
{
  for (byte i = 0; i < 10; i++)
  {
    buttonState[i] = false;
  }
}

// enabled interrupt X fires ISR(Interrupt Service Routine) Y: PCIE0>PCINT0_vect, PCIE1>PCINT1_vect, PCIE2>PCINT2_vect
ISR(PCINT0_vect) {
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles
  bool any = false;
  for (byte i = 0; i < 4; i++)
  {
    buttonState[6 + i] = (PINB & _BV(i)) == 0; // If bit is low, that button is pressed
    any = true;
  }
  hit = any;
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

ISR(PCINT2_vect) {
  cli(); // turn off interrupt to avoid switch noise
  delay(1); // wait till switch settles
  bool any = false;
  for (byte i = 0; i < 6; i++)
  {
    buttonState[i] = (PIND & _BV(2 + i)) == 0; // If bit is low, that button is pressed
    any = true;
  }
  hit = any;
  sei(); // enable interrupt.  I think same as: sbi(SREG, SREG_I); // Enable global interrupt
}

ISR(PCINT1_vect) {
  isProgramming = (PINC & _BV(PC0)) == 0;
}
void Blink(byte n)
{
  for (byte i = 0; i < n; i++) {
    delay(250);
    sbi(PORTB, PB5);  // turn the LED on (HIGH is the voltage level)
    delay(200);
    cbi(PORTB, PB5);  // turn the LED off by making the voltage LOW

  }
}
