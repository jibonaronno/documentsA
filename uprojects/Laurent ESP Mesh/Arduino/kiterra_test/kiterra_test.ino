#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* server = "api.kaiterra.com";
const char* apiKey = "CcUdlG2ozUb4cKDhkqhCom6a3uOrJSeCRwuOXc6PaTkTIYum";  // Replace with your API key
const char* deviceId = "170fe28c-4c5f-47fa-889d-1a44c27cc852"; // Replace with your Sensedge device ID

const char* ssid = "sanion";
const char* password = "Sanionwifi12!@";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
}

void getEnvironmentData() {
    WiFiClientSecure client;
    client.setInsecure();  // Bypass SSL verification (Not recommended for production)

    Serial.println("Connecting to API...");
    if (!client.connect(server, 443)) {
        Serial.println("Connection failed");
        return;
    }

    String url = "/v1/devices/" + String(deviceId) + "/top?key=" + String(apiKey);

    Serial.print("Requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Wait for response
    while (client.connected() || client.available()) {
        if (client.available()) {
            String response = client.readString();
            Serial.println("Response: ");
            Serial.println(response);
            break;
        }
    }

    client.stop();
}

void loop() {
    // Your API request code goes here
    getEnvironmentData();
    delay(60000);
}
