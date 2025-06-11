#ifndef tester_h
#define tester_h

#include "Arduino.h"
#include "panel.h"
#include "pins.h"

class Tester{
    private:
        Panel* panel;
    public:
      void setup(Panel* panel);
      void test();
      void test2();
};
#endif