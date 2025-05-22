#include "mcp.h"
#include <Wire.h>

// PINS
#define SDA_PIN 21
#define SCL_PIN 22

MCP* mcp;
TwoWire I2Cobj = TwoWire(0);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(5);
  }
  Serial.println("Serial setup.");

  I2Cobj.begin(SDA_PIN, SCL_PIN);
  mcp = new MCP();

  mcp->setup(I2Cobj);
}

void loop() {
  mcp->loopLED();
}
