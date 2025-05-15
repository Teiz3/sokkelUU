#ifndef status_leds_h
#define status_leds_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include "pins.h"


class StatusLeds{
    private:
        void setupPinMode();
        void setLed(uint8_t val, uint8_t address);
    public:
        void setup(TwoWire& i2c);
        void setStatus(uint8_t status);
};



#endif