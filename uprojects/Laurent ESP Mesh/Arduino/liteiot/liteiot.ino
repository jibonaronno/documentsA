#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif


void setup(){
  Serial.begin(115200);

  pinMode(D6, OUTPUT);

}

void loop(){

  digitalWrite(D6, HIGH);
  Serial.println("Light is On");

  delay(5000);

  digitalWrite(D6, LOW);
  Serial.println("Light is Off");
  
  delay(5000);
}

