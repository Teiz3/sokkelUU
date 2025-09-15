#ifndef screen_h
#define screen_h

#include "Arduino.h"
#include "pins.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#if SOKKEL == 0
  #include <Adafruit_DotStarMatrix.h>
  #include <Adafruit_DotStar.h>
#elif SOKKEL == 1
  #include <Adafruit_NeoMatrix.h>
  #include <Adafruit_NeoPixel.h>
#endif

class Screen{
    private:
      String msg_buffer; // Buffer for the current message
      String multi_msg_buffer[5]; // Buffer 2 store 5 messages that can be displayed after each other
      uint8_t msg_count = 1; // Number of messages in the multi_msg_buffer
      uint8_t msg_index = 0; // 0 based index

      int x; // Start position of the text (0=left, 32=right)
      int msg_pixel_size;
      unsigned long readTime = 2000;
      unsigned long lastUpdate;
      // Freeze text once done scrolling
      bool freeze = false;
      unsigned long freezeTime;
      void nextMsg();
    public:
      void setup();
      void setColor(uint8_t r, uint8_t g, uint8_t b);
      // Writes a new single message to the message buffer and resets all the screen timers
      // so it starts anew with the new message in the buffer.
      // If the message is already in the buffer it does nothing
      void print(String msg);
      void setBuffer(String msg_arr[], uint8_t size);
      void tick();
      // Animated wipe of the screen.
      // BLOCKING FUNCTION
      void screenWipe();

      // DEBUG BROKEN MESS OF SOKKEL 1
      void newtick();
      void newprint(String msg);
};
#endif