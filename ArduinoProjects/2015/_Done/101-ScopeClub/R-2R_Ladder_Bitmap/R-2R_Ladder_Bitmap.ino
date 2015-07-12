// Scope Screen by Hari Wiguna, 2015
// Playing with R-2R Ladder to convert Digital to Analog

#define swap(a, b) { int16_t t = a; a = b; b = t; }

// Bitmap is 256x128 pixels
byte bitmap[128][8];

void setup() {
  // put your setup code here, to run once:
  drawLine(0,0, 255,127, 1);
}

void loop() {
  // put your main code here, to run repeatedly:  
}

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if (color==0)
    bitClear(bitmap[y][x/8], x % 8);
  else
    bitSet(bitmap[y][x/8], x % 8);
}

// Bresenham's line drawing from wikipedia via AdaFruit
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } 
  else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } 
    else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

