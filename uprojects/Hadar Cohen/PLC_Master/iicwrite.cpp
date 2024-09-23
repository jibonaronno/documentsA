
#include "iicwrite.h"

void IICWrite::IICWrite(void)
{
  return;
}

void IICWrite::writeToAddress(int Address, int Data)
{
  int retEndTx = 0;
  uint8_t data_bytes[3];
  data_bytes[0] = 0x55;
  data_bytes[1] = 0x5A;
  data_bytes[2] = 0xA5;
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(TX_DATA0_REG);
  Wire.write(data_bytes[0]);
  retEndTx = Wire.endTransmission();

  if(retEndTx == 0)
  {
    Serial.println("SUCCESS writeToAddress(...) ");
  }
  else
  {
    Serial.println("ERROR writeToAddress(...) ");
    return; 
  }

  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(TX_TRIGGER_REG);
  Wire.write(0x03);
  retEndTx = Wire.endTransmission();

  if(retEndTx == 0)
  {
    Serial.println("SUCCESS writeToAddress(...) TX_TRIGGER_REG");
  }
  else
  {
    Serial.println("ERROR writeToAddress(...) TX_TRIGGER_REG");
    return; 
  }

}
