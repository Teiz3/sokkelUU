#include "esp32-hal-gpio.h"
#include "game.h"


void Game::setup(Panel* panel, Screen screen){
    Game::panel = panel;
    Game::screen = screen;
    Serial.println("Setup game!");
}

void Game::gameLoop(){
    // Update components
    screen.tick();
    panel->updateAvoMeter();
    
    // Gameloop
    switch (currentState){
        case INITIAL:
        default:
            screen.setColor(128, 128, 128); // This one is half brightness, because white looks quite bright.
            screen.print("put in safe mode");
            panel->setWarnLed(HIGH);
            if(panel->keyTurned()){
                currentState = SAFEMODE;
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
            currentState = PRELAUNCH;
          }
            break;
        case PRELAUNCH:
            if (!panel->sunConnected()){
                screen.setColor(255, 255, 0);
                screen.print("place new sun");
            }else{
              screen.setColor(255, 0, 0);
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
                currentState = LAUNCH;
            }
            break;
        case LAUNCH:
        {
            screen.setColor(0, 255, 0);
            String launch_msgs[3] = {"launch sun", "code 6043", "pull lever"};
            screen.setBuffer(launch_msgs, 3);
            if(panel->giantHandleActive()){
                currentState = POSTLAUNCH;
                timer = millis();
            }
            break;
        }
        case POSTLAUNCH:
            screen.setColor(255, 255, 0);
            screen.print("sun launched!");
            launchSun();
            if(millis() - timer > (10 * 1000) && !panel->giantHandleActive() && !panel->keyTurned()){
                digitalWrite(SUN_OUT, LOW);
                launced=false;
                currentState = INITIAL;
            }
            break; 
    }
    return;
}

void Game::skip(){
  Serial.println("Skipping current state. Skipped state is: ");
  Serial.println(currentState);
  switch (currentState){
    case INITIAL: currentState = SAFEMODE; break;
    case SAFEMODE: currentState = PRELAUNCH; break;
    case PRELAUNCH: currentState = LAUNCH; break;
    case LAUNCH: 
        currentState = POSTLAUNCH; 
        timer = millis();
        break;
    case POSTLAUNCH:
        digitalWrite(SUN_OUT, LOW);
        launced=false;
        currentState = INITIAL;
  }
}

void Game::launchSun(){
    // SPAM protection
    if(launced){
        return;
    }
    for (int i = 0; i <= 255; i++){
        analogWrite(SUN_OUT, i);
        delay(100);
    }
    launced=true;
}