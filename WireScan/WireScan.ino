#include "Wire.h"

void setup() {
  Serial.begin(115200);
  // Wire.begin(47, 38); // ESP1
  Wire.begin(21, 38); // ESP0
}

void loop() {
  byte error, address;
  int nDevices = 0;

  delay(50);

  // Serial.println("Scanning for I2C devices ...");
  for (address = 0x01; address < 0x7f; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      // Serial.printf("I2C device found at address 0x%02X\n", address);
      Serial.println(address);
      nDevices++;
    } else if (error != 2) {
      Serial.printf("Error %d at address 0x%02X\n", error, address);
    }
  }
  if (nDevices == 0) {
    // Serial.println("No I2C devices found");
    Serial.println("0");
  }
}
