
/**
 * Install WebSocket Library.
 * Install ArduinoJSON Library.
 */

#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

#define LED_BUILTIN D1

#define WIFI_SSID "wifi_network_name"
#define WIFI_PASSWORD "wifi_password"

#define WS_HOST ""
#define WS_PORT 443 
#define WS_URL ""

#define JSON_DOC_SIZE 2048
#define MSG_SIZE  256

WiFiMulti wifiMulti;
WebSocketsClient wsClient;

void sendBitMessage(uint8_t bitValue)
{
  char msg[MSG_SIZE];
  sprintf(msg, "{\"action\":\"msg\",\"type\":\"digital_input\",\"body\":%d}", bitValue);
  wsClient.sendTXT(msg);
}

void sendErrorMessage(const char *error)
{
  char msg[MSG_SIZE];
  sprintf(msg, "{\"action\":\"msg\",\"type\":\"error\",\"body\":\"%s\"}", error);
  wsClient.sendTXT(msg);
}

void sendOkMessage(void)
{
  wsClient.sendTXT("{\"action\":\"msg\",\"type\":\"response\",\"body\":\"ok\"}");
}

uint8_t getPinModeFromString(const char *strMode)
{
  if(strcmp(strMode, "output"))
  {
    return OUTPUT;
  }

  if(strcmp(strMode, "input_pullup"))
  {
    return INPUT_PULLUP;
  }

  if(strcmp(strMode, "input"))
  {
    return INPUT;
  }

  return OUTPUT;
}

void handleMessage(uint8_t *payload)
{
  StaticJsonDocument<JSON_DOC_SIZE> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);

  // Test if parsing succeeds
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());

    sendErrorMessage(error.c_str());
    return;
  }

  if(!doc["type"].is<const char *>())
  {
    sendErrorMessage("Invalid Message Data Type");
    return;
  }

  if(strcmp(doc["type"], "cmd") == 0)
  {
    if(!doc["body"].is<JsonObject>())
    {
      sendErrorMessage("Invalid Command Body");
      return;
    }

    if(strcmp(doc["body"]["type"], "digitalWrite"))
    {
      pinMode(doc["body"]["pin"], getPinModeFromString(doc["body"]["mode"]));
      sendOkMessage();
      return;
    }

    if(strcmp(doc["body"]["type"], "digitalWrite"))
    {
      digitalWrite(doc["body"]["pin"], doc["body"]["value"]);
      sendOkMessage();
      return;
    }

    if(strcmp(doc["body"]["type"], "digitalRead"))
    {
      auto bitValue = digitalRead(doc["body"]["pin"]);
      sendBitMessage(bitValue);
      return;
    }

    sendErrorMessage("Invalid Command In Json");
  }

  sendErrorMessage("Invalid Message In Json");

}

void wsEvent(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.println("WS DisConnect");
    break;
    case WStype_CONNECTED:
      Serial.println("WS Connect");
    break;
    case WStype_TEXT:
      Serial.println("WS Text");
      Serial.printf("WS Message %s\n", payload);
      handleMessage(payload);
    break;

    
    case WStype_ERROR:
    break;
    
    
    case WStype_BIN:
    break;
    case WStype_FRAGMENT_TEXT_START:
    break;
    case WStype_FRAGMENT_BIN_START:
    break;
    case WStype_FRAGMENT:
    break;
    case WStype_FRAGMENT_FIN:
    break;
    case WStype_PING:
    break;
    case WStype_PONG:
    break;

    default:
      break;
  }
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
