#include <Wire.h>
#include <INA219.h>   // Ensure this is the correct header for your library

// Use the correct class name from your library. For example, if it's INA219_WE:
INA219 ina219(0x40);  // Adjust the class name accordingly

#define RELAY_PIN D6

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Wire.begin();

  // Initialize the INA219 sensor using the appropriate method
  while (!ina219.begin()) {
    Serial.println("Failed to find INA219 sensor. Retrying.");
    delay(3000);
  }
  
  // LAE following 4 lines added
    ina219.setMaxCurrentShunt(2.5, 0.002);
    delay(1000);
    Serial.println("Code starts HERE!");
    ina219.setBusVoltageRange(24);
    Serial.println(ina219.getBusVoltageRange());

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay ON");
  
  delay(5000);
  float current_mA = ina219.getCurrent();  // Verify that this method exists in your library
  Serial.printf("Current: %.2f mA\n", current_mA);
  // Serial.print(ina219.getShuntVoltage_mV(), 2);
  
  delay(25000);

  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF");
  
  delay(5000);
  current_mA = ina219.getCurrent_mA();
  Serial.printf("Current: %.2f mA\n", current_mA);
  
  delay(5000);
}