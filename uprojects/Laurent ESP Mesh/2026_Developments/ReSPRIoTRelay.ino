#include <Wire.h>
#include <INA219.h>            // Cambiado a tu librería

#define RELAY_PIN D6           // D6 en tu XIAO
#define SDA_PIN D4
#define SCL_PIN D5

INA219 ina219(0x40);  // Default. Address is determined by jumpers on A0 and A1

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);

  //Wire.begin(); // only valid if default SDA and SCL ports are used
  Wire.begin(SDA_PIN, SCL_PIN);

  // Inicializa el INA219
  
  //if (!ina219.begin()) {
  //  Serial.println("Error: no se detecta INA219 en 0x40");
  //  while (1) delay(10);
  //}

  while (!ina219.begin()) {
    Serial.println("Error: no se detecta INA219 en 0x40. Probando de nuevo.");
    delay(3000);
  }
    
  // Si tu módulo requiere calibración de shunt, descomenta y ajusta:
  // ina219.setShuntResistor(0.002);  // valor en ohmios
  // ina219.setMaxCurrent(2.5);       // valor en amperios

  ina219.setMaxCurrentShunt(2.5, 0.1); // LAE Amperes and resistance (0,1 Ohm (R100))
  ina219.setBusVoltageRange(24); // LAE
    

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);   // Relé desactivado (HIGH = OFF)
}

void loop() {
  static bool on = false;
  on = !on;
  
  //Conmuta el relé
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);  // LOW activa el relé

  Serial.print("Relay ");
  Serial.print(on ? "ON" : "OFF");

  // Wait for load to stabilize
  if (on) {
    // T5 lamp and ballast take some time to pull load
    delay (10000);
      } else {
        // when switching off less time is needed for current to drop
        delay (500);
      }
  

  // Lectura de corriente según tu librería; ajusta el nombre si es distinto
  float mA = ina219.getCurrent_mA();
  Serial.print("   Curr mA: ");
  // otras variaciones comunes: ina219.readCurrent(), ina219.readCurrent_mA(), etc.
  Serial.println(mA, 2);
  float busV   = ina219.getBusVoltage_mV();
  float shuntV = ina219.getShuntVoltage_mV();
  Serial.printf("   Vbus: %.3f mV  Vshunt: %.3f mV\n", busV, shuntV);
  Serial.println("-----------------------");
  // Now wait for complete cycle to end (30s in total)
  if (on) {
    delay(20000);
  } else {
    delay(9500);
  }
  
}
