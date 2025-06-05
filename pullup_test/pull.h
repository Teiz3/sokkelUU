#ifndef pull_h
#define pull_h

#include "Arduino.h"  
#include <Adafruit_MCP23X17.h>


class Pull{
    private:
    public:
      void setup(TwoWire& i2c);
      int read();
};
#endif