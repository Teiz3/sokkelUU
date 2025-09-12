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
int ServoMode;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial online!");
  pinMode(LOCK_OUT, OUTPUT);
  // pinMode(LOCK_LED, OUTPUT);

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  
  status_leds = new StatusLeds();
  marble = new Marble();
  contacts = new Contacts();
  
  status_leds->setup(I2Cobj);
  marble->setup();
  contacts->setup(I2Cobj);
  digitalWrite(RGB_BUILTIN, LOW);

  game.setup(contacts, status_leds, marble);
  ServoMode = 0;
}

void loop() {
  // game.gameLoop();
  // checkSerial();
  // testContacts();
  // testLeds();
  // marble->debugServo();
  testServo();
}

void checkSerial(){
  String msg = "";
  if (Serial.available()){
    msg = Serial.readString();
  }
  if (msg != ""){
    Serial.println("RECIEVED MESSAGE");
    Serial.println(msg);
  }
  if (msg == "debug"){
    game.debugOut = !game.debugOut;
  }
  if (msg == "skip"){
    game.nextLevel();
  }
}


void testLeds(){
  for(int i = 0; i <= 4; i++){
    status_leds->setStatus(i);
    delay(1000);
    Serial.println(i);
  }
}

void testServo(){
  String msg = "";
  if (Serial.available()){
    msg = Serial.readString();
  }
  if (msg != ""){
    ServoMode += 1;
    if (ServoMode > 3){
      ServoMode = 0;
    }
  }
  marble->setMarble(ServoMode);
  Serial.println(ServoMode);
  delay(100);
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

  Serial.println("");
  delay(1000);
;}

