#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>

namespace led{
  extern const int pixels;  // number of Neopixels
  extern Adafruit_NeoPixel strip;
  
  // Main LEDs color state (0-255):
  extern int r[10];
  extern int g[10];
  extern int b[10];

  void initLed();
  void testOn();
  void loopLed();
  void off();
  void green();
  void red();
  }

#endif
