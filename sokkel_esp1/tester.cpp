#include "tester.h"


void Tester::setup(Panel* panel){
    Tester::panel = panel;
    Serial.println("Setup tester!");
}

int cometToInt(enum CometSwitch c, int offset){
  switch (c){
      case UP:
        return 2+offset;
      case DOWN:
        return -2+offset;
      default:
        return 0+offset;
    }
}

void Tester::test(){
    Serial.print("B:-3 ");
    Serial.print("T:9 ");
    Serial.print("Star:");
    Serial.print(panel->getStardust());

    Serial.print(" Key:");
    Serial.print(panel->keyTurned());

    enum CometSwitch Juno = panel->getComet('j');
    enum CometSwitch Vesta = panel->getComet('v');
    enum CometSwitch Pluto = panel->getComet('p');
    enum CometSwitch Hudig = panel->getComet('h');
    Serial.print(" Juno:");
    Serial.print(cometToInt(Juno, 4));
    Serial.print(" Vesta:");
    Serial.print(cometToInt(Vesta, 3));
    Serial.print(" Pluto:");
    Serial.print(cometToInt(Pluto, 2));
    Serial.print(" Hudig:");
    Serial.print(cometToInt(Hudig, 5));
    panel->setWarnLed(!digitalRead(GIANT_HANDLE));
    Serial.println("");

}
