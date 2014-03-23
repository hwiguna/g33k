import processing.serial.*;

Serial myPort;        // The serial port
PFont f;

void setup() {
  size(360, 360);
  background(0);

  // Create the font
  printArray(PFont.list());
  f = createFont("ComicSansMS", 320);
  textFont(f);
  textAlign(CENTER, CENTER);
  translate(180,180);
  fill(255, 204, 0);

  // List all the available serial ports
  println(Serial.list());
  
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[7], 9600);
  
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
} 

void draw() {
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    background(0);
    //rectMode(CENTER);
    text(inString, 180, 120);
  }
}





