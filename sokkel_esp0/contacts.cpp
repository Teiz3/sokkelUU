#include "esp32-hal-gpio.h"
#include "contacts.h"

// GPIO expander for side ABC
Adafruit_MCP23X17 mcpABC;
// GPIO expander for side D
Adafruit_MCP23X08 mcpD;



void Contacts::setup(TwoWire& i2c){
    if(!mcpABC.begin_I2C(CONTACT_MCP_ABC_ADDR, &i2c) || !mcpD.begin_I2C(CONTACT_MCP_D_ADDR, &i2c)){
        Serial.println("[ERROR] - MCP I2C connection failed for contacts");
    }
    setupPinMode();
    Serial.println("Setup contacts!");
}

bool Contacts::connected(enum ContactEnum c1, enum ContactEnum c2){
  if(c1 == c2){
    return true;
  }
  // Put 3.3v on c1
  uint8_t c1_pin = getPin(c1);
  if(isPlateD(c1)){
    mcpD.pinMode(c1_pin, OUTPUT);
    mcpD.digitalWrite(c1_pin, LOW);
  }
  else{
    mcpABC.pinMode(c1_pin, OUTPUT);
    mcpABC.digitalWrite(c1_pin, LOW);
  }
  // Test if c2 recieves power
  uint8_t c2_pin = getPin(c2);
  bool result;
  if(isPlateD(c2)){
    result = mcpD.digitalRead(c2_pin);
  }
  else{
    result = mcpABC.digitalRead(c2_pin);
  }
  // reset c1
  if(isPlateD(c1)){
    mcpD.pinMode(c1_pin, INPUT_PULLUP);
  }
  else{
    mcpABC.pinMode(c1_pin, INPUT_PULLUP);
  }
  // HIGH = disconnected
  // LOW = connected
  return !result;
}


bool Contacts::isPlateD(enum ContactEnum connectorName){
  switch(connectorName){
    case cD1:
    case cD2:
    case cD3:
    case cD4:
    case cD5:
      return true;
    default:
      return false;
  }
}

uint8_t Contacts::getPin(enum ContactEnum connectorName){
    switch(connectorName){
      case cA1:
        return CONTACT_A1;
      case cA2:
        return CONTACT_A2;
      case cA3:
        return CONTACT_A3;
      case cA4:
        return CONTACT_A4;
      case cA5:
        return CONTACT_A5;
      case cB1:
        return CONTACT_B1;
      case cB2:
        return CONTACT_B2;
      case cB3:
        return CONTACT_B3;
      case cB4:
        return CONTACT_B4;
      case cB5:
        return CONTACT_B5;
      case cC1:
        return CONTACT_C1;
      case cC2:
        return CONTACT_C2;
      case cC3:
        return CONTACT_C3;
      case cC4:
        return CONTACT_C4;
      case cC5:
        return CONTACT_C5;
      case cD1:
        return CONTACT_D1;
      case cD2:
        return CONTACT_D2;
      case cD3:
        return CONTACT_D3;
      case cD4:
        return CONTACT_D4;
      case cD5:
        return CONTACT_D5;
    }
}

int Contacts::debugReadABC(enum ContactEnum connectorName){
  uint8_t pin = getPin(connectorName);
  if (isPlateD(connectorName)){
    return mcpD.digitalRead(pin);
  }
  else{
    return mcpABC.digitalRead(pin);
  }
}

void Contacts::setupPinMode(){
    mcpABC.pinMode(CONTACT_A1, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_A2, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_A3, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_A4, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_A5, INPUT_PULLUP);

    mcpABC.pinMode(CONTACT_B1, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_B2, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_B3, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_B4, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_B5, INPUT_PULLUP);

    mcpABC.pinMode(CONTACT_C1, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_C2, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_C3, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_C4, INPUT_PULLUP);
    mcpABC.pinMode(CONTACT_C5, INPUT_PULLUP);

    mcpD.pinMode(CONTACT_D1, INPUT_PULLUP);
    mcpD.pinMode(CONTACT_D2, INPUT_PULLUP);
    mcpD.pinMode(CONTACT_D3, INPUT_PULLUP);
    mcpD.pinMode(CONTACT_D4, INPUT_PULLUP);
    mcpD.pinMode(CONTACT_D5, INPUT_PULLUP);
}