
#include <Wire.h>

// Define the upper and lower limits of the calibration pressure
#define PMIN 20000.0  //Full range pressure for example 20Kpa
#define PMAX 120000.0  //Zero Point Pressure Value, for example 120Kpa
#define DMIN 3355443.0  //AD value corresponding to pressure zero, for example 20%AD=2^24*0.2
#define DMAX 13421772.0  //AD Value Corresponding to Full Pressure Range, for example 80%AD=2^24*0.8

//The 7-bit IIC address of the JHM1200 is 0x78
uint8_t Device_Address = 0x78 << 1;

uint32_t ashot = 0;
uint8_t bufferA[6] = {0};
uint32_t Dtest = 0;
uint16_t temp_raw = 0;
double pressure = 0.0, temp = 0.0;
int lidxA = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  ashot = millis();
  bufferA[0] = 0xAC;
}

void loop() {
  // put your main code here, to run repeatedly:

  if(millis() > (ashot + 1000))
  {
    ashot = millis();

    Wire.beginTransmission(Device_Address);
    Wire.write(bufferA[0]);
    Wire.endTransmission();

    Wire.requestFrom(Device_Address, 6); 
    //while(Wire.available() < 1);

    for(lidxA=0;lidxA<6;lidxA++)
    {
      bufferA[lidxA] = Wire.read();
    }

    Dtest = ((uint32_t)bufferA[1] << 16) | ((uint16_t)bufferA[2] << 8) | bufferA[3];
    temp_raw = ((uint16_t)bufferA[4] << 8) | (bufferA[5] << 0);
    pressure = (PMAX-PMIN)/(DMAX-DMIN)*(Dtest-DMIN)+PMIN;
    temp = (double)temp_raw / 65536;
    temp = temp * 19000 - 4000;

    Serial.print(Dtest);
    Serial.print(", ");
    Serial.print(temp_raw);
    Serial.println(pressure);
    Serial.print(temp);
  }

}
