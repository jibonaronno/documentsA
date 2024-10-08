
#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU

//#define USE_SPI       // Uncomment this to use SPI
#define ICM_20948_REG_BANK_SEL 0x76
#define ICM_20948_REG_ACCEL_CONFIG 0x14
#define ICM_20948_ACCEL_FULLSCALE_8G 0x02
#define SERIAL_PORT Serial

#define SPI_PORT SPI // Your desired SPI port.       Used only when "USE_SPI" is defined
#define CS_PIN 2    // Which pin you connect CS to. Used only when "USE_SPI" is defined
#include <bluefruit.h>
unsigned long previousMillis = 0;
const long interval = 25;
BLEUart bleuart;  // BLE UART service

BLEService uartService = BLEService("6E400001B5A3F393E0A9E50E24DCCA9E"); // UART service UUID
BLECharacteristic txCharacteristic = BLECharacteristic("6E400002B5A3F393E0A9E50E24DCCA9E"); // TX characteristic UUID
ICM_20948_SPI myICM; 
bool connect = false;
const int numReadings = 1;
double rollReadings;
double pitchReadings;
double yawReadings;
float accelXReadings;
float accelYReadings;
float accelZReadings;
float gyroXReadings;
float gyroYReadings;
float gyroZReadings;

int totalReadings = 0;



void setup()
{

  SERIAL_PORT.begin(115200); // Start the serial console

  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.setName("test");

  // Configure and start BLE Uart service
  bleuart.begin();

 // Set up callbacks for connection
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  //Bluefruit.Periph.mtu_request_Callback(mtu_request_callback);

// Set the callback in setup()

  Bluefruit.Periph.setConnInterval(16, 80);
  Bluefruit.Periph.setConnSupervisionTimeout(500); 

  // Start advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addService(bleuart);

  
  Bluefruit.Advertising.start();


  delay(100);

 rollReadings=0;
 pitchReadings=0;
 yawReadings=0;
 accelXReadings=0;
 accelYReadings=0;
 accelZReadings=0;
  gyroXReadings = 0;
  gyroYReadings = 0;
  gyroZReadings = 0;
  SPI_PORT.begin();

  bool initialized = false;
  while (!initialized)
  {
 SERIAL_PORT.print(F("status:"));
    myICM.begin(CS_PIN, SPI_PORT);
    SERIAL_PORT.println(myICM.status);
 //SERIAL_PORT.print(F("Avg loll22:"));
    if (myICM.status != ICM_20948_Stat_Ok)
    {
       //SERIAL_PORT.print(F("Avg 3:"));
      delay(500);
    }
    else
    {
      initialized = true;
       SERIAL_PORT.print(F("Avg Roll2:"));
    }
  }


  bool success = true; // Use success to show if the DMP configuration was successful
  setAccelerometerRange(ICM_20948_ACCEL_FULLSCALE_8G);
  // Initialize the DMP. initializeDMP is a weak function. You can overwrite it if you want to e.g. to change the sample rate
  success &= (myICM.initializeDMP() == ICM_20948_Stat_Ok);

  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR) == ICM_20948_Stat_Ok);

  // Enable any additional sensors / features
  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_RAW_GYROSCOPE) == ICM_20948_Stat_Ok);
  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_ACCELEROMETER) == ICM_20948_Stat_Ok);

  success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Quat6, 0) == ICM_20948_Stat_Ok); // Set to the maximum
   //success &=( myICM.setAccelRange(ICM_20948_ACCEL_RANGE_8G== ICM_20948_Stat_Ok);

  // Enable the FIFO
  success &= (myICM.enableFIFO() == ICM_20948_Stat_Ok);

  // Enable the DMP
  success &= (myICM.enableDMP() == ICM_20948_Stat_Ok);

  // Reset DMP
  success &= (myICM.resetDMP() == ICM_20948_Stat_Ok);

  // Reset FIFO
  success &= (myICM.resetFIFO() == ICM_20948_Stat_Ok);

  // Check success
  if (success)
  {

  }
  else
  {
    SERIAL_PORT.println(F("Enable DMP failed!"));
    SERIAL_PORT.println(F("Please check that you have uncommented line 29 (#define ICM_20948_USE_DMP) in ICM_20948_C.h..."));
    while (1)
      ; // Do nothing more
  }
}

void loop()
{
  
  icm_20948_DMP_data_t data;
  myICM.readDMPdataFromFIFO(&data);

  if ((myICM.status == ICM_20948_Stat_Ok) || (myICM.status == ICM_20948_Stat_FIFOMoreDataAvail)) // Was valid data available?
  {


    if ((data.header & DMP_header_bitmap_Quat6) > 0) // We have asked for GRV data so we should receive Quat6
    {

      // Scale to +/- 1
      double q1 = ((double)data.Quat6.Data.Q1) / 1073741824.0; // Convert to double. Divide by 2^30
      double q2 = ((double)data.Quat6.Data.Q2) / 1073741824.0; // Convert to double. Divide by 2^30
      double q3 = ((double)data.Quat6.Data.Q3) / 1073741824.0; // Convert to double. Divide by 2^30
      
      

      double q0 = sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3)));

      double q2sqr = q2 * q2;

      // roll (x-axis rotation)
      double t0 = +2.0 * (q0 * q1 + q2 * q3);
      double t1 = +1.0 - 2.0 * (q1 * q1 + q2sqr);
      double roll = atan2(t0, t1) * 180.0 / PI;

      // pitch (y-axis rotation)
      double t2 = +2.0 * (q0 * q2 - q3 * q1);
      t2 = t2 > 1.0 ? 1.0 : t2;
      t2 = t2 < -1.0 ? -1.0 : t2;
      double pitch = asin(t2) * 180.0 / PI;

      // yaw (z-axis rotation)
      double t3 = +2.0 * (q0 * q3 + q1 * q2);
      double t4 = +1.0 - 2.0 * (q2sqr + q3 * q3);
      double yaw = atan2(t3, t4) * 180.0 / PI;

      rollReadings += roll;
      pitchReadings += pitch;
      yawReadings += yaw;
      

    }
     if ((data.header & DMP_header_bitmap_Accel) > 0) { // We have asked for Accel data so we should receive it
        
      int16_t accelX = data.Raw_Accel.Data.X;
      int16_t accelY = data.Raw_Accel.Data.Y;
      int16_t accelZ = data.Raw_Accel.Data.Z;

      // Convert raw acceleration data to g's (assuming the default 2g range)
      float accelX_g = (float)accelX/4096 ; // 16384 LSB/g for 2g range
      float accelY_g = (float)accelY/4096 ; // 16384 LSB/g for 2g range
      float accelZ_g = (float)accelZ/4096 ; // 16384 LSB/g for 2g range
      accelY_g-=1;
      if(accelX_g <= 0.50 && accelX_g>=-0.50)
      {
        accelX_g=0.0;
      }
      if(accelY_g - 1 <= 0.50 && accelY_g >= -0.50)
      {
        accelY_g=0.0;
      }
if(accelZ_g <= 0.50 && accelZ_g>=-0.50)
      {
        accelZ_g=0.0;
      }


      accelXReadings += accelX_g;
      accelYReadings += accelY_g;
      accelZReadings += accelZ_g;

   
    }
     if ((data.header & DMP_header_bitmap_Gyro) > 0) { // We have asked for Gyro data so we should receive it
      int16_t gyroX = data.Raw_Gyro.Data.X;
      int16_t gyroY = data.Raw_Gyro.Data.Y;
      int16_t gyroZ = data.Raw_Gyro.Data.Z;
      // Convert raw gyro data to degrees per second (assuming default sensitivity of 250 dps)
      float gyroX_dps = (float)gyroX / 131.0; // 131 LSB/dps for 250 dps range
      float gyroY_dps = (float)gyroY / 131.0; // 131 LSB/dps for 250 dps range
      float gyroZ_dps = (float)gyroZ / 131.0; // 131 LSB/dps for 250 dps range
      gyroXReadings += gyroX_dps;
      gyroYReadings += gyroY_dps;
      gyroZReadings += gyroZ_dps;
    }
     totalReadings++;
     if(totalReadings >= numReadings)
     {
      double rollAvg = rollReadings / totalReadings;
      double pitchAvg = pitchReadings / totalReadings;
      double yawAvg = yawReadings / totalReadings;
      float accelXAvg = accelXReadings / totalReadings;
      float accelYAvg = accelYReadings / totalReadings;
      float accelZAvg = accelZReadings / totalReadings;
      float gyroXAvg = gyroXReadings / totalReadings;
      float gyroYAvg =gyroYReadings / totalReadings;
      float gyroZAvg =gyroZReadings / totalReadings;

/*if(accelXAvg <= 0.50 && accelXAvg>=-0.50)
      {
        accelXAvg=0.0;
      }
      if(accelYAvg <= 0.50 && accelYAvg >= -0.50)
      {
        accelYAvg=0.0;
      }
if(accelZAvg <= 0.50 && accelZAvg>=-0.50)
      {
        accelZAvg=0.0;
      }*/

    /*SERIAL_PORT.print("x:");
    SERIAL_PORT.println(rollAvg);
    SERIAL_PORT.print("y:");
    SERIAL_PORT.println(pitchAvg);
    SERIAL_PORT.print("z:");
    SERIAL_PORT.println(yawAvg);*/
      unsigned long currentMillis = millis();
     // if(accelZAvg!=0 ||accelYAvg!=0 || accelXAvg!=0)
      //{
      //SERIAL_PORT.print("z:");
      //SERIAL_PORT.println(accelZAvg);
      //SERIAL_PORT.print("y:");
      //SERIAL_PORT.println(accelYAvg);
      //SERIAL_PORT.print("x:");
      //SERIAL_PORT.println(accelXAvg);
     // }

      
    if (connect && (currentMillis - previousMillis >= interval)) {
    previousMillis = currentMillis;

       float accelX_g = ((float)accelXAvg) + 8.0; // Offset by 2 to remove negative values
      float accelY_g = ((float)accelYAvg ) + 8.0; // Offset by 2 to remove negative values
      float accelZ_g = ((float)accelZAvg )  + 8.0; // Offset by 2 to remove negative values
      rollAvg+=180;
      pitchAvg+=180;
      yawAvg+=180;
      uint16_t quantizedGyroX = (uint16_t)((gyroXAvg + 250.0) * 100); // Offset by 250.0 to remove negative values and scale
      uint16_t quantizedGyroY = (uint16_t)((gyroYAvg + 250.0) * 100); // Offset by 250.0 to remove negative values and scale
      uint16_t quantizedGyroZ = (uint16_t)((gyroZAvg + 250.0) * 100);
      //   SERIAL_PORT.print("z:");
    //SERIAL_PORT.println(yawAvg);
      uint16_t rollQ = (uint16_t)(rollAvg * 10);  // Quantize to 0.1 degrees
      uint16_t pitchQ = (uint16_t)(pitchAvg * 10); // Quantize to 0.1 degrees
      uint16_t yawQ = (uint16_t)(yawAvg * 10);   // Quantize to 0.1 degrees
      uint16_t accelXQ = (uint16_t)(accelX_g * 100); // Quantize to 0.01g
      uint16_t accelYQ = (uint16_t)(accelY_g * 100); // Quantize to 0.01g
      uint16_t accelZQ = (uint16_t)(accelZ_g * 100); // Quantize to 0.01g
      
       static uint8_t buffer[20];
      buffer[0] = rollQ >> 8;
      buffer[1] = rollQ & 0xFF;
      buffer[2] = pitchQ >> 8;
      buffer[3] = pitchQ & 0xFF;
      buffer[4] = yawQ >> 8;
      buffer[5] = yawQ & 0xFF;
      buffer[6] = accelXQ >> 8;
      buffer[7] = accelXQ & 0xFF;
      buffer[8] = accelYQ >> 8;
      buffer[9] = accelYQ & 0xFF;
      buffer[10] = accelZQ >> 8;
      buffer[11] = accelZQ & 0xFF;
      buffer[12]=quantizedGyroX >> 8;
      buffer[13]=quantizedGyroX & 0xFF;
      buffer[14]=quantizedGyroY >> 8;
      buffer[15]=quantizedGyroY & 0xFF;
      buffer[16]=quantizedGyroZ >> 8;
      buffer[17]=quantizedGyroZ & 0xFF;
      buffer[18]=0;
      buffer[19]=0;
     // bleuart.print("x:");
      //bleuart.print(rollQ);
     // bleuart.print(pitchQ);

      //bleuart.print(yawQ);
    //  SERIAL_PORT.print("x:");
    //SERIAL_PORT.println(rollAvg);
    //SERIAL_PORT.print("y:");
    //SERIAL_PORT.println(pitchAvg);
   
      bleuart.write(buffer,sizeof(buffer));
     
      }
    
      
       rollReadings=0;
 pitchReadings=0;
 yawReadings=0;
 accelXReadings=0;
 accelYReadings=0;
 accelZReadings=0;
 totalReadings=0;
  gyroXReadings = 0;
  gyroYReadings = 0;
  gyroZReadings = 0;
     }
  }

  if (myICM.status != ICM_20948_Stat_FIFOMoreDataAvail) // If more data is available then we should read it right away - and not delay
  {
    delay(10);
  }
  //delay(100);
  //yield();
}



uint16_t conn_han;

void connect_callback(uint16_t conn_handle) {
    connect = true;
    conn_han = conn_handle;
    Serial.println("Connected!");
    txCharacteristic.notify(conn_handle, (uint8_t*)"LOLOL", 5);
    //bleuart.print("LOLOL2");
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
    Serial.println("Disconnected!");
    Serial.println(reason);
    connect = false;
    // Optionally restart advertising here
    Bluefruit.Advertising.start();
}
  void mtu_request_callback(uint16_t conn_handle, uint16_t requested_mtu)
{
    Serial.print("Requested MTU size: ");
    Serial.println(requested_mtu);
    uint16_t accepted_mtu = min(requested_mtu, 247); // or BLE_GATT_ATT_MTU_DEFAULT
//Bluefruit.conn(conn_handle)->attServer().exchangeMtuResponse(accepted_mtu);
Serial.print("Accepted MTU size: ");
Serial.println(accepted_mtu);
    // Decide how to handle it here
}
void setAccelerometerRange(uint8_t range) {
  // ICM-20948 uses register banks. The ACCEL_CONFIG register is in register bank 2 at address 0x14.
  selectBank(2); // Select register bank 2
  
  uint8_t regValue = 0;
  myICM.read(0x14, &regValue, 1); // Read the ACCEL_CONFIG register (0x14)
 Serial.print("Accepted MTU size: ");
  Serial.println(regValue);
  // Clear the current FS_SEL bits and set new range
  regValue &= ~(0x06); // Clear bits [2:1]
  regValue |= (range << 1); // Set the new range value (range shifted by 1 position)
  Serial.println(regValue);
  myICM.write(0x14, &regValue, 1); // Write back to the ACCEL_CONFIG register
  
  selectBank(0); // Go back to register bank 0
}

// Function to select the appropriate register bank
void selectBank(uint8_t bank) {
  uint8_t regValue = (bank << 4); // Shift the bank value to bits [4:6]
  myICM.write(0x7F, &regValue, 1); // Write to REG_BANK_SEL (0x7F)
}