#include "UsbKeyboard.h"

#define BUTTON_PIN 12

// If the timer isr is corrected
// to not take so long change this to 0.
#define BYPASS_TIMER_ISR 1

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  
#if BYPASS_TIMER_ISR
  // disable timer 0 overflow interrupt (used for millis)
  TIMSK0&=!(1<<TOIE0); // ++
#endif
}

#if BYPASS_TIMER_ISR
void delayMs(unsigned int ms) {
   /*
  */ 
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
#endif

void loop() {
  
  UsbKeyboard.update();

  digitalWrite(13, !digitalRead(13));

  if (digitalRead(BUTTON_PIN) == 0) {
    
    //UsbKeyboard.sendKeyStroke(KEY_B, MOD_GUI_LEFT);
    
    UsbKeyboard.sendKeyStroke(KEY_H);
    UsbKeyboard.sendKeyStroke(KEY_E);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_O);

    UsbKeyboard.sendKeyStroke(KEY_SPACE);

    UsbKeyboard.sendKeyStroke(KEY_W);
    UsbKeyboard.sendKeyStroke(KEY_O);
    UsbKeyboard.sendKeyStroke(KEY_R);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_D);
    //UsbKeyboard.sendKeyStroke(KEY_B, MOD_GUI_LEFT);

    UsbKeyboard.sendKeyStroke(KEY_ENTER);
#if BYPASS_TIMER_ISR  // check if timer isr fixed.
    delayMs(20);
#else
    delay(20);
#endif
    
   }

}
