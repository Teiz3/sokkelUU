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
}

void Marble::setup(){
  servo1.attach(MARBLE_SERVO_1);
  servo2.attach(MARBLE_SERVO_2);
  servo3.attach(MARBLE_SERVO_3);
  Serial.println("Setup marble track!");
}