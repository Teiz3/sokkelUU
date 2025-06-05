// Reads a button attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
#include <Adafruit_MCP23X17.h>
#include "pull.h"


#define BUTTON_PIN 10  // MCP23XXX pin button is attached to

Adafruit_MCP23X17 mcp;
Pull* pull;
TwoWire wire = TwoWire(0);

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("MCP23xxx Button Test!");

  wire.begin(8, 9);

  pull = new Pull();
  pull->setup(wire);

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C(0x20, &wire)) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure pin for input with pull up
  mcp.pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Looping...");
}

void loop() {
  // LOW = pressed, HIGH = not pressed
  Serial.print("A: ");
  Serial.print(mcp.digitalRead(BUTTON_PIN));

  Serial.print(" B: ");
  Serial.println(pull->read());

  delay(50);


}