#include "panel.h"
#include "pins.h"
#include "tester.h"
#include "screen.h"
#include "game.h"
#include <Wire.h>

Panel* panel;
TwoWire I2Cobj = TwoWire(0);
Screen screen;

// Tester is used to print debug output to serial
Tester tester;
Game game;
bool debugOut = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial port started.");
  I2Cobj.begin(SDA_PIN, SCL_PIN);

  panel = new Panel();
  panel->setup(I2Cobj);
  screen.setup();
  game.setup(panel, screen);
  tester.setup(panel);
}

void loop() {
  checkSerial();
  if(debugOut){
    tester.test();
  }
  game.gameLoop();
  delay(100);
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
    debugOut = !debugOut;
  }
  if (msg == "skip"){
    game.skip();
  }
}
