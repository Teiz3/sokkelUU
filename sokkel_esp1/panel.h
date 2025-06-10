#ifndef panel_h
#define panel_h

#include "Arduino.h"  
#include "pins.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

enum CometSwitch{
  UP,
  OFF,
  DOWN
};

enum AVOSwitch{
  VOLT,
  A_OHM,
  AVO_OFF
};

class Panel{
    private:
      void setPinModes();
      enum CometSwitch checkComet(uint8_t pinUp, uint8_t pinDown);
      int getLinPot();
    public:
      void setup(TwoWire& i2c);
      // Gets the stardust level (3 OR 8), returns 0 if both are not connected.
      int getStardust();
      // Sets the big warnlight to val (HIGH|LOW).
      void setWarnLed(uint8_t val);
      // Checks if the key switch is turned.
      bool keyTurned();
      bool giantHandleActive();
      // Get the status of a comet switch, takes the first letter of the comet as char parameter.
      // Options are 'h', 'j', 'v', 'p'
      enum CometSwitch getComet(char cometName);
      enum AVOSwitch getAVOAC();
      enum AVOSwitch getAVODC();
      // Gets the radiation of the linear potentiometer. 
      // 0 = left, 1 = middle, 2 = right
      int getRadiation();

      int debugRead(uint8_t pin);
};
#endif