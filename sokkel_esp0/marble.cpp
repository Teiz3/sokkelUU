#include "marble.h"

MyServo servo1;
MyServo servo2;
MyServo servo3;

void Marble::setMarble(uint8_t section){
  switch(section){
    case 0:
      servo1.close();
      servo2.close();
      servo3.close();
      break;
    case 1:
      servo1.open();
      servo2.close();
      servo3.close();
      break;
    case 2:
      servo1.open();
      servo2.open();
      servo3.close();
      break;
    case 3:
    default:
      servo1.open();
      servo2.open();
      servo3.open();
      break;
  }
}

void Marble::setup(){
  servo1.setup(MARBLE_SERVO_1);
  servo2.setup(MARBLE_SERVO_2);
  servo3.setup(MARBLE_SERVO_3);
  // servo1.attach(MARBLE_SERVO_1);
  // servo2.attach(MARBLE_SERVO_2);
  // servo3.attach(MARBLE_SERVO_3);
  Serial.println("Setup marble track!");
}

void MyServo::setup(uint8_t pin){
  servo.attach(pin, 1000, 2000);
}

void MyServo::open(){
  if(!isOpen){
    Serial.println("OPEN");
    servo.write(0);
    delay(1000);
    servo.write(90);
    isOpen = true;
  }
}
void MyServo::close(){
  if(isOpen){
    Serial.println("CLOSE");
    servo.write(180);
    delay(1000);
    servo.write(90);
    isOpen = false;
  }
}