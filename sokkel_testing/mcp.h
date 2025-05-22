#ifndef MCP_h
#define MCP_h

#include "Arduino.h"  
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

class MCP{
    private:
    public:
      void setup(TwoWire& i2c);
      void loopLED();
};
#endif