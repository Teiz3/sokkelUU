#include "esp32-hal-gpio.h"
#include "contacts.h"

// GPIO expander for side ABC
Adafruit_MCP23X17 mcpABC;
// GPIO expander for side D
Adafruit_MCP23X08 mcpD;

uint8_t Contacts::getPin(string connectorName){}

void Contacts::setup(TwoWire& i2c){
    if(!mcpABC.begin_I2C(CONTACT_MCP_ABC_ADDR, &i2c) || !mcpD.begin_I2C(CONTACT_MCP_D_ADDR, &i2c)){
        Serial.println("[ERROR] - MCP I2C connection failed for contacts");
    }
    setupPinMode()
    Serial.println("Setup contacts!");
}

void Contacts::setupPinMode(){
    mcpABC.pinMode(CONTACT_A1, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_A2, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_A3, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_A4, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_A5, INPUT_PULLDOWN);

    mcpABC.pinMode(CONTACT_B1, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_B2, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_B3, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_B4, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_B5, INPUT_PULLDOWN);

    mcpABC.pinMode(CONTACT_C1, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_C2, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_C3, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_C4, INPUT_PULLDOWN);
    mcpABC.pinMode(CONTACT_C5, INPUT_PULLDOWN);

    mcpD.pinMode(CONTACT_D1, INPUT_PULLDOWN);
    mcpD.pinMode(CONTACT_D2, INPUT_PULLDOWN);
    mcpD.pinMode(CONTACT_D3, INPUT_PULLDOWN);
    mcpD.pinMode(CONTACT_D4, INPUT_PULLDOWN);
    mcpD.pinMode(CONTACT_D5, INPUT_PULLDOWN);
}