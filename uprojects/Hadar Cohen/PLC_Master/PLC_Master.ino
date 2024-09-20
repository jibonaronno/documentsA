
#include "Wire.h"

#define I2C_DEV_ADDR 0x28

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin();

}

int snapA = 0;

void loop() {
  // put your main code here, to run repeatedly:
  snapA = millis();

}
