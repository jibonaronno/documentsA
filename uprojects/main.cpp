define MQTT_MAX_PACKET_SIZE 512

/****************************************
  Include Libraries
  These libraries are packaged with the sketch so that you do not have to import/install them yourself.
  If these libraries become out of date or no longer work, then install them in the Arduino IDE and 
  remove the "src/" prefix from each of the libraries below.
****************************************/
#include "UbidotsESPMQTT.h"
#include "PubSubClient.h"
#include "OneWire.h"
#include "DallasTemperature.h"

/****************************************
  Define Constants and Instances
****************************************/
#define TOKEN "BBFF-MI133Q5WVJJ4QhLUh0ArDSTMdRYgfp" // Your Ubidots TOKEN
#define WIFINAME "CryoSRV" // Your SSID
#define WIFIPASS "COLDHEAD" // Your Wifi Pass
#define PUBLISHNAME "TST-CM-10"
#define ONE_WIRE_BUS 4

int UPDATE_INTERVAL = 15000; // Time between temperature readings in milliseconds

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Ubidots client(TOKEN);

char deviceNames[16][30];

/****************************************
  Auxilary Functions
****************************************/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
  Main Functions
****************************************/
void setup() {
  Serial.begin(9600);
  client.wifiConnection(WIFINAME, WIFIPASS);
  sensors.begin();
  client.begin(callback);
  client.setDebug(true);
}

void loop() {
  if (!client.connected()) {
    client.reconnect();
  }
  sensors.requestTemperatures();
  //Prepare the sensor for reading
  int deviceCount = sensors.getDeviceCount();
  for (int deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++) {
    
    sprintf(deviceNames[deviceIndex], "%s_%i", "Temperature", deviceIndex + 1);
    float tempF = sensors.getTempFByIndex(deviceIndex);
    
    Serial.print(deviceNames[deviceIndex]);
    Serial.print("\t");
    Serial.println(tempF);
    
    client.add(deviceNames[deviceIndex], tempF);
  }

  client.ubidotsPublish(PUBLISHNAME);
  client.loop();
  
  delay(UPDATE_INTERVAL);
}