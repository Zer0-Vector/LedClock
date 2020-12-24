#include <LedControl.h>

LedControl lc = LedControl(12,11,10,1);

void setup() {
    lc.shutdown(0, true);
    delay(1000);
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
}


// delay time between faces
unsigned long delaytime=1000;

byte zero[8] = {
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte one[8] = {
    B00011000,
    B00111000,
    B01011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
};

byte two[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111110
};

byte three[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

byte four[8] = {
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111110,
    B00000100,
    B00000100,
    B00000100
};

byte five[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

byte six[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte seven[8] = {
    B01111110,
    B01000010,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B01000000
};

byte eight[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte nine[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

byte ten[8] = {
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010
};

byte eleven[8] = {
    B01111100,
    B01000010,
    B01000010,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B01111100
};

byte twelve[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000010,
    B00111100
};

byte thirteen[8] = {
    B01111000,
    B01000100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000100,
    B01111000
};

byte fourteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01111110
};

byte fifteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01000000
};

void draw(byte pixels[8]) {
    lc.setRow(0,0,pixels[0]);
    lc.setRow(0,1,pixels[1]);
    lc.setRow(0,2,pixels[2]);
    lc.setRow(0,3,pixels[3]);
    lc.setRow(0,4,pixels[4]);
    lc.setRow(0,5,pixels[5]);
    lc.setRow(0,6,pixels[6]);
    lc.setRow(0,7,pixels[7]);
}

#define DELAY 250

void loop(){
  draw(zero);
  delay(DELAY);
  draw(one);
  delay(DELAY);
  draw(two);
  delay(DELAY);
  draw(three);
  delay(DELAY);
  draw(four);
  delay(DELAY);
  draw(five);
  delay(DELAY);
  draw(six);
  delay(DELAY);
  draw(seven);
  delay(DELAY);
  draw(eight);
  delay(DELAY);
  draw(nine);
  delay(DELAY);
  draw(ten);
  delay(DELAY);
  draw(eleven);
  delay(DELAY);
  draw(twelve);
  delay(DELAY);
  draw(thirteen);
  delay(DELAY);
  draw(fourteen);
  delay(DELAY);
  draw(fifteen);
  delay(DELAY);
}