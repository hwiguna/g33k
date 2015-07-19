// v01 - Original

//---------------------------------------------------------
/*

NHD_1_5_128128UGC3_example_uno.ino

Program for writing to Newhaven Display 128x128 Graphic Color OLED with SSD1351 controller.

 Pick one up today in the Newhaven Display shop!
 ------> http://www.newhavendisplay.com/nhd15128128ugc3-p-5602.html

This code is written for the Arduino Uno R3.

Copyright (c) 2015 - Newhaven Display International, Inc.

 Newhaven Display invests time and resources providing this open source code,
 please support Newhaven Display by purchasing products from Newhaven Display!

*/
//---------------------------------------------------------

// The 8 bit data bus is connected to PORTD[7..0]

#define   SDI_PIN    1    // SDI (serial mode) signal connected to pin 1
#define   SCL_PIN    0    // SCL (serial mdoe) signal connected to pin 0
#define    RS_PIN    8    // RS signal connected to pin 8
#define    RW_PIN    9    // R/W (6800 mode) signal connected to pin 9
#define    WR_PIN    9    // /WR (8080 mode) signal connected to pin 9
#define     E_PIN   10    // E (6800 mode) signal connected to pin 10
#define    RD_PIN   10    // /RD (8080 mode) signal connected to pin 10
#define   RES_PIN   11    // /RES signal connected to pin 11
#define    CS_PIN   12    // /CS signal connected to pin 12
#define   BS1_PIN   A0    // BS1 signal connected to pin A0
#define   BS0_PIN   A1    // BS0 signal connected to pin A1
#define   LVL_DIR   A2    // DIR (direction control) signal of level shifter IC connected to pin A2
#define   LVL_OEN   A3    // /OE (output enable) signal of level shifter IC connected to pin A3

#define    RED  0x0000FF
#define  GREEN  0x00FF00
#define   BLUE  0xFF0000
#define  WHITE  0xFFFFFF
#define  BLACK  0x000000


/*********************************/
/****** INTERFACE SELECTION ******/
/*********************************/

 const unsigned char interface = 1;    // 0 = 8-bit parallel (6800 mode) interface; 1 = 8-bit parallel (8080 mode) interface; 2 = 4-wire SPI interface
 
/*===============================*/
/*===============================*/
/*===============================*/


/*********************************/
/******** FONT TABLE 5x8 *********/
/************* START *************/
/*********************************/

unsigned char Ascii_1[97][5] = {     // Refer to "Times New Roman" Font Database...
                        //   Basic Characters
    {0x00,0x00,0x00,0x00,0x00},     //   (  0)    - 0x0000 Empty set
    {0x00,0x00,0x4F,0x00,0x00},     //   (  1)  ! - 0x0021 Exclamation Mark
    {0x00,0x07,0x00,0x07,0x00},     //   (  2)  " - 0x0022 Quotation Mark
    {0x14,0x7F,0x14,0x7F,0x14},     //   (  3)  # - 0x0023 Number Sign
    {0x24,0x2A,0x7F,0x2A,0x12},     //   (  4)  $ - 0x0024 Dollar Sign
    {0x23,0x13,0x08,0x64,0x62},     //   (  5)  % - 0x0025 Percent Sign
    {0x36,0x49,0x55,0x22,0x50},     //   (  6)  & - 0x0026 Ampersand
    {0x00,0x05,0x03,0x00,0x00},     //   (  7)  ' - 0x0027 Apostrophe
    {0x00,0x1C,0x22,0x41,0x00},     //   (  8)  ( - 0x0028 Left Parenthesis
    {0x00,0x41,0x22,0x1C,0x00},     //   (  9)  ) - 0x0029 Right Parenthesis
    {0x14,0x08,0x3E,0x08,0x14},     //   ( 10)  * - 0x002A Asterisk
    {0x08,0x08,0x3E,0x08,0x08},     //   ( 11)  + - 0x002B Plus Sign
    {0x00,0x50,0x30,0x00,0x00},     //   ( 12)  , - 0x002C Comma
    {0x08,0x08,0x08,0x08,0x08},     //   ( 13)  - - 0x002D Hyphen-Minus
    {0x00,0x60,0x60,0x00,0x00},     //   ( 14)  . - 0x002E Full Stop
    {0x20,0x10,0x08,0x04,0x02},     //   ( 15)  / - 0x002F Solidus
    {0x3E,0x51,0x49,0x45,0x3E},     //   ( 16)  0 - 0x0030 Digit Zero
    {0x00,0x42,0x7F,0x40,0x00},     //   ( 17)  1 - 0x0031 Digit One
    {0x42,0x61,0x51,0x49,0x46},     //   ( 18)  2 - 0x0032 Digit Two
    {0x21,0x41,0x45,0x4B,0x31},     //   ( 19)  3 - 0x0033 Digit Three
    {0x18,0x14,0x12,0x7F,0x10},     //   ( 20)  4 - 0x0034 Digit Four
    {0x27,0x45,0x45,0x45,0x39},     //   ( 21)  5 - 0x0035 Digit Five
    {0x3C,0x4A,0x49,0x49,0x30},     //   ( 22)  6 - 0x0036 Digit Six
    {0x01,0x71,0x09,0x05,0x03},     //   ( 23)  7 - 0x0037 Digit Seven
    {0x36,0x49,0x49,0x49,0x36},     //   ( 24)  8 - 0x0038 Digit Eight
    {0x06,0x49,0x49,0x29,0x1E},     //   ( 25)  9 - 0x0039 Dight Nine
    {0x00,0x36,0x36,0x00,0x00},     //   ( 26)  : - 0x003A Colon
    {0x00,0x56,0x36,0x00,0x00},     //   ( 27)  ; - 0x003B Semicolon
    {0x08,0x14,0x22,0x41,0x00},     //   ( 28)  < - 0x003C Less-Than Sign
    {0x14,0x14,0x14,0x14,0x14},     //   ( 29)  = - 0x003D Equals Sign
    {0x00,0x41,0x22,0x14,0x08},     //   ( 30)  > - 0x003E Greater-Than Sign
    {0x02,0x01,0x51,0x09,0x06},     //   ( 31)  ? - 0x003F Question Mark
    {0x32,0x49,0x79,0x41,0x3E},     //   ( 32)  @ - 0x0040 Commercial At
    {0x7E,0x11,0x11,0x11,0x7E},     //   ( 33)  A - 0x0041 Latin Capital Letter A
    {0x7F,0x49,0x49,0x49,0x36},     //   ( 34)  B - 0x0042 Latin Capital Letter B
    {0x3E,0x41,0x41,0x41,0x22},     //   ( 35)  C - 0x0043 Latin Capital Letter C
    {0x7F,0x41,0x41,0x22,0x1C},     //   ( 36)  D - 0x0044 Latin Capital Letter D
    {0x7F,0x49,0x49,0x49,0x41},     //   ( 37)  E - 0x0045 Latin Capital Letter E
    {0x7F,0x09,0x09,0x09,0x01},     //   ( 38)  F - 0x0046 Latin Capital Letter F
    {0x3E,0x41,0x49,0x49,0x7A},     //   ( 39)  G - 0x0047 Latin Capital Letter G
    {0x7F,0x08,0x08,0x08,0x7F},     //   ( 40)  H - 0x0048 Latin Capital Letter H
    {0x00,0x41,0x7F,0x41,0x00},     //   ( 41)  I - 0x0049 Latin Capital Letter I
    {0x20,0x40,0x41,0x3F,0x01},     //   ( 42)  J - 0x004A Latin Capital Letter J
    {0x7F,0x08,0x14,0x22,0x41},     //   ( 43)  K - 0x004B Latin Capital Letter K
    {0x7F,0x40,0x40,0x40,0x40},     //   ( 44)  L - 0x004C Latin Capital Letter L
    {0x7F,0x02,0x0C,0x02,0x7F},     //   ( 45)  M - 0x004D Latin Capital Letter M
    {0x7F,0x04,0x08,0x10,0x7F},     //   ( 46)  N - 0x004E Latin Capital Letter N
    {0x3E,0x41,0x41,0x41,0x3E},     //   ( 47)  O - 0x004F Latin Capital Letter O
    {0x7F,0x09,0x09,0x09,0x06},     //   ( 48)  P - 0x0050 Latin Capital Letter P
    {0x3E,0x41,0x51,0x21,0x5E},     //   ( 49)  Q - 0x0051 Latin Capital Letter Q
    {0x7F,0x09,0x19,0x29,0x46},     //   ( 50)  R - 0x0052 Latin Capital Letter R
    {0x46,0x49,0x49,0x49,0x31},     //   ( 51)  S - 0x0053 Latin Capital Letter S
    {0x01,0x01,0x7F,0x01,0x01},     //   ( 52)  T - 0x0054 Latin Capital Letter T
    {0x3F,0x40,0x40,0x40,0x3F},     //   ( 53)  U - 0x0055 Latin Capital Letter U
    {0x1F,0x20,0x40,0x20,0x1F},     //   ( 54)  V - 0x0056 Latin Capital Letter V
    {0x3F,0x40,0x38,0x40,0x3F},     //   ( 55)  W - 0x0057 Latin Capital Letter W
    {0x63,0x14,0x08,0x14,0x63},     //   ( 56)  X - 0x0058 Latin Capital Letter X
    {0x07,0x08,0x70,0x08,0x07},     //   ( 57)  Y - 0x0059 Latin Capital Letter Y
    {0x61,0x51,0x49,0x45,0x43},     //   ( 58)  Z - 0x005A Latin Capital Letter Z
    {0x00,0x7F,0x41,0x41,0x00},     //   ( 59)  [ - 0x005B Left Square Bracket
    {0x02,0x04,0x08,0x10,0x20},     //   ( 60)  \ - 0x005C Reverse Solidus
    {0x00,0x41,0x41,0x7F,0x00},     //   ( 61)  ] - 0x005D Right Square Bracket
    {0x04,0x02,0x01,0x02,0x04},     //   ( 62)  ^ - 0x005E Circumflex Accent
    {0x40,0x40,0x40,0x40,0x40},     //   ( 63)  _ - 0x005F Low Line
    {0x01,0x02,0x04,0x00,0x00},     //   ( 64)  ` - 0x0060 Grave Accent
    {0x20,0x54,0x54,0x54,0x78},     //   ( 65)  a - 0x0061 Latin Small Letter A
    {0x7F,0x48,0x44,0x44,0x38},     //   ( 66)  b - 0x0062 Latin Small Letter B
    {0x38,0x44,0x44,0x44,0x20},     //   ( 67)  c - 0x0063 Latin Small Letter C
    {0x38,0x44,0x44,0x48,0x7F},     //   ( 68)  d - 0x0064 Latin Small Letter D
    {0x38,0x54,0x54,0x54,0x18},     //   ( 69)  e - 0x0065 Latin Small Letter E
    {0x08,0x7E,0x09,0x01,0x02},     //   ( 70)  f - 0x0066 Latin Small Letter F
    {0x06,0x49,0x49,0x49,0x3F},     //   ( 71)  g - 0x0067 Latin Small Letter G
    {0x7F,0x08,0x04,0x04,0x78},     //   ( 72)  h - 0x0068 Latin Small Letter H
    {0x00,0x44,0x7D,0x40,0x00},     //   ( 73)  i - 0x0069 Latin Small Letter I
    {0x20,0x40,0x44,0x3D,0x00},     //   ( 74)  j - 0x006A Latin Small Letter J
    {0x7F,0x10,0x28,0x44,0x00},     //   ( 75)  k - 0x006B Latin Small Letter K
    {0x00,0x41,0x7F,0x40,0x00},     //   ( 76)  l - 0x006C Latin Small Letter L
    {0x7C,0x04,0x18,0x04,0x7C},     //   ( 77)  m - 0x006D Latin Small Letter M
    {0x7C,0x08,0x04,0x04,0x78},     //   ( 78)  n - 0x006E Latin Small Letter N
    {0x38,0x44,0x44,0x44,0x38},     //   ( 79)  o - 0x006F Latin Small Letter O
    {0x7C,0x14,0x14,0x14,0x08},     //   ( 80)  p - 0x0070 Latin Small Letter P
    {0x08,0x14,0x14,0x18,0x7C},     //   ( 81)  q - 0x0071 Latin Small Letter Q
    {0x7C,0x08,0x04,0x04,0x08},     //   ( 82)  r - 0x0072 Latin Small Letter R
    {0x48,0x54,0x54,0x54,0x20},     //   ( 83)  s - 0x0073 Latin Small Letter S
    {0x04,0x3F,0x44,0x40,0x20},     //   ( 84)  t - 0x0074 Latin Small Letter T
    {0x3C,0x40,0x40,0x20,0x7C},     //   ( 85)  u - 0x0075 Latin Small Letter U
    {0x1C,0x20,0x40,0x20,0x1C},     //   ( 86)  v - 0x0076 Latin Small Letter V
    {0x3C,0x40,0x30,0x40,0x3C},     //   ( 87)  w - 0x0077 Latin Small Letter W
    {0x44,0x28,0x10,0x28,0x44},     //   ( 88)  x - 0x0078 Latin Small Letter X
    {0x0C,0x50,0x50,0x50,0x3C},     //   ( 89)  y - 0x0079 Latin Small Letter Y
    {0x44,0x64,0x54,0x4C,0x44},     //   ( 90)  z - 0x007A Latin Small Letter Z
    {0x00,0x08,0x36,0x41,0x00},     //   ( 91)  { - 0x007B Left Curly Bracket
    {0x00,0x00,0x7F,0x00,0x00},     //   ( 92)  | - 0x007C Vertical Line
    {0x00,0x41,0x36,0x08,0x00},     //   ( 93)  } - 0x007D Right Curly Bracket
    {0x02,0x01,0x02,0x04,0x02},     //   ( 94)  ~ - 0x007E Tilde
    {0x08,0x0C,0x0E,0x0C,0x08},     //   ( 95)  upward facing triangle/arrow
    {0x08,0x18,0x38,0x18,0x08},     //   ( 96)  downward facing triangle/arrow
};

/*===============================*/
/*======= FONT TABLE 5x8 ========*/
/*============= END =============*/
/*===============================*/


/*********************************/
/******* CUSTOM CHARACTERS *******/
/************* START *************/
/*********************************/

const unsigned char A10pt [] = {  // 'A' (11 pixels wide)
  0x0E, 0x00, //     ###    
  0x0F, 0x00, //     ####   
  0x1B, 0x00, //    ## ##   
  0x1B, 0x00, //    ## ##   
  0x13, 0x80, //    #  ###  
  0x31, 0x80, //   ##   ##  
  0x3F, 0xC0, //   ######## 
  0x7F, 0xC0, //  ######### 
  0x60, 0xC0, //  ##     ## 
  0x60, 0xE0, //  ##     ###
  0xE0, 0xE0, // ###     ###
};
const unsigned char D10pt [] = {  // 'D' (9 pixels wide)
  0xFC, 0x00, // ######   
  0xFF, 0x00, // ######## 
  0xC7, 0x00, // ##   ### 
  0xC3, 0x80, // ##    ###
  0xC1, 0x80, // ##     ##
  0xC1, 0x80, // ##     ##
  0xC1, 0x80, // ##     ##
  0xC3, 0x80, // ##    ###
  0xC7, 0x00, // ##   ### 
  0xFE, 0x00, // #######  
  0xFC, 0x00, // ######
};
const unsigned char E10pt [] = {  // 'E' (7 pixels wide)
  0xFE, // #######
  0xFE, // #######
  0xC0, // ##     
  0xC0, // ##     
  0xFC, // ###### 
  0xFC, // ###### 
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xFE, // #######
  0xFE, // #######
};
const unsigned char H10pt [] = {  // 'H' (8 pixels wide)
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xFF, // ########
  0xFF, // ########
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC3, // ##    ##
};
const unsigned char I10pt [] = {  // 'I' (2 pixels wide)
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
  0xC0, // ##
};
const unsigned char L10pt [] = {  // 'L' (7 pixels wide)
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xC0, // ##     
  0xFE, // #######
  0xFE, // #######
};
const unsigned char N10pt [] = {  // 'N' (9 pixels wide)
  0xE1, 0x80, // ###    ##
  0xE1, 0x80, // ###    ##
  0xF1, 0x80, // ####   ##
  0xF9, 0x80, // #####  ##
  0xD9, 0x80, // ## ##  ##
  0xDD, 0x80, // ## ### ##
  0xCD, 0x80, // ##  ## ##
  0xC7, 0x80, // ##   ####
  0xC7, 0x80, // ##   ####
  0xC3, 0x80, // ##    ###
  0xC1, 0x80, // ##     ##
};
const unsigned char P10pt [] = {  // 'P' (8 pixels wide)
  0xFC, // ######  
  0xFF, // ########
  0xC3, // ##    ##
  0xC3, // ##    ##
  0xC7, // ##   ###
  0xFE, // ####### 
  0xF8, // #####   
  0xC0, // ##      
  0xC0, // ##      
  0xC0, // ##      
  0xC0, // ##
};
const unsigned char S10pt [] = {  // 'S' (7 pixels wide)
  0x7C, //  ##### 
  0xFC, // ###### 
  0xC0, // ##     
  0xC0, // ##     
  0xF0, // ####   
  0x7C, //  ##### 
  0x1E, //    ####
  0x06, //      ##
  0x06, //      ##
  0xFE, // #######
  0xF8, // #####
};
const unsigned char V10pt [] = {  // 'V' (10 pixels wide)
  0xE0, 0xC0, // ###     ##
  0xE1, 0xC0, // ###    ###
  0x61, 0x80, //  ##    ## 
  0x71, 0x80, //  ###   ## 
  0x73, 0x00, //  ###  ##  
  0x33, 0x00, //   ##  ##  
  0x3B, 0x00, //   ### ##  
  0x1E, 0x00, //    ####   
  0x1E, 0x00, //    ####   
  0x1C, 0x00, //    ###    
  0x0C, 0x00, //     ##
};
const unsigned char W10pt [] = {  // 'W' (16 pixels wide)
  0xE1, 0x83, // ###    ##     ##
  0xE1, 0xC7, // ###    ###   ###
  0x63, 0xC6, //  ##   ####   ## 
  0x63, 0xC6, //  ##   ####   ## 
  0x72, 0xC6, //  ###  # ##   ## 
  0x32, 0x6C, //   ##  #  ## ##  
  0x36, 0x6C, //   ## ##  ## ##  
  0x3E, 0x6C, //   #####  ## ##  
  0x1C, 0x28, //    ###    # #   
  0x1C, 0x38, //    ###    ###   
  0x1C, 0x38, //    ###    ###
};
const unsigned char Y10pt [] = {  // 'Y' (8 pixels wide)
  0xE3, // ###   ##
  0x66, //  ##  ## 
  0x66, //  ##  ## 
  0x34, //   ## #  
  0x34, //   ## #  
  0x18, //    ##   
  0x18, //    ##   
  0x18, //    ##   
  0x18, //    ##   
  0x18, //    ##   
  0x18, //    ##
};

/*===============================*/
/*====== CUSTOM CHARACTERS ======*/
/*============= END =============*/
/*===============================*/


/*********************************/
/********** ICON BITMAP **********/
/************* START *************/
/*********************************/

const unsigned char smiley20x20[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x00, 0x3e, 0x44, 0x60, 0xa1, 0xca, 0x2e, 0x84, 0xb7, 0x0c, 0x70, 0xac, 
0x0c, 0x70, 0xae, 0x2f, 0x84, 0xb7, 0x60, 0xa1, 0xca, 0x00, 0x3e, 0x44, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x41, 0x91, 0xc1, 0x41, 0x9b, 0xc7, 0x61, 0xbf, 0xdd, 0x73, 0xdc, 0xef, 0x80, 0xef, 0xfb, 
0x7f, 0xef, 0xfb, 0x73, 0xdc, 0xef, 0x5f, 0xbf, 0xdd, 0x41, 0x9c, 0xc7, 0x41, 0x92, 0xc1, 0x00, 0x3e, 0x44, 0x1b, 0x1b, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x1b, 0x00, 0x3e, 0x44, 0x37, 0x95, 0xc5, 0x61, 0xc9, 0xe5, 0x79, 0xf4, 0xfe, 0x7a, 0xf5, 0xfe, 0x7a, 0xf5, 0xfe, 0x7a, 0xf5, 0xfe, 
0x7a, 0xf5, 0xfe, 0x79, 0xf4, 0xfe, 0x7a, 0xf5, 0xfe, 0x79, 0xf5, 0xfe, 0x5e, 0xca, 0xe5, 0x36, 0x94, 0xc5, 0x00, 0x3e, 0x44, 0x1b, 0x1b, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x3f, 0xa0, 0xcd, 0x65, 0xe0, 0xf3, 0x71, 0xf4, 0xfe, 0x71, 0xf4, 0xfe, 0x71, 0xf4, 0xfe, 0x71, 0xf3, 0xfe, 0x70, 0xf4, 0xfe, 
0x71, 0xf4, 0xfe, 0x70, 0xf3, 0xfe, 0x71, 0xf4, 0xfe, 0x71, 0xf3, 0xfe, 0x70, 0xf4, 0xfe, 0x64, 0xde, 0xf3, 0x3d, 0xa1, 0xcd, 0x00, 0x3e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x34, 0x98, 0xca, 0x5d, 0xde, 0xf4, 0x68, 0xf2, 0xfe, 0x67, 0xf2, 0xfe, 0x67, 0xf2, 0xfe, 0x2c, 0x8f, 0xa2, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 
0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x2c, 0x8f, 0xa2, 0x68, 0xf2, 0xfe, 0x67, 0xf3, 0xfe, 0x67, 0xf2, 0xfe, 0x5b, 0xde, 0xf4, 0x33, 0x98, 0xca, 0x00, 0x3e, 0x44, 0x00, 0x00, 0x00, 
0x22, 0x22, 0x22, 0x41, 0x9b, 0xcd, 0x4f, 0xcb, 0xe9, 0x5f, 0xf1, 0xfe, 0x5e, 0xf1, 0xfe, 0x3d, 0xb5, 0xc6, 0x00, 0x46, 0x5d, 0xa6, 0xbe, 0xc6, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xa6, 0xbe, 0xc6, 0x00, 0x46, 0x5d, 0x3e, 0xb5, 0xc6, 0x5f, 0xf1, 0xfe, 0x5f, 0xf1, 0xfe, 0x4c, 0xcb, 0xe9, 0x40, 0x9b, 0xcd, 0x22, 0x22, 0x22, 
0x00, 0x3e, 0x44, 0x38, 0xa5, 0xd5, 0x56, 0xef, 0xfe, 0x55, 0xf0, 0xfe, 0x37, 0xb5, 0xc6, 0x00, 0x46, 0x5d, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf6, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x46, 0x5d, 0x37, 0xb4, 0xc6, 0x55, 0xef, 0xfe, 0x55, 0xf0, 0xfe, 0x37, 0xa5, 0xd4, 0x00, 0x3e, 0x44, 
0x60, 0xb0, 0xda, 0x40, 0xc4, 0xe7, 0x4c, 0xef, 0xfe, 0x4d, 0xee, 0xfe, 0x00, 0x46, 0x5d, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x46, 0x5d, 0x4c, 0xef, 0xfe, 0x4d, 0xee, 0xfe, 0x3f, 0xc4, 0xe8, 0x60, 0xb0, 0xda, 
0x30, 0x9c, 0xd3, 0x3e, 0xdb, 0xf5, 0x44, 0xed, 0xfe, 0x44, 0xee, 0xfe, 0x00, 0x46, 0x5d, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x46, 0x5d, 0x44, 0xed, 0xfe, 0x43, 0xed, 0xfe, 0x3d, 0xda, 0xf5, 0x2f, 0x9c, 0xd3, 
0x0e, 0x8f, 0xd0, 0x39, 0xe8, 0xfd, 0x3b, 0xec, 0xfe, 0x3e, 0xed, 0xfe, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 
0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x3f, 0xed, 0xfe, 0x3a, 0xec, 0xfe, 0x38, 0xe8, 0xfd, 0x0e, 0x8f, 0xd0, 
0x0e, 0x94, 0xd5, 0x30, 0xe7, 0xfe, 0x32, 0xeb, 0xfe, 0x4a, 0xee, 0xfe, 0x63, 0xf1, 0xfe, 0x63, 0xf2, 0xfe, 0x63, 0xf2, 0xfe, 0x63, 0xf1, 0xfe, 0x63, 0xf2, 0xfe, 0x64, 0xf2, 0xfe, 
0x63, 0xf2, 0xfe, 0x63, 0xf2, 0xfe, 0x63, 0xf2, 0xfe, 0x63, 0xf1, 0xfe, 0x64, 0xf2, 0xfe, 0x64, 0xf2, 0xfe, 0x4a, 0xee, 0xfe, 0x32, 0xeb, 0xfe, 0x30, 0xe7, 0xfd, 0x0e, 0x94, 0xd4, 
0x30, 0xa6, 0xe0, 0x2a, 0xda, 0xf8, 0x2a, 0xe9, 0xfe, 0x60, 0xf1, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 
0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x6f, 0xf3, 0xfe, 0x60, 0xf1, 0xfe, 0x2a, 0xea, 0xfe, 0x29, 0xda, 0xf8, 0x30, 0xa7, 0xde, 
0x61, 0xbe, 0xea, 0x2c, 0xca, 0xf1, 0x23, 0xe9, 0xfe, 0x7b, 0xf5, 0xfe, 0x00, 0x46, 0x5d, 0x7e, 0xf5, 0xfe, 0x7d, 0xf5, 0xfe, 0x7e, 0xf5, 0xfe, 0x00, 0x46, 0x5d, 0x7e, 0xf5, 0xfe, 
0x7e, 0xf5, 0xfe, 0x00, 0x46, 0x5d, 0x7e, 0xf5, 0xfe, 0x7e, 0xf5, 0xfe, 0x7d, 0xf5, 0xfe, 0x00, 0x46, 0x5d, 0x7b, 0xf4, 0xfe, 0x23, 0xe9, 0xfe, 0x2c, 0xc9, 0xf1, 0x61, 0xbe, 0xe9, 
0x00, 0x3e, 0x44, 0x2e, 0xb9, 0xeb, 0x1b, 0xe8, 0xfe, 0x74, 0xf4, 0xfe, 0x8d, 0xf7, 0xfe, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x8d, 0xf7, 0xfe, 0x8d, 0xf7, 0xfe, 
0x8d, 0xf7, 0xfe, 0x8d, 0xf7, 0xfe, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x00, 0x46, 0x5d, 0x8d, 0xf7, 0xfe, 0x74, 0xf4, 0xfe, 0x1b, 0xe7, 0xfe, 0x2d, 0xba, 0xeb, 0x00, 0x3e, 0x44, 
0x22, 0x22, 0x22, 0x40, 0xb9, 0xec, 0x21, 0xd1, 0xf6, 0x56, 0xf0, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xf9, 0xfe, 0x9e, 0xfa, 0xfe, 
0x9e, 0xfa, 0xfe, 0x9e, 0xf9, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x9e, 0xfa, 0xfe, 0x57, 0xf0, 0xfe, 0x21, 0xd1, 0xf6, 0x3f, 0xb9, 0xec, 0x22, 0x22, 0x22, 
0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x2a, 0xb9, 0xef, 0x24, 0xde, 0xfc, 0x79, 0xf5, 0xfe, 0xad, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 
0xad, 0xfc, 0xfe, 0xae, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 0xad, 0xfc, 0xfe, 0xae, 0xfc, 0xfe, 0x79, 0xf5, 0xfe, 0x24, 0xde, 0xfc, 0x2a, 0xb9, 0xef, 0x00, 0x3e, 0x44, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x2b, 0xc1, 0xf3, 0x29, 0xdf, 0xfd, 0x74, 0xf4, 0xfe, 0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 
0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 0xbb, 0xfd, 0xfe, 0x74, 0xf4, 0xfe, 0x28, 0xe0, 0xfd, 0x2a, 0xc1, 0xf3, 0x00, 0x3e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x1b, 0x00, 0x3e, 0x44, 0x28, 0xbf, 0xf3, 0x1a, 0xd4, 0xfa, 0x41, 0xec, 0xfe, 0x74, 0xf4, 0xfe, 0x9e, 0xfa, 0xfe, 0xbb, 0xfe, 0xfe, 
0xbb, 0xfe, 0xfe, 0x9e, 0xfa, 0xfe, 0x74, 0xf4, 0xfe, 0x42, 0xec, 0xfe, 0x19, 0xd3, 0xfa, 0x29, 0xbf, 0xf4, 0x00, 0x3e, 0x44, 0x1b, 0x1b, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x44, 0x41, 0xc3, 0xf5, 0x2a, 0xc4, 0xf6, 0x1b, 0xd1, 0xfa, 0x0a, 0xdb, 0xfd, 0x01, 0xe2, 0xfe, 
0x01, 0xe2, 0xfe, 0x0a, 0xdb, 0xfd, 0x1b, 0xd1, 0xfa, 0x29, 0xc5, 0xf7, 0x41, 0xc3, 0xf6, 0x00, 0x3e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x00, 0x3e, 0x44, 0x62, 0xce, 0xf9, 0x32, 0xbe, 0xf6, 0x10, 0xb3, 0xf5, 
0x10, 0xb3, 0xf5, 0x32, 0xbe, 0xf6, 0x62, 0xce, 0xf9, 0x00, 0x3e, 0x44, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*===============================*/
/*========= ICON BITMAP =========*/
/*============= END =============*/
/*===============================*/


/*********************************/
/****** LOW LEVEL FUNCTIONS ******/
/************ START **************/
/*********************************/

void OLED_Command_128128RGB(unsigned char c)        // send command to OLED
{  
   unsigned char i;
   unsigned char mask = 0x80;
   switch(interface)
   {
      case 0:   digitalWrite(CS_PIN, LOW);               
                digitalWrite(RS_PIN, LOW);
                PORTD = c;
                digitalWrite(RW_PIN, LOW);
                digitalWrite(E_PIN, HIGH);
                digitalWrite(E_PIN, LOW);
                digitalWrite(CS_PIN, HIGH);
                break;
      case 1:   digitalWrite(CS_PIN, LOW);               
                digitalWrite(RS_PIN, LOW);
                PORTD = c;
                digitalWrite(WR_PIN, LOW);
                digitalWrite(WR_PIN, HIGH);
                digitalWrite(CS_PIN, HIGH);
                break;
      case 2:   digitalWrite(CS_PIN, LOW);               
                digitalWrite(RS_PIN, LOW);
                for(i=0;i<8;i++)
                {
                   digitalWrite(SCL_PIN, LOW);
                   if((c & mask) >> 7 == 1)
                   {
                      digitalWrite(SDI_PIN, HIGH);
                   }
                   else
                   {
                      digitalWrite(SDI_PIN, LOW);
                   }
                   digitalWrite(SCL_PIN, HIGH);
                   c = c << 1;
                }
                digitalWrite(CS_PIN, HIGH);
                break;
      default:  break;           
   }
} 

void OLED_Data_128128RGB(unsigned char d)        // send data to OLED
{ 
   unsigned char i;
   unsigned char mask = 0x80;
   switch(interface)
   {
      case 0:   digitalWrite(CS_PIN, LOW);
                digitalWrite(RS_PIN, HIGH);
                PORTD = d;
                digitalWrite(RW_PIN, LOW);
                digitalWrite(E_PIN, HIGH);
                digitalWrite(E_PIN, LOW);
                digitalWrite(CS_PIN, HIGH);
                break;
      case 1:   digitalWrite(CS_PIN, LOW);               
                digitalWrite(RS_PIN, HIGH);
                PORTD = d;
                digitalWrite(WR_PIN, LOW);
                digitalWrite(WR_PIN, HIGH);
                digitalWrite(CS_PIN, HIGH);
                break;
                break;
      case 2:   digitalWrite(CS_PIN, LOW);               
                digitalWrite(RS_PIN, HIGH);
                for(i=0;i<8;i++)
                {
                   digitalWrite(SCL_PIN, LOW);
                   if((d & mask) >> 7 == 1)
                   {
                      digitalWrite(SDI_PIN, HIGH);
                   }
                   else
                   {
                      digitalWrite(SDI_PIN, LOW);
                   }
                   digitalWrite(SCL_PIN, HIGH);
                   d = d << 1;
                }
                digitalWrite(CS_PIN, HIGH);
                break;
      default:  break;           
   }
}

void OLED_SetColumnAddress_128128RGB(unsigned char x_start, unsigned char x_end)    // set column address start + end
{
   OLED_Command_128128RGB(0x15);
   OLED_Data_128128RGB(x_start);
   OLED_Data_128128RGB(x_end);
}

void OLED_SetRowAddress_128128RGB(unsigned char y_start, unsigned char y_end)    // set row address start + end
{
   OLED_Command_128128RGB(0x75);
   OLED_Data_128128RGB(y_start);
   OLED_Data_128128RGB(y_end);
}

void OLED_WriteMemoryStart_128128RGB(void)    // write to RAM command
{
    OLED_Command_128128RGB(0x5C);
}

void OLED_Pixel_128128RGB(unsigned long color)    // write one pixel of a given color
{
        OLED_Data_128128RGB((color>>16));
        OLED_Data_128128RGB((color>>8));
        OLED_Data_128128RGB(color);
}

void OLED_FillScreen_128128RGB(unsigned long color)    // fill screen with a given color
{
   unsigned int i,j;
   OLED_SetColumnAddress_128128RGB(0x00, 0x7F);
   OLED_SetRowAddress_128128RGB(0x00, 0x7F);
   OLED_WriteMemoryStart_128128RGB();
   for(i=0;i<128;i++)
   {
      for(j=0;j<128;j++)
      {
   OLED_Pixel_128128RGB(color);
      }
   }
}

/*===============================*/
/*===== LOW LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/***** HIGH LEVEL FUNCTIONS ******/
/************ START **************/
/*********************************/

void OLED_Text_128128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text
{
    int i;
    int count;
    unsigned char mask = 0x80;
    
    for(i=0;i<8;i++)     //each character is 8 px tall
    {
        OLED_SetColumnAddress_128128RGB(x_pos, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<5;count++)    //each character is 5px wide
        {
            if((Ascii_1[letter][count] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
        }
        y_pos++;
        mask = mask >> 1;
   }
}

void OLED_Text2x_128128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text (2x size)
{
    int i;
    int count;
    unsigned char mask = 0x80;
    
    for(i=1;i<=16;i++)     // each character is 16 pixels tall
    {
        OLED_SetColumnAddress_128128RGB(x_pos, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<10;count++)    // each character is 10 pixels wide
        {
            if((Ascii_1[letter][(count/2)] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
        }
        y_pos++;
        if((i%2)==0)
        {
          mask = mask >> 1;
        }
   }
}

void OLED_NHDText_128128RGB(unsigned long textColor, unsigned long backgroundColor)    // function to show NEWHAVEN DISPLAY
{
    int i;
    int count;
    unsigned char index = 0;
    unsigned char y_pos = 108;
    unsigned char mask = 0x80;
    
    for(i=0;i<11;i++)     // display custom character N
    {
        OLED_SetColumnAddress_128128RGB(11, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character E
    {
        OLED_SetColumnAddress_128128RGB(25, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((E10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character W
    {
        OLED_SetColumnAddress_128128RGB(36, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((W10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((W10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character H
    {
        OLED_SetColumnAddress_128128RGB(56, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((H10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character A
    {
        OLED_SetColumnAddress_128128RGB(68, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character V
    {
        OLED_SetColumnAddress_128128RGB(81, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((V10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((V10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character E
    {
        OLED_SetColumnAddress_128128RGB(95, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((E10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 108;
   
   for(i=0;i<11;i++)     // display custom character N
    {
        OLED_SetColumnAddress_128128RGB(107, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;  
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character D
    {
        OLED_SetColumnAddress_128128RGB(25, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((D10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((D10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character I
    {
        OLED_SetColumnAddress_128128RGB(39, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((I10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character S
    {
        OLED_SetColumnAddress_128128RGB(46, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((S10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character P
    {
        OLED_SetColumnAddress_128128RGB(57, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((P10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character L
    {
        OLED_SetColumnAddress_128128RGB(69, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((L10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character A
    {
        OLED_SetColumnAddress_128128RGB(80, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character Y
    {
        OLED_SetColumnAddress_128128RGB(94, 0x7F);
        OLED_SetRowAddress_128128RGB(y_pos, 0x7F);
        OLED_WriteMemoryStart_128128RGB();
        for (count=0;count<8;count++)
        {
            if((Y10pt[index] & mask) == mask)
                OLED_Pixel_128128RGB(textColor);
            else
                OLED_Pixel_128128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
}

void OLED_Icon_128128RGB(unsigned char x_pos, unsigned char y_pos)    // function to show icon
{
   unsigned int i, j;
   unsigned int height = 20;
   unsigned int width  = 20;
   
   OLED_SetColumnAddress_128128RGB(x_pos, (x_pos+width-1));
   OLED_SetRowAddress_128128RGB(y_pos, (y_pos+height-1));
   OLED_WriteMemoryStart_128128RGB();
   for(j=0;j<(height*width*3);j+=3)
   {
      OLED_Data_128128RGB(smiley20x20[j]>>2);
      OLED_Data_128128RGB(smiley20x20[(j+1)]>>2);
      OLED_Data_128128RGB(smiley20x20[(j+2)]>>2);
   }
}

void OLED_Spectrum_128128RGB(void)                  // function to show color spectrum
{
      unsigned char i, j;
      unsigned char blue, green, red;
      
      OLED_SetColumnAddress_128128RGB(0, 127);
      OLED_SetRowAddress_128128RGB(0, 37);
      OLED_WriteMemoryStart_128128RGB();
      for(i=0;i<128;i++)
      {
        OLED_Pixel_128128RGB(WHITE);
      }
      for(i=0;i<36;i++)
      {
        blue = 0x00;
        green = 0x00;
        red = 0x3F;
        OLED_Pixel_128128RGB(WHITE);
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          green += 3;
        }
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          red -= 3;
        }
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          blue += 3;
        }
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          green -= 3;
        }
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          red += 3;
        }
        for(j=0;j<21;j++)
        {
          OLED_Data_128128RGB(blue);
          OLED_Data_128128RGB(green);
          OLED_Data_128128RGB(red);
          blue -= 3;
        }
        OLED_Pixel_128128RGB(WHITE);
      }
      for(i=0;i<128;i++)
      {
        OLED_Pixel_128128RGB(WHITE);
      }
}

/*===============================*/
/*==== HIGH LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/******** INITIALIZATION *********/
/************ START **************/
/*********************************/

void OLED_Init_128128RGB(void)      //OLED initialization
{
    digitalWrite(RES_PIN, LOW);
    delay(500);
    digitalWrite(RES_PIN, HIGH);
    delay(500);

    OLED_Command_128128RGB(0xFD); // Command lock setting
    OLED_Data_128128RGB(0x12);    // unlock
    OLED_Command_128128RGB(0xFD); // Command lock setting
    OLED_Data_128128RGB(0xB1);    // unlock
    OLED_Command_128128RGB(0xAE);
    OLED_Command_128128RGB(0xB3); // clock & frequency
    OLED_Data_128128RGB(0xF1);    // clock=Diviser+1 frequency=fh 
    OLED_Command_128128RGB(0xCA); // Duty
    OLED_Data_128128RGB(0x7F);    // OLED _END+1
    OLED_Command_128128RGB(0xA2);   // Display offset
    OLED_Data_128128RGB(0x00);
    OLED_Command_128128RGB(0xA1); // Set display start line
    OLED_Data_128128RGB(0x00);    // 0x00 start line
    OLED_Command_128128RGB(0xA0); // Set Re-map, color depth
    OLED_Data_128128RGB(0xA0);    // 8-bit 262K
    OLED_Command_128128RGB(0xB5); // set GPIO
    OLED_Data_128128RGB(0x00);    // disabled
    OLED_Command_128128RGB(0xAB); // Function Set
    OLED_Data_128128RGB(0x01);    // 8-bit interface, internal VDD regulator
    OLED_Command_128128RGB(0xB4); // set VSL
    OLED_Data_128128RGB(0xA0);    // external VSL
    OLED_Data_128128RGB(0xB5);
    OLED_Data_128128RGB(0x55);
    OLED_Command_128128RGB(0xC1); // Set contrast current for A,B,C
    OLED_Data_128128RGB(0x8A);    // Color A
    OLED_Data_128128RGB(0x70);    // Color B
    OLED_Data_128128RGB(0x8A);    // Color C
    OLED_Command_128128RGB(0xC7); // Set master contrast
    OLED_Data_128128RGB(0x0F);    //  
    OLED_Command_128128RGB(0xB9); // use linear grayscale LUT
    OLED_Command_128128RGB(0xB1); // Set pre & dis-charge
    OLED_Data_128128RGB(0x32);    // pre=1h, dis=1h  
    OLED_Command_128128RGB(0xBB); // Set precharge voltage of color A,B,C
    OLED_Data_128128RGB(0x07);    //
    OLED_Command_128128RGB(0xB2);       // display enhancement
    OLED_Data_128128RGB(0xa4);    
    OLED_Data_128128RGB(0x00);
    OLED_Data_128128RGB(0x00);
    OLED_Command_128128RGB(0xB6); // precharge period
    OLED_Data_128128RGB(0x01);    
    OLED_Command_128128RGB(0xBE); // Set VcomH
    OLED_Data_128128RGB(0x07);
    OLED_Command_128128RGB(0xA6); // Normal display
    OLED_Command_128128RGB(0xAF); // Display on
}

/*===============================*/
/*======= INITIALIZATION ========*/
/*============= END =============*/
/*===============================*/

void setup()                                       // for Arduino, runs first at power on
{
   pinMode(LVL_OEN, OUTPUT);                       // configure LVL_OEN as output
   digitalWrite(LVL_OEN, LOW);
   pinMode(LVL_DIR, OUTPUT);                       // configure LVL_DIR as output
   digitalWrite(LVL_DIR, HIGH);
   DDRD = 0xFF;                                    // configure PORTD as output
   pinMode(RS_PIN, OUTPUT);                        // configure RS_PIN as output
   pinMode(RES_PIN, OUTPUT);                       // configure RES_PIN as output
   pinMode(CS_PIN, OUTPUT);                        // configure CS_PIN as output
   pinMode(BS0_PIN, OUTPUT);                       // configure BS0_PIN as output
   pinMode(BS1_PIN, OUTPUT);                       // configure BS1_PIN as output
   digitalWrite(CS_PIN, HIGH);                     // set CS_PIN
   switch(interface)
   {
     case 0:
       pinMode(RW_PIN, OUTPUT);                    // configure RW_PIN as output
       pinMode(E_PIN, OUTPUT);                     // configure E_PIN as output
       digitalWrite(BS0_PIN, HIGH);                // set BS0_PIN
       digitalWrite(BS1_PIN, HIGH);                // set BS1_PIN
       digitalWrite(RW_PIN, LOW);                  // reset RW_PIN
       digitalWrite(E_PIN, HIGH);                  // set E_PIN
       break;
     case 1: 
       pinMode(WR_PIN, OUTPUT);                    // configure WR_PIN as output
       pinMode(RD_PIN, OUTPUT);                    // configure RD_PIN as output
       digitalWrite(BS0_PIN, LOW);                 // set BS0_PIN
       digitalWrite(BS1_PIN, HIGH);                // reset BS1_PIN
       digitalWrite(WR_PIN, HIGH);                 // set WR_PIN
       digitalWrite(RD_PIN, HIGH);                 // set RD_PIN
       break;
     case 2:
       pinMode(SDI_PIN, OUTPUT);                   // configure SDI_PIN as output
       pinMode(SCL_PIN, OUTPUT);                   // configure SCL_PIN as output
       PORTD = 0x00;                               // reset SDI_PIN and SCL_PIN, ground DB[5..0] of the display
       digitalWrite(BS0_PIN, LOW);                 // reset BS0_PIN
       digitalWrite(BS1_PIN, LOW);                 // reset BS1_PIN
       digitalWrite(WR_PIN, LOW);                  // reset WR_PIN
       digitalWrite(RD_PIN, LOW);                  // reset RD_PIN
       break;
     default:
       break;
   }
}

void loop()                                         // main loop, runs after "setup()"
{  
   OLED_Init_128128RGB();                           // initialize display
   
   OLED_FillScreen_128128RGB(BLACK);                // fill screen with black
   
   OLED_NHDText_128128RGB(GREEN, BLACK);            // show NEWHAVEN DISPLAY
   
   OLED_Text_128128RGB(10, 56, 40, WHITE, BLACK);   // H
   OLED_Text_128128RGB(17, 56, 69, WHITE, BLACK);   // e
   OLED_Text_128128RGB(24, 56, 76, WHITE, BLACK);   // l
   OLED_Text_128128RGB(31, 56, 76, WHITE, BLACK);   // l
   OLED_Text_128128RGB(38, 56, 79, WHITE, BLACK);   // o
   OLED_Text_128128RGB(45, 56, 0, WHITE, BLACK);    //
      
   OLED_Text_128128RGB(52, 56, 55, WHITE, BLACK);   // W
   OLED_Text_128128RGB(59, 56, 79, WHITE, BLACK);   // o
   OLED_Text_128128RGB(66, 56, 82, WHITE, BLACK);   // r
   OLED_Text_128128RGB(73, 56, 76, WHITE, BLACK);   // l
   OLED_Text_128128RGB(80, 56, 68, WHITE, BLACK);   // d
   OLED_Text_128128RGB(87, 56, 1, WHITE, BLACK);    // !
   
   OLED_Icon_128128RGB(102, 50);                    // show icon
   
   OLED_Spectrum_128128RGB();                       // show color spectrum
   
   while(1);                                        // wait here forever
}
