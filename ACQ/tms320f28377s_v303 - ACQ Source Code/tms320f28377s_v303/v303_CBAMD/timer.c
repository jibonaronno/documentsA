/* ************************************ ************************************ *
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : timer.c
 *
 * ************************************ ************************************ */


/* Includes ------------------------------------------------------------------*/
#include <F28x_Project.h>		// Device Headerfile and Examples Include File

#include "main.h"				    // main Header
#include "timer.h"          // timer Header
#include "adc.h"            // adc Header
#include "rtc.h"            // Rtc Header
#include "emif.h"           // emif Header

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

__interrupt void cpu_timer0_isr(void);
#pragma CODE_SECTION( cpu_timer0_isr, ".TI.ramfunc" );
__interrupt void cpu_timer1_isr(void);
#pragma CODE_SECTION( cpu_timer1_isr, ".TI.ramfunc" );
__interrupt void cpu_timer2_isr(void);
#pragma CODE_SECTION( cpu_timer2_isr, ".TI.ramfunc" );



void Init_Timer( void );


void Init_Timer( void )
{
  EALLOW;
  PieVectTable.TIMER0_INT = &cpu_timer0_isr;
  PieVectTable.TIMER1_INT = &cpu_timer1_isr;
  PieVectTable.TIMER2_INT = &cpu_timer2_isr;
  EDIS;

  IER |= M_INT1;      // Timer0 //
  IER |= M_INT13;     // Timer1 // 50/60Hz 64smaple Counter
  IER |= M_INT14;     // Timer2 //

  PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block


  InitCpuTimers();   // For this example, only initialize the Cpu Timers

  sSetTemp.bFreq50Hz = sSet.bFreq50Hz ^ BIT0;
  Freq_TimeSetting( );


#if(1)
  ConfigCpuTimer(&CpuTimer0, MAIN_CLOCK_MHz, eADC_READ_TIME );
  CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
#endif
#if(0)
  ConfigCpuTimer(&CpuTimer2, MAIN_CLOCK_MHz, eMPRAM_DEFAULT);
  CpuTimer2Regs.TCR.all = 0x0001; // Use write-only instruction to set TSS bit = 0
#endif

}

void Freq_TimeSetting( void )
{
  if( sSetTemp.bFreq50Hz != sSet.bFreq50Hz )
  {
/*
    if( sSet.bFreq50Hz )    ConfigCpuTimer(&CpuTimer1, MAIN_CLOCK_MHz, FREQ_50Hz_CLOCK);
    else                    ConfigCpuTimer(&CpuTimer1, MAIN_CLOCK_MHz, FREQ_60Hz_CLOCK);
    CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
*/
    sSetTemp.bFreq50Hz = sSet.bFreq50Hz;

    if( sSet.bFreq50Hz == eFREQ_60Hz )
    {
//      sSet.w1secCount = 3840;
//      sSet.wFreqTime = ( MAIN_CLOCK_MHz * 1000000 / ( 60*64 ) ) - eTIME_SYNC_CAL;     // 1/60/64
      sSet.wFreqTime = ( MAIN_CLOCK_MHz * 1000000 / ( 60*eSAMPLE_NO ) );     // 1/60/128
    }
    else
    {
//      sSet.w1secCount = 3200;
//      sSet.wFreqTime = ( MAIN_CLOCK_MHz * 1000000 / ( 50*64 ) ) - eTIME_SYNC_CAL;     // 1/50/64
      sSet.wFreqTime = ( MAIN_CLOCK_MHz * 1000000 / ( 50*eSAMPLE_NO ) );     // 1/50/128
    }
    sSet.w1usecCount = 1/(1/MAIN_CLOCK_MHz);

    CpuTimer1Regs.PRD.all = sSet.wFreqTime;
    CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
    CpuTimer1Regs.TIM.all  = 0;
    CpuTimer1Regs.TPR.all = 0x0000;
    CpuTimer1Regs.TPRH.all = 0x0000;

  }

}


//*****************************************************************************
//
// ADC Read Interrupt
// 5usec // 200KSPS = 1/200000=5usec
//
//*****************************************************************************
__interrupt void cpu_timer0_isr(void)
{
  while( ADC_BUSY )
  {
    NOP;
//    LD_ALM_T;
  }
//  LD_ALM_LO;

  Adc_Read();

  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


//*****************************************************************************
//
// ADC Start Interrupt
// 60Hz = 1/60/128
// 50Hz = 1/50/128
//
//*****************************************************************************
__interrupt void cpu_timer1_isr(void)
{
  UINT8   i_bFreq1sec;

//  LD_ALM_HI;

  CpuTimer1Regs.TIM.all  = 0;
  CpuTimer1Regs.PRD.all = sSet.wFreqTime;
  CpuTimer1Regs.TCR.bit.TIF = 1;

  ADC_RST_HI;
  NOP;    NOP;    NOP;    NOP;    NOP;
  ADC_RST_LO;
  NOP;    NOP;    NOP;    NOP;    NOP;

  ADC_CONV_LO;
  NOP;    NOP;    NOP;    NOP;    NOP;
  ADC_CONV_HI;

  CpuTimer0Regs.TIM.all = 0;
  CpuTimer0Regs.PRD.all = sSet.w1usecCount * eADC_READ_TIME;
  CpuTimer0Regs.TCR.bit.TIE = 1;
  CpuTimer0Regs.TCR.bit.TIF = 1;
  PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      // ADC_Read È£Ãâ¿ë
  sCnt.bAdcRead = 0;    // 0: AD CONV -> 1: AD Read

  if( ++sCnt.b64sample >= 2 )
  {
    sCnt.b64sample = 0;
    sSta.bMainLoop = 1;     // 64sample (1/60/64=260.4167usec)
    if( ++sCnt.b16sample >= 4 )
    {
      sCnt.b16sample = 0;
      ++sDsp.Time.wms;
      if( sSet.bFreq50Hz )  i_bFreq1sec = 4;
      else                  i_bFreq1sec = 24;
      if( ++sCnt.bFreq1sec >= i_bFreq1sec )
      {
        sCnt.bFreq1sec = 0;
        ++sDsp.Time.wms;
      }
      if( sDsp.Time.wms >= 1000 )
        sDsp.Time.wms = 999;
      if( sDsp.Time.wms >= 998 )
        sRtc.bTimeRead = 1;
      sDsp.lUtcMs = (UINT32)sDsp.Time.wms;
      if( sSta.bPowerStart )
      {
        Conv_MramWr( (UINT16 *)&pMram->ilUtc, 2, (UINT16 *)&sDsp.ilUtc );
        Conv_MramWr( (UINT16 *)&pMram->lUtcMs, 2, (UINT16 *)&sDsp.lUtcMs );
      }
    }
  }

#if(0)
  Adc_DataFix( );
#endif

}



//*****************************************************************************
//
// MRAM Sync Start Time
//
//*****************************************************************************
__interrupt void cpu_timer2_isr(void)
{
#if(0)
#endif
}



/******************************* TIGERWIN END OF FILE *******************************/
