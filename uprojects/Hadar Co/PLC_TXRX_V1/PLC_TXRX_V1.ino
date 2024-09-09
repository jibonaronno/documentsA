#define ENABLEM5

#ifdef ENABLEM5
#include <M5Atom.h>   // http://librarymanager/All#M5Atom  https://github.com/m5stack/M5Atom
#endif

#define HOST_BITRATE                115200     // UART host bitrate               
#define SIG_BITRATE                 0x05      // '0x00' - 9.6K, '0x01' - 10.4K, '0x02' - 19.2k, '0x03' - 38.4K, '0x04' - 57.6K, '0x05' - 115.2K


//Pins allocation
const int HDC = 23;        // SIG100 HOST data command pin for local READ and WRITE internal registers operations.
const int NRESET = 33;        // SIG100 NRESET pin
auto& host_serial = Serial;
auto &power_serial = Serial2;
byte  rd_val;             // Read val in SIG local read command
byte temp_byte = 0x41;


//Terminal Code Start
char frame[200];
char bufferB[200];

//Terminal Code End

void setup() {
  #ifdef ENABLEM5
  // 初期化
  M5.begin(true, false, false);  // (Serial, I2C, NeoPixel)

  // GPIO初期化
  pinMode(22, OUTPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(19, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(HDC, OUTPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(NRESET, OUTPUT); // PIN  (INPUT, OUTPUT, ANALOG)
  pinMode(21, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(25, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可
  pinMode(26, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(12, OUTPUT_OPEN_DRAIN); // IR赤外線(LOWで出力)
  digitalWrite(12, HIGH);

  //UART IF
  host_serial.begin(HOST_BITRATE, SERIAL_8N1, 19, 22); // UART bitrate interfacing with the SIG100 ('SIG_BITRATE' must be set accorodingly in define above).
  Serial.begin(HOST_BITRATE);
  //HDC pin Idle
  digitalWrite(HDC, HIGH);
  //NRESET pin Idle
  digitalWrite(NRESET, HIGH);

  delay(3);

  // SIG100 config
  YAMAR_IC_CONFIG(); // Set the SIG100 bitrate and disable loopback (default carrier frequency is 13MHz).
  #endif

  host_serial.begin(HOST_BITRATE);
  power_serial.begin(HOST_BITRATE, SERIAL_8N1, 19, 22);
}

void loop() {
//Terminal Code Start
  int8_t counter, terminal_flag;
  long previous;
  int8_t confirmation_flag = 0;
  int8_t counterB = 0;
//Terminal Code End

/* Lines commented from previous code
  Serial2.write(temp_byte);
  if (temp_byte == 0x5A)
    temp_byte = 0x0d;
  else if (temp_byte == 0x0d)
    temp_byte = 0x0a;
  else if (temp_byte == 0x0a)
    temp_byte = 0x41;
  else
    temp_byte++;
*/

  //Terminal Code Start
  previous = millis();
  
  if(host_serial.available())
  {
    do{

        if(host_serial.available() != 0){    
            frame[counter] = host_serial.read();
            counter++;
            frame[counter] = 0;
            // check if the desired flag is in the response of the module
            if (strstr(frame, "\n") != NULL)    
            {
                terminal_flag = 1;
                power_serial.println(frame);
                //Serial.println("0xEFAE02889");
                counter = 0;
            }
            previous = millis();
        }
        // Waits for the flag with time out
      }
      while((terminal_flag == 0) && ((millis() - previous) < 200));  
  }

  previous = millis();
  if(terminal_flag)
  {
    do{
        if(power_serial.available())
        {
          bufferB[counterB] = power_serial.read();
          counterB++;
          bufferB[counterB] = 0;
          if(strstr(bufferB, "\n") != NULL)
          {
            if(strstr(bufferB, "0xEFAE02889") != NULL)
            {
              host_serial.println("Received Confirmed");
              confirmation_flag = 1;
              counterB = 0;
            }
          }
          previous = millis();
        }
    }
    while((confirmation_flag == 0) && ((millis() - previous) < 2000));

    if(confirmation_flag == 0)
    {
      host_serial.println("Data Send Failed. Trying Again");
      power_serial.println(frame);
    }
    else
    {
      confirmation_flag = 0;
      terminal_flag = 0;
    }
  }
  else
  {
    counterB = 0;
    previous = millis();
    if(power_serial.available())
    {
      do{
          if(power_serial.available())
          {
            bufferB[counterB] = power_serial.read();
            counterB++;
            bufferB[counterB] = 0;
            previous = millis();
          }
      }
      while((strstr(bufferB, "\n") == NULL) && ((millis() - previous) < 1000));
      power_serial.println("0xEFAE02889");
      counterB = 0;
    }
  }



  //Terminal Code End

/* Lines commented from previous code
   if (Serial2.available()) {
     Serial.println(Serial2.read());
   }

  delay(2);
*/

}

#ifdef ENABLEM5

/*******************************************************
  Function Name: YAMAR_IC_CONFIG
  Description:  Confiugre SIG102 UART bitrate, carrier frequency and other features (see datasheet).
  Inputs:
  Outputs: None
  Notes:
  Author:
********************************************************/
void YAMAR_IC_CONFIG()
{
  WRITE_REG_CMD(0x00, (0x28 + SIG_BITRATE)); // Disable loopback  & selected bitrate
}


/*******************************************************
  Function Name: WRITE_REG_CMD
  Description:
  Inputs:
  Outputs: None
  Notes:
  Author:
********************************************************/
void WRITE_REG_CMD(byte address, byte value)
{
  digitalWrite(HDC, LOW);
  delayMicroseconds(1);
  host_serial.write(0xf5);    // WRITE-REG-COMMAND
  host_serial.flush();        // Wait for Tx to end
  host_serial.write(address); // Address of the register to write to.
  host_serial.flush();        // Wait for Tx to end
  host_serial.write(value);   // Data to write.
  host_serial.flush();        // Wait for Tx to end
  delayMicroseconds(1);
  digitalWrite(HDC, HIGH);
  delay(1); // Delay 1 msec (Mainly needed when we configure REG_2 which requires 1ms delay after carrier frequency configuration).

  // Dummy reads in case of loopback is still enabled.
  rd_val = host_serial.read();
  rd_val = host_serial.read();
  rd_val = host_serial.read();
}

/*******************************************************
  Function Name: READ_REG_CMD
  Description:
  Inputs:
  Outputs: FALSE -ERROR , TRUE - SUCC
  Notes:
  Author:
********************************************************/
boolean READ_REG_CMD(byte address)
{
  boolean res = false;
  digitalWrite(HDC, LOW);
  delayMicroseconds(1);
  host_serial.write(0xfd); // READ-REG-COMMAND
  host_serial.flush(); // Wait for Tx to end
  host_serial.write(address); // Address of the register to read from
  host_serial.flush(); // Wait for Tx to end
  // Wait for 1 read value byte
  delay(2); // Delay 2 msec
  if (host_serial.available() > 0)
  {
    // read the incoming bytes:
    rd_val = host_serial.read(); // Read value of the register
    res = true;
  }
  else
    res = false; // Read time our err

  delayMicroseconds(1);
  digitalWrite(HDC, HIGH);
  delayMicroseconds(1);

  return res;
}
#endif
