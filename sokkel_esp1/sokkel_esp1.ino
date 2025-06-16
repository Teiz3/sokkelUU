#include "panel.h"
#include "pins.h"
#include "tester.h"
#include "screen.h"
#include "game.h"
#include <Wire.h>

Panel* panel;
TwoWire I2Cobj = TwoWire(0);
Screen screen;

Tester tester;
Game game;

void setup() {
  Serial.begin(115200);
  // while(!Serial){
  //   delay(5);
  // }
  Serial.println("Serial port started.");
  I2Cobj.begin(SDA_PIN, SCL_PIN);
  // I2Cobj.setClock(100000);

  panel = new Panel();
  panel->setup(I2Cobj);
  screen.setup();

  game.setup(panel, screen);
  tester.setup(panel);
}

void loop() {
  tester.test();
  // if(panel->giantHandleActive()){
  //   screen.print("Sun launced!");
  // }
  // else{
  //   screen.print("Pull lever");
  // }
  // screen.tick();
  game.gameLoop();
  delay(100);

}
