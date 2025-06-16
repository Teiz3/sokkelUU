#ifndef game_h
#define game_h

#include "Arduino.h"  
#include "contacts.h"
#include "marble.h"
#include "status_leds.h"

class Game{
    private:
        uint8_t level = 1;
        Contacts* contacts;
        StatusLeds* statusleds;
        Marble* marble;
        void nextLevel();
    public:
      void setup(Contacts* contacts, StatusLeds* leds, Marble* marble);
      void gameLoop();
};
#endif