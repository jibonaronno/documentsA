#include "iicread.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin();

}

IICRead plc;
int snapA = 0;

void loop() {
  // put your main code here, to run repeatedly:
  snapA = millis();

  //if(snapA < (millis()+5000))
  {
    snapA = millis();

    plc.readFromAddress(0, 0);

  }

}