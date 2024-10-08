#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>

#define LED_BUILTIN D1

#define WIFI_SSID "wifi_network_name"
#define WIFI_PASSWORD "wifi_password"

#define WS_HOST ""
#define WS_PORT 443 
#define WS_URL ""

WiFiMulti wifiMulti;
WebSocketsClient wsClient;

void wsEvent(WStype_t type, uint8_t * payload, size_t length)
{

}

void setup() {
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Connected");

  wsClient.beginSSL(WS_HOST, WS_PORT, WS_URL, "", "wss");

  wsClient.onEvent(wsEvent);
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  wsClient.loop();
}
