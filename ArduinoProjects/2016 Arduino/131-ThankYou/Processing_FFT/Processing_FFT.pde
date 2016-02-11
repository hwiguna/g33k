
import processing.sound.*;

FFT fft;
AudioIn in;
int bands = 2;
float[] spectrum = new float[bands];

//-- Serial --
import processing.serial.*;
Serial myPort;  // Create object from Serial class

void setupSerial()
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void setup() {
  setupSerial();

  size(512, 360);
  background(255);

  // Create an Input stream which is routed into the Amplitude analyzer
  fft = new FFT(this, bands);
  in = new AudioIn(this, 0);

  // start the Audio Input
  in.start();

  // patch the AudioIn
  fft.input(in);
}      

void draw() { 
  background(255);
  fft.analyze(spectrum);

  for (int i = 0; i < bands; i++) {
    // The result of the FFT is normalized
    // draw the line for frequency band i scaling it up by 5 to get more amplitude.
    line( i, height, i, height - spectrum[i]*height*5 );
  } 
float level = spectrum[1]*1000;
println(level);
  if (level > 30) myPort.write('4'); else
  if (level > 20) myPort.write('3'); else
  if (level > 10) myPort.write('2'); else
  if (level > 2) myPort.write('1'); else
    myPort.write('0');
}