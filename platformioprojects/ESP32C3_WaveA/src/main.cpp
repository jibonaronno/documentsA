/**
 * project from PlatformIO . Location : documentsA\ESP32\platformioprojects\ESP32C3_WaveA .
 * It uses ledc library to generate different frequency PWM signals. 
 * ledc library could handle the pwm output from D10 pin at different frequencies. 
 * It can produce 10KHz PWM carrier signal. One 220 Ohm Resistor and two 105 capacitor 
 * smooth out the signal well. 
 */

#include <Arduino.h>

int ledPin = D10;    // LED connected to digital pin 10

void setup() {
  // declaring LED pin as output
  pinMode(ledPin, OUTPUT);
  ledcSetup(0, 10000, 8);
  ledcAttachPin(ledPin, 0);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    //analogWrite(ledPin, fadeValue);
    ledcWrite(0, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delayMicroseconds(300);
    //delay(1);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    //analogWrite(ledPin, fadeValue);
    ledcWrite(0, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delayMicroseconds(300);
  }
}
