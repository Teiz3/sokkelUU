#ifndef status_leds_h
#define status_leds_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include "pins.h"


class StatusLeds{
    private:
        void setupPinMode();
        bool frozen = false;
        unsigned long unfreezetime;
    public:
        // Sets 4 leds to val, 1 on each side. Address range: 1-4
        void setLed(uint8_t address, uint8_t val);
        void setup(TwoWire& i2c);
        void setStatus(uint8_t status);
        void freeze(unsigned long duration);
        void tick();
};



#endif