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
  Serial.println("Serial online!");
  pinMode(LOCK_OUT, OUTPUT);
  pinMode(LOCK_LED, OUTPUT);

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  
  status_leds = new StatusLeds();
  marble = new Marble();
  contacts = new Contacts();
  
  status_leds->setup(I2Cobj);
  marble->setup();
  contacts->setup(I2Cobj);
  digitalWrite(RGB_BUILTIN, LOW);

  game.setup(contacts, status_leds, marble);
  // status_leds->test();
  // marble->setLed(1, HIGH);
  // marble->setLed(2, HIGH);
  // marble->setLed(3, HIGH);
  // marble->setMarble(3);
}

void loop() {
  game.gameLoop();
    // digitalWrite(LOCK_LED, LOW);
    // delay(2000);
    // digitalWrite(LOCK_LED, HIGH);
    // delay(2000);
    // digitalWrite(LOCK_OUT, HIGH); // Lock the lock
    // delay(2000);
    // digitalWrite(LOCK_OUT, LOW); // Lock the lock
    // delay(2000);
    
    // digitalWrite(LOCK_LED, HIGH); // Lock the lock
    // delay(2000);
    // digitalWrite(LOCK_LED, LOW); // Lock the lock
    // delay(2000);


  // testContacts();
  // for(int i = 1; i <= 4; i++){
  //   for (int j = 1; j <= 4; j++){
  //     status_leds->setLed(j, (i == j) ? HIGH : LOW);

  //   }
  //   delay(1000);
  // }
  // for (int i = 0; i < 4; i++){
  //   marble->setMarble(i);
  //   Serial.println(i);
  //   delay(2000);
  // }

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
  delay(1000);
;}

