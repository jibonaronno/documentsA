/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : emif.c
 *
 * *************************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include <F28x_Project.h>   // Device Headerfile and Examples Include File
#include <F2837xS_Emif.h>   // Device Headerfile and Examples Include File

#include "main.h"
#include "tigerwin.h"
#include "emif.h"
#include "adc.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define MPRAM_ADDR  ((UINT32)0x00100000)
#define ADC_ADDR    ((UINT32)0x00300000)
#define W5300_ADDR  ((UINT32)0x00380000)

//#define BUFFER_SIZE        0x100
//#define BUFFER_SIZE        8192       // Test 프로그램 용
//#define BUFFER_SIZE        64

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

UINT32 WriteReadStatus = 0;
UINT32 Index = 0;


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
void Init_EM1( void );

void setup_emif1_pinmux_async_16bit(Uint16 cpu_sel);

void Emif_Make( void );
void Conv_MramRd( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam );
void Conv_MramWr( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam );
void Conv_MramRdXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs );
void Conv_MramWrXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs );
void Init_FactoryMramData( void );



// CS2 MRAM
// CS3 AD7606
// CS4 W5300
void Init_EM1( void )
{
  UINT16  ErrCount = 0;

  EALLOW;
  ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;
  EDIS;

  EALLOW;

  Emif1ConfigRegs.EMIF1ACCPROT0.all = 0x0;
  if( Emif1ConfigRegs.EMIF1ACCPROT0.all != 0x0 )
    ErrCount++;

  Emif1ConfigRegs.EMIF1COMMIT.all = 0x1;
  if( Emif1ConfigRegs.EMIF1COMMIT.all != 0x1 )
    ErrCount++;

  Emif1ConfigRegs.EMIF1LOCK.all = 0x1;
  if( Emif1ConfigRegs.EMIF1LOCK.all != 1 )
    ErrCount++;

  EDIS;

  setup_emif1_pinmux_async_16bit( 0 );

// 20220322
// MRAM 2word 당 1개 Data
// W5300 4word 당 1개 Data
  Emif1Regs.ASYNC_CS2_CR.all = 0x00A00501;    // CS2(MRAM 설정) // CS 180ns~200ns 추후 튜닝 해야 될 수도 있음 / 저장 속도가 부족할 경우
  Emif1Regs.ASYNC_CS3_CR.all = 0x00200181;    // CS3(ADC 설정)
  Emif1Regs.ASYNC_CS4_CR.all = 0x00500301;    // CS4(W5300 설정) // CS 90ns

#if(0)
  if( ErrCount == 0x0 )
    sSta.bTestFail = 0;
  else
    sSta.bTestFail = 1;
#endif

}



void Emif_MagicCheck( void )
{
  Conv_MramRd( (UINT16 *)&pMram->wMagic, 6, (UINT16 *)&sSet.wMagic );

  if( sSet.wMagic != eMAGIC_CODE || sSet.wClear != eCLEAR_CODE )
  {
    if( sSet.wMagic != eMAGIC_CODE )
    {
      Init_FactoryMramData( );

      Conv_MramWr   ( (UINT16 *)&pMram->wMagic,         6,    (UINT16 *)&sSet.wMagic  );
      Conv_MramWrXCs( (UINT16 *)&pMram->wPass,          1,    (UINT16 *)&sSet.wPass,      (UINT16 *)&pMram->wPassXCs,     (UINT16 *)&sSet.wPassXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->wId,            8,    (UINT16 *)&sSet.wId,        (UINT16 *)&pMram->wCommXCs,     (UINT16 *)&sSet.wCommXCs    );
      Conv_MramWr   ( (UINT16 *)&pMram->wModel,         8,    (UINT16 *)&sDsp.wModel  );
      Conv_MramWr   ( (UINT16 *)&pMram->wSerial,        16,   (UINT16 *)&sDsp.wSerial );
      Conv_MramWrXCs( (UINT16 *)&pMram->wMac[0],        3,    (UINT16 *)&sSet.wMac[0],    (UINT16 *)&pMram->wMacXCs,      (UINT16 *)&sSet.wMacXCs     );
      Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,        9,    (UINT16 *)&sDsp.wIpAddr,    (UINT16 *)&pMram->wEthXCs,      (UINT16 *)&sDsp.wEthXCs     );
      Conv_MramWrXCs( (UINT16 *)&pMram->wTrig,          1,    (UINT16 *)&sDsp.wTrig,      (UINT16 *)&pMram->wTrigXCs,     (UINT16 *)&sDsp.wTrigXCs    );
      Conv_MramWr   ( (UINT16 *)&pMram->wChat,          1,    (UINT16 *)&sSet.wChat );
      Conv_MramWrXCs( (UINT16 *)&pMram->wDebo,          1,    (UINT16 *)&sDsp.wDebo,      (UINT16 *)&pMram->wDeboXCs,     (UINT16 *)&sDsp.wDeboXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->wTrip[0*2],     3,    (UINT16 *)&sDsp.wTrip[0],   (UINT16 *)&pMram->wTripXCs,     (UINT16 *)&sDsp.wTripXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->wNo100ms,       2,    (UINT16 *)&sSet.wNo100ms,   (UINT16 *)&pMram->wNoXCs,       (UINT16 *)&sSet.wNoXCs      );
      Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[1*2*2],  3*2,  (UINT16 *)&sSet.fRatio[1],  (UINT16 *)&pMram->wDcRatioXCs,  (UINT16 *)&sSet.wDcRatioXCs );
      Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[4*2*2],  4*2,  (UINT16 *)&sSet.fRatio[4],  (UINT16 *)&pMram->wAcRatioXCs,  (UINT16 *)&sSet.wAcRatioXCs );
      Conv_MramWr   ( (UINT16 *)&pMram->wZeR[0*2],      1,    (UINT16 *)&sSet.wZeR[0] );
      Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[1*2],      3,    (UINT16 *)&sSet.wZeR[1],    (UINT16 *)&pMram->wZeRDcXCs,    (UINT16 *)&sSet.wZeRDcXCs   );
      Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[1*2],      3,    (UINT16 *)&sSet.wSpR[1],    (UINT16 *)&pMram->wSpRDcXCs,    (UINT16 *)&sSet.wSpRDcXCs   );
      Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[4*2],      4,    (UINT16 *)&sSet.wZeR[4],    (UINT16 *)&pMram->wZeRAcXCs,    (UINT16 *)&sSet.wZeRAcXCs   );
      Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[4*2],      4,    (UINT16 *)&sSet.wSpR[4],    (UINT16 *)&pMram->wSpRAcXCs,    (UINT16 *)&sSet.wSpRAcXCs   );
      Conv_MramWrXCs( (UINT16 *)&pMram->fZe[1*2*2],     3*2,  (UINT16 *)&sSet.fZe[1],     (UINT16 *)&pMram->wZeDcXCs,     (UINT16 *)&sSet.wZeDcXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->fSp[1*2*2],     3*2,  (UINT16 *)&sSet.fSp[1],     (UINT16 *)&pMram->wSpDcXCs,     (UINT16 *)&sSet.wSpDcXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2],     4*2,  (UINT16 *)&sSet.fZe[4],     (UINT16 *)&pMram->wZeAcXCs,     (UINT16 *)&sSet.wZeAcXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2],     4*2,  (UINT16 *)&sSet.fSp[4],     (UINT16 *)&pMram->wSpAcXCs,     (UINT16 *)&sSet.wSpAcXCs    );
      Conv_MramWrXCs( (UINT16 *)&pMram->fPh[4*2*2],     4*2,  (UINT16 *)&sSet.fPh[4],     (UINT16 *)&pMram->wPhXCs,       (UINT16 *)&sSet.wPhXCs      );
    }
    else if( sSet.wClear != eCLEAR_CODE )
    {
    }
  }

  sCnt.wEv = pMram->wEv;
  sCnt.wFaNum = pMram->wFaNum;
  sCnt.wFaMb = pMram->wFaMb;
  sCnt.wFa = sCnt.wFaEnd = pMram->wFaEnd;
//  sCnt.wFaEnd = pMram->wFaEnd;

  Conv_MramRd   ( (UINT16 *)&pMram->wMagic,         6,    (UINT16 *)&sSet.wMagic  );
  Conv_MramRdXCs( (UINT16 *)&pMram->wPass,          1,    (UINT16 *)&sSet.wPass,      (UINT16 *)&pMram->wPassXCs,     (UINT16 *)&sSet.wPassXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->wId,            8,    (UINT16 *)&sSet.wId,        (UINT16 *)&pMram->wCommXCs,     (UINT16 *)&sSet.wCommXCs    );
  Conv_MramRd   ( (UINT16 *)&pMram->wModel,         8,    (UINT16 *)&sDsp.wModel  );
  Conv_MramRd   ( (UINT16 *)&pMram->wSerial,        16,   (UINT16 *)&sDsp.wSerial );
  Conv_MramRdXCs( (UINT16 *)&pMram->wMac[0],        3,    (UINT16 *)&sSet.wMac[0],    (UINT16 *)&pMram->wMacXCs,      (UINT16 *)&sSet.wMacXCs     );
  Conv_MramRdXCs( (UINT16 *)&pMram->wIpAddr,        9,    (UINT16 *)&sDsp.wIpAddr,    (UINT16 *)&pMram->wEthXCs,      (UINT16 *)&sDsp.wEthXCs     );
  Conv_MramRdXCs( (UINT16 *)&pMram->wTrig,          1,    (UINT16 *)&sDsp.wTrig,      (UINT16 *)&pMram->wTrigXCs,     (UINT16 *)&sDsp.wTrigXCs    );
  Conv_MramRd   ( (UINT16 *)&pMram->wChat,          1,    (UINT16 *)&sSet.wChat );
  Conv_MramRdXCs( (UINT16 *)&pMram->wDebo,          1,    (UINT16 *)&sDsp.wDebo,      (UINT16 *)&pMram->wDeboXCs,     (UINT16 *)&sDsp.wDeboXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->wTrip[0*2],     3,    (UINT16 *)&sDsp.wTrip[0],   (UINT16 *)&pMram->wTripXCs,     (UINT16 *)&sDsp.wTripXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->wNo100ms,       2,    (UINT16 *)&sSet.wNo100ms,   (UINT16 *)&pMram->wNoXCs,       (UINT16 *)&sSet.wNoXCs      );
  Conv_MramRdXCs( (UINT16 *)&pMram->fRatio[1*2*2],  3*2,  (UINT16 *)&sSet.fRatio[1],  (UINT16 *)&pMram->wDcRatioXCs,  (UINT16 *)&sSet.wDcRatioXCs );
  Conv_MramRdXCs( (UINT16 *)&pMram->fRatio[4*2*2],  4*2,  (UINT16 *)&sSet.fRatio[4],  (UINT16 *)&pMram->wAcRatioXCs,  (UINT16 *)&sSet.wAcRatioXCs );
  Conv_MramRd   ( (UINT16 *)&pMram->wZeR[0*2],      1,    (UINT16 *)&sSet.wZeR[0] );
  Conv_MramRdXCs( (UINT16 *)&pMram->wZeR[1*2],      3,    (UINT16 *)&sSet.wZeR[1],    (UINT16 *)&pMram->wZeRDcXCs,    (UINT16 *)&sSet.wZeRDcXCs   );
  Conv_MramRdXCs( (UINT16 *)&pMram->wSpR[1*2],      3,    (UINT16 *)&sSet.wSpR[1],    (UINT16 *)&pMram->wSpRDcXCs,    (UINT16 *)&sSet.wSpRDcXCs   );
  Conv_MramRdXCs( (UINT16 *)&pMram->wZeR[4*2],      4,    (UINT16 *)&sSet.wZeR[4],    (UINT16 *)&pMram->wZeRAcXCs,    (UINT16 *)&sSet.wZeRAcXCs   );
  Conv_MramRdXCs( (UINT16 *)&pMram->wSpR[4*2],      4,    (UINT16 *)&sSet.wSpR[4],    (UINT16 *)&pMram->wSpRAcXCs,    (UINT16 *)&sSet.wSpRAcXCs   );
  Conv_MramRdXCs( (UINT16 *)&pMram->fZe[1*2*2],     3*2,  (UINT16 *)&sSet.fZe[1],     (UINT16 *)&pMram->wZeDcXCs,     (UINT16 *)&sSet.wZeDcXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->fSp[1*2*2],     3*2,  (UINT16 *)&sSet.fSp[1],     (UINT16 *)&pMram->wSpDcXCs,     (UINT16 *)&sSet.wSpDcXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->fZe[4*2*2],     4*2,  (UINT16 *)&sSet.fZe[4],     (UINT16 *)&pMram->wZeAcXCs,     (UINT16 *)&sSet.wZeAcXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->fSp[4*2*2],     4*2,  (UINT16 *)&sSet.fSp[4],     (UINT16 *)&pMram->wSpAcXCs,     (UINT16 *)&sSet.wSpAcXCs    );
  Conv_MramRdXCs( (UINT16 *)&pMram->fPh[4*2*2],     4*2,  (UINT16 *)&sSet.fPh[4],     (UINT16 *)&pMram->wPhXCs,       (UINT16 *)&sSet.wPhXCs      );

  sDsp.wVersion     = eVERSION;
  sDsp.lYYYYMMDD    = eYYYYMMDD;

}

void Conv_MramRd( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam )
{
  UINT16  i;

  for( i=0; i<i_wLen; i++ )
  {
    i_pwRam[i] = *i_pwMram;
    i_pwMram += 2;
  }
}
void Conv_MramWr( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam )
{
  UINT16  i;

  for( i=0; i<i_wLen; i++ )
  {
    *i_pwMram = i_pwRam[i];
    i_pwMram += 2;
  }
}
void Conv_MramRdXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs )
{
  UINT16  i;

  for( i=0; i<i_wLen; i++ )
  {
    i_pwRam[i] = *i_pwMram;
    i_pwMram += 2;
  }
  *i_pwXCs = *i_pwMramXCs;
}
void Conv_MramWrXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs )
{
  UINT16  i, i_wXCs = 0;

  for( i=0; i<i_wLen; i++ )
  {
    *i_pwMram = i_pwRam[i];
    i_wXCs += i_pwRam[i];
    i_pwMram += 2;
  }
  *i_pwMramXCs = *i_pwXCs = ~i_wXCs;
}


char  bModel[] = "SPDS-ACQ        ";
char  bSerial[] = "ACQ-SPDS-K-2022-0001            ";
void Init_FactoryMramData( void )
{
  UINT16  i;

  sSet.wMagic = eSV_MAGIC_DEF;
  sSet.wClear = eSV_CLEAR_DEF;
  sSet.wPcb   = eSV_PCB_DEF;
  sSet.wVer   = eSV_VER_DEF;
  sSet.wYYYY  = eSV_YYYY_DEF;
  sSet.wMMDD  = eSV_MMDD_DEF;

  sSet.wPass  = eSV_PASS_DEF;
  sSet.wId    = eSV_ID_DEF;
  sSet.wBps   = eSV_BPS_DEF;
  sSet.wN20   = eSV_NOP_DEF;
  sSet.wN21   = eSV_NOP_DEF;
  sSet.wN22   = eSV_NOP_DEF;
  sSet.wN23   = eSV_NOP_DEF;
  sSet.wN24   = eSV_NOP_DEF;
  sSet.wN25   = eSV_NOP_DEF;

  sSet.wNo100ms = eSV_NO100MS_DEF;
  sSet.wNo500ms = eSV_NO500MS_DEF;
//  sSet.wDeboXCs;

  for( i=1; i<1+3; i++ )
    sSet.fRatio[i] = eSV_DCRATIO_DEF;
  sSet.fRatio[4] = eSV_ACVRATIO_DEF;
  for( i=5; i<5+3; i++ )
    sSet.fRatio[i] = eSV_ACIRATIO_DEF;

  for( i=0; i<4; i++ )
  {
    sSet.wZeR[i] = eSV_DCZER_DEF;
    sSet.wSpR[i] = eSV_DCSPR_DEF;
    sSet.fZe[i]  = eSV_DCZE_DEF;
    sSet.fSp[i]  = eSV_DCSP_DEF;
  }
  i = 4;
  sSet.wZeR[i] = eSV_ACVZER_DEF;
  sSet.wSpR[i] = eSV_ACVSPR_DEF;
  sSet.fZe[i]  = eSV_ACVZE_DEF;
  sSet.fSp[i]  = eSV_ACVSP_DEF;
  for( i=5; i<8; i++ )
  {
    sSet.wZeR[i] = eSV_ACIZER_DEF;
    sSet.wSpR[i] = eSV_ACISPR_DEF;
    sSet.fZe[i]  = eSV_ACIZE_DEF;
    sSet.fSp[i]  = eSV_ACISP_DEF;
  }
  for( i=0; i<8; i++ )
    sSet.fPh[i]  = eSV_PH_DEF;


  sDsp.wModel[0]    = (bModel[0 ] <<8) | bModel[1 ];
  sDsp.wModel[1]    = (bModel[2 ] <<8) | bModel[3 ];
  sDsp.wModel[2]    = (bModel[4 ] <<8) | bModel[5 ];
  sDsp.wModel[3]    = (bModel[6 ] <<8) | bModel[7 ];
  sDsp.wModel[4]    = (bModel[8 ] <<8) | bModel[9 ];
  sDsp.wModel[5]    = (bModel[10] <<8) | bModel[11];
  sDsp.wModel[6]    = (bModel[12] <<8) | bModel[13];
  sDsp.wModel[7]    = (bModel[14] <<8) | bModel[15];
#if(1)
  sDsp.wSerial[0 ]  = (bSerial[0 ] <<8) | bSerial[1 ];
  sDsp.wSerial[1 ]  = (bSerial[2 ] <<8) | bSerial[3 ];
  sDsp.wSerial[2 ]  = (bSerial[4 ] <<8) | bSerial[5 ];
  sDsp.wSerial[3 ]  = (bSerial[6 ] <<8) | bSerial[7 ];
  sDsp.wSerial[4 ]  = (bSerial[8 ] <<8) | bSerial[9 ];
  sDsp.wSerial[5 ]  = (bSerial[10] <<8) | bSerial[11];
  sDsp.wSerial[6 ]  = (bSerial[12] <<8) | bSerial[13];
  sDsp.wSerial[7 ]  = (bSerial[14] <<8) | bSerial[15];
  sDsp.wSerial[8 ]  = (bSerial[16] <<8) | bSerial[17];
  sDsp.wSerial[9 ]  = (bSerial[18] <<8) | bSerial[19];
  sDsp.wSerial[10]  = (bSerial[20] <<8) | bSerial[21];
  sDsp.wSerial[11]  = (bSerial[22] <<8) | bSerial[23];
  sDsp.wSerial[12]  = (bSerial[24] <<8) | bSerial[25];
  sDsp.wSerial[13]  = (bSerial[26] <<8) | bSerial[27];
  sDsp.wSerial[14]  = (bSerial[28] <<8) | bSerial[29];
  sDsp.wSerial[15]  = (bSerial[30] <<8) | bSerial[31];
#else
  UINT16  i_wSerial = ( '0' << 8 ) + '1';
  for( i=0; i<16; i++ )
  {
    sDsp.wSerial[i]   = i_wSerial;
    i_wSerial += 0x0202;
  }
#endif

  sSet.wMac[0]      = 0x1011;
  sSet.wMac[1]      = 0x1213;
  sSet.wMac[2]      = 0x1415;

  sDsp.wIpAddr[0]    = eSV_IP_H_DEF;
  sDsp.wIpAddr[1]    = eSV_IP_L_DEF;
  sDsp.wSubMask[0]   = eSV_SUB_H_DEF;
  sDsp.wSubMask[1]   = eSV_SUB_L_DEF;
  sDsp.wDefGate[0]   = eSV_GAT_H_DEF;
  sDsp.wDefGate[1]   = eSV_GAT_L_DEF;
  sDsp.wPortNum      = eSV_PORT_DEF;
  sDsp.wLocIpAddr[0]  = eSV_LOC_H_DEF;
  sDsp.wLocIpAddr[1]  = eSV_LOC_L_DEF;
//  sSet.wEthXCs;      // wIpAddress[0] ~ LocalIpAddr[1]

  sDsp.wTrig =  eSV_TRIG_DEF;
//  sSet.wTripXCs  = ~eSV_TRIG_DEF;
  sDsp.wDebo =  eSV_DEBO_DEF;
//  sSet.wDeboXCs  = ~eSV_DEBO_DEF;
  for( i=0; i<3; i++ )
    sDsp.wTrip[i] = eSV_TRIP_DEF;          // 5(0.5)A
  sSet.wChat =  eSV_CHAT_DEF;

}


/******************************* TIGERWIN END OF FILE *******************************/
