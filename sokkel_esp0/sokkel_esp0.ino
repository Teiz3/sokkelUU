#include "status_leds.h"
#include "contacts.h"
#include "marble.h"
#include "incubator.h"
#include "pins.h"
#include "game.h"
#include <Wire.h>

StatusLeds* status_leds; // Status leds object to control the 16 status leds
Marble* marble; // Status leds object to control the 16 status leds
Contacts* contacts; // Status leds object to control the 16 status leds
Incubator* incubator; // Status leds object to control the 16 status leds

Game game;

TwoWire I2Cobj = TwoWire(0);

void setup() {
  Serial.begin(115200);
  while(!Serial){
    delay(5);
  }

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  
  status_leds = new StatusLeds();
  marble = new Marble();
  contacts = new Contacts();
  // incubator = new Incubator();
  
  status_leds->setup(I2Cobj);
  marble->setup();
  contacts->setup(I2Cobj);
  // incubator->setup();
  digitalWrite(RGB_BUILTIN, LOW);

  game.setup(contacts, status_leds, marble);
}

void loop() {
  // put your main code here, to run repeatedly:
  // testContacts();
  // testServo();
  game.gameLoop();
}

void testServo(){
  marble->setMarble(0);
  delay(1500);
  marble->setMarble(1);
  delay(1500);
}

void testContacts(){
  Serial.print("B4-D2:");
  Serial.print(contacts->connected(cB4, cD2));
  
  Serial.print(" A1-A2:");
  Serial.print(contacts->connected(cA4, cA2));

  // Serial.print(" DebugA1:");
  // Serial.print(contacts->debugReadABC(cB1));
  
  // Serial.print(" DebugA2:");
  // Serial.print(contacts->debugReadABC(cA2));




  Serial.println("");
  delay(100);
;}

