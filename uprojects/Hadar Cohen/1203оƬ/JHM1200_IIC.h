/*
****************************************************************************
*
* JHM1200_IIC.h
* Date: 2015/06/26
* Revision: 1.0.0
*
* Usage: IIC read and write interface
*
**************************************************************************/
#ifndef __JHM1200_IIC_H_
#define __JHM1200_IIC_H_

uint8 BSP_IIC_Write(uint8 IIC_Address, uint8 *buffer, uint8 count);
uint8 BSP_IIC_Read(uint8 IIC_Address, uint8 *buffer, uint8 count);

#endif
