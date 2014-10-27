void setup()   {
  Serial.begin(9600);
  SetupScreen();
  SetupKeypad();
  SetupBoard();

  //TestPattern();
  DrawBoard();
}

void SetupBoard()
{
  for (int x=0; x<9; x++) {
    for (int y=0; y<9; y++) {
      board[x][y] = puzzle[y][x];
    }
  }
}

void SetupScreen()
{
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);
  display.clearDisplay();   // clears the screen and buffer
  display.setRotation(3);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
}

void SetupKeypad()
{
  for (byte index=0; index<4; index++)
  {
    pinMode(col3Pin+index, OUTPUT);
    digitalWrite(col3Pin+index, HIGH);
    pinMode(row0Pin+index, INPUT_PULLUP);
  }
}

