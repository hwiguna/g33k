// by Eduardo Zola - Zola Lab (Copyright) - www.zolalab.com.br

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"


#define echo_Pin  4
#define trig_Pin  3
#define snd_pin   7
#define led_pin  10
#define MAX_DIST 3254


Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();





static const uint8_t numbertable[] = { 
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
	B01010000, /* r */
	B01011100, /* o */
};



int dlyTEMPO; 
int i;
float duration,distancia;

void setup()
{
   Serial.begin(9600); //inicia a porta serial
   pinMode(echo_Pin, INPUT); // define o pino 13 como entrada (recebe)
   pinMode(trig_Pin, OUTPUT); // define o pino 12 como saida (envia)
   pinMode(snd_pin, OUTPUT);
   pinMode(led_pin, OUTPUT);

   matrix.begin(0x70);  // pass in the address
   matrix.setBrightness(15); 
   clearAll();
}

void loop()
{
  //seta o pino Trigger com um pulso baixo
    digitalWrite(trig_Pin, LOW);
  // delay de 2 microssegundos
    delayMicroseconds(2);
  //seta o pino Trigger com pulso alto
    digitalWrite(trig_Pin, HIGH);
  //delay de 10 microssegundos
    delayMicroseconds(10);
  //seta o pino Trigger com pulso baixo
    digitalWrite(trig_Pin, LOW);
  //pulsa o pino Echo e  lÃª o tempo entre a chamada e a volta quando o pino entra em HIGH
    duration = pulseIn(echo_Pin,HIGH);
  //Esse calculo Ã© baseado em s = v . t, lembrando que o tempo vem dobrado
  //porque Ã© o tempo de ida e volta do ultrassom
    distancia = duration /29 / 2 ;

    if(distancia > MAX_DIST) distancia = 0;

    dlyTEMPO = map((int)distancia,0,1000,10,700);
    
    if(distancia > 0 && distancia < 500.00) 
    {
        digitalWrite(led_pin,HIGH);
        if(dlyTEMPO > 700) dlyTEMPO = 700;
        for(i=0;i<20;i++) {digitalWrite(snd_pin,HIGH);delayMicroseconds(300);digitalWrite(snd_pin,LOW);delayMicroseconds( 700 + (int) distancia  );};
        digitalWrite(led_pin,LOW);
      
        showNumber(distancia);
    } else clearAll();
    
//tone(7,250);
//delay(30);
//noTone(7);


  Serial.print("Distancia em CM: ");
  Serial.println(distancia);

//  delay(200);
delay(dlyTEMPO);
delay(500);

}




void clear(int bus)
{
    int P;
    for(P=0;P < 5;P++) matrix.displaybuffer[P]=0;
    matrix.writeDisplay();    
}

void clearAll()
{
    clear(0);
}

void xprint(int bus,int p,int digit)
{
    matrix.displaybuffer[p]=numbertable[digit];
    matrix.writeDisplay();
}


void showNumber(float num)
{
  int n1 = (int) num;             // parte inteira
  int n2 = (int) (num * 100);     // parte decimal
  
  int d1 = (n1 / 100) % 10;
  int d2 = (n1 /  10) % 10;
  int d3 = (n1 % 10);
  int d4 = (n2 / 10) % 10; 
  
  if(d1 == 0) matrix.displaybuffer[0]=0x00; else xprint(0, 0, d1);
  if(d2 == 0 && d1 == 0) matrix.displaybuffer[1]=0x00; else xprint(0, 1, d2);
  matrix.displaybuffer[3]=numbertable[d3] | (1 << 7);  
  xprint(0, 4, d4);

  matrix.writeDisplay();  
}


