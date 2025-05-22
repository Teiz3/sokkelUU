#include "sun.h"
#include "panel.h"
#include "pins.h"
#include <Wire.h>

Panel* panel;
TwoWire I2Cobj = TwoWire(0);

void setup() {
  Serial.begin(115200);
  while(!Serial){
    delay(5);
  }
  I2Cobj.begin(SDA_PIN, SCL_PIN);

  panel = new Panel();

  panel->setup(I2Cobj);
}

void loop() {
  // put your main code here, to run repeatedly:

}
