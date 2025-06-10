#include "game.h"


void Game::setup(Panel* panel, Screen screen){
    Game::panel = panel;
    Game::screen = screen;
    Serial.println("Setup game!");
}

void Game::gameLoop(){
    switch (currentState){
        case INITIAL:
        default:
            screen.print("put in safe mode");
            if(panel->keyTurned()){
                currentState = SAFEMODE;
            }
            break;
        case SAFEMODE:
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
            if ("Sun detection here" == ""){
                screen.print("place new sun");
            }
            screen.print("error 501: new sun detected");
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
                currentState = LAUNCH
            }
            break;
        case LAUNCH:
            if(!panel->giantHandleActice){
                screen.print("launch sun    code 6043    pull lever");
            }
            else{
                // Disco mode
                panel.print("sun launched!");
            }

            break; 
    }
    return;
}