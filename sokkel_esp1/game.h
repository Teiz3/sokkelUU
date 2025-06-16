#ifndef game_h
#define game_h

#include "Arduino.h"  
#include "panel.h"
#include "screen.h"

enum State{
    // 1. Display "put in safe mode". 
    // 2. To proceed: key turned
    INITIAL,
    // 3. Display "ERROR 404"
    // 4. To proceed: star 3, rad gamma, GForce DC100V AC250V, 
    // Hudig up, Juno down, Vesta down, Pluto down
    SAFEMODE,
    // 5. Check for sun. Display "place new sun" or "error 501 new sun detected"
    // 6. To proceed: Star 8, rad beta, GForce DC250uA ACOhmx100,
    // Hudig down, Juno up, Vesta up, Pluto down
    PRELAUNCH,
    // 7. Display "launch sun, code 6043, pull lever"
    // 8. To proceed, pull lever
    LAUNCH,
    // 8. disco mode
    // (9.) To proceed, wait 10 sec and lever back
    POSTLAUNCH

};

class Game{
    private:
        Panel* panel;
        Screen screen;
        enum State currentState = INITIAL;
        void launchSun();
        bool launced = false;
    public:
      void setup(Panel* panel, Screen screen);
      void gameLoop();
};
#endif