
#include "iicread.h"

void IICRead::readFromAddress(int Address, int Data)
{
  int retEndTx = 0;
  int val01 = 0;
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(RX_TRIGGER_REG);
  retEndTx = Wire.endTransmission();
  Wire.requestFrom(I2C_DEV_ADDR, 1); // We want one byte
  val01 = Wire.read();
  
  if(retEndTx == 0)
  {
    Serial.println("SUCCESS Reading RX_TRIGGER_REG");
  }
  else
  {
    Serial.println("ERROR Reading RX_TRIGGER_REG");
    return;
  }

  //if((val01 & 0x06))
  {
    Wire.beginTransmission(I2C_DEV_ADDR);
    Wire.write(RX_DATA0_REG);
    retEndTx = Wire.endTransmission();
    Wire.requestFrom(I2C_DEV_ADDR, 1); // We want one byte
    val01 = Wire.read();
    Serial.print("Received Value : ");
    Serial.println(val01);
  }
}
