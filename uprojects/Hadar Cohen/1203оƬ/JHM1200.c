/*
****************************************************************************
*
* JHM1200.c
* Date: 2017/02/04
* Revision: 1.0.0
*
* Usage: Sensor Driver file for JHM1200
*
**************************************************************************/
#include "JHM1200.h"
#include "JHM1200_IIC.h"

// Define the upper and lower limits of the calibration pressure
#define PMIN 20000.0  //Full range pressure for example 20Kpa
#define PMAX 120000.0  //Zero Point Pressure Value, for example 120Kpa
#define DMIN 3355443.0  //AD value corresponding to pressure zero, for example 20%AD=2^24*0.2
#define DMAX 13421772.0  //AD Value Corresponding to Full Pressure Range, for example 80%AD=2^24*0.8

//The 7-bit IIC address of the JHM1200 is 0x78
uint8 Device_Address = 0x78 << 1;

//Delay function needs to be defined
void DelayMs(uint8 count)
{
}

//Read the status of IIC and judge whether IIC is busy
uint8 JHM1200_IsBusy(void)
{
	uint8 status;
	BSP_IIC_Read(Device_Address, &status, 1);
	status = (status >> 5) & 0x01;
	return status;
}

/**
  * @brief Using the 0xAC command to calculate the actual pressure and temperature using the JHM1200 internal algorithm
  * @note  Send 0xAC, read IIC status until IIC is not busy
  *	@note  The returned data is a total of six bytes, in order: status word, three-byte pressure value, two-byte temperature value
  * @note  The returned three-byte pressure value is proportional to the 24-bit maximum value 16777216. According to this ratio, 
           the actual pressure value is again converted according to the calibration range.
  * @note  The returned two-byte temperature value is proportional to the 16-bit maximum value 65536. According to this ratio, 
           the actual pressure value is again converted according to the calibration range.
  * @note  Zero pressure point and full pressure point of calibration pressure correspond to 20kpa and 120Kpa, respectively   
  * @note  The zero point of the calibration temperature is -40°C and the full point is 150°C
  * @note  The pressure actual value is calculated according to the span pressure unit is Pa, temperature actual value temp unit is 0.01°C
  */
void JHM1200_get_cal(void)
{
	uint8 buffer[6] = {0};
	uint32 Dtest = 0;
	uint16 temp_raw = 0;
	double pressure = 0.0, temp = 0.0;

	//Send 0xAC command and read the returned six-byte data
	buffer[0] = 0xAC;
	BSP_IIC_Write(Device_Address, buffer, 1);
	DelayMs(5);
	while (1)
	{
		if (JHM1200_IsBusy())
		{
			DelayMs(1);
		}
		else
			break;
	}
	BSP_IIC_Read(Device_Address, buffer, 6);

	//The returned pressure and temperature values are converted into actual values according to the calibration range
	Dtest = ((uint32)buffer[1] << 16) | ((uint16)buffer[2] << 8) | buffer[3];
	temp_raw = ((uint16)buffer[4] << 8) | (buffer[5] << 0);
	pressure = (PMAX-PMIN)/(DMAX-DMIN)*(Dtest-DMIN)+PMIN;
	temp = (double)temp_raw / 65536;
	temp = temp * 19000 - 4000;
}
