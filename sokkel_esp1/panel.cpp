#include "esp32-hal-gpio.h"
#include "panel.h"

// GPIO expander board
Adafruit_MCP23X17 mcp;

void Panel::setup(TwoWire& i2c){
    if(!mcp.begin_I2C(0x20, &i2c)){
    Serial.println("[ERROR] - MCP I2C connection failed for panel!");
    }
    Serial.println("Setup panel!");
}

void Panel::setPinModes(){
    mcp.pinMode(STARDUST_3, INPUT_PULLUP);
    mcp.pinMode(STARDUST_8, INPUT_PULLUP);
    
    mcp.pinMode(JUNO_UP, INPUT_PULLUP);
    mcp.pinMode(JUNO_DOWN, INPUT_PULLUP);
    mcp.pinMode(VESTA_UP, INPUT_PULLUP);
    mcp.pinMode(VESTA_DOWN, INPUT_PULLUP);
    mcp.pinMode(PLUTO_UP, INPUT_PULLUP);
    mcp.pinMode(PLUTO_DOWN, INPUT_PULLUP);
    mcp.pinMode(HUDIG_UP, INPUT_PULLUP);
    mcp.pinMode(HUDIG_DOWN, INPUT_PULLUP);

    mcp.pinMode(KEY_SWITCH, INPUT_PULLUP);
}