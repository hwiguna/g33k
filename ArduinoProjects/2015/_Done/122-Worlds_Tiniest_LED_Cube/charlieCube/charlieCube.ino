/********************************** SIGNATURE *********************************\
  |                                      ,,                                      |
  |                     db             `7MM                                      |
  |                    ;MM:              MM                                      |
  |                   ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8               |
  |                  ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'               |
  |                  AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                   |
  |                 A'     VML  L.   I8  MM    MM YM.    ,  MM                   |
  |               .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                 |
  |                                                                              |
  |                                                                              |
  |                                  ,,    ,,                                    |
  |                      .g8"""bgd `7MM    db        `7MM                        |
  |                    .dP'     `M   MM                MM                        |
  |                    dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                  |
  |                    MM            MM    MM 6M'  OO  MM ;Y                     |
  |                    MM.    `7MMF' MM    MM 8M       MM;Mm                     |
  |                    `Mb.     MM   MM    MM YM.    , MM `Mb.                   |
  |                      `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                  |
  |                                                                              |
  \******************************************************************************/
/*********************************** LICENCE **********************************\
  | Copyright (c) 2012, Asher Glick                                              |
  | All rights reserved.                                                         |
  |                                                                              |
  | Redistribution and use in source and binary forms, with or without           |
  | modification, are permitted provided that the following conditions are met:  |
  |                                                                              |
  | * Redistributions of source code must retain the above copyright notice,     |
  |   this list of conditions and the following disclaimer.                      |
  | * Redistributions in binary form must reproduce the above copyright notice,  |
  |   this list of conditions and the following disclaimer in the documentation  |
  |   and/or other materials provided with the distribution.                     |
  |                                                                              |
  | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
  | AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
  | IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
  | ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
  | LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
  | CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
  | SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
  | INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
  | CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
  | ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
  | POSSIBILITY OF SUCH DAMAGE.                                                  |
  \******************************************************************************/

#include "cubeplex.h"

int color = red;


void setup() {
  initCube();

  // how many secconds until the animation is told to progress
  animationMax = 5; //10;
}

void loop() {
  animationMax = 5;
  push();
  slide();
  bounce();

  animationMax = 5;   shiftSquares();

  animationMax = 10;
  fountian();
  
  animationMax = 10;  
  planarFlop3D();
  planarSpin();
  
  animationMax = 5;   trifade();
  
  //tunnel(); // color fade (too subtle?)
  //HariTest(); // too bright
  //chaseTheDot(); too bright
}

void bounce() {
  continuePattern = true;
  int animationSpeed = 80;
  while (continuePattern) {
    animationSpeed = 30;
    for (int z = 0; z <= 3; z++) {
      drawBox(color, 0, 0, z, 3, 3, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    animationSpeed = 30;
    for (int z = 3; z >= 0; z--) {
      drawBox(color, 0, 0, z, 3, 3, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    color = nextColor(color);
  }
}

void push() {
  continuePattern = true;
  int animationSpeed;
  while (continuePattern) {
    animationSpeed = 30;
    for (int x = 0; x <= 3; x++) {
      drawBox(color, x, 0, 0, x, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    animationSpeed = 30;
    for (int x = 3; x >= 0; x--) {
      drawBox(color, x, 0, 0, x, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    color = nextColor(color);
  }
}

void slide() {
  continuePattern = true;
  int animationSpeed = 80;
  while (continuePattern) {
    animationSpeed = 30;
    for (int y = 0; y <= 3; y++) {
      drawBox(color, 0, y, 0, 3, y, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    animationSpeed = 30;
    for (int y = 3; y >= 0; y--) {
      drawBox(color, 0, y, 0, 3, y, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
      animationSpeed += 40;
    }
    color = nextColor(color);
  }
}
void HariTest()
{
  int animationSpeed = 80;
  for (byte cl = 0; cl < 3; cl++)
  {
    byte c;
    switch (cl)
    {
      case 0: c = yellow; break;
      case 1: c = green; break;
      case 2: c = blue; break;
    }
    for (int z = 0; z < 4; z++) {
      for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
          drawLed(c, 1, x, y, z);
          flushBuffer();
          clearBuffer();
          delay(animationSpeed);
        }
      }
    }
  }
}
/********************************* PLANAR SPIN ********************************\
  | A plane of light spins around the virtical center of the cube and changes    |
  | colors after a certian number of rotations                                   |
  |                                                                              |
  | Written By: Asher Glick                                                      |
  \******************************************************************************/
void planarSpin() {
  continuePattern = true;
  int animationSpeed = 50;
  int spinsPerColor = 1; // a spin is actually half a revolution
  while (continuePattern) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < spinsPerColor; i++) {
      for (int x = 0; x < 3; x++) {
        drawLine(color, x, 0, 0, 3 - x, 3, 0);
        drawLine(color, x, 0, 1, 3 - x, 3, 1);
        drawLine(color, x, 0, 2, 3 - x, 3, 2);
        drawLine(color, x, 0, 3, 3 - x, 3, 3);
        flushBuffer();
        clearBuffer();
        delay(animationSpeed);
      }
      for (int y = 0; y < 3; y++) {
        drawLine(color, 3, y, 0, 0, 3 - y, 0);
        drawLine(color, 3, y, 1, 0, 3 - y, 1);
        drawLine(color, 3, y, 2, 0, 3 - y, 2);
        drawLine(color, 3, y, 3, 0, 3 - y, 3);
        flushBuffer();
        clearBuffer();
        delay(animationSpeed);
      }
    }
    color = nextColor(color);
  }
}

/********************************** FOUNTIAN **********************************\
  | Light shoots up the middle of the cube then once it reaches the top fall     |
  | back down on the outside of the cube. After it hits the bottom it changes    |
  | color and starts again                                                       |
  |                                                                              |
  | Written By: Asher Glick                                                      |
  \******************************************************************************/
void fountian() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    for (int z = 0; z <= 3; z++) {
      drawBoxWalls(color, 1, 1, z, 2, 2, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 3; z >= 0; z--) {
      drawBoxWalls(color, 0, 0, z, 3, 3, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    color = nextColor(color);
  }
}

/********************************** TRI-FADE **********************************\
  | This animation fades through the red green and blue colors of the leds       |
  | creating different mixtures of each of the colors.                           |
  |                                                                              |
  | Written By: Asher Glick                                                      |
  \******************************************************************************/
void trifade() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    // blue fade out, red fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(blue, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(red, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // red fade out, green fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(red, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(green, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // green fade out, blue fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(green, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(blue, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
}

/******************************** SHIFT SQUARES *******************************\
  | Three 2x2x2 squares start on the cube each a red green or blue. then they    |
  | randomly move around the cube one at a time, if they crash into each other   |
  | then then both leds turn on and while they occupy the same space they apear  |
  | a different color                                                            |
  |                                                                              |
  | Written By: Asher Glick                                                      |
  \******************************************************************************/
void shiftSquares() {
  int animationSpeed = 100;

  int blx = 2; // blue x
  int bly = 0; // blue y
  int blz = 0; // blue z

  int rdx = 0; // red x
  int rdy = 2; // red y
  int rdz = 0; // red z

  int gnx = 0; // green x
  int gny = 0; // green y
  int gnz = 2; // green z

  int * mover = &blx;
  continuePattern = true;

  while (continuePattern) {
    switch (random(0, 9)) {
      case 0: mover = &blx; break;
      case 1: mover = &bly; break;
      case 2: mover = &blz; break;
      case 3: mover = &rdx; break;
      case 4: mover = &rdy; break;
      case 5: mover = &rdz; break;
      case 6: mover = &gnx; break;
      case 7: mover = &gny; break;
      case 8: mover = &gnz; break;
    }
    *mover = (((*mover) + 2) % 4) - 1;
    drawBox(blue , abs(blx), abs(bly), abs(blz), abs(blx) + 1, abs(bly) + 1, abs(blz) + 1);
    drawBox(red  , abs(gnx), abs(gny), abs(gnz), abs(gnx) + 1, abs(gny) + 1, abs(gnz) + 1);
    drawBox(green, abs(rdx), abs(rdy), abs(rdz), abs(rdx) + 1, abs(rdy) + 1, abs(rdz) + 1);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed);
    *mover = (((*mover) + 2) % 4) - 1;
    drawBox(blue , abs(blx), abs(bly), abs(blz), abs(blx) + 1, abs(bly) + 1, abs(blz) + 1);
    drawBox(red  , abs(gnx), abs(gny), abs(gnz), abs(gnx) + 1, abs(gny) + 1, abs(gnz) + 1);
    drawBox(green, abs(rdx), abs(rdy), abs(rdz), abs(rdx) + 1, abs(rdy) + 1, abs(rdz) + 1);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed * 2);
  }
}

/*********************************** TUNNEL ***********************************\
  |
  \******************************************************************************/
void tunnel() {
  continuePattern = true;
  int animationSpeed = 100;

  int color1[]  = {R, R, R, R, B, B, B, B};
  int bright1[] = {2, 4, 6, 8, 2, 4, 6, 8};
  int color2[]  = {B, B, B, B, R, R, R, R};
  //int bright2[] = {6,4,2,0,6,4,2,0};
  int bright2[] = {8, 6, 4, 2, 8, 6, 4, 2};

  int index[]   = {0, 1, 2, 3, 4, 5, 6, 7};

  while (continuePattern) {
    drawBoxWalls(color1[index[0]], bright1[index[0]], 1, 1, 0, 2, 2, 0);
    drawBoxWalls(color2[index[0]], bright2[index[0]], 1, 1, 0, 2, 2, 0);
    drawBoxWalls(color1[index[1]], bright1[index[1]], 1, 1, 1, 2, 2, 1);
    drawBoxWalls(color2[index[1]], bright2[index[1]], 1, 1, 1, 2, 2, 1);
    drawBoxWalls(color1[index[2]], bright1[index[2]], 1, 1, 2, 2, 2, 2);
    drawBoxWalls(color2[index[2]], bright2[index[2]], 1, 1, 2, 2, 2, 2);
    drawBoxWalls(color1[index[3]], bright1[index[3]], 1, 1, 3, 2, 2, 3);
    drawBoxWalls(color2[index[3]], bright2[index[3]], 1, 1, 3, 2, 2, 3);

    drawBoxWalls(color1[index[4]], bright1[index[4]], 0, 0, 3, 3, 3, 3);
    drawBoxWalls(color2[index[4]], bright2[index[4]], 0, 0, 3, 3, 3, 3);
    drawBoxWalls(color1[index[5]], bright1[index[5]], 0, 0, 2, 3, 3, 2);
    drawBoxWalls(color2[index[5]], bright2[index[5]], 0, 0, 2, 3, 3, 2);
    drawBoxWalls(color1[index[6]], bright1[index[6]], 0, 0, 1, 3, 3, 1);
    drawBoxWalls(color2[index[6]], bright2[index[6]], 0, 0, 1, 3, 3, 1);
    drawBoxWalls(color1[index[7]], bright1[index[7]], 0, 0, 0, 3, 3, 0);
    drawBoxWalls(color2[index[7]], bright2[index[7]], 0, 0, 0, 3, 3, 0);


    flushBuffer();
    clearBuffer();
    for (int i = 0; i < 8; i++) {
      //index[i] = index[i]==7?0:index[i]+1;
      index[i] = (index[i] + 1) % 8;
    }
    delay(animationSpeed);

  }
}
/******************************** CHASE THE DOT *******************************\
  | A single point of light moves around the cube randomly and changes colors    |
  | when it tries to go out of bounds                                            |
  |                                                                              |
  | Inspired By: Jonah Glick                                                     |
  | Written By: Asher Glick                                                      |
  \******************************************************************************/
void chaseTheDot() {
  continuePattern = true;
  int animationSpeed = 100;

  int xpos = 0;
  int ypos = 0;
  int zpos = 0;

  while (continuePattern) {
    switch (random(0, 6)) {
      case 0:
        if (xpos > 0) {
          xpos--;
          break;
        }
        else color = nextColor(color);
      case 1:
        if (xpos < 3) {
          xpos++;
          break;
        }
        else color = nextColor(color);
        xpos--; break;

      case 2:
        if (ypos > 0) {
          ypos--;
          break;
        }
        else color = nextColor(color);
      case 3:
        if (ypos < 3) {
          ypos++;
          break;
        }
        else color = nextColor(color);
        ypos--; break;

      case 4:
        if (zpos > 0) {
          zpos--;
          break;
        }
        else color = nextColor(color);
      case 5:
        if (zpos < 3) {
          zpos++;
          break;
        }
        else color = nextColor(color);
        zpos--; break;
    }
    drawLed(color, xpos, ypos, zpos);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed);
  }
}
/********************************* PLANAR FLOP ********************************\
  |
  \******************************************************************************/
/******************************* PLANAR FLOP 3D *******************************\
  | Version 2 of the planar flop, doing more complicated maths and 3D vectors    |
  | 'n stuff. Making this function found the bug of reversed z axis line drawing |
  \******************************************************************************/
void planarFlop3D() {
  continuePattern = true;
  int animationSpeed = 50;
  while (continuePattern) {

    for (int y = 3; y > 0; y--) {
      for (int z = 0; z < 4; z++) drawLine(color, 0, 3, z, 3, y, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int x = 3; x > 0; x--) {
      for (int z = 0; z < 4; z++) drawLine(color, 0, 3, z, x, 0, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }


    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 4; y++) drawLine(color, 0, y, 0, x, y, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 3; z > 0; z--) {
      for (int y = 0; y < 4; y++) drawLine(color, 0, y, 0, 3, y, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }

    for (int z = 0; z < 3; z++) {
      for (int x = 0; x < 4; x++) drawLine(color, x, 0, 0, x, 3, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int y = 3; y > 0; y--) {
      for (int x = 0; x < 4; x++) drawLine(color, x, 0, 0, x, y, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }

    for (int y = 0; y < 3; y++) {
      for (int z = 0; z < 4; z++) drawLine(color, 3, 0, z, 0, y, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int x = 0; x < 3; x++) {
      for (int z = 0; z < 4; z++) drawLine(color, 3, 0, z, x, 3, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }

    for (int x = 3; x > 0; x--) {
      for (int y = 0; y < 4; y++) drawLine(color, 3, y, 3, x, y, 0);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 0; z < 3; z++) {
      for (int y = 0; y < 4; y++) drawLine(color, 3, y, 3, 0, y, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }

    for (int z = 3; z > 0; z--) {
      for (int x = 0; x < 4; x++) drawLine(color, x, 3, 3, x, 0, z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 4; x++) drawLine(color, x, 3, 3, x, y, 0);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    color = nextColor(color);
  }
}
