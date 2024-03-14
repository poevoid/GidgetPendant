#pragma once
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = SECRET_SSID;        // your network SSID (name)
const char password[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


static const unsigned char PROGMEM twinkle7 []  = {
	B00000000, 
  B00000000, 
  B00100000, 
  B00000000, 
  B00000000
}; 
static const unsigned char PROGMEM twinkle6 []  = {
	B00000000, 
  B00100000, 
  B01110000, 
  B00100000, 
  B00000000
}; 
static const unsigned char PROGMEM twinkle5 []  = {
	B00000000, 
  B01010000, 
  B00100000, 
  B01010000, 
  B00000000
}; 
static const unsigned char PROGMEM twinkle4 []  = {
	B00001000, 
  B01010000, 
  B00100000, 
  B01010000, 
  B10000000
}; 
// 'twinkle1', 5x5px
static const unsigned char PROGMEM twinkle3 []  = {
	B00100000, 
  B01010000, 
  B00100000, 
  B01010000, 
  B00100000
}; 
static const unsigned char PROGMEM twinkle2 []  = {
	B10000000, 
  B01010000, 
  B00100000, 
  B01010000, 
  B00001000
}; 
static const unsigned char PROGMEM twinkle1 []  = {
	B00000000, 
  B01010000, 
  B00100000, 
  B01010000, 
  B00000000
}; 

static unsigned char PROGMEM twinkle0 []  = { 
  B01101100, 
  B10010010, 
  B10000010, 
  B01000100, 
  B00101000,
  B00010000,
  B00000000
};


static const unsigned char* PROGMEM twinkleArray[8] = {
  twinkle0,
  twinkle1,
  twinkle2,
  twinkle3,
  twinkle4,
  twinkle5,
  twinkle6,
  twinkle7
};
