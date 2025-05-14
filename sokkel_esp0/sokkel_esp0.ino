#include "status_leds.h"
#include "contacts.h"
#include "marble.h"
#include "incubator.h"
#include "pins.h"
#include <Wire.h>

StatusLeds* status_leds; // Status leds object to control the 16 status leds
Marble* marble; // Status leds object to control the 16 status leds
Contacts* contacts; // Status leds object to control the 16 status leds
Incubator* incubator; // Status leds object to control the 16 status leds

TwoWire I2Cobj = TwoWire(0);

void setup() {
  Serial.begin(115200);

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  
  status_leds = new StatusLeds();
  marble = new Marble();
  contacts = new Contacts();
  incubator = new Incubator();
  
  status_leds->setup(I2Cobj);
  marble->setup();
  contacts->setup();
  incubator->setup();
}

void loop() {
  // put your main code here, to run repeatedly:

}

