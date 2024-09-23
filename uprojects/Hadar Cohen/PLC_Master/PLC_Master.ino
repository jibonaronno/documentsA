
#include "Wire.h"

#define I2C_DEV_ADDR 0x6A

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin();

}

int snapA = 0;

void loop() {
  // put your main code here, to run repeatedly:
uint8_t data_bytes[3];
data_bytes[0] = 0x55;
data_bytes[1] = 0x5A;
data_bytes[2] = 0xA5;
  snapA = millis();

  if(snapA < (millis()+2000))
  {
    snapA = millis();
    Wire.beginTransmission(I2C_DEV_ADDR);
    Wire.write(data_bytes[0]);

  }

}
