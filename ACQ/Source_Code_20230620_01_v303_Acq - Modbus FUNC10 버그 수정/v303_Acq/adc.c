/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : adc.c
 *
 * *************************************************************************/ 


#include <F28x_Project.h>
#include <math.h>               // TMU math Header
#include <float.h>              // float Header

#include "main.h"
#include "tigerwin.h"
#include "adc.h"
#include "sci.h"


ADC_REG       sAdc;
//ADC_DATA      *pAdc;

//ADCLOW_DATA   *pAdcLow;


#define eADC_MINMAX_FILTER      1       // Adc Data 4 개 중 Min Max 뺀 2개 Data
#define eADC_ERROR_CHECK        1       // Adc Error 구분하여 2개 버퍼 중 하나로 동작 하게 작업





//#define eADC_READ_TIME          5       // ADC Read Time
#define eADC_READ_CNT           8       // ADC Read 회수


void Adc_DataFix( void );
//#pragma CODE_SECTION( Adc_DataFix, ".TI.ramfunc" );


void Adc_Read( void );
#pragma CODE_SECTION( Adc_Read, ".TI.ramfunc" );
void Adc_LowDataRead( void );
#pragma CODE_SECTION( Adc_LowDataRead, ".TI.ramfunc" );

void Adc_Make( void );
#pragma CODE_SECTION( Adc_Make, ".TI.ramfunc" );
void Fault_Make( void );
void FaultWr_Start( UINT16 i_wType );
void FaultWr_Run( UINT16 i_wNo );
void Adc_Conv( void );
#pragma CODE_SECTION( Adc_Conv, ".TI.ramfunc" );
void Dft_Conv( UINT8 i_bCh, UINT16 i_wPoint );
#pragma CODE_SECTION( Dft_Conv, ".TI.ramfunc" );
void Value_Real( void );
#pragma CODE_SECTION( Value_Real, ".TI.ramfunc" );
void Phase_Gain( void );
#pragma CODE_SECTION( Phase_Gain, ".TI.ramfunc" );





float fSin[eADC_SAMPLE] = {
//1               2               3               4               5               6               7               8
  0, 0.049067674,    0.09801714,     0.146730474,    0.195090322,    0.24298018,     0.290284677,    0.336889853,    0.382683432,
  0.427555093,    0.471396737,    0.514102744,    0.555570233,    0.595699304,    0.634393284,    0.671558955,    0.707106781,
  0.740951125,    0.773010453,    0.803207531,    0.831469612,    0.85772861,     0.881921264,    0.903989293,    0.923879533,
  0.941544065,    0.956940336,    0.970031253,    0.98078528,     0.98917651,     0.995184727,    0.998795456,    1,
  0.998795456,    0.995184727,    0.98917651,     0.98078528,     0.970031253,    0.956940336,    0.941544065,    0.923879533,
  0.903989293,    0.881921264,    0.85772861,     0.831469612,    0.803207531,    0.773010453,    0.740951125,    0.707106781,
  0.671558955,    0.634393284,    0.595699304,    0.555570233,    0.514102744,    0.471396737,    0.427555093,    0.382683432,
  0.336889853,    0.290284677,    0.24298018,     0.195090322,    0.146730474,    0.09801714,     0.049067674,    1.22515E-16,
  -0.049067674,   -0.09801714,    -0.146730474,   -0.195090322,   -0.24298018,    -0.290284677,   -0.336889853,   -0.382683432,
  -0.427555093,   -0.471396737,   -0.514102744,   -0.555570233,   -0.595699304,   -0.634393284,   -0.671558955,   -0.707106781,
  -0.740951125,   -0.773010453,   -0.803207531,   -0.831469612,   -0.85772861,    -0.881921264,   -0.903989293,   -0.923879533,
  -0.941544065,   -0.956940336,   -0.970031253,   -0.98078528,    -0.98917651,    -0.995184727,   -0.998795456,   -1,
  -0.998795456,   -0.995184727,   -0.98917651,    -0.98078528,    -0.970031253,   -0.956940336,   -0.941544065,   -0.923879533,
  -0.903989293,   -0.881921264,   -0.85772861,    -0.831469612,   -0.803207531,   -0.773010453,   -0.740951125,   -0.707106781,
  -0.671558955,   -0.634393284,   -0.595699304,   -0.555570233,   -0.514102744,   -0.471396737,   -0.427555093,   -0.382683432,
  -0.336889853,   -0.290284677,   -0.24298018,    -0.195090322,   -0.146730474,   -0.09801714,    -0.049067674,   
};

float fCos[eADC_SAMPLE] = {
//1               2               3               4               5               6               7               8
  1, 0.998795456,    0.995184727,    0.98917651,     0.98078528,     0.970031253,    0.956940336,    0.941544065,    0.923879533,
  0.903989293,    0.881921264,    0.85772861,     0.831469612,    0.803207531,    0.773010453,    0.740951125,    0.707106781,
  0.671558955,    0.634393284,    0.595699304,    0.555570233,    0.514102744,    0.471396737,    0.427555093,    0.382683432,
  0.336889853,    0.290284677,    0.24298018,     0.195090322,    0.146730474,    0.09801714,     0.049067674,    6.12574E-17,
  -0.049067674,   -0.09801714,    -0.146730474,   -0.195090322,   -0.24298018,    -0.290284677,   -0.336889853,   -0.382683432,
  -0.427555093,   -0.471396737,   -0.514102744,   -0.555570233,   -0.595699304,   -0.634393284,   -0.671558955,   -0.707106781,
  -0.740951125,   -0.773010453,   -0.803207531,   -0.831469612,   -0.85772861,    -0.881921264,   -0.903989293,   -0.923879533,
  -0.941544065,   -0.956940336,   -0.970031253,   -0.98078528,    -0.98917651,    -0.995184727,   -0.998795456,   -1,
  -0.998795456,   -0.995184727,   -0.98917651,    -0.98078528,    -0.970031253,   -0.956940336,   -0.941544065,   -0.923879533,
  -0.903989293,   -0.881921264,   -0.85772861,    -0.831469612,   -0.803207531,   -0.773010453,   -0.740951125,   -0.707106781,
  -0.671558955,   -0.634393284,   -0.595699304,   -0.555570233,   -0.514102744,   -0.471396737,   -0.427555093,   -0.382683432,
  -0.336889853,   -0.290284677,   -0.24298018,    -0.195090322,   -0.146730474,   -0.09801714,    -0.049067674,   -1.83772E-16,
  0.049067674,    0.09801714,     0.146730474,    0.195090322,    0.24298018,     0.290284677,    0.336889853,    0.382683432,
  0.427555093,    0.471396737,    0.514102744,    0.555570233,    0.595699304,    0.634393284,    0.671558955,    0.707106781,
  0.740951125,    0.773010453,    0.803207531,    0.831469612,    0.85772861,     0.881921264,    0.903989293,    0.923879533,
  0.941544065,    0.956940336,    0.970031253,    0.98078528,     0.98917651,     0.995184727,    0.998795456,    
};




void Adc_DataFix( void )
{

}


//*****************************************************************************
//
// Adc Read (0x00300000)
//
//*****************************************************************************
UINT16 uFail = 0;
void Adc_Read( void )
{
// ADC_BUSY 인터럽트로 동작 시켜도 되지만 정주기 동작을 위하여 Timer 사용하였음 // 기존 사용하던 구조가 이 구조이며 추후 추가 내용 대응을 위하여 이구조 유지
  if( sCnt.bAdcRead++ >= eADC_READ_COUNT )
  {
    sCnt.bAdcRead = 0;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 0;      // Timer0 Off // ADC_Read Off
    CpuTimer0Regs.TCR.all = 0x0001; // Use write-only instruction to set TSS bit = 0
    CpuTimer0Regs.TIM.all = 0;

    Adc_LowDataRead( );
  }
  else
//  else if( sCnt.bAdcRead < eADC_READ_COUNT )
  {
    ADC_CONV_LO;
    NOP;    NOP;    NOP;    NOP;    NOP;
    ADC_CONV_HI;
  }
}

void Adc_LowDataRead( void )
{
  UINT16  i;
  UINT8   i_bPoint, i_bNewPoint;
  UINT16  i_wPoint, i_wOldPoint, i_wNewPoint;
  INT16   i_iwOld, i_iwNew;
  INT16   *i_piwRaw;
//  INT16   *i_piwRaw, *i_piwRawOld, *i_piwRawNew;

#if(1)  // MRAM에 저장 되는 2주기 Data를 이용하여 Bias를 연산하므로 속도는 느린 반면 RAM 차지가 적음
  INT16   i_iwRaw[eADC_MAX];

#if(1)
  i_iwRaw[0] = pAdc->iwAdcCs0;        // Temp
  i_iwRaw[1] = pAdc->iwAdcCs0 *-1;    // TC1
  i_iwRaw[2] = pAdc->iwAdcCs0 *-1;    // TC2
  i_iwRaw[3] = pAdc->iwAdcCs0 *-1;    // CC
  i_iwRaw[4] = pAdc->iwAdcCs0;        // V
  i_iwRaw[5] = pAdc->iwAdcCs0;        // IA
  i_iwRaw[6] = pAdc->iwAdcCs0;        // IB
  i_iwRaw[7] = pAdc->iwAdcCs0;        // IC
#else
  for( i=0; i<eADC_MAX; i++ )
    i_iwRaw[i] = pAdc->iwAdcCs0;
#endif

  i_bPoint = sAdc.Cnt.bRaw;
  i_bNewPoint = sAdc.Cnt.bRaw +1;
  if( i_bNewPoint >= eADC_SAMPLE )  i_bNewPoint = 0;
  for( i=0; i<eADC_MAX; i++ )
  {
    i_iwOld = sAdc.iwRawData[i][i_bPoint];
    i_iwNew = sAdc.iwRawData[i][i_bPoint] = i_iwRaw[i];
    sAdc.ilBiasData[i] += (INT32)( i_iwNew - i_iwOld );
  }
  sAdc.Cnt.bRaw = i_bNewPoint;

  i_wPoint = sAdc.Cnt.wRaw;
  i_wOldPoint = i_wPoint + eWAVE_MAX;
  if( i_wOldPoint >= ( eWAVE_MAX *2 ) )  i_wOldPoint -= ( eWAVE_MAX *2 );
  i_wNewPoint = sAdc.Cnt.wRaw +2;
  if( i_wNewPoint >= ( eWAVE_MAX *2 ) )  i_wNewPoint = 0;
//  i_piwRawOld = &pRaw->No.iwTripCoil1[i_wOldPoint];
  i_piwRaw = &pRaw->No.iwTripCoil1[i_wPoint];
  for( i=1; i<eADC_MAX; i++ )
  {
    if( i <= 3 )    *i_piwRaw = i_iwRaw[i];
    else            *i_piwRaw = i_iwRaw[i];
//    sAdc.ilBiasData[i] += (INT32)( *i_piwRaw - *i_piwRawOld );
//    i_piwRawOld += ( eWAVE_MAX *2 );
    i_piwRaw += ( eWAVE_MAX *2 );
  }
  i_wPoint >>= 1;
  if( ( i_wPoint & BIT0 ) == 0 )
    pRaw->No.wContact[i_wPoint]  = ( sAdc.bSta[sAdc.Cnt.bSta ^ BIT0] << 8 );
  else
    pRaw->No.wContact[i_wPoint] |= ( sAdc.bSta[sAdc.Cnt.bSta ^ BIT0] );
  sAdc.Cnt.wRaw = i_wNewPoint;
  if( sAdc.Cnt.wRaw == sAdc.Cnt.wTrip )
    sAdc.Sta.bTrip = 0;
#else
  i_bPoint = sAdc.Cnt.bRaw;
  i_bNewPoint = sAdc.Cnt.bRaw +1;
  if( i_bNewPoint >= eADC_SAMPLE )  i_bNewPoint = 0;
  i_iwOld = sAdc.iwRawData[0][i_bPoint];
  i_iwNew = sAdc.iwRawData[0][i_bPoint] = pAdc->iwAdcCs0;
  sAdc.ilBiasData[0] += (INT32)( i_iwNew - i_iwOld );
  sAdc.Cnt.bRaw = i_bNewPoint;

  i_wPoint = sAdc.Cnt.wRaw;
  i_wOldPoint = i_wPoint + eWAVE_MAX;
  if( i_wOldPoint >= ( eWAVE_MAX *2 ) )  i_wOldPoint -= ( eWAVE_MAX *2 );
  i_wNewPoint = sAdc.Cnt.wRaw +2;
  if( i_wNewPoint >= ( eWAVE_MAX *2 ) )  i_wNewPoint = 0;
  i_piwRawOld = &pRaw->No.iwTripCoil1[i_wOldPoint];
  i_piwRaw = &pRaw->No.iwTripCoil1[i_wPoint];
  for( i=1; i<eADC_MAX; i++ )
  {
    *i_piwRaw = pAdc->iwAdcCs0;
    sAdc.ilBiasData[i] += (INT32)( *i_piwRaw - *i_piwRawOld );
    i_piwRawOld += ( eWAVE_MAX *2 );
    i_piwRaw += ( eWAVE_MAX *2 );
  }
  i_wPoint >>= 1;
  if( ( i_wPoint & BIT0 ) == 0 )
    pRaw->No.wContact[i_wPoint]  = ( sAdc.bSta[sAdc.Cnt.bSta ^ BIT0] << 8 );
  else
    pRaw->No.wContact[i_wPoint] |= ( sAdc.bSta[sAdc.Cnt.bSta ^ BIT0] );
  sAdc.Cnt.wRaw = i_wNewPoint;
#endif
}


//*****************************************************************************
//
// Adc_Make (0x00300000)
//
//*****************************************************************************
void Adc_Make( void )
{
  Adc_Conv( );
  Fault_Make( );
}


void Fault_Make( void )
{
  UINT16  i;
  float   i_fTrip[3], i_fClose[3];
  i_fTrip[0] = (float)sDsp.wTrip[0] /10;
  i_fTrip[1] = (float)sDsp.wTrip[1] /10;
  i_fTrip[2] = (float)sDsp.wTrip[2] /10;
  i_fClose[0] = i_fTrip[0] *0.9;
  i_fClose[1] = i_fTrip[1] *0.9;
  i_fClose[2] = i_fTrip[2] *0.9;

  float   i_fFreq;
  UINT16  i_wDebounce;

  if( sSet.bFreq50Hz == eFREQ_60Hz )    i_fFreq = (float)1000 /60 /( eADC_SAMPLE /2);
  else                                  i_fFreq = (float)1000 /50 /( eADC_SAMPLE /2);
  i_wDebounce = (UINT16)( ( (float)sSet.wChat / i_fFreq ) +0.5 );

  if( sSta.wTc1 == 0 && sDsp.fRealVal[eCAL_DSP_TC1] >= i_fTrip[0] )
  {
    if( sAdc.Sta.bTrip == 0 && ++sCnt.wTc1 >= i_wDebounce )
//    if( ++sCnt.wTc1 >= i_wDebounce )
    {
      sCnt.wTc1 = i_wDebounce;
      FaultWr_Start( eFA_TRIP1 );
    }
  }
  else if( sDsp.fRealVal[eCAL_DSP_TC1] < i_fClose[0] )
  {
    if( sSta.wTc1 != 0 )
      sFat.No[sSta.wTc1 -1].wNo = 0;
    sSta.wTc1 = 0;
    sCnt.wTc1 = 0;
  }
  if( sSta.wTc2 == 0 && sDsp.fRealVal[eCAL_DSP_TC2] >= i_fTrip[1] )
  {
    if( sAdc.Sta.bTrip == 0 && ++sCnt.wTc2 >= i_wDebounce )
//    if( ++sCnt.wTc2 >= i_wDebounce )
    {
      sCnt.wTc2 = i_wDebounce;
      FaultWr_Start( eFA_TRIP2 );
    }
  }
  else if( sDsp.fRealVal[eCAL_DSP_TC2] < i_fClose[0] )
  {
    if( sSta.wTc2 != 0 )
      sFat.No[sSta.wTc2 -1].wNo = 0;
    sSta.wTc2 = 0;
    sCnt.wTc2 = 0;
  }
  if( sSta.wCc == 0 && sDsp.fRealVal[eCAL_DSP_CC] >= i_fTrip[2] )
  {
    if( ++sCnt.wCc >= i_wDebounce )
    {
      sCnt.wCc = i_wDebounce;
      FaultWr_Start( eFA_CLOSE );
    }
  }
  else if( sDsp.fRealVal[eCAL_DSP_CC] < i_fClose[2] )
  {
    if( sSta.wCc != 0 )
      sFat.No[sSta.wCc -1].wNo = 0;
    sSta.wCc = 0;
    sCnt.wCc = 0;
  }

  if( sCnt.wFa != sCnt.wFaEnd )
  {
    for( i=sCnt.wFa; i!=sCnt.wFaEnd; )
    {
      FaultWr_Run( i % eFAULT_MAX );
      if( ++i >= ( eFAULT_MAX *2 ) )
        i = eFAULT_MAX;
    }
  }

}
void FaultWr_Start( UINT16 i_wType )
{
  float   i_fFreq;
  UINT16  i_wNo, i_wRawPit, i_wPit, i_wTrip;

  if( sCnt.wFa == eFAULT_EMPTY )
  {
    sCnt.wFaNum = sCnt.wFaMb = sCnt.wFa = sCnt.wFaEnd = 0;
    pMram->wFaNum = pMram->wFaMb = pMram->wFaEnd = 0;
  }
  i_wRawPit = sAdc.Cnt.wRaw;    // 저장 포인트 짝수로 만듬

  i_wNo = sCnt.wFaEnd % eFAULT_MAX;
       if( i_wType == eFA_TRIP1 )   sSta.wTc1 = i_wNo +1;
  else if( i_wType == eFA_TRIP2 )   sSta.wTc2 = i_wNo +1;
  else if( i_wType == eFA_CLOSE )   sSta.wCc = i_wNo +1;

  sFat.No[i_wNo].wNo      = sFat.No[i_wNo].bType = i_wType;
  sFat.No[i_wNo].wType    = i_wType == eFA_CLOSE ? 0xAA : 0x55;   // 0x55: Trip, 0xAA: Close
  sFat.No[i_wNo].ilUtc    = sDsp.ilUtc;
  sFat.No[i_wNo].lUtcMs   = sDsp.lUtcMs;
  sFat.No[i_wNo].fContDA  = sDsp.fRealVal[eCAL_DSP_IA];
  sFat.No[i_wNo].fContDB  = sDsp.fRealVal[eCAL_DSP_IB];
  sFat.No[i_wNo].fContDC  = sDsp.fRealVal[eCAL_DSP_IC];
  sFat.No[i_wNo].fTc1Pc   = sDsp.fRealVal[eCAL_DSP_TC1];
  sFat.No[i_wNo].fTc1Cf   = 0;
  sFat.No[i_wNo].fTc2Pc   = sDsp.fRealVal[eCAL_DSP_TC2];
  sFat.No[i_wNo].fTc2Cf   = 0;
  sFat.No[i_wNo].fCc_Pc   = sDsp.fRealVal[eCAL_DSP_CC];
  sFat.No[i_wNo].fCc_Cf   = 0;
  sFat.No[i_wNo].fCc_A    = 0;
  sFat.No[i_wNo].fTc_B    = 0;
  sFat.No[i_wNo].fTc_Cc_A = 0;
  sFat.No[i_wNo].fTc_Cc_B = 0;
  sFat.No[i_wNo].fTc_Cc_C = 0;

  if( sSet.bFreq50Hz == eFREQ_60Hz )    i_fFreq = (float)1000 /60 /eADC_SAMPLE;
  else                                  i_fFreq = (float)1000 /50 /eADC_SAMPLE;
  if( sTest.wPit )
    i_wPit = sTest.wPit;
  else
  {
float   i_fTrig = (float)sDsp.wTrig + sSet.wChat;
    i_wPit = (UINT16)( ( ( i_fTrig / i_fFreq ) *2 ) +0.5 );
  }
  if( i_wRawPit < i_wPit )
    sFat.No[i_wNo].wTrig = ( eWAVE_MAX *2 ) + i_wRawPit - i_wPit;
  else
    sFat.No[i_wNo].wTrig = i_wRawPit - i_wPit;
  sFat.No[i_wNo].wTrig &= 0xFFFE;
  i_wTrip = sFat.No[i_wNo].wTrig + eWAVE_MAX;
  sAdc.Cnt.wTrip = i_wTrip % ( eWAVE_MAX *2 );
  sAdc.Sta.bTrip = 1;
  sFat.No[i_wNo].bNo = 0;
  sFat.No[i_wNo].wEnd = 0;

  if( ++sCnt.wFaEnd >= ( eFAULT_MAX *2 ) )
    sCnt.wFaEnd = eFAULT_MAX;
  pMram->wFaEnd = sCnt.wFaEnd;
}
void FaultWr_Run( UINT16 i_wNo )
{
  UINT16 i,  i_wPit, i_wCnt;

  if( sFat.No[i_wNo].wNo == eFA_TRIP1 )   sFat.No[i_wNo].fTc1Cf++;
  if( sFat.No[i_wNo].wNo == eFA_TRIP2 )   sFat.No[i_wNo].fTc2Cf++;
  if( sFat.No[i_wNo].wNo == eFA_CLOSE )   sFat.No[i_wNo].fCc_Cf++;
  if( sFat.No[i_wNo].wNo == eFA_TRIP1 || sFat.No[i_wNo].wNo == eFA_TRIP2 || sFat.No[i_wNo].wNo == eFA_CLOSE )
  {
    if( sFat.No[i_wNo].fContDA < sDsp.fRealVal[eCAL_DSP_IA] )   sFat.No[i_wNo].fContDA   = sDsp.fRealVal[eCAL_DSP_IA];
    if( sFat.No[i_wNo].fContDB < sDsp.fRealVal[eCAL_DSP_IB] )   sFat.No[i_wNo].fContDB   = sDsp.fRealVal[eCAL_DSP_IB];
    if( sFat.No[i_wNo].fContDC < sDsp.fRealVal[eCAL_DSP_IC] )   sFat.No[i_wNo].fContDC   = sDsp.fRealVal[eCAL_DSP_IC];
    if( sFat.No[i_wNo].fTc1Pc  < sDsp.fRealVal[eCAL_DSP_TC1] )  sFat.No[i_wNo].fTc1Pc    = sDsp.fRealVal[eCAL_DSP_TC1];
    if( sFat.No[i_wNo].fTc2Pc  < sDsp.fRealVal[eCAL_DSP_TC2] )  sFat.No[i_wNo].fTc2Pc    = sDsp.fRealVal[eCAL_DSP_TC2];
    if( sFat.No[i_wNo].fCc_Pc  < sDsp.fRealVal[eCAL_DSP_CC] )   sFat.No[i_wNo].fCc_Pc    = sDsp.fRealVal[eCAL_DSP_CC];
  }

float   i_fTrip[3], i_fClose[3];
  i_fTrip[0] = 0.1;
  i_fTrip[1] = 0.1;
  i_fTrip[2] = 0.1;
  i_fClose[0] = i_fTrip[0] *0.9;
  i_fClose[1] = i_fTrip[1] *0.9;
  i_fClose[2] = i_fTrip[2] *0.9;
  if( sFat.No[i_wNo].bType == eFA_TRIP1 )
  {
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC1_DI2 ) && sIn.wInput & eST_B_IN_DI2 )   sFat.No[i_wNo].fTc_B++;                        // B접점
    else                                                                          sFat.No[i_wNo].wEnd |= eFA_B_TC1_DI2;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC1_IA ) && sDsp.fRealVal[eCAL_DSP_IA] >= i_fClose[0] )  sFat.No[i_wNo].fTc_Cc_A++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC1_IA;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC1_IB ) && sDsp.fRealVal[eCAL_DSP_IB] >= i_fClose[1] )  sFat.No[i_wNo].fTc_Cc_B++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC1_IB;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC1_IC ) && sDsp.fRealVal[eCAL_DSP_IC] >= i_fClose[2] )  sFat.No[i_wNo].fTc_Cc_C++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC1_IC;
  }
  else if( sFat.No[i_wNo].bType == eFA_TRIP2 )
  {
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC2_DI2 ) && sIn.wInput & eST_B_IN_DI2 )   sFat.No[i_wNo].fTc_B++;                        // B접점
    else                                                                          sFat.No[i_wNo].wEnd |= eFA_B_TC2_DI2;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC2_IA ) && sDsp.fRealVal[eCAL_DSP_IA] >= i_fClose[0] )  sFat.No[i_wNo].fTc_Cc_A++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC2_IA;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC2_IB ) && sDsp.fRealVal[eCAL_DSP_IB] >= i_fClose[1] )  sFat.No[i_wNo].fTc_Cc_B++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC2_IB;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_TC2_IC ) && sDsp.fRealVal[eCAL_DSP_IC] >= i_fClose[2] )  sFat.No[i_wNo].fTc_Cc_C++;
    else                                                                                        sFat.No[i_wNo].wEnd |= eFA_B_TC2_IC;
  }
  else if( sFat.No[i_wNo].bType == eFA_CLOSE )
  {
    if( !( sFat.No[i_wNo].wEnd & eFA_B_CC_DI1 ) && !( sIn.wInput & eST_B_IN_DI1 ) ) sFat.No[i_wNo].fCc_A++;                        // A접점
    else                                                                            sFat.No[i_wNo].wEnd |= eFA_B_CC_DI1;
//#define eCURR_ON    0.1
    if( !( sFat.No[i_wNo].wEnd & eFA_B_CC_IA ) && sDsp.fRealVal[eCAL_DSP_IA] <= i_fTrip[0] )  sFat.No[i_wNo].fTc_Cc_A++;
    else                                                                                      sFat.No[i_wNo].wEnd |= eFA_B_CC_IA;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_CC_IB ) && sDsp.fRealVal[eCAL_DSP_IB] <= i_fTrip[1] )  sFat.No[i_wNo].fTc_Cc_B++;
    else                                                                                      sFat.No[i_wNo].wEnd |= eFA_B_CC_IB;
    if( !( sFat.No[i_wNo].wEnd & eFA_B_CC_IC ) && sDsp.fRealVal[eCAL_DSP_IC] <= i_fTrip[2] )  sFat.No[i_wNo].fTc_Cc_C++;
    else                                                                                      sFat.No[i_wNo].wEnd |= eFA_B_CC_IC;
  }

  i_wPit = sFat.No[i_wNo].wTrig;
  i_wCnt = sFat.No[i_wNo].bNo;
  pWave->No[i_wNo].wContact[i_wCnt /2]    = pRaw->No.wContact[i_wPit /2];

  if( i_wCnt == 4602 )
    NOP;
  for( i=0; i<2; i++ )
  {
    pWave->No[i_wNo].iwTripCoil1[i_wCnt] = pRaw->No.iwTripCoil1[i_wPit];
    pWave->No[i_wNo].iwTripCoil2[i_wCnt] = pRaw->No.iwTripCoil2[i_wPit];
    pWave->No[i_wNo].iwCloseCoil[i_wCnt] = pRaw->No.iwCloseCoil[i_wPit];
    pWave->No[i_wNo].iwVolt[i_wCnt]      = pRaw->No.iwVolt[i_wPit];
    pWave->No[i_wNo].iwCurr[0][i_wCnt]   = pRaw->No.iwCurr[0][i_wPit];
    pWave->No[i_wNo].iwCurr[1][i_wCnt]   = pRaw->No.iwCurr[1][i_wPit];
    pWave->No[i_wNo].iwCurr[2][i_wCnt]   = pRaw->No.iwCurr[2][i_wPit];
//    pWave->No[i_wNo].wContact[i_wCnt]    = pRaw->No.wContact[i_wPit];

    sFat.No[i_wNo].wTrig += 2;
    if( sFat.No[i_wNo].wTrig >= ( eWAVE_MAX *2 ) )  sFat.No[i_wNo].wTrig = 0;
    i_wPit = sFat.No[i_wNo].wTrig;
    sFat.No[i_wNo].bNo += 2;
    i_wCnt = sFat.No[i_wNo].bNo;
    if( sFat.No[i_wNo].bNo >= ( eWAVE_MAX ) )
      FaultWr( i_wNo );
  }
}


void Adc_Conv( void )
{
  UINT8   i_bPoint[2];
  UINT16  i_wPoint;

// Bias 및 DC Data(128 sample Data 16.6msec)
  sInt.fReal[eINT_TEMP]     = ( (float)sAdc.ilBiasData[eINT_TEMP]    *0.736 );
//  sInt.fReal[eINT_TEMP]     = ( (float)sAdc.ilBiasData[eINT_TEMP]    /eSAMPLE_NO );
#if(1)
  i_bPoint[0] = sAdc.Cnt.bRaw;
  if( i_bPoint[0] == 0 )  i_bPoint[1] = i_bPoint[0] = eADC_SAMPLE -1;
  else                    i_bPoint[1] = i_bPoint[0] = sAdc.Cnt.bRaw -1;
  if( i_bPoint[1] == 0 )  i_bPoint[1] = eADC_SAMPLE -1;
  else                    i_bPoint[1] = i_bPoint[0] -1;
  sInt.fReal[eINT_TC1]      = ( (float)( (INT32)sAdc.iwRawData[eINT_TC1][i_bPoint[0]] + sAdc.iwRawData[eINT_TC1][i_bPoint[1]] ) /2 );
  sInt.fReal[eINT_TC2]      = ( (float)( (INT32)sAdc.iwRawData[eINT_TC2][i_bPoint[0]] + sAdc.iwRawData[eINT_TC2][i_bPoint[1]] ) /2 );
  sInt.fReal[eINT_CC]       = ( (float)( (INT32)sAdc.iwRawData[eINT_CC ][i_bPoint[0]] + sAdc.iwRawData[eINT_CC ][i_bPoint[1]] ) /2 );
#else
  sInt.fReal[eINT_TC1]      = ( (float)-sAdc.ilBiasData[eINT_TC1]    /eSAMPLE_NO );
  sInt.fReal[eINT_TC2]      = ( (float)-sAdc.ilBiasData[eINT_TC2]    /eSAMPLE_NO );
  sInt.fReal[eINT_CC]       = ( (float)-sAdc.ilBiasData[eINT_CC]     /eSAMPLE_NO );
#endif
  sInt.fReal[eINT_V_BIAS]   = ( (float)sAdc.ilBiasData[eINT_V_BIAS]  /eSAMPLE_NO );
  sInt.fReal[eINT_IA_BIAS]  = ( (float)sAdc.ilBiasData[eINT_IA_BIAS] /eSAMPLE_NO );
  sInt.fReal[eINT_IB_BIAS]  = ( (float)sAdc.ilBiasData[eINT_IB_BIAS] /eSAMPLE_NO );
  sInt.fReal[eINT_IC_BIAS]  = ( (float)sAdc.ilBiasData[eINT_IC_BIAS] /eSAMPLE_NO );

  if( sAdc.Cnt.wRaw == 0 )
    i_wPoint = ( eWAVE_MAX *2 ) -2;
  else
    i_wPoint = sAdc.Cnt.wRaw -2;
  i_wPoint &= 0xFFFC;               // 홀수 저장되는 Data가 없게 만들기 위하여 번지가 2개씩 증가하므로 홀수는 /4 해야 됨

#if(1)
  Dft_Conv( eV,  i_wPoint );
  Dft_Conv( eIA, i_wPoint );
  Dft_Conv( eIB, i_wPoint );
  Dft_Conv( eIC, i_wPoint );

  Value_Real( );
  Phase_Gain( );

#endif
}

void Dft_Conv( UINT8 i_bCh, UINT16 i_wPoint )
{
  UINT16  i;
//  UINT16  i, j, k;
  float   i_fImag = 0, i_fReal = 0;
  float   i_fImag2, i_fReal2;
  float   i_fData, i_fData1, i_fData2, i_fRms;
  float   i_fImagPhase, i_fRealPhase, i_fPhaseData;

  UINT16  i_wMax;
  UINT16  i_wNo;
  INT16   *i_piwData;
  float   *i_pfRawRms;
  float   *i_pfRawPh;


  i_wMax = eWAVE_MAX *2;
  i_wNo = ( eSAMPLE_NO *2 ) / eDFT_SAMPLE_NO;
  i_piwData = &pRaw->No.iwVolt[0];
  i_piwData += ( (INT16)i_bCh * i_wMax );
  i_pfRawRms = &sInt.fReal[eINT_V] + i_bCh;
  i_pfRawPh = &sInt.fReal[eINT_VP] + i_bCh;
#if(0)    // Bias 최대 최소를 보기위하여 만든 부분으로 현재 불필요하여 제거 함
  sAdc.iwReal[i_bCh] = i_piwData[i_wPoint];
  if( sAdc.ilMeasMin[i_bCh] > sAdc.iwReal[i_bCh] )
    sAdc.ilMeasMin[i_bCh] = sAdc.iwReal[i_bCh];
  else if( sAdc.ilMeasMax[i_bCh] < sAdc.iwReal[i_bCh] )
    sAdc.ilMeasMax[i_bCh] = sAdc.iwReal[i_bCh];
  if( sTest.bMinMax )
  {
    sTest.bMinMax++;
    sAdc.ilMeasMin[i_bCh] = sAdc.iwReal[i_bCh];
    sAdc.ilMeasMax[i_bCh] = sAdc.iwReal[i_bCh];
    if( sTest.bMinMax > 12 )
      sTest.bMinMax = 0;
  }
#endif

  for( i=0; i<eDFT_SAMPLE_NO; i++ )
  {
    sAdc.fLowData[i_bCh][i] = (float)i_piwData[i_wPoint];
    i_fImag += ( (float)i_piwData[i_wPoint] * fSin[i*8] );
    i_fReal += ( (float)i_piwData[i_wPoint] * fCos[i*8] );

    if( i_wNo > i_wPoint )  i_wPoint += ( i_wMax - i_wNo );
    else                    i_wPoint -= i_wNo;
  }
//  fImag[i_bCh] = i_fImag;
//  fReal[i_bCh] = i_fReal;
  i_fImag2 = ( i_fImag * i_fImag );
  i_fReal2 = ( i_fReal * i_fReal );
  i_fData  = ( i_fImag2 + i_fReal2 );
  i_fData1 = i_fData / eDFT_SAMPLE_NO;
  i_fData2 = sqrt( i_fData1 );
  i_fRms   = i_fData2 / e2SQRT2;

  *i_pfRawRms = i_fRms;     // sInt.fReal[eINT_RAW_V] / eINT_RAW_V eINT_RAW_IA eINT_RAW_IB eINT_RAW_IC


// 위상
  i_fImagPhase = i_fImag * e1dSQRT2;
  i_fRealPhase = i_fReal * e1dSQRT2;
  i_fPhaseData = ( atan( i_fImagPhase / i_fRealPhase ) *e180dPI );

#if(1)
  if( i_fRealPhase > 0 )      i_fPhaseData += 180;
  if( i_fRealPhase > 180 )    i_fPhaseData -= 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
  *i_pfRawPh = i_fPhaseData;
#else

  if( i_fPhaseData >= 360 )     i_fPhaseData -= 360;
  else if( i_fPhaseData < 0 )   i_fPhaseData += 360;
//  if( i_fPhaseData >= 360 )     i_fPhaseData -= 360;
//  else if( i_fPhaseData < 0 )   i_fPhaseData += 360;
  sInt.fPhaseReal[i_bCh] = i_fPhaseData;
#endif

//  if( sStatus.lPowerOnDelay & eON_DELAY_700MS )
//    Freq_Conv( i_bCh, i_fPhaseData );

}

void Value_Real( void )
{
#if(1)
  sRms = sRmsSet[eCAL_DSP_V ];  sRms.pfCode = &sInt.fReal[eINT_V ];   sRms.pfRms = &sDsp.fRealVVal[eADC_V ];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_V , &sDsp.fRealVVal[eADC_V ], &sDsp.fRealVal[eCAL_DSP_V ] );
  sRms = sRmsSet[eCAL_DSP_IA];  sRms.pfCode = &sInt.fReal[eINT_IA];   sRms.pfRms = &sDsp.fRealVVal[eADC_IA];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_IA, &sDsp.fRealVVal[eADC_IA], &sDsp.fRealVal[eCAL_DSP_IA] );
  sRms = sRmsSet[eCAL_DSP_IB];  sRms.pfCode = &sInt.fReal[eINT_IB];   sRms.pfRms = &sDsp.fRealVVal[eADC_IB];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_IB, &sDsp.fRealVVal[eADC_IB], &sDsp.fRealVal[eCAL_DSP_IB] );
  sRms = sRmsSet[eCAL_DSP_IC];  sRms.pfCode = &sInt.fReal[eINT_IC];   sRms.pfRms = &sDsp.fRealVVal[eADC_IC];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_IC, &sDsp.fRealVVal[eADC_IC], &sDsp.fRealVal[eCAL_DSP_IC] );
#else
  sRms = sRmsSet[eCAL_DSP_V ];  sRms.pfCode = &sInt.fReal[eINT_V ];   sRms.pfRms = &sDsp.fRealVal[eCAL_DSP_V ];   Conv_CODE2RMS( sRms );
  sRms = sRmsSet[eCAL_DSP_IA];  sRms.pfCode = &sInt.fReal[eINT_IA];   sRms.pfRms = &sDsp.fRealVal[eCAL_DSP_IA];   Conv_CODE2RMS( sRms );
  sRms = sRmsSet[eCAL_DSP_IB];  sRms.pfCode = &sInt.fReal[eINT_IB];   sRms.pfRms = &sDsp.fRealVal[eCAL_DSP_IB];   Conv_CODE2RMS( sRms );
  sRms = sRmsSet[eCAL_DSP_IC];  sRms.pfCode = &sInt.fReal[eINT_IC];   sRms.pfRms = &sDsp.fRealVal[eCAL_DSP_IC];   Conv_CODE2RMS( sRms );
#endif

  sRms = sRmsSet[eCAL_DSP_TC1]; sRms.pfCode = &sInt.fReal[eINT_TC1];  sRms.pfRms = &sDsp.fRealVVal[eADC_TC1];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_TC1, &sDsp.fRealVVal[eADC_TC1], &sDsp.fRealVal[eCAL_DSP_TC1] );
  sRms = sRmsSet[eCAL_DSP_TC2]; sRms.pfCode = &sInt.fReal[eINT_TC2];  sRms.pfRms = &sDsp.fRealVVal[eADC_TC2];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_TC2, &sDsp.fRealVVal[eADC_TC2], &sDsp.fRealVal[eCAL_DSP_TC2] );
  sRms = sRmsSet[eCAL_DSP_CC ]; sRms.pfCode = &sInt.fReal[eINT_CC ];  sRms.pfRms = &sDsp.fRealVVal[eADC_CC ];  Conv_CODE2RMS( sRms );  Conv_VOLT2CURR( eADC_CC,  &sDsp.fRealVVal[eADC_CC ], &sDsp.fRealVal[eCAL_DSP_CC ] );
}
void Phase_Gain( void )
{
#if(1)
  float   *i_pfRawPh = &sInt.fReal[eINT_VP];
  float   i_fPhase;

  if( sDsp.fRealVal[eCAL_DSP_V] == 0 )
  {
    *i_pfRawPh = 0;       // VP
    if( sDsp.fRealVal[eCAL_DSP_IA] == 0 )
    {
      i_pfRawPh++;
      *i_pfRawPh = 0;     // IAP
      if( sDsp.fRealVal[eCAL_DSP_IB] == 0 )
      {
        i_pfRawPh++;
        *i_pfRawPh = 0;   // IBP
        i_pfRawPh++;
        *i_pfRawPh = 0;   // ICP
      }
      else
      {
        i_fPhase = sInt.fReal[eINT_IBP];
        i_pfRawPh++;
        *i_pfRawPh = 0;   // IBP
        i_pfRawPh++;
        *i_pfRawPh = i_fPhase - sInt.fReal[eINT_ICP];
             if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
        else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
      }
    }
    else
    {
      i_fPhase = sInt.fReal[eINT_IAP];
      i_pfRawPh++;
      *i_pfRawPh = 0;     // IAP
      i_pfRawPh++;
      *i_pfRawPh = i_fPhase - sInt.fReal[eINT_IBP];
           if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
      else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
      i_pfRawPh++;
      *i_pfRawPh = i_fPhase - sInt.fReal[eINT_ICP];
           if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
      else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
    }
  }
  else
  {
    i_fPhase = sInt.fReal[eINT_VP];

    *i_pfRawPh = 0;       // VP
    i_pfRawPh++;
    *i_pfRawPh = i_fPhase - sInt.fReal[eINT_IAP];
         if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
    else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
    i_pfRawPh++;
    *i_pfRawPh = i_fPhase - sInt.fReal[eINT_IBP];
         if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
    else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
    i_pfRawPh++;
    *i_pfRawPh = i_fPhase - sInt.fReal[eINT_ICP];
         if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
    else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
  }
#else
  float   *i_pfRawPh = &sInt.fReal[eINT_VP];

  i_pfRawPh++;
  *i_pfRawPh = sInt.fReal[eINT_VP] - sInt.fReal[eINT_IAP];
       if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
  else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
  i_pfRawPh++;
  *i_pfRawPh = sInt.fReal[eINT_VP] - sInt.fReal[eINT_IBP];
       if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
  else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
  i_pfRawPh++;
  *i_pfRawPh = sInt.fReal[eINT_VP] - sInt.fReal[eINT_ICP];
       if( *i_pfRawPh > 180 )     *i_pfRawPh -= 360;
  else if( *i_pfRawPh < -180 )    *i_pfRawPh += 360;    // 적분을 하기 위하여는 +-180으로 해야 편함
//  i_pfRawPh++;
  sInt.fReal[eINT_VP] = 0;
#endif

}

void DcCurr_Gain( void )
{
/* 아래 정보 가지고 Dc 전류 Real 만들어야 됨 
  sAdc.ilBiasData[i] += (INT32)( i_iwNew - i_iwOld );
  sAdc.Cnt.bRaw = i_bNewPoint;
*/
}





void Adc_Phase( UINT16 i_wPhase )
{
  float   i_fImagPhase;
  float   i_fRealPhase;
  float   i_fPhaseData;
//  UINT8   i_bCh;
//  UINT8   i_bFirst;
//  INT16   i_iwPhase;

  if( fabs( sAdc.fImagSum[i_wPhase] ) > fabs( sAdc.fRealSum[i_wPhase] ) )   // __atan() 함수가 1이상을 1로 연산하므로 이렇게 작업함
  {       // 58clk
    i_fImagPhase = sAdc.fImagSum[i_wPhase] * e1dSQRT2;                    // 6clk
    i_fRealPhase = sAdc.fRealSum[i_wPhase] * e1dSQRT2;                    // 6clk
    i_fPhaseData = __atan( __divf32( i_fRealPhase, i_fImagPhase ) ) * e180dPI;   // 17clk
    if( i_fImagPhase > 0 )  i_fPhaseData += 360;
    else                    i_fPhaseData += 180;
  }
  else
  {       // 58clk
    i_fImagPhase = -sAdc.fImagSum[i_wPhase] * e1dSQRT2;                   // 6clk
    i_fRealPhase =  sAdc.fRealSum[i_wPhase] * e1dSQRT2;                   // 6clk
    i_fPhaseData = __atan( __divf32( i_fImagPhase, i_fRealPhase ) ) * e180dPI;// 243clk
    if (i_fRealPhase > 0)
      i_fPhaseData += 90;
    else
      i_fPhaseData += 270;
  }

  i_fPhaseData += 0.005;
  if( i_fPhaseData >= 360 )   i_fPhaseData -= 360;
  i_fPhaseData *= 100;
//  PhaseData = ( PhaseData + 0.05 ) * 10;
//  if( PhaseData >= 3600 ) PhaseData -= 3600;
}


#define eVOLT_SPAN      4000
#define eVOLT_ZERO      800
void Ai_Conv( UINT16 i_wPhase )
{
#if(0)

  UINT16  i, i_wData;
  INT16   i_wCodeScale;
  INT16   i_wVoltScale;
  INT16   i_wDataScale;
//  INT32   i_lData;
  UINT32  i_lPhaseBit;

  i_wData = 0;
  for( i=0; i<eSPI_DATA_MAX; i++ )
  {
    i_wData += sSpib.Rx.wData[i_wPhase][i];
  }

//20170308 여기에서 Code 값을 0.8~4.0V로 변경 작업 하시요.
  i_wData /= eSPI_DATA_MAX;
//  sSet.wAi[i_wPhase] = i_wData;

  i_wCodeScale = (INT16)sSet.wSpan[i_wPhase] - sSet.wZero[i_wPhase];
  i_wVoltScale = (INT16)sSet.wCalSpanEE[i_wPhase] - sSet.wCalZeroEE[i_wPhase];
  i_wDataScale = (INT16)i_wData - sSet.wZero[i_wPhase];

  sSet.wAi[i_wPhase] = ( ( (INT32)i_wDataScale * i_wVoltScale ) / i_wCodeScale ) + sSet.wCalZeroEE[i_wPhase];

  i_lPhaseBit = ( (UINT32)BIT0 << i_wPhase );
  if( sSet.wCtrlFlag & eCAL_ZERO_CAL )
  {
    if( sSet.wZeroFlag & (UINT16)i_lPhaseBit )
    {
// 적분이 필요하면 여기서 하시요.
      sSet.wZeroTemp[i_wPhase] = i_wData;
      if( sSet.wCtrlFlag & eCAL_AI_SAVE )
        sI2c.lSave2Temp |= i_lPhaseBit;
    }
  }
  else if( sSet.wCtrlFlag & eCAL_SPAN_CAL )
  {
    if( sSet.wZeroFlag & (UINT16)i_lPhaseBit )
    {
// 적분이 필요하면 여기서 하시요.
      sSet.wSpanTemp[i_wPhase] = i_wData;
      if( sSet.wCtrlFlag & eCAL_AI_SAVE )
        sI2c.lSave2Temp |= ( i_lPhaseBit << 16 );
    }
  }
  else if( sI2c.lSave2Temp & ( i_lPhaseBit ) )            // Zero
  {
    sI2c.lSave2 = sI2c.lSave2Temp;
    sSet.wZero[i_wPhase] = sSet.wZeroTemp[i_wPhase];
    sSet.wCalZeroEE[i_wPhase] = sSet.wCalZero;
    sI2c.lSave2Temp &= ~( i_lPhaseBit );
  }
  else if( sI2c.lSave2Temp & ( i_lPhaseBit << 16 ) )      // Span
  {
    sI2c.lSave2 = sI2c.lSave2Temp;
    sSet.wSpan[i_wPhase] = sSet.wSpanTemp[i_wPhase];
    sSet.wCalSpanEE[i_wPhase] = sSet.wCalSpan;
    sI2c.lSave2Temp &= ~( i_lPhaseBit << 16 );
  }
#endif
}


/******************************* TIGERWIN END OF FILE *******************************/
