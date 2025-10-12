/*
****************************************************************************
*
* JHM1200_IIC.c
* Date: 2015/06/26
* Revision: 1.0.0
*
* Usage: IIC read and write interface
*
**************************************************************************/
#include "JHM1200_IIC.h"

//IIC clock line
sbit SCL = P1 ^ 1;

//IIC data line
sbit SDA = P1 ^ 0;

//Set the input and output mode of IIC data pin
#define Set_SDA_INPUT() \
	P1MDOUT &= 0xFE;    \
	P1 |= 0X01
#define Set_SDA_OUTPUT() P1MDOUT |= 0x01;

////Delay function needs to be defined
void DelayUs(unsigned char i)
{
}

//Start signal
void Start(void)
{
	SDA = 1;
	DelayUs(2);
	SCL = 1;
	DelayUs(2);
	SDA = 0;
	DelayUs(2);
	SCL = 0;
}

//Stop signal
void Stop(void)
{
	Set_SDA_OUTPUT();
	SDA = 0;
	DelayUs(2);
	SCL = 1;
	DelayUs(2);
	SDA = 1;
	DelayUs(2);
}

//Read ACK signal
unsigned char Check_ACK(void)
{
	unsigned char ack;
	Set_SDA_INPUT();
	SCL = 1;
	DelayUs(2);
	ack = SDA;
	SCL = 0;
	Set_SDA_OUTPUT();
	return ack;
}

//Send ACK signal
void Send_ACK(void)
{
	Set_SDA_OUTPUT();
	SDA = 0;
	DelayUs(2);
	SCL = 1;
	DelayUs(2);
	SCL = 0;
	DelayUs(2);
}

//Send one byte
void SendByte(unsigned char byte)
{
	unsigned char i = 0;
	Set_SDA_OUTPUT();
	do
	{
		if (byte & 0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		DelayUs(2);
		SCL = 1;
		DelayUs(2);
		byte <<= 1;
		i++;
		SCL = 0;
	} while (i < 8);
	SCL = 0;
}

//Receive one byte
unsigned char ReceiveByte(void)
{
	unsigned char i = 0, tmp = 0;
	Set_SDA_INPUT();
	do
	{
		tmp <<= 1;
		SCL = 1;
		DelayUs(2);
		if (SDA)
		{
			tmp |= 1;
		}
		SCL = 0;
		DelayUs(2);
		i++;
	} while (i < 8);
	return tmp;
}

//Write a byte of data through IIC
uint8 BSP_IIC_Write(uint8 address, uint8 *buf, uint8 count)
{
	unsigned char timeout, ack;
	address &= 0xFE;
	Start();
	DelayUs(2);
	SendByte(address);
	Set_SDA_INPUT();
	DelayUs(2);
	timeout = 0;
	do
	{
		ack = Check_ACK();
		timeout++;
		if (timeout == 10)
		{
			Stop();
			return 1;
		}
	} while (ack);
	while (count)
	{
		SendByte(*buf);
		Set_SDA_INPUT();
		DelayUs(2);
		timeout = 0;
		do
		{
			ack = Check_ACK();
			timeout++;
			if (timeout == 10)
			{
				return 2; 
			}
		} while (0);
		buf++;
		count--;
	}
	Stop();
	return 0;
}

//Read a byte of data through IIC
uint8 BSP_IIC_Read(uint8 address, uint8 *buf, uint8 count)
{
	unsigned char timeout, ack;
	address |= 0x01;
	Start();
	SendByte(address);
	Set_SDA_INPUT();
	DelayUs(2);
	timeout = 0;
	do
	{
		ack = Check_ACK();
		timeout++;
		if (timeout == 4)
		{
			Stop();
			return 1; 
		}
	} while (ack);
	DelayUs(2);
	while (count)
	{
		*buf = ReceiveByte();
		if (count != 1)
			Send_ACK();
		buf++;
		count--;
	}
	Stop();
	return 0;
}
