#include "MCP.h"

// GPIO expander board
Adafruit_MCP23X17 mcp_lib;

void MCP::setup(TwoWire& i2c){
    if(!mcp_lib.begin_I2C(0x20, &i2c)){
    Serial.println("[ERROR] - MCP I2C connection failed for status_leds");
    }
    mcp_lib.pinMode(7, OUTPUT);
    mcp_lib.digitalWrite(7, LOW);
    Serial.println("Setup MCP!");
}

void MCP::loopLED(){
  mcp_lib.digitalWrite(7, HIGH);
  delay(1000);
  mcp_lib.digitalWrite(7, LOW);
  delay(1000);
}