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
      String multi_msg_buffer[5];
      uint8_t msg_count = 1;
      uint8_t msg_index = 0;
      int x;
      int msg_pixel_size;
      unsigned long readTime = 2500;
      unsigned long lastUpdate;
      // Freeze text once done scrolling
      bool freeze = false;
      unsigned long freezeTime;
      void nextMsg();
    public:
      void setup();
      void print(String msg);
      void setBuffer(String msg_arr[], uint8_t size);
      void tick();
};
#endif