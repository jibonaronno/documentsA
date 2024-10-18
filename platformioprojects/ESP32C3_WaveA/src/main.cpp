/**
 * project from PlatformIO . Location : documentsA\ESP32\platformioprojects\ESP32C3_WaveA .
 * It uses ledc library to generate different frequency PWM signals. 
 * ledc library could handle the pwm output from D10 pin at different frequencies. 
 * It can produce 10KHz PWM carrier signal. One 220 Ohm Resistor and two 105 capacitor 
 * smooth out the signal well. 
 */

#include <Arduino.h>

typedef struct _INTARRAY
{
  int size;
  uint8_t *array;
}INTARRAY;

class _StreamData
{
  public:
    static int InsertionTimeOut;
    String header; // Header came from Serial port
    void InsertValueAsString(char *strIntValue)
    {

    }
    _StreamData(void){this->InsertionTimeOut = 100;}
};

int ledPin = D10;    // LED connected to digital pin 10

uint8_t int_array[] = {0,30,60,90,110,135,150,165,180,190,195,200,200,195,190,180,170,155,145,130,120,105,95,80,70,60,50,35,30,20,10,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,10,15,20,25,35,40,50,55,65,80,90,100,115,125,135,140,145,150,150,150,145,140,135,130,120,115,105,100,95,90,85,80,75,70,65,60,55,50,50,45,40,40,35,35,30,30,30,25,25,25,20,20,20,15,15,15,10,10,10,10,10};
INTARRAY plotData;
void setup() {

  Serial.begin(115200);
  // declaring LED pin as output
  pinMode(ledPin, OUTPUT);
  ledcSetup(0, 10000, 8);
  ledcAttachPin(ledPin, 0);
  plotData.size = 120;
  plotData.array = int_array;
  Serial.println("Starting up...");
}

void loop() {

  // fade in from min to max in increments of 5 points:
  //for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
  for(int lidx=0; lidx<plotData.size; lidx++){
    // sets the value (range from 0 to 255):
    //analogWrite(ledPin, fadeValue);
    ledcWrite(0, plotData.array[lidx]);
    // wait for 30 milliseconds to see the dimming effect
    delayMicroseconds(100);
    //delay(1);
  }

  // fade out from max to min in increments of 5 points:
  ////for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    //analogWrite(ledPin, fadeValue);
    ////ledcWrite(0, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    ////delayMicroseconds(300);
  //}
}
