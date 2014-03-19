// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float xMid;
float yMid;
float xVal, yVal, zVal;

void setup () {
  // set the window size:
  size(700, 700); 
  xMid = width/2;  
  yMid = height/2;

  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[7], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
  frameRate(15);
}
void draw () {
  fill(0);
  rect(0,0,100,50);
  fill(255);
  DrawNum("X=", xVal, 10,15);
  DrawNum("Y=", yVal, 10,30);
  DrawNum("Z=", zVal, 10,45);
}

void serialEvent (Serial myPort) {

  // get the ASCII string:
  String  inString = myPort.readStringUntil('\n');

  if (inString != null) {
    String[] list = split(inString, ',');
    float[] floats = {
      0, 0, 0
    };
    for (int i=0; i < list.length; i++) {
      floats[i] = float(list[i]); 
      float forPlot = map(floats[i], 0, 1023, 0, height);

      // draw the line:
      switch (i) {
      case 0: 
        stroke(0x0);        line(xMid, yMid, width, yMid);
        stroke(255, 0, 0);  line(xMid, yMid, xMid+forPlot, yMid);
        xVal = floats[i];
        break;

      case 1: 
        stroke(0x0);        line(xMid, yMid, xMid, 0);
        stroke(0, 255, 127);  line(xMid, yMid, xMid, yMid-forPlot);
        yVal = floats[i];
        break;

      case 2: 
        stroke(0x0); strokeWeight(2);        line(xMid, yMid, xMid+1023, yMid-1023);
        stroke(127, 127, 255);  strokeWeight(1); line(xMid, yMid, xMid+forPlot, yMid-forPlot);
        zVal = floats[i];
        break;
      }

      line(xPos, height - forPlot, xPos, height - forPlot);
    }


    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }
  }
}

void DrawNum( String label, float num, float x, float y) {
  //fill(0xFF0000);
  //rect(0,0,90,30);
  text(label + num, x,y);
}

void Stop() {
  myPort.stop();
}

