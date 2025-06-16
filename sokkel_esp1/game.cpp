#include "esp32-hal-gpio.h"
#include "game.h"


void Game::setup(Panel* panel, Screen screen){
    Game::panel = panel;
    Game::screen = screen;
    Serial.println("Setup game!");
}

void Game::gameLoop(){
    screen.tick();
    Serial.println(currentState);
    panel->updateAvoMeter();
    unsigned long timer;
    switch (currentState){
        case INITIAL:
        default:
            screen.print("put in safe mode");
            panel->setWarnLed(HIGH);
            if(panel->keyTurned()){
                currentState = SAFEMODE;
            }
            break;
        case SAFEMODE:
          panel->setWarnLed(LOW);
          screen.print("ERROR 404");
          if (
            panel->getStardust() == 3 &&
            // panel->getRadiation() == 2 &&
            panel->getAVOAC() == VOLT &&
            panel->getAVODC() == VOLT &&
            panel->getComet('h') == UP &&
            // panel->getComet('j') == DOWN &&
            panel->getComet('v') == DOWN &&
            panel->getComet('p') == DOWN
        ){
            currentState = PRELAUNCH;
          }
            break;
        case PRELAUNCH:
            if (!panel->sunConnected()){
                screen.print("place new sun");
            }else{
              String pre_msgs[2] = {"error 501", "new sun detected"};
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
                panel->getComet('p') == DOWN 
            ){
                currentState = LAUNCH;
            }
            break;
        case LAUNCH:
        {

            String launch_msgs[3] = {"launch sun", "code 6043", "pull lever"};
            screen.setBuffer(launch_msgs, 3);
            if(panel->giantHandleActive()){
                currentState = POSTLAUNCH;
                timer = millis();
            }
            break;
        }
        case POSTLAUNCH:
            screen.print("sun launched!");
            // digitalWrite(SUN_OUT, HIGH);
            launchSun();
            if(millis() - timer > (10 * 1000) && !panel->giantHandleActive() && !panel->keyTurned()){
                digitalWrite(SUN_OUT, LOW);
                currentState = INITIAL;
            }
            break; 
    }
    return;
}

void Game::launchSun(){
    for (int i = 0; i <= 255; i++){
        analogWrite(SUN_OUT, i);
        delay(10);
    }
}