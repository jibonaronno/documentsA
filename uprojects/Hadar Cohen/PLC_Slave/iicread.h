#include <Arduino.h>
#include "Wire.h"

#define I2C_DEV_ADDR 0x15
#define TX_DATA0_REG 0x0D
#define TX_DATA1_REG 0x0E
#define TX_DATA2_REG 0x0F
#define TX_TRIGGER_REG  0x09

#define RX_DATA0_REG 0x10
#define RX_DATA1_REG 0x11
#define RX_DATA2_REG 0x12
#define RX_TRIGGER_REG  0x0B

class IICRead
{
  public:
    void readFromAddress(int Address, int Data);
};