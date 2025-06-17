#include "status_leds.h"
#include "contacts.h"
#include "marble.h"
#include "pins.h"
#include "game.h"
#include <Wire.h>

StatusLeds* status_leds; // Status leds object to control the 16 status leds
Marble* marble; // Status leds object to control the 16 status leds
Contacts* contacts; // Status leds object to control the 16 status leds

Game game;

TwoWire I2Cobj = TwoWire(0);

void setup() {
  Serial.begin(115200);
  while(!Serial){
    delay(5);
  }
  Serial.println("Serial online!");

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  
  status_leds = new StatusLeds();
  // marble = new Marble();
  // contacts = new Contacts();
  
  status_leds->setup(I2Cobj);
  // marble->setup();
  // contacts->setup(I2Cobj);
  // digitalWrite(RGB_BUILTIN, LOW);

  // game.setup(contacts, status_leds, marble);
  // status_leds->setLed(1, HIGH);
  status_leds->test();
}

void loop() {
  // put your main code here, to run repeatedly:
  // testContacts();
  // testServo();
  // game.gameLoop();
  // testLeds();
  // status_leds->setStatus(2);
  // status_leds->setLed(1, LOW);
  // status_leds->setLed(2, HIGH);
  // status_leds->setLed(3, LOW);
  // status_leds->setLed(4, LOW);
  // testContacts();
}

void testLeds(){
  for(int i = 0; i <= 4; i++){
    status_leds->setStatus(i);
    delay(1000);
    Serial.println(i);
  }
}

void testServo(){
  marble->setMarble(0);
  delay(500);
  // marble->setMarble(1);
  // delay(500);
}

void testContacts(){
  Serial.print("Plate A - ");
  Serial.print(contacts->debugReadABC(cA1));
  Serial.print(contacts->debugReadABC(cA2));
  Serial.print(contacts->debugReadABC(cA3));
  Serial.print(contacts->debugReadABC(cA4));
  Serial.println(contacts->debugReadABC(cA5));
  Serial.print("Plate B - ");
  Serial.print(contacts->debugReadABC(cB1));
  Serial.print(contacts->debugReadABC(cB2));
  Serial.print(contacts->debugReadABC(cB3));
  Serial.print(contacts->debugReadABC(cB4));
  Serial.println(contacts->debugReadABC(cB5));
  Serial.print("Plate C - ");
  Serial.print(contacts->debugReadABC(cC1));
  Serial.print(contacts->debugReadABC(cC2));
  Serial.print(contacts->debugReadABC(cC3));
  Serial.print(contacts->debugReadABC(cC4));
  Serial.println(contacts->debugReadABC(cC5));
  Serial.print("Plate D - ");
  Serial.print(contacts->debugReadABC(cD1));
  Serial.print(contacts->debugReadABC(cD2));
  Serial.print(contacts->debugReadABC(cD3));
  Serial.print(contacts->debugReadABC(cD4));
  Serial.println(contacts->debugReadABC(cD5));
  // Serial.print(" DebugA1:");
  // Serial.print(contacts->debugReadABC(cB1));
  
  // Serial.print(" DebugA2:");
  // Serial.print(contacts->debugReadABC(cA2));




  Serial.println("");
  delay(100);
;}

