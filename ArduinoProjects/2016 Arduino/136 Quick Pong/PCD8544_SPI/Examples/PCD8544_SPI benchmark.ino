#include <SPI.h>
#include "PCD8544_SPI.h"

#define USE_FRAME_BUFFER

#ifdef USE_FRAME_BUFFER
PCD8544_SPI_FB lcd;
#else
PCD8544_SPI lcd;
#endif

void setup(void)
{
	Serial.begin(9600);
	lcd.begin();
	lcd.print(F("Preparing benchmark"));
#ifdef USE_FRAME_BUFFER
	lcd.renderAll();
#endif
	delay(1000);
}

uint8_t bmp[] = {
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
};

void loop(void) 
{
	size_t len;

	lcd.clear();
	unsigned long time = micros();
	len = lcd.print(F("012345678901234567890123456789012345678901234567890123456789012345678901234567890123"));
#ifdef USE_FRAME_BUFFER
	lcd.renderString(0, 0, len);
#endif
	time = micros() - time;
	delay(3000);

	lcd.clear();
	lcd.print(F("The time it took to print 84 chars is:    "));
	lcd.print(time);
#ifdef USE_FRAME_BUFFER
	lcd.renderAll();
#endif
	delay(3000);

	lcd.clear();
	lcd.gotoXY(5,3);
	lcd.print(F("Test gotoXY"));
#ifdef USE_FRAME_BUFFER
	lcd.renderAll();
#endif
	delay(3000);

	lcd.clear();
	time = micros();
	lcd.writeBitmap(bmp, 10, 2, 25, 3);
#ifdef USE_FRAME_BUFFER
	lcd.renderAll();
#endif
	time = micros() - time;
	delay(3000);

	lcd.clear();
	lcd.print(F("The time it took to draw a 25x3 (25x18) bitmap is: "));
	lcd.print(time);
#ifdef USE_FRAME_BUFFER
	lcd.renderAll();
#endif
	delay(3000);
	
#ifdef USE_FRAME_BUFFER
	lcd.clear();
	time = micros();
	lcd.writeRect(5, 5, 50, 40);
	lcd.writeLine(75, 3, 75, 35);
	lcd.writeLine(60, 10, 60, 40);
	lcd.writeLine(10, 47, 60, 47);
	lcd.renderAll();
	time = micros() - time;
	delay(3000);

	lcd.clear();
	len = lcd.print(F("The time it took draw a rect and 3 lines: "));
	len += lcd.print(time);
	lcd.renderString(0, 0, len);
	delay(3000);

	lcd.clear();
	time = micros();
	for (uint8_t row = 0; row < PCD8544_Y_PIXELS; row++)
	{
		for (uint8_t col = 0; col < PCD8544_X_PIXELS; col++)
		{
			uint8_t pixel = (col + row) % 2;
			lcd.setPixel(col, row, pixel);
		}
	}
	lcd.renderAll();
	time = micros() - time;
	delay(5000);

	lcd.clear();
	lcd.print(F("The time it took to run setPixel on all 4032 pixels and render it:    "));
	lcd.print(time);
	lcd.renderAll();
	delay(5000);
#endif
}