#ifndef contacts_h
#define contacts_h

#include "Wire.h"
#include "Arduino.h"  
#include "pins.h"
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

enum ContactEnum{
  cA1, cA2, cA3, cA4, cA5,
  cB1, cB2, cB3, cB4, cB5,
  cC1, cC2, cC3, cC4, cC5,
  cD1, cD2, cD3, cD4, cD5,
};

class Contacts{
    private:
      void setupPinMode();
      // Converts a connector name like "A2" or "D5" to a pinnumber
      uint8_t getPin(enum ContactEnum connectorName);
      bool isPlateD(enum ContactEnum connectorName);
    public:
      void setup(TwoWire& i2c);
      bool connected(enum ContactEnum c1, enum ContactEnum c2);
};


#endif