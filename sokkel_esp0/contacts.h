#ifndef contacts_h
#define contacts_h

#include "Wire.h"
#include "Arduino.h"  
#include "pins.h"
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

class Contacts{
    private:
      void setupPinMode();
      // Converts a connector name like "A2" or "D5" to a pinnumber
      uint8_t getPin(string connectorName);
    public:
      void setup(TwoWire& i2c);
      bool connected()
};
#endif