#include "FastLED.h"
#include <PS2Keyboard.h>

#define NUM_LEDS 50
#define DATA_PIN 7

const int DataPin = 8;
const int IRQpin =  3;

PS2Keyboard keyboard;
CRGB leds[NUM_LEDS];

void setup() { 
    delay(1000);
    keyboard.begin(DataPin, IRQpin);
    Serial.begin(9600);
    
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); 
}

void clear(){
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
void loop() { 

  char c;
  
  if (keyboard.available()) {  
    // read the next key
    c = keyboard.read();
  }
  
  clear();
  
  switch (c) {
    case 'a':
      leds[0] = CRGB::White;
      break;
    case 'b':
      leds[1] = CRGB::Blue;
      break;
    case 'c':
      leds[2] = CRGB::Red;
      break;
    case 'd':
      leds[3] = CRGB::White;
      break;
    case 'e':
      leds[4] = CRGB::Blue;
      break;
    case 'f':
      leds[5] = CRGB::Yellow;
      break;
    case 'g':
      leds[6] = CRGB::Red;
      break;
    case 'h':
      leds[7] = CRGB::Blue;
      break;
    case 'i':
      leds[17] = CRGB::Blue;
      break;
    case 'j':
      leds[16] = CRGB::Red;
      break;
    case 'k':
      leds[15] = CRGB::Blue;
      break;
    case 'l':
      leds[14] = CRGB::White;
      break;
    case 'm':
      leds[13] = CRGB::Yellow;
      break;
    case 'n':
      leds[12] = CRGB::Red;
      break;
    case 'o':
      leds[11] = CRGB::Red;
      break;
    case 'p':
      leds[10] = CRGB::White;
      break;
    case 'q':
      leds[9] = CRGB::Red;
      break;
    case 'r':
      leds[23] = CRGB::White;
      break;
    case 's':
      leds[24] = CRGB::White;
      break;
    case 't':
      leds[25] = CRGB::Yellow;
      break;
    case 'u':
      leds[26] = CRGB::Blue;
      break;
    case 'v':
      leds[27] = CRGB::Red;
      break;
    case 'w':
      leds[28] = CRGB::Blue;
      break;
    case 'x':
      leds[29] = CRGB::Yellow;
      break;
    case 'y':
      leds[30] = CRGB::Red;s
      break;
    case 'z':
      leds[31] = CRGB::Red;
      break;
  }
  FastLED.show();
  delay(1000);
  clear();
  delay(500);
}
