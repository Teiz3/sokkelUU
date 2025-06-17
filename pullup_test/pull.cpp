#include "pull.h"

Adafruit_MCP23X17 mcp2;

void Pull::setup(TwoWire& i2c){
    if(!mcp2.begin_I2C(0x26, &i2c)){
    Serial.println("[ERROR] - MCP I2C connection failed for panel!");
    }
    mcp2.pinMode(11, INPUT_PULLUP);
    Serial.println("Setup pulltest!");
}

int Pull::read(){
    return mcp2.digitalRead(11);
}