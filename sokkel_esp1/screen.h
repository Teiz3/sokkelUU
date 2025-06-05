#ifndef screen_h
#define screen_h

#include "Arduino.h"
#include "pins.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>

class Screen{
    private:
      String msg_buffer;
      int x;
    public:
      void setup();
      void print(String msg);
      void tick();
};
#endif