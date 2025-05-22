#ifndef panel_h
#define panel_h

#include "Arduino.h"  
#include "pins.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

class Panel{
    private:
      void setPinModes();
    public:
      void setup(TwoWire& i2c);
};
#endif