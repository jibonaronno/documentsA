/* *************************************************************************
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : main.c
 *
 * *************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <F28x_Project.h>         // Device Headerfile and Examples Include File
#include <F2837xS_I2c_defines.h>  //

#include "main.h"                 // main Header
#include "tigerwin.h"             // hw Header
#include "timer.h"                // timer Header
#include "emif.h"                 // emif Header
#include "sci.h"                  // sci Header
#include "adc.h"                  // adc Header
#include "rtc.h"                  // Rtc Header

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

MRAM_DATA *pMram;
EVENT_DATA *pEvent;
FAULT_DATA *pFault;
WAVE_DATA *pWave;
RAW_DATA *pRaw;
ADC_DATA *pAdc;
W5300_DATA *pW5300;
INPUT_REG sIn;
//ERROR_REG sError;
//ERROR_REG sETemp;
//FAULT_REG sFault;
TEST_REG sTest;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
//void Test_Mode(void);
//*****************************************************************************
//
// main 占쎈맙占쎈땾
//
//*****************************************************************************
void main(void)
{
  DINT;

  InitSysCtrl();

  InitPieCtrl();

  IER = 0x0000;
  IFR = 0x0000;

  EALLOW;
  ClkCfgRegs.LOSPCP.all = 1;
  EDIS;

  InitPieVectTable();

  Init_Interrupt();

  Init_SettingRegister();

  Init_EM1();                     // EM1 초기화 || ADC, MRAM, W5300

  Init_Gpio();                    // GPIO 초기화

  Init_MemoryPointer();           // Memory Point초기화

  Init_Register();

  Init_Timer();                   // Timer 초기화

  Init_Sci();

#if(0)    // MRAM/ADC Test 프로그램
#if(1)
  while( 1 )
  {
//    MAIN_RDY_ON;
    ADC_Test( );
  }
#else
  while( 1 )
  {
//    MAIN_RDY_ON;
    MAIN_RDY_OFF;
    EMIF_Test( );
  }
#endif
#endif
//  Init_Interrupt();				// Interrupt 활성화

  EINT;
  // Enable Global __interrupt INTM
  ERTM;
  // Enable Global realtime __interrupt DBGM

  main_loop();

}

/******************************* TIGERWIN END OF FILE *******************************/
