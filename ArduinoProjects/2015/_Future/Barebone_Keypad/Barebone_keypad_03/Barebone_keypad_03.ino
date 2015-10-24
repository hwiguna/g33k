// Barebones keyboard v03.0
// V3 - uses UsbKeyboard library instead of Leonardo's built-in Keyboard library

int rowPins[] = {14, 15, 16, 17}; // aka A0..A3
int columnPins[] = {0, 1, 3, 6, 7, 8, 9, 10, 11, 12}; // We skipped 2,4,5 so they can be used by the USB keyboard
int shiftPin = 18; // aka A4
int redShiftPin = 19; // aka A5

//*** COMMENT THIS NEXT LINE TO COMPILE USBKEYBOARD UNDER OLD Arduino IDE ***
#define LEONARDO

#ifdef LEONARDO
#define HIT Keyboard.press
#else
#include "UsbKeyboard.h"
#define HIT UsbKeyboard.sendKeyStroke
#endif

// If the timer isr is corrected
// to not take so long change this to 0.
#define BYPASS_TIMER_ISR 1

void setupKeyboard() {
#ifdef LEONARDO
  Keyboard.begin();
#else
#if BYPASS_TIMER_ISR
  // disable timer 0 overflow interrupt (used for millis)
  TIMSK0 &= !(1 << TOIE0); // ++
#endif
#endif
}


#if BYPASS_TIMER_ISR
void delayMs(unsigned int ms) {
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
#endif

void setup() {
  setupKeyboard();

  for (byte c = 0; c < 10; c++)
  {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
  }
  for (byte r = 0; r < 4; r++)
  {
    pinMode(rowPins[r], INPUT);
    digitalWrite(rowPins[r], HIGH);
  }

  // Shift Key
  pinMode(shiftPin, INPUT);
  digitalWrite(shiftPin, HIGH);

  // Red Shift Key
  pinMode(redShiftPin, INPUT);
  digitalWrite(redShiftPin, HIGH);
}

void loop() {
#ifndef LEONARDO
  UsbKeyboard.update();
#endif

  for (byte c = 0; c < 10; c++)
  {
    digitalWrite(columnPins[c], LOW);
    for (byte r = 0; r < 4; r++)
    {
      if (digitalRead(rowPins[r]) == 0)
      {
        if (r == 0 && c == 0) {
          HIT('1');
        }
        if (r == 0 && c == 1) {
          if (Shift())
            HIT('@');
          else
            HIT('2');
        }
        if (r == 0 && c == 2) {
          HIT('3');
        }
        if (r == 0 && c == 3) {
          HIT('4');
        }
        if (r == 0 && c == 4) {
          HIT('5');
        }
        if (r == 0 && c == 5) {
          HIT('6');
        }
        if (r == 0 && c == 6) {
          HIT('7');
        }
        if (r == 0 && c == 7) {
          HIT('8');
        }
        if (r == 0 && c == 8) {
          HIT('9');
        }
        if (r == 0 && c == 9) {
          HIT('0');
        }
        //Second Column
        if (r == 1 && c == 0) {
          HIT('q');
        }
        if (r == 1 && c == 1) {
          HIT('w');
        }
        if (r == 1 && c == 2) {
          HIT('e');
        }
        if (r == 1 && c == 3) {
          HIT('r');
        }
        if (r == 1 && c == 4) {
          HIT('t');
        }
        if (r == 1 && c == 5) {
          HIT('y');
        }
        if (r == 1 && c == 6) {
          HIT('u');
        }
        if (r == 1 && c == 7) {
          HIT('i');
        }
        if (r == 1 && c == 8) {
          HIT('o');
        }
        if (r == 1 && c == 9) {
          HIT('p');
        }
        //third column
        if (r == 2 && c == 0) {
          HIT('a');
        }
        if (r == 2 && c == 1) {
          HIT('s');
        }
        if (r == 2 && c == 2) {
          HIT('d');
        }
        if (r == 2 && c == 3) {
          HIT('f');
        }
        if (r == 2 && c == 4) {
          HIT('g');
        }
        if (r == 2 && c == 5) {
          HIT('h');
        }
        if (r == 2 && c == 6) {
          HIT('j');
        }
        if (r == 2 && c == 7) {
          HIT('k');
        }
        if (r == 2 && c == 8) {
          HIT('l');
        }
        if (r == 2 && c == 9) {
          HIT(KEY_RETURN);
        }
        //Forth Column
        if (r == 3 && c == 0) {
          HIT(KEY_CAPS_LOCK);
        }
        if (r == 3 && c == 1) {
          HIT('z');
        }
        if (r == 3 && c == 2) {
          HIT('x');
        }
        if (r == 3 && c == 3) {
          HIT('c');
        }
        if (r == 3 && c == 4) {
          HIT('v');
        }
        if (r == 3 && c == 5) {
          HIT('b');
        }
        if (r == 3 && c == 6) {
          HIT('n');
        }
        if (r == 3 && c == 7) {
          HIT('m');
        }
        if (r == 3 && c == 8) {
          HIT(KEY_RIGHT_SHIFT);
        }
        if (r == 3 && c == 9) {
          HIT(' ');
        }
        while (digitalRead(rowPins[c]) == 0) delay(10);

        #ifdef LEONARDO
        Keyboard.releaseAll();
        #endif
      }
    }
    digitalWrite(columnPins[c], HIGH);
  }

#ifndef LEONARDO
#if BYPASS_TIMER_ISR  // check if timer isr fixed.
  delayMs(20);
#else
  delay(20);
#endif
#endif
}

bool Shift()
{
  return digitalRead(shiftPin) == 0;
}

bool RedShift()
{
  return digitalRead(redShiftPin) == 0;
}

