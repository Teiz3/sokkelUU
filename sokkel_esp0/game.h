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
        void checkReset(); // Checks for the reset combination that resets the game, no matter which level the game is in.
        uint8_t resetStep; // Holds the current reset step. Reset is a multi step process to reduce the chance of players accidentaly resetting the game.
        unsigned long resetTimer;
    public:
      void setup(Contacts* contacts, StatusLeds* leds, Marble* marble);
      void gameLoop();
      bool debugOut = true;
      void nextLevel();
};
#endif