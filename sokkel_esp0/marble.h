#ifndef marble_h
#define marble_h  

#include <ESP32Servo.h>
#include "Arduino.h"  
#include "pins.h"

class Marble{
    private:
    public:
      // Open up the marble track till parameter section. section 0 = all closed, section 3 = all open
      void setMarble(uint8_t section);
      void setup();
};

class MyServo{
  private:
    bool isOpen = true;
    Servo servo;
  public:
    void setup(uint8_t pin);
    void open();
    void close();
};
#endif