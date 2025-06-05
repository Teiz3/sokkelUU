#include "sun.h"
#include "panel.h"
#include "pins.h"
#include "tester.h"
#include <Wire.h>

Panel* panel;
TwoWire I2Cobj = TwoWire(0);
Tester tester;

void setup() {
  Serial.begin(115200);
  while(!Serial){
    delay(5);
  }
  Serial.println("Serial port started.");
  I2Cobj.begin(SDA_PIN, SCL_PIN);
  // I2Cobj.setClock(100000);

  panel = new Panel();
  panel->setup(I2Cobj);
  

  tester.setup(panel);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Serial!");
  // delay(50);
  tester.test();
  delay(50);

}
