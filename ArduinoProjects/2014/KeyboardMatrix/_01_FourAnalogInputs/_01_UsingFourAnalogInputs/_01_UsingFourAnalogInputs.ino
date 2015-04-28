// Keyboard Matrix reader using 4 analog pins
// by Hari Wiguna 2014
// Circuit and this code at https://github.com/hwiguna/g33k

byte rowPins[] = {A0,A1,A2,A3};
byte rowChars[][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
}

void setup() {
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  // initialize the serial communication:
  Serial.begin(9600);
}

byte AnalogToIndex(int a) {
  return a < 360 ? 0 : a < 548 ? 1 : a < 734 ? 2 : a < 920 ? 3 : 4;
}

void loop() {
  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  int a2 = analogRead(A2);
  int a3 = analogRead(A3);
  
  int x0 = AnalogToIndex(a0);
  int x1 = AnalogToIndex(a1);
  int x2 = AnalogToIndex(a2);
  int x3 = AnalogToIndex(a3);
  
  Serial.print(a0);  Serial.print(",");
  Serial.print(a1);  Serial.print(",");
  Serial.print(a2);  Serial.print(",");
  Serial.print(a3);  Serial.print("  ");

  Serial.print(x0);  Serial.print(",");
  Serial.print(x1);  Serial.print(",");
  Serial.print(x2);  Serial.print(",");
  Serial.print(x3);  Serial.println("  ");

  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(500);
}

/* Processing code for this example
 
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
 
 void setup () {
 // set the window size:
 size(400, 300);        
 
 // List all the available serial ports
 println(Serial.list());
 // I know that the first port in the serial list on my mac
 // is always my  Arduino, so I open Serial.list()[0].
 // Open whatever port is the one you're using.
 myPort = new Serial(this, Serial.list()[0], 9600);
 // don't generate a serialEvent() unless you get a newline character:
 myPort.bufferUntil('\n');
 // set inital background:
 background(0);
 }
 void draw () {
 // everything happens in the serialEvent()
 }
 
 void serialEvent (Serial myPort) {
 // get the ASCII string:
 String inString = myPort.readStringUntil('\n');
 
 if (inString != null) {
 // trim off any whitespace:
 inString = trim(inString);
 // convert to an int and map to the screen height:
 float inByte = float(inString); 
 inByte = map(inByte, 0, 1023, 0, height);
 
 // draw the line:
 stroke(127,34,255);
 line(xPos, height, xPos, height - inByte);
 
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
 
 */

/* Max/MSP v5 patch for this example
 ----------begin_max5_patcher----------
1591.3oc0YszbaaCD9r7uBL5RalQUAO3CvdyS5zVenWZxs5NcfHgjPCIfJIT
RTxj+6AOHkoTDooroUs0AQPR73a+1cwtK3WtZxzEpOwqlB9YveAlL4KWMYh6
Q1GLo99ISKXeJMmU451zTUQAWpmNy+NM+SZ2y+sR1l02JuU9t0hJvFlNcMPy
dOuBv.U5Rgb0LPpRpYBooM3529latArTUVvzZdFPtsXAuDrrTU.f.sBffXxL
vGE50lIHkUVJXq3fRtdaoDvjYfbgjujaFJSCzq4.tLaN.bi1tJefWpqbO0uz
1IjIABoluxrJ1guxh2JfPO2B5zRNyBCLDFcqbwNvuv9fHCb8bvevyyEU2JKT
YhkBSWPAfq2TZ6YhqmuMUo0feUn+rYpY4YtY+cFw3lUJdCMYAapZqzwUHX8S
crjAd+SIOU6UBAwIygy.Q1+HAA1KH6EveWOFQlitUK92ehfal9kFhUxJ3tWc
sgpxadigWExbt1o7Ps5dk3yttivyg20W0VcSmg1G90qtx92rAZbH4ez.ruy1
nhmaDPidE07J+5n2sg6E6oKXxUSmc20o6E3SPRDbrkXnPGUYE.i5nCNB9TxQ
jG.G0kCTZtH88f07Rt0ZMMWUw8VvbKVAaTk6GyoraPdZff7rQTejBN54lgyv
HE0Ft7AvIvvgvIwO23jBdUkYOuSvIFSiNcjFhiSsUBwsUCh1AgfNSBAeNDBZ
DIDqY.f8.YjfjV1HAn9XDTxyNFYatVTkKx3kcK9GraZpI5jv7GOx+Z37Xh82
LSKHIDmDXaESoXRngIZQDKVkpxUkMCyXCQhcCK1z.G457gi3TzMz4RFD515F
G3bIQQwcP3SOF0zlkGhiCBQ1kOHHFFlXaEBQIQnCwv9QF1LxPZ.A4jR5cyQs
vbvHMJsLll01We+rE2LazX6zYmCraRrsPFwKg1ANBZFY.IAihr8Ox.aH0oAL
hB8nQVw0FSJiZeunOykbT6t3r.NP8.iL+bnwNiXuVMNJH9H9YCm89CFXPBER
bz422p8.O4dg6kRxdyjDqRwMIHTbT3QFLskxJ8tbmQK4tm0XGeZWF7wKKtYY
aTAF.XPNFaaQBinQMJ4QLF0aNHF0JtYuHSxoUZfZY6.UU2ejJTb8lQw8Fo5k
Rv6e2PI+fOM71o2ecY1VgTYdCSxxUqLokuYq9jYJi6lxPgD2NIPePLB0mwbG
YA9Rgxdiu1k5xiLlSU6JVnx6wzg3sYHwTesB8Z5D7RiGZpXyvDNJY.DQX3.H
hvmcUN4bP1yCkhpTle2P37jtBsKrLWcMScEmltOPv22ZfAqQAdKr9HzATQwZ
q18PrUGt6Tst2XMCRUfGuhXs6ccn23YloomMqcTiC5iMGPsHsHRWhWFlaenV
XcqwgCQiGGJzptyS2ZMODBz6fGza0bzmXBj7+DA94bvpR01MffAlueO7HwcI
pWCwmzJdvi9ILgflLAFmyXB6O7ML0YbD26lenmcGxjVsZUN+A6pUK7AtTrPg
M+eRYG0qD9j4I7eEbco8Xh6WcO.or9XDC6UCiewbXHkh6xm5LiPEkzpJDRTu
mEB44Fgz4NCtJvX.SM1vo2SlTCZGAe7GZu6ahdRyzFOhYZ+mbVVSYptBw.K1
tboIkatIA7c1cTKD1u.honLYV04VkluHsXe0szv9pQCE9Ro3jaVB1o15pz2X
zYoBvO5KXCAe0LCYJybE8ZODf4fV8t9qW0zYxq.YJfTosj1bv0xc.SaC0+AV
9V9L.KKyV3SyTcRtmzi6rO.O16USvts4B5xe9EymDvebK0eMfW6+NIsNlE2m
eqRyJ0utRq13+RjmqYKN1e.4d61jjdsauXe3.2p6jgi9hsNIv97CoyJ01xzl
c3ZhUCtSHx3UZgjoEJYqNY+hYs5zZQVFW19L3JDYaTlMLqAAt1G2yXlnFg9a
53L1FJVcv.cOX0dh7mCVGCLce7GFcQwDdH5Ta3nyAS0pQbHxegr+tGIZORgM
RnMj5vGl1Fs16drnk7Tf1XOLgv1n0d2iEsCxR.eQsNOZ4FGF7whofgfI3kES
1kCeOX5L2rifbdu0A9ae2X.V33B1Z+.Bj1FrP5iFrCYCG5EUWSG.hhunHJd.
HJ5hhnng3h9HPj4lud02.1bxGw.
-----------end_max5_patcher-----------
  
 */
