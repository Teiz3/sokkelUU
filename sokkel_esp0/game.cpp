#include "esp32-hal-gpio.h"
#include "game.h"

void Game::setup(Contacts* contacts, StatusLeds* leds, Marble* marble){
    Game::contacts = contacts;
    Game::statusleds = leds;
    Game::marble = marble;
    digitalWrite(LOCK_OUT, HIGH); // Lock the lock

}

void Game::gameLoop(){
    statusleds->tick();
    uint8_t connections = 0;
    switch (level){
    // Level 1 (4 contacts)
        case 1:
            connections += contacts->connected(cA1, cA2);
            connections += contacts->connected(cB1, cB2);
            connections += contacts->connected(cC1, cC2);
            connections += contacts->connected(cD1, cD2);
            break;
    // Level 2 (4 contacts)
        case 2:
            connections += contacts->connected(cA3, cD4); // stars to twins
            connections += contacts->connected(cD3, cC4); // stars to capricorn
            connections += contacts->connected(cC3, cB4); // stars to crab
            connections += contacts->connected(cB3, cA4); // stars to scales
            break;
    // Level 3 (2 contacts)
        case 3:
            connections += contacts->connected(cA5, cC5);
            connections += contacts->connected(cB5, cD5);
            connections *= 2;
            break;
    // Wait for reset
        case 4:
            digitalWrite(LOCK_LED, HIGH);
            digitalWrite(LOCK_OUT, LOW);
            break;
    }
    statusleds->setStatus(connections);
    Serial.print("Level:");
    Serial.print(level);
    Serial.print("Connections: ");
    Serial.println(connections);
    if (connections >= 4){
      statusleds->freeze(1500);
      nextLevel();
    }

}

void Game::nextLevel(){
  // Open the marbletrack-part of the level just completed
  // marble->setMarble(level);
  level += 1;
  

}