#include <Arduino.h>
#include "esp32-hal-gpio.h"
#include "status_leds.h"

// GPIO expander board
Adafruit_MCP23X17 mcp;

void StatusLeds::test(){
  // mcp.digitalWrite(0, HIGH);
  // delay(1000);
  // mcp.digitalWrite(1, HIGH);
  // delay(1000);
  // mcp.digitalWrite(2, HIGH);
  // delay(1000);
  // mcp.digitalWrite(3, HIGH);
  // delay(1000);
  for(int i = 0; i < 16; i++){
    // if(i == BUTTON_PIN){
    //   continue;
    // }
    mcp.digitalWrite(i, HIGH);
    Serial.print(i);
    delay(3000);
  }
}


void StatusLeds::setStatus(uint8_t status){
  // if(frozen){
  //   return;
  // }
  for (int i = 1; i <= status && i <= 4; i++){
    setLed(i, HIGH);
  }
  for (int i = status+1; i<= 4; i++){
    setLed(i, LOW);
  }
}

void StatusLeds::freeze(unsigned long duration){
  frozen = true;
  unfreezetime = millis() + duration;
}

void StatusLeds::tick(){
  if ((millis() - unfreezetime) > 0){
    frozen = false;
  }
}

void StatusLeds::setup(TwoWire& i2c) {
  // Start mcp connection with 0x20 as default i2c address
  if(!mcp.begin_I2C(0x20, &i2c)){
    Serial.println("[ERROR] - MCP I2C connection failed for status_leds");
  }
  setupPinMode();
  for(int i = 0; i < 16; i++){
    mcp.digitalWrite(i, LOW);
  }
  Serial.println("Setup status leds completed!");
}

void StatusLeds::setLed(uint8_t val, uint8_t address){
  switch (address) {
    case 1:
      mcp.digitalWrite(STATUS_LED_A1, val);
      mcp.digitalWrite(STATUS_LED_B1, val);
      mcp.digitalWrite(STATUS_LED_C1, val);
      mcp.digitalWrite(STATUS_LED_D1, val);
      break;
    case 2:
      mcp.digitalWrite(STATUS_LED_A2, val);
      mcp.digitalWrite(STATUS_LED_B2, val);
      mcp.digitalWrite(STATUS_LED_C2, val);
      mcp.digitalWrite(STATUS_LED_D2, val);
      break;
    case 3:
      mcp.digitalWrite(STATUS_LED_A3, val);
      mcp.digitalWrite(STATUS_LED_B3, val);
      mcp.digitalWrite(STATUS_LED_C3, val);
      mcp.digitalWrite(STATUS_LED_D3, val);
      break;
    case 4:
      mcp.digitalWrite(STATUS_LED_A4, val);
      mcp.digitalWrite(STATUS_LED_B4, val);
      mcp.digitalWrite(STATUS_LED_C4, val);
      mcp.digitalWrite(STATUS_LED_D4, val);
      break;
  }
}

void StatusLeds::setupPinMode(){
  mcp.pinMode(STATUS_LED_A1, OUTPUT);
  mcp.pinMode(STATUS_LED_A2, OUTPUT);
  mcp.pinMode(STATUS_LED_A3, OUTPUT);
  mcp.pinMode(STATUS_LED_A4, OUTPUT);

  mcp.pinMode(STATUS_LED_B1, OUTPUT);
  mcp.pinMode(STATUS_LED_B2, OUTPUT);
  mcp.pinMode(STATUS_LED_B3, OUTPUT);
  mcp.pinMode(STATUS_LED_B4, OUTPUT);

  mcp.pinMode(STATUS_LED_C1, OUTPUT);
  mcp.pinMode(STATUS_LED_C2, OUTPUT);
  mcp.pinMode(STATUS_LED_C3, OUTPUT);
  mcp.pinMode(STATUS_LED_C4, OUTPUT);

  mcp.pinMode(STATUS_LED_D1, OUTPUT);
  mcp.pinMode(STATUS_LED_D2, OUTPUT);
  mcp.pinMode(STATUS_LED_D3, OUTPUT);
  mcp.pinMode(STATUS_LED_D4, OUTPUT);
}