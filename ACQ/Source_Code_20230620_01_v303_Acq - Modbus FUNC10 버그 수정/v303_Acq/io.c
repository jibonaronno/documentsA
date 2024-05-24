/* *************************************************************************
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name	  : io.c
 *
 * *************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <F28x_Project.h>         // Device Headerfile and Examples Include File

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "tigerwin.h"
#include "io.h"
#include "adc.h"
#include "emif.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void IO_Make( void );

/* Private user code ---------------------------------------------------------*/

void IO_Make(void)
{
  UINT16 i_wInput = 0;

#if(1)
  float   i_fFreq;
  UINT16  i_wDebounce;

  if( sSet.bFreq50Hz == eFREQ_60Hz )    i_fFreq = (float)1000 /60 /( eADC_SAMPLE /2);
  else                                  i_fFreq = (float)1000 /50 /( eADC_SAMPLE /2);
  i_wDebounce = (UINT16)( ( (float)sDsp.wDebo / i_fFreq ) +0.5 );

  if( DI1 == 0 )
  {
    sIn.Cnt.w1Lo = 0;
    if( ++sIn.Cnt.w1Hi >= i_wDebounce )
    {
      sIn.Cnt.w1Hi = i_wDebounce;
      sIn.wInput |= eST_B_IN_DI1;
    }
  }
  else
  {
    sIn.Cnt.w1Hi = 0;
    if( ++sIn.Cnt.w1Lo >= i_wDebounce )
    {
      sIn.Cnt.w1Lo = i_wDebounce;
      sIn.wInput &= ~eST_B_IN_DI1;
    }
  }
  if( DI2 == 0 )
  {
    sIn.Cnt.w2Lo = 0;
    if( ++sIn.Cnt.w2Hi >= i_wDebounce )
    {
      sIn.Cnt.w2Hi = i_wDebounce;
      sIn.wInput |= eST_B_IN_DI2;
    }
  }
  else
  {
    sIn.Cnt.w2Hi = 0;
    if( ++sIn.Cnt.w2Lo >= i_wDebounce )
    {
      sIn.Cnt.w2Lo = i_wDebounce;
      sIn.wInput &= ~eST_B_IN_DI2;
    }
  }
#else
  if( DI1 == 0 )
    i_wInput |= eST_B_IN_DI1;
  if( DI2 == 0 )
    i_wInput |= eST_B_IN_DI2;
#endif
  if( MON_N5V )
    i_wInput |= eST_B_IN_N5V;
  if( MON_N15V )
    i_wInput |= eST_B_IN_N15V;
  if( MON_P15V )
    i_wInput |= eST_B_IN_P15V;
  if( MON_P24V )
    i_wInput |= eST_B_IN_P24V;

  if( sIn.wInput != i_wInput )
  {
    if( ++sIn.Cnt.wInput >= eIN_CHANGE )
    {
      sIn.Cnt.wInput = 0;
      sIn.wInput |= ( i_wInput & 0x00FC );
    }
  }
  else
    sIn.Cnt.wInput = 0;

  if( !( sSta.lPowerOnDelay & eON_DELAY_500MS ) )
    return;

  sDsp.wDi = sAdc.bSta[sAdc.Cnt.bSta] = sIn.wInput & 0x03;

  if( ++sAdc.Cnt.bSta >= 2 )
    sAdc.Cnt.bSta = 0;


  
  if( sSta.bPowerStart == 0 )
    return;

//-> Event 저장 해야 됨
  if( sIn.wInput & eST_B_IN_N5V )
  {
    if( !( sSta.lError & eST_B_IN_N5V ) )
      EventWr( eEV_N5V_FA );
    sSta.lError |= eST_B_IN_N5V;
  }
  else
  {
    if( ( sSta.lError & eST_B_IN_N5V ) )
      EventWr( eEV_N5V_CL );
    sSta.lError &= ~eST_B_IN_N5V;
  }
  if( sIn.wInput & eST_B_IN_N15V )
  {
    if( !( sSta.lError & eST_B_IN_N15V ) )
      EventWr( eEV_N15V_FA );
    sSta.lError |= eST_B_IN_N15V;
  }
  else
  {
    if( ( sSta.lError & eST_B_IN_N15V ) )
      EventWr( eEV_N15V_CL );
    sSta.lError &= ~eST_B_IN_N15V;
  }
  if( sIn.wInput & eST_B_IN_P15V )
  {
    if( !( sSta.lError & eST_B_IN_P15V ) )
      EventWr( eEV_P15V_FA );
    sSta.lError |= eST_B_IN_P15V;
  }
  else
  {
    if( ( sSta.lError & eST_B_IN_P15V ) )
      EventWr( eEV_P15V_CL );
    sSta.lError &= ~eST_B_IN_P15V;
  }
  if( sIn.wInput & eST_B_IN_P24V )
  {
    if( !( sSta.lError & eST_B_IN_P24V ) )
      EventWr( eEV_P24V_FA );
    sSta.lError |= eST_B_IN_P24V;
  }
  else
  {
    if( ( sSta.lError & eST_B_IN_P24V ) )
      EventWr( eEV_P24V_CL );
    sSta.lError &= ~eST_B_IN_P24V;
  }
//<- Event 저장 해야 됨

// Alarm 켜지는 경우 정리 안되어 정리 해달라고 해야 됨
//  sDsp.wAlarm = 0xFF00;
  sDsp.wAlarm = 0x0000;
  if( sSta.lError )   sDsp.wError = 0xFF00;
  else                sDsp.wError = 0x0000;

// Pwr 꺼지는 경우 정리 안되어 정리 해달라고 해야 됨
  LD_PWR_HI;
// Run 꺼지는 경우 정리 안되어 정리 해달라고 해야 됨
  LD_RUN_HI;

  if( sDsp.wAlarm )   LD_ALM_HI;
  else                LD_ALM_LO;
  if( sDsp.wError )   LD_ERR_HI;
  else                LD_ERR_LO;

}




/******************************* TIGERWIN END OF FILE *******************************/
