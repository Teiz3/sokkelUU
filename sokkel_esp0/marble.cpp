#include "esp32-hal-gpio.h"
#include "marble.h"

uint8_t openval_1 = 0;
uint8_t openval_2 = 10;
uint8_t openval_3 = 5;
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
      servo1.write(openval_1);
      servo2.write(closedval);
      servo3.write(closedval);
      break;
    case 2:
      servo1.write(openval_1);
      servo2.write(openval_2);
      servo3.write(closedval);
      break;
    case 3:
    default:
      servo1.write(openval_1);
      servo2.write(openval_2);
      servo3.write(openval_3);
      break;
  }
  ledsOnTill(section);
  delay(100);
}

void Marble::setup(){
  servo1.attach(MARBLE_SERVO_1);
  servo2.attach(MARBLE_SERVO_2);
  servo3.attach(MARBLE_SERVO_3);

  pinMode(MARBLE_LED_0, OUTPUT);
  pinMode(MARBLE_LED_1, OUTPUT);
  pinMode(MARBLE_LED_2, OUTPUT);
  pinMode(MARBLE_LED_3, OUTPUT);

  setMarble(0);
  digitalWrite(MARBLE_LED_0, HIGH);
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
    break;
  }

}

void Marble::ledsOnTill(uint8_t section){
  for(int i = 1; i <= section; i++){
    setLed(i, HIGH);
  }
  for(int i = section+1; i <= 4; i++){
    setLed(i, LOW);
  }
}
