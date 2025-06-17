#include "esp32-hal-gpio.h"
#include "marble.h"

uint8_t openval = 0;
uint8_t closedval = 90;

Servo servo1;
Servo servo2;
Servo servo3;

void Marble::setMarble(uint8_t section){
  switch(section){
    case 0:
      servo1.write(closedval);
      servo2.write(closedval);
      servo3.write(closedval);
      break;
    case 1:
      servo1.write(openval);
      servo2.write(closedval);
      servo3.write(closedval);
      break;
    case 2:
      servo1.write(openval);
      servo2.write(openval);
      servo3.write(closedval);
      break;
    case 3:
    default:
      servo1.write(openval);
      servo2.write(openval);
      servo3.write(openval);
      break;
  }
  ledsOnTill(section);
  delay(100);
}

void Marble::setup(){
  servo1.attach(MARBLE_SERVO_1);
  servo2.attach(MARBLE_SERVO_2);
  servo3.attach(MARBLE_SERVO_3);

  pinMode(MARBLE_LED_1, OUTPUT);
  pinMode(MARBLE_LED_2, OUTPUT);
  pinMode(MARBLE_LED_3, OUTPUT);

  setMarble(0);
  Serial.println("Setup marble track!");
}


void Marble::setLed(uint8_t led, uint8_t val){
  switch (led) {
  case 1:
    digitalWrite(MARBLE_LED_1, val);
    break;
  case 2:
    digitalWrite(MARBLE_LED_2, val);
    break;
  case 3:
    digitalWrite(MARBLE_LED_3, val);
    break;
  case 4:
    digitalWrite(MARBLE_LED_4, val);
    break;
  }

}

void Marble::ledsOnTill(uint8_t section){
  for(int i = 1; i <= section; i++){
    setLed(i, HIGH);
  }
  for(int i = section+1; i <= 3; i++){
    setLed(i, LOW);
  }
}
