// Barebones keyboard v02.1

int c0 = 4;
int r0 = 0;

void setup() {
  Keyboard.begin();
  for (byte c = 0; c < 10; c++)
  {
    pinMode(c0 + c, OUTPUT);
    digitalWrite(c0 + c, LOW);
  }
  for (byte r = 0; r < 4; r++)
  {
    pinMode(r0 + r, INPUT);
    digitalWrite(r0 + r, HIGH);
  }

  // Shift Key
  pinMode(A0,INPUT);
    digitalWrite(A0, HIGH);
}
void loop() {
  for (byte c = 0; c < 10; c++)
  {
    digitalWrite(c0 + c, LOW);
    for (byte r = 0; r < 4; r++)
    {
      if (digitalRead(r0 + r) == 0)
      {
        if (r == 0 && c == 0) {
          Keyboard.press('1');
        }
        if (r == 0 && c == 1) {
          if (Shift())
            Keyboard.press('@');
          else
            Keyboard.press('2');
        }
        if (r == 0 && c == 2) {
          Keyboard.press('3');
        }
        if (r == 0 && c == 3) {
          Keyboard.press('4');
        }
        if (r == 0 && c == 4) {
          Keyboard.press('5');
        }
        if (r == 0 && c == 5) {
          Keyboard.press('6');
        }
        if (r == 0 && c == 6) {
          Keyboard.press('7');
        }
        if (r == 0 && c == 7) {
          Keyboard.press('8');
        }
        if (r == 0 && c == 8) {
          Keyboard.press('9');
        }
        if (r == 0 && c == 9) {
          Keyboard.press('0');
        }
        //Second Column
        if (r == 1 && c == 0) {
          Keyboard.press('q');
        }
        if (r == 1 && c == 1) {
          Keyboard.press('w');
        }
        if (r == 1 && c == 2) {
          Keyboard.press('e');
        }
        if (r == 1 && c == 3) {
          Keyboard.press('r');
        }
        if (r == 1 && c == 4) {
          Keyboard.press('t');
        }
        if (r == 1 && c == 5) {
          Keyboard.press('y');
        }
        if (r == 1 && c == 6) {
          Keyboard.press('u');
        }
        if (r == 1 && c == 7) {
          Keyboard.press('i');
        }
        if (r == 1 && c == 8) {
          Keyboard.press('o');
        }
        if (r == 1 && c == 9) {
          Keyboard.press('p');
        }
        //third column
        if (r == 2 && c == 0) {
          Keyboard.press('a');
        }
        if (r == 2 && c == 1) {
          Keyboard.press('s');
        }
        if (r == 2 && c == 2) {
          Keyboard.press('d');
        }
        if (r == 2 && c == 3) {
          Keyboard.press('f');
        }
        if (r == 2 && c == 4) {
          Keyboard.press('g');
        }
        if (r == 2 && c == 5) {
          Keyboard.press('h');
        }
        if (r == 2 && c == 6) {
          Keyboard.press('j');
        }
        if (r == 2 && c == 7) {
          Keyboard.press('k');
        }
        if (r == 2 && c == 8) {
          Keyboard.press('l');
        }
        if (r == 2 && c == 9) {
          Keyboard.press(KEY_RETURN);
        }
        //Forth Column
        if (r == 3 && c == 0) {
          Keyboard.press(KEY_CAPS_LOCK);
        }
        if (r == 3 && c == 1) {
          Keyboard.press('z');
        }
        if (r == 3 && c == 2) {
          Keyboard.press('x');
        }
        if (r == 3 && c == 3) {
          Keyboard.press('c');
        }
        if (r == 3 && c == 4) {
          Keyboard.press('v');
        }
        if (r == 3 && c == 5) {
          Keyboard.press('b');
        }
        if (r == 3 && c == 6) {
          Keyboard.press('n');
        }
        if (r == 3 && c == 7) {
          Keyboard.press('m');
        }
        if (r == 3 && c == 8) {
          Keyboard.press(KEY_RIGHT_SHIFT);
        }
        if (r == 3 && c == 9) {
          Keyboard.press(' ');
        }
        while (digitalRead(r0 + r) == 0) delay(10);
        Keyboard.releaseAll();
      }
    }
    digitalWrite(c0 + c, HIGH);
  }
}

bool Shift()
{
  return digitalRead(A0)==0;
}

