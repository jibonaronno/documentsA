/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name	  : modbus.h
 *
 * *************************************************************************/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MODBUS_H
#define __MODBUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tigerwin.h"
#include "sci.h"


/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

typedef struct _MODBUS_COUNT
{
  UINT16            wErr;
  UINT16            wRxData;
  UINT16            wStart;
  UINT8             bNo;

  UINT16            wLen;       // modbus Byte Count 저장

  UINT8             bInitFail[18];  // 전자저항 설정 안될 때
  UINT8             bDiscord[18];   // 전자저항 설정값 불일치 Count

  UINT16            wInput;
} MODBUS_COUNT;


typedef struct _MODBUS_PIT
{
  UINT16            *pwPit;           // [0]Setting, [1]계측, [2]Fault List, [3]Fault Wave
  UINT16            wSta;             // Start Address
  UINT16            wEnd;             // End Address
} MODBUS_PIT;
enum
{
  eMB_ADDR_12,
  eMB_ADDR_20,
  eMB_ADDR_302,
  eMB_ADDR_STEP_LEN,
};
#define eMODBUS_RX_LEN    256
enum    // sMb.lStatus
{
  eMB_STAT_B_VAP        = BIT0,
  eMB_STAT_B_VAN        = BIT1,
  eMB_STAT_B_VBP        = BIT2,
  eMB_STAT_B_VBN        = BIT3,
  eMB_STAT_B_VCP        = BIT4,
  eMB_STAT_B_VCN        = BIT5,
  eMB_STAT_B_IAPP       = BIT6,
  eMB_STAT_B_IAPN       = BIT7,
  eMB_STAT_B_IAMP       = BIT8,
  eMB_STAT_B_IAMN       = BIT9,
  eMB_STAT_B_IBPP       = BIT10,
  eMB_STAT_B_IBPN       = BIT11,
  eMB_STAT_B_IBMP       = BIT12,
  eMB_STAT_B_IBMN       = BIT13,
  eMB_STAT_B_ICPP       = BIT14,
  eMB_STAT_B_ICPN       = BIT15,
  eMB_STAT_B_ICMP       = BIT16,
  eMB_STAT_B_ICMN       = BIT17,
  eMB_STAT_B_P5V        = BIT20,
  eMB_STAT_B_N5V        = BIT21,
};
typedef struct _MODBUS_REG
{
  MODBUS_COUNT      Cnt;

  UINT8             bId;
  UINT8             bFn;
  UINT16            wAddr;
  UINT16            wLen;

  UINT8             bRxBCount;
  UINT8             bRxData[eMODBUS_RX_LEN];
  UINT16            wRxCrc;
  UINT16            wRxLen;

  UINT8             bStep;

  UINT8             bRegWr[18];
  UINT16            wMainStatus;

  UINT8             bRegRd[18];
  UINT32            lStatFail;            // I2C Fail
  UINT32            lStatDiscord;         // 쓴 값과 다를 때
  UINT8             bStatInTemp;          // DC5V Input Temp (P5V, N5V)
  UINT32            lStatInput;           // DC5V Input (P5V, N5V)
  UINT32            lStatus;              // 3가지(I2C Fail(0~17), 다를때(0~17), Input(20~21)) + 1가지(Version(24~31)) OR

  MODBUS_PIT        Pit[10];
  UINT16            wNo;                  // Point No

} MODBUS_REG;
extern MODBUS_REG     sMb;




/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

extern void Modbus_Data( void );

extern void Init_Modbus( void );

extern void Modbus_RxMake( ETHER_REG *pSci );

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_H */

/******************************* TIGERWIN END OF FILE *******************************/
