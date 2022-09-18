#ifndef LED_CPP
#define LED_CPP

#include "led.h"
#include "config.h"


const int led::pixels = 10 ;  // number of Neopixels

int led::r[10] = {0};
int led::g[10] = {0};
int led::b[10] = {0};


Adafruit_NeoPixel led::strip = Adafruit_NeoPixel(pixels, configu::LEDPWM1, NEO_GRB + NEO_KHZ800);

void led::initLed(){
  led::strip.begin();
  led::strip.show();
  }

void led::testOn(){
    for(int i=0; i<led::strip.numPixels(); i++) {
      b[i]=50;
    }
    led::loopLed();
  }

void led::loopLed(){
    for(int i=0; i<led::strip.numPixels(); i++) {
      led::strip.setPixelColor(i, r[i],g[i],b[i]);
    }
    led::strip.show();
  }

void led::off(){
    for(int i=0; i<led::strip.numPixels(); i++) {
        r[i]=0;
        g[i]=0;
        b[i]=0;
    }
  }

void led::green(){
    for(int i=0; i<led::strip.numPixels(); i++) {
        r[i]=0;
        g[i]=255;
        b[i]=0;
    }
  }

void led::red(){
    for(int i=0; i<led::strip.numPixels(); i++) {
        r[i]=255;
        g[i]=0;
        b[i]=0;
    }
  }

#endif
