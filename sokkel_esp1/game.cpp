#include "esp32-hal-gpio.h"
#include "game.h"


void Game::setup(Panel* panel, Screen screen){
    Game::panel = panel;
    Game::screen = screen;
    Serial.println("Setup game!");
}

void Game::gameLoop(){  
    // Gameloop
    switch (currentState){
        case INITIAL:
        default:
            screen.setColor(128, 128, 128); // This one is half brightness, because white looks quite bright.
            screen.print("put in safe mode");
            panel->setWarnLed(HIGH);
            if(panel->keyTurned()){
                nextLevel();
                return;
            }
            break;
        case SAFEMODE:
          panel->setWarnLed(LOW);
          screen.setColor(255, 0, 0);
          screen.print("ERROR 404");
          if (
            panel->getStardust() == 3 &&
            panel->getRadiation() == 2 &&
            panel->getAVOAC() == VOLT &&
            panel->getAVODC() == VOLT &&
            panel->getComet('h') == UP &&
            panel->getComet('j') == DOWN &&
            panel->getComet('v') == DOWN &&
            panel->getComet('p') == DOWN
        ){
            nextLevel();
            return;
          }
            break;
        case PRELAUNCH:
            if (!panel->sunConnected()){
                screen.setColor(255, 255, 0);
                screen.print("place new sun");
            }else{
              screen.setColor(255, 120, 0); // Oranje achtig
              String pre_msgs[2] = {"Error 501", "new sun detected"};
              screen.setBuffer(pre_msgs, 2);
            }
            if(
                panel->getStardust() == 8 &&
                panel->getRadiation() == 1 &&
                panel->getAVODC() == A_OHM &&
                panel->getAVOAC() == A_OHM &&
                panel->getComet('h') == DOWN &&
                panel->getComet('j') == UP &&
                panel->getComet('v') == UP &&
                panel->getComet('p') == DOWN &&
                panel->sunConnected()
            ){
                nextLevel();
                return;
            }
            break;
        case LAUNCH:
        {
            screen.setColor(0, 255, 0);
            String launch_msgs[3] = {"launch sun", "code 6043", "pull lever"};
            screen.setBuffer(launch_msgs, 3);
            if(panel->giantHandleActive()){
                nextLevel();
                return;
            }
            break;
        }
        case POSTLAUNCH:
            screen.setColor(255, 255, 0);
            screen.print(" sun  launced!");
            screen.tick();
            delay(100);
            launchSun();
            if(millis() - timer > (10 * 1000) && !panel->giantHandleActive() && !panel->keyTurned()){
                nextLevel();
                return;
            }
            break; 
    }
    // Update components
    screen.tick();
    panel->updateAvoMeter();
    return;
}

void Game::nextLevel(){
    switch(currentState){
        case INITIAL: currentState = SAFEMODE; break;
        case SAFEMODE: currentState = PRELAUNCH; break;
        case PRELAUNCH: currentState = LAUNCH; break;
        case LAUNCH: 
            currentState = POSTLAUNCH; 
            timer = millis();
            break;
        case POSTLAUNCH:
            analogWrite(SUN_OUT, 0);
            launced=false;
            currentState = INITIAL;
    }
    screen.screenWipe();
}

void Game::skip(){
  Serial.println("Skipping current state. Skipped state is: ");
  Serial.println(currentState);
  nextLevel();
}

void Game::launchSun(){
    // SPAM protection
    if(launced){
        return;
    }
    for (int i = 0; i <= 255; i++){
        analogWrite(SUN_OUT, i);
        delay(25);
    }
    launced=true;
}