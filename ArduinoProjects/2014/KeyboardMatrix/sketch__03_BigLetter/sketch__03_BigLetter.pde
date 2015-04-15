
import processing.serial.*;

Serial myPort;        // The serial port
PFont f;

void setup() {
  size(360, 360);
  background(0);

  // Create the font
  // printArray(PFont.list()); // Uncomment this line to see a list of fonts
  f = createFont("ComicSansMS", 320);
  textFont(f);
  textAlign(CENTER, CENTER);
  translate(180,180);
  fill(255, 204, 0);

  String portNames[] = Serial.list();
  String portName = "";
  for (int i=0; i < portNames.length; i++)
  {
    print(portNames[i]);
    if (portNames[i].indexOf("/dev/tty.usbmodem") == 0) {
      println(" ***");
      portName = portNames[i];
    }
    else {
      println();
    }
  }
  myPort = new Serial(this, portName, 9600);
  
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
} 

void stop() {
  myPort.stop();
}

void draw() {
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    inString = trim(inString);
    background(0);
    text(inString, 180, 120);
  }
}

