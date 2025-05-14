#ifndef contacts_h
#define contacts_h

#include "Wire.h"
#include "Arduino.h"  
#include "pins.h"

class Contacts{
    private:
    public:
      void setup(TwoWire& i2c);
};
#endif