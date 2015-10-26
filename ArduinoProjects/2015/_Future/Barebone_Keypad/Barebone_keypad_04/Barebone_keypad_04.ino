// Barebones keyboard v03.0
// V3 - uses UsbKeyboard library instead of Leonardo's built-in Keyboard library
// v4 - remove leonardo code. can't do both because they use different keycodes :-(

// If you need a key code that is not in the usbKeyboard.h, look here, and add it below
// https://github.com/technomancy/orestes/blob/master/usb_keyboard.h
#define KEY_CAPS_LOCK   57
#define KEY_COMMA   54

int rowPins[] = {
  14, 15, 16, 17}; // aka A0..A3
int columnPins[] = {
  0, 1, 3, 6, 7, 8, 9, 10, 11, 12}; // We skipped 2,4,5 so they can be used by the USB keyboard
int shiftPin = 18; // aka A4
int redShiftPin = 19; // aka A5

#include "UsbKeyboard.h"

// If the timer isr is corrected
// to not take so long change this to 0.
#define BYPASS_TIMER_ISR 1

void setupKeyboard() {
#if BYPASS_TIMER_ISR
  // disable timer 0 overflow interrupt (used for millis)
  TIMSK0 &= !(1 << TOIE0); // ++
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
  UsbKeyboard.update();
  //digitalWrite(13, !digitalRead(13)); // I don't understand this, but it's in Oxer's code

  int mods = Shift() + RedShift();
  for (byte c = 0; c < 10; c++)
  {
    digitalWrite(columnPins[c], LOW);
    for (byte r = 0; r < 4; r++)
    {
      if (digitalRead(rowPins[r]) == 0)
      {
        SendKey(r,c, mods);
        while (digitalRead(rowPins[r]) == 0) delay(10);
      }
    }
    digitalWrite(columnPins[c], HIGH);

#if BYPASS_TIMER_ISR  // check if timer isr fixed.
    delayMs(50);
#else
    delay(50);
#endif
  }
}

void SendKey(byte r, byte c, int mods)
{
  int k = -1;
  if (r==0)
  {
    if (c == 0) k=KEY_1;
    if (c == 1) k=KEY_2;
    if (c == 2) k=KEY_3;
    if (c == 3) k=KEY_4;
    if (c == 4) k=KEY_5;
    if (c == 5) k=KEY_6;
    if (c == 6) k=KEY_7;
    if (c == 7) k=KEY_8;
    if (c == 8) k=KEY_9;
    if (c == 9) k=KEY_0;
  }

  //Second Row
  if (r==1){
    if (c == 0) k=KEY_Q;
    if (c == 1) k=KEY_W;
    if (c == 2) k=KEY_E;
    if (c == 3) k=KEY_R;
    if (c == 4) k=KEY_T;
    if (c == 5) k=KEY_Y;
    if (c == 6) k=KEY_U;
    if (c == 7) k=KEY_I;
    if (c == 8) k=KEY_O;
    if (c == 9) k=KEY_P;
  }

  //third Row
  if (r==2){
    if (c == 0) k=KEY_A;
    if (c == 1) k=KEY_S;
    if (c == 2) k=KEY_D;
    if (c == 3) k=KEY_F;
    if (c == 4) k=KEY_G;
    if (c == 5) k=KEY_H;
    if (c == 6) k=KEY_J;
    if (c == 7) k=KEY_K;
    if (c == 8) k=KEY_L;
    if (c == 9) k=KEY_ENTER;
  }

  //Fourth Row
  if (r==3){
    if (c == 0) k=KEY_CAPS_LOCK;
    if (c == 1) k=KEY_Z;
    if (c == 2) k=KEY_X;
    if (c == 3) k=KEY_C;
    if (c == 4) k=KEY_V;
    if (c == 5) k=KEY_B;
    if (c == 6) k=KEY_N;
    if (c == 7) k=KEY_M;
    if (c == 8) k=KEY_COMMA;
    if (c == 9) k=KEY_SPACE;
  }

  if (k != -1)
	UsbKeyboard.sendKeyStroke(k,mods);
}

int Shift()
{
  return digitalRead(shiftPin) == 0 ? MOD_SHIFT_RIGHT : 0;
}

int RedShift()
{
  return digitalRead(redShiftPin) == 0 ? MOD_SHIFT_LEFT : 0;
}



