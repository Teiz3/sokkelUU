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
        void setLed(uint8_t val, uint8_t address);
        void setup(TwoWire& i2c);
        void setStatus(uint8_t status);
        void freeze(unsigned long duration);
        void tick();
        void test();
};



#endif