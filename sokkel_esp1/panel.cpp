#include "esp32-hal-adc.h"
#include "esp32-hal-gpio.h"
#include "panel.h"

// GPIO expander board
Adafruit_MCP23X17 mcp;

int Panel::getStardust(){
    if(mcp.digitalRead(STARDUST_3) == LOW){
        return 3;
    }
    if(mcp.digitalRead(STARDUST_8) == LOW){
        return 8;
    }
    return 0;
}

bool Panel::keyTurned(){
    return mcp.digitalRead(KEY_SWITCH) == LOW;
}

bool Panel::giantHandleActive(){
    return digitalRead(GIANT_HANDLE) == LOW;
}

void Panel::setWarnLed(uint8_t val){
    mcp.digitalWrite(LED_PIN, val);
}

int Panel::getLinPot(){
  return analogRead(SLIDE_POT_METER);
}

int Panel::getRadiation(){
  int a = getLinPot();
  if (a < 1300){
    return 0;
  }
  if (a > 3000){
    return 2;
  }
  return 1;
}

enum CometSwitch Panel::checkComet(uint8_t pinUp, uint8_t pinDown){
    if(mcp.digitalRead(pinUp) == LOW){
        return UP;
    }
    if(mcp.digitalRead(pinDown) == LOW){
        return DOWN;
    }
    return OFF;
}

int Panel::debugRead(uint8_t pin){
  return mcp.digitalRead(pin);
}

enum CometSwitch Panel::getComet(char cometName){
  switch (cometName){
    case 'j':
      return checkComet(JUNO_UP, JUNO_DOWN);
      break;
    case 'v':
      return checkComet(VESTA_UP, VESTA_DOWN);
      break;
    case 'p':
      return checkComet(PLUTO_UP, PLUTO_DOWN);
      break;
    case 'h':
      return checkComet(HUDIG_UP, HUDIG_DOWN);
      break;
  }
}

enum AVOSwitch Panel::getAVOAC(){
    if(digitalRead(AVO_AC_250V) == LOW){
        return VOLT;
    }
    if(digitalRead(AVO_AC_OHM) == LOW){
        return A_OHM;
    }
    return AVO_OFF;
}


enum AVOSwitch Panel::getAVODC(){
    if(digitalRead(AVO_DC_100V) == LOW){
        return VOLT;
    }
    if(digitalRead(AVO_DC_250uA) == LOW){
        return A_OHM;
    }
    return AVO_OFF;
}

void Panel::updateAvoMeter(){
  int potVal = getLinPot();
  potVal = map(potVal, 1, 4095, 1, 255);
  analogWrite(AVO_DISPLAY, potVal);
}

bool Panel::sunConnected(){
  return analogRead(SUN_IN) > 2800;
}

void Panel::setup(TwoWire& i2c){
    if(!mcp.begin_I2C(0x20, &i2c)){
    Serial.println("[ERROR] - MCP I2C connection failed for panel!");
    }
    setPinModes();
    digitalWrite(SUN_OUT, LOW);
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
    mcp.pinMode(LED_PIN, OUTPUT);

    pinMode(GIANT_HANDLE, INPUT_PULLUP);
    pinMode(AVO_DISPLAY, OUTPUT);
    
    pinMode(SUN_IN, INPUT);
    pinMode(SUN_OUT, OUTPUT);

    pinMode(AVO_DC_100V, INPUT_PULLUP);
    pinMode(AVO_DC_250uA, INPUT_PULLUP);
    pinMode(AVO_AC_250V, INPUT_PULLUP);
    pinMode(AVO_AC_OHM, INPUT_PULLUP);


}