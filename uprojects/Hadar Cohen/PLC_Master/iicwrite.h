
#include "Wire.h"

#define I2C_DEV_ADDR 0x6A
#define TX_DATA0_REG 0x0D
#define TX_DATA1_REG 0x0E
#define TX_DATA2_REG 0x0F
#define TX_TRIGGER_REG  0x09

class IICWrite
{
  public:
    void writeToAddress(int Address, int Data);
};