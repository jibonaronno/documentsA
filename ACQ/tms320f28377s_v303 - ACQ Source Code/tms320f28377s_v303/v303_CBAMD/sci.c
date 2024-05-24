/* ************************************ ************************************ *
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : Sci.c
 *
 * ************************************ ************************************ */


#include "F28x_Project.h"       // Device Headerfile and Examples Include File
#include "string.h"             //
#include "stdio.h"              //
//#include "math.h"               // TMU math Header

#include "main.h"        // main Header
#include "sci.h"                // sci Header
#include "modbus.h"             // modbus Header
#include "emif.h"               // emif Header
#include "tigerwin.h"          // h/w config Header
#include "timer.h"              // timer Header
#include "adc.h"                // adc Header
#include "rtc.h"                // i2c Header


DEBUG_REG     sDbg;
KEY_REG       sKey;
EVT_REG       sEvt;
FATRD_REG     sFatRd;
FAT_REG       sFat;


void Init_Sci( void );
void Init_Scia( void );
#if(0)
void Init_Scib( void );
void Init_Scic( void );
void Init_Scid( void );
#endif

__interrupt void sciaRxFifoIsr( void );
#pragma CODE_SECTION( sciaRxFifoIsr, ".TI.ramfunc" );
__interrupt void sciaTxFifoIsr( void );
#pragma CODE_SECTION( sciaTxFifoIsr, ".TI.ramfunc" );

#if(0)
__interrupt void scibRxFifoIsr( void );
#pragma CODE_SECTION( scibRxFifoIsr, ".TI.ramfunc" );
__interrupt void scibTxFifoIsr( void );
#pragma CODE_SECTION( scibTxFifoIsr, ".TI.ramfunc" );

__interrupt void scicRxFifoIsr( void );
#pragma CODE_SECTION( scicRxFifoIsr, ".TI.ramfunc" );
__interrupt void scicTxFifoIsr( void );
#pragma CODE_SECTION( scicTxFifoIsr, ".TI.ramfunc" );

__interrupt void scidRxFifoIsr( void );
#pragma CODE_SECTION( scidRxFifoIsr, ".TI.ramfunc" );
__interrupt void scidTxFifoIsr( void );
#pragma CODE_SECTION( scidTxFifoIsr, ".TI.ramfunc" );
#endif

void Debug_Make( DEBUG_REG *pSci );
#pragma CODE_SECTION( Debug_Make, ".TI.ramfunc" );
void Number_Start( DEBUG_REG *pSci );
#pragma CODE_SECTION( Number_Start, ".TI.ramfunc" );
void Char_Start( DEBUG_REG *pSci );
#pragma CODE_SECTION( Char_Start, ".TI.ramfunc" );
void List_Help( DEBUG_REG *pSci );
#pragma CODE_SECTION( List_Help, ".TI.ramfunc" );
void List_Char( DEBUG_REG *pSci, UINT8 i_bType );
#pragma CODE_SECTION( List_Char, ".TI.ramfunc" );
void List_ShotKey( DEBUG_REG *pSci, UINT8 i_bType, UINT8 i_bData );
#pragma CODE_SECTION( List_ShotKey, ".TI.ramfunc" );

void Terminal_Goto( DEBUG_REG *pSci, UINT8 i_bStartX, UINT8 i_bStartY );
#pragma CODE_SECTION( Terminal_Goto, ".TI.ramfunc" );

UINT16 BCD2DEC( UINT16 i_wBcd );
UINT16 DEC2BCD( UINT16 i_wDec );


char* Debug_TList( UINT16 i_wType, UINT8 i_bData );
char* Debug_TCursor( DEBUG_REG *pSci, UINT16 i_wType );
char* Debug_THelpList( UINT16 i_wType, char *i_pbChr );
char* Debug_THelpListFull( UINT16 i_wType );
char* Setting_View( UINT16 i_wType, char *i_pbChr );

void Debug_Normal( DEBUG_REG *pSci, UINT16 i_wType );
#pragma CODE_SECTION( Debug_Normal, ".TI.ramfunc" );
void Char2WordChar( DEBUG_REG *pSci, float *i_pfValue );
void Char2Float( DEBUG_REG *pSci, float *i_pfValue );
UINT8 Key_MinMax( KEY_REG *pKey );



UINT16 aCrcTableLow[256] = {
  0x00, 0xc0, 0xc1, 0x01, 0xc3, 0x03, 0x02, 0xc2, 0xc6, 0x06, 0x07, 0xc7, 0x05, 0xc5, 0xc4, 0x04, 0xcc, 0x0c, 0x0d, 0xcd,
  0x0f, 0xcf, 0xce, 0x0e, 0x0a, 0xca, 0xcb, 0x0b, 0xc9, 0x09, 0x08, 0xc8, 0xd8, 0x18, 0x19, 0xd9, 0x1b, 0xdb, 0xda, 0x1a,
  0x1e, 0xde, 0xdf, 0x1f, 0xdd, 0x1d, 0x1c, 0xdc, 0x14, 0xd4, 0xd5, 0x15, 0xd7, 0x17, 0x16, 0xd6, 0xd2, 0x12, 0x13, 0xd3,
  0x11, 0xd1, 0xd0, 0x10, 0xf0, 0x30, 0x31, 0xf1, 0x33, 0xf3, 0xf2, 0x32, 0x36, 0xf6, 0xf7, 0x37, 0xf5, 0x35, 0x34, 0xf4,
  0x3c, 0xfc, 0xfd, 0x3d, 0xff, 0x3f, 0x3e, 0xfe, 0xfa, 0x3a, 0x3b, 0xfb, 0x39, 0xf9, 0xf8, 0x38, 0x28, 0xe8, 0xe9, 0x29,
  0xeb, 0x2b, 0x2a, 0xea, 0xee, 0x2e, 0x2f, 0xef, 0x2d, 0xed, 0xec, 0x2c, 0xe4, 0x24, 0x25, 0xe5, 0x27, 0xe7, 0xe6, 0x26,
  0x22, 0xe2, 0xe3, 0x23, 0xe1, 0x21, 0x20, 0xe0, 0xa0, 0x60, 0x61, 0xa1, 0x63, 0xa3, 0xa2, 0x62, 0x66, 0xa6, 0xa7, 0x67,
  0xa5, 0x65, 0x64, 0xa4, 0x6c, 0xac, 0xad, 0x6d, 0xaf, 0x6f, 0x6e, 0xae, 0xaa, 0x6a, 0x6b, 0xab, 0x69, 0xa9, 0xa8, 0x68,
  0x78, 0xb8, 0xb9, 0x79, 0xbb, 0x7b, 0x7a, 0xba, 0xbe, 0x7e, 0x7f, 0xbf, 0x7d, 0xbd, 0xbc, 0x7c, 0xb4, 0x74, 0x75, 0xb5,
  0x77, 0xb7, 0xb6, 0x76, 0x72, 0xb2, 0xb3, 0x73, 0xb1, 0x71, 0x70, 0xb0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
  0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9c, 0x5c, 0x5d, 0x9d, 0x5f, 0x9f, 0x9e, 0x5e, 0x5a, 0x9a, 0x9b, 0x5b,
  0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4b, 0x8b, 0x8a, 0x4a, 0x4e, 0x8e, 0x8f, 0x4f, 0x8d, 0x4d, 0x4c, 0x8c,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40 };
UINT16 aCrcTableHigh[256] = {
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
  0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40,
  0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40,
  0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
  0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
  0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40,
  0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
  0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40   };


void Init_Sci( void )
{

  EALLOW;
  PieVectTable.SCIA_RX_INT = &sciaRxFifoIsr;  // SCIA rx TTL Debug
  PieVectTable.SCIA_TX_INT = &sciaTxFifoIsr;  // SCIA tx

#if(0)
  PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;  // SCIB rx SYNC RS-485
  PieVectTable.SCIB_TX_INT = &scibTxFifoIsr;  // SCIB tx

  PieVectTable.SCIC_RX_INT = &scicRxFifoIsr;  // SCIC rx CN4 RS-232C TTL
  PieVectTable.SCIC_TX_INT = &scicTxFifoIsr;  // SCIC tx

  PieVectTable.SCID_RX_INT = &scidRxFifoIsr;  // SCID rx CN1 RS-232C
  PieVectTable.SCID_TX_INT = &scidTxFifoIsr;  // SCID tx
#endif

    EDIS;

//  IER |= M_INT8;    // SCIC // SCID
  IER |= M_INT9;    // SCIA // SCIB

//  PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block

  PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1 // SCIA_rx
  PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2 // SCIA_tx
#if(0)
  PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3 // SCIB_rx
  PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4 // SCIB_tx
  PieCtrlRegs.PIEIER8.bit.INTx5=1;     // PIE Group 8, INT5 // SCIC_rx
  PieCtrlRegs.PIEIER8.bit.INTx6=1;     // PIE Group 8, INT6 // SCIC_tx
  PieCtrlRegs.PIEIER8.bit.INTx7=1;     // PIE Group 8, INT7 // SCID_rx
  PieCtrlRegs.PIEIER8.bit.INTx8=1;     // PIE Group 8, INT8 // SCID_tx
#endif

#if(1)  
  Init_Scia( );   // SCIA Debug
#endif

#if(0)  
  Init_Scib( );   // SCIB 
  Init_Scic( );   // SCIC 
  Init_Scid( );   // SCID 
#endif

}

void Init_Scia( void )
{
  SciaRegs.SCICCR.all = 0x0007;         // 1 stop bit,  No loopback
                                        // No parity,8 char bits,
                                        // async mode, idle-line protocol
  SciaRegs.SCICTL1.all = 0x0003;        // enable TX, RX, internal SCICLK,
                                        // Disable RX ERR, SLEEP, TXWAKE
  SciaRegs.SCICTL2.bit.TXINTENA   = 1;
  SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
  SciaRegs.SCIHBAUD.all = SCI_PRD_115200 >> 8;
  SciaRegs.SCILBAUD.all = SCI_PRD_115200 % 256;
  SciaRegs.SCICCR.bit.LOOPBKENA = 0;    // Enable loop back
  SciaRegs.SCIFFTX.all  = 0xA0A0;       // 20150723 송신을 어떻게 처리 할 것인지?
  SciaRegs.SCIFFRX.all  = 0x0021;
  SciaRegs.SCIFFCT.all  = 0x00;

  SciaRegs.SCICTL1.all  = 0x0023;       // Relinquish SCI from Reset
  SciaRegs.SCIFFTX.bit.TXFIFORESET = 1;
  SciaRegs.SCIFFRX.bit.RXFIFORESET  = 1;
}

#if(0)
void Init_Scib( void )
{
  ScibRegs.SCICCR.all = 0x0007;         // 1 stop bit,  No loopback
                                        // No parity,8 char bits,
                                        // async mode, idle-line protocol
  ScibRegs.SCICTL1.all = 0x0003;        // enable TX, RX, internal SCICLK,
                                        // Disable RX ERR, SLEEP, TXWAKE
  ScibRegs.SCICTL2.bit.TXINTENA   = 0;
//  ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
  ScibRegs.SCIHBAUD.all = SCI_PRD_921600 >> 8;
  ScibRegs.SCILBAUD.all = SCI_PRD_921600 % 256;
//  ScibRegs.SCIHBAUD.all = SCI_PRD_460800 >> 8;         // STM32F030이 이 속도까지 지원 함
//  ScibRegs.SCILBAUD.all = SCI_PRD_460800 % 256;
//  ScibRegs.SCIHBAUD.all = SCI_PRD_115200 >> 8;         // STM32F030이 이 속도까지 지원 함
//  ScibRegs.SCILBAUD.all = SCI_PRD_115200 % 256;
//  ScibRegs.SCIHBAUD.all = SCI_PRD_76800 >> 8;         // STM32F030이 이 속도까지 지원 함
//  ScibRegs.SCILBAUD.all = SCI_PRD_76800 % 256;
//  ScibRegs.SCIHBAUD.all = SCI_PRD_57600 >> 8;         // STM32F030이 이 속도까지 지원 함
//  ScibRegs.SCILBAUD.all = SCI_PRD_57600 % 256;
//  ScibRegs.SCIHBAUD.all = SCI_PRD_19200 >> 8;         // 이 정도로 낮춰야 에러 없어 짐
//  ScibRegs.SCILBAUD.all = SCI_PRD_19200 % 256;
  ScibRegs.SCICCR.bit.LOOPBKENA = 0;    // Enable loop back
  ScibRegs.SCIFFTX.all  = 0xA0A1;     //
  ScibRegs.SCIFFRX.all  = 0x0021;
  ScibRegs.SCIFFCT.all  = 0x00;

  ScibRegs.SCICTL1.all  = 0x0023;       // Relinquish SCI from Reset
  ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
  ScibRegs.SCIFFRX.bit.RXFIFORESET  = 1;
//  ScibRegs.SCIFFRX.bit.RXFFIENA = 1;
}

void Init_Scic( void )
{
  ScicRegs.SCICCR.all = 0x0007;         // 1 stop bit,  No loopback
                                        // No parity,8 char bits,
                                        // async mode, idle-line protocol
  ScicRegs.SCICTL1.all = 0x0003;        // enable TX, RX, internal SCICLK,
                                        // Disable RX ERR, SLEEP, TXWAKE
  ScicRegs.SCICTL2.bit.TXINTENA   = 1;
  ScicRegs.SCICTL2.bit.RXBKINTENA = 1;
  ScicRegs.SCIHBAUD.all = SCI_PRD_115200 >> 8;
  ScicRegs.SCILBAUD.all = SCI_PRD_115200 % 256;
  ScicRegs.SCICCR.bit.LOOPBKENA = 0;    // Enable loop back
  ScicRegs.SCIFFTX.all  = 0xA0A1;       //
  ScicRegs.SCIFFRX.all  = 0x0021;
  ScicRegs.SCIFFCT.all  = 0x00;

  ScicRegs.SCICTL1.all  = 0x0023;       // Relinquish SCI from Reset
  ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
  ScicRegs.SCIFFRX.bit.RXFIFORESET  = 1;
}

void Init_Scid( void )
{
  ScidRegs.SCICCR.all = 0x0007;         // 1 stop bit,  No loopback
                                        // No parity,8 char bits,
                                        // async mode, idle-line protocol
  ScidRegs.SCICTL1.all = 0x0003;        // enable TX, RX, internal SCICLK,
                                        // Disable RX ERR, SLEEP, TXWAKE
  ScidRegs.SCICTL2.bit.TXINTENA   = 1;
  ScidRegs.SCICTL2.bit.RXBKINTENA = 1;
  ScidRegs.SCIHBAUD.all = SCI_PRD_921600 >> 8;
  ScidRegs.SCILBAUD.all = SCI_PRD_921600 % 256;
  ScidRegs.SCICCR.bit.LOOPBKENA = 0;    // Enable loop back
  ScidRegs.SCIFFTX.all  = 0xA0A1;       //
  ScidRegs.SCIFFRX.all  = 0x0021;
  ScidRegs.SCIFFCT.all  = 0x00;

  ScidRegs.SCICTL1.all  = 0x0023;       // Relinquish SCI from Reset
  ScidRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
  ScidRegs.SCIFFRX.bit.RXFIFORESET  = 1;
}
#endif


interrupt void sciaRxFifoIsr( void )
{
  char    i_bRxData = SciaRegs.SCIRXBUF.all;

  if( i_bRxData != 0x00 || sTest.bModbus == 1 )
  {
    sDbg.bRxData[sDbg.Cnt.bRx++] = i_bRxData;
    sDbg.Cnt.bRx %= eSCI_BUFFER;
  }

  SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
  PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack

//  SciaRegs.SCITXBUF.all = i_bData;
}

interrupt void sciaTxFifoIsr( void )
{
  UINT16  i;

//  SciaRegs.SCITXBUF.all = sDbg.bTxData[sDbg.Cnt.bTx];
  if( sDbg.Cnt.bTx == sDbg.Cnt.bTxEnd )
  {
    sDbg.Cnt.bTx = 0;
    sDbg.Cnt.bTxEnd = 0;
    sDbg.Cnt.bTxOff = 0;
    SciaRegs.SCIFFTX.bit.SCIFFENA = 0;
    SciaRegs.SCICTL2.bit.TXINTENA = 0;    // TX Int
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;  // RX Int
  }
  else
  {
    for( i=0; sDbg.Cnt.bTx != sDbg.Cnt.bTxEnd; i++ )
    {
      if( i >= 8 )
        break;
      SciaRegs.SCITXBUF.all = sDbg.bTxData[sDbg.Cnt.bTx++];
    }
    if( i >= 8 )
      SciaRegs.SCICTL2.bit.TXINTENA = 0;      // TX Int
  }

  SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clea0r SCI Interrupt flag
  PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}


#if(0)
interrupt void scibRxFifoIsr( void )
{
  i_bRxData = ScibRegs.SCIRXBUF.all;
  CpuTimer1Regs.TCR.bit.TIE = 0;

  ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
  PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

interrupt void scibTxFifoIsr( void )
{
  if( sScib.Cnt.bTx == sScib.Cnt.bTxEnd )
  {
    SYNC_PTT_OFF;
    sScib.Cnt.bTx = 0;
    sScib.Cnt.bTxEnd = 0;
    sScib.Cnt.bTxOff = 0;
    ScibRegs.SCIFFTX.bit.SCIFFENA = 0;
    ScibRegs.SCICTL2.bit.TXINTENA = 0;      // TX Int
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;    // RX Int
  }
  else
  {
    SYNC_PTT_ON;
    sCnt.wSyncOff = 0;
    ScibRegs.SCITXBUF.all = sScib.bTxData[sScib.Cnt.bTx++];
  }

  ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
  PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK

}
#endif



void Sci_Make( void )
{
// Main 주기 마다 통신 해야 되므로 인터럽트에서 송신
// PTT OFF는 Timer 동작 시켜야 될 것으로 판단 됨
#if(0)
  if( ++sDbg.Cnt.bTxStart >= eSCI_START_SYNC )
  {
    SciaRegs.SCIFFRX.bit.RXFIFORESET  = 0;
    SYNC_PTT_ON;
    Sync_Tx_Make( &sDbg );
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
  }
#endif

#if(0)
// 매주기마타 통신을 해야 되므로
//  if( ++sScib.Cnt.bTxStart >= eSCI_START_POWER )
  {
    SciㅠRegs.SCIFFRX.bit.RXFIFORESET  = 0;
    POWER_PTT_ON;
    Power_Tx_Make( &sScib );
    SciㅠRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
  }
#endif

//  Sci_Power_Make( &sScib );

#if(1)
  Modbus_Data( );
// -> 20220615 이 부분은 수신이 일정 시간 없으면 수신 버퍼 초기화 시키는 부분임
//  Modbus_Make( &sEth );
// <- 20220615 
//  if( sTest.bModbus )
//    Modbus_Make( &sEth );
//  else
    Debug_Make( &sDbg );
#endif
}



enum    // sKeySet
{
// Password
  eKN_DBG_PASSWORD,

// Ethernet
  eKN_DBG_IP,
  eKN_DBG_SUB,
  eKN_DBG_DEF,
  eKN_DBG_PORT,
  eKN_DBG_LOC,
  eKN_DBG_MAC,

// System
  eKN_DBG_DEBOUNCE,
  eKN_DBG_TRIPNUM,
  eKN_DBG_TRIPCURR,

// List/Fault
  eKN_DBG_NO,

// Etc
  eKN_DBG_MODEL,
  eKN_DBG_SERIAL,
  eKN_DBG_100MS,
  eKN_DBG_500MS,

// Etc/Time
  eKN_DBG_TIME,
  eKN_DBG_YEAR,
  eKN_DBG_MON,
  eKN_DBG_DAY,
  eKN_DBG_HOUR,
  eKN_DBG_MIN,
  eKN_DBG_SEC,

// Cali/Dccali
  eKN_DBG_DCALLRZERO,
  eKN_DBG_DCALLRSPAN,
  eKN_DBG_DC1RZERO,
  eKN_DBG_DC1RSPAN,
  eKN_DBG_DC2RZERO,
  eKN_DBG_DC2RSPAN,
  eKN_DBG_DC3RZERO,
  eKN_DBG_DC3RSPAN,

// Cali/Accali
  eKN_DBG_ACVRZERO,
  eKN_DBG_ACVRSPAN,
  eKN_DBG_ACIRZERO,
  eKN_DBG_ACIRSPAN,
  eKN_DBG_AC1RZERO,
  eKN_DBG_AC1RSPAN,
  eKN_DBG_AC2RZERO,
  eKN_DBG_AC2RSPAN,
  eKN_DBG_AC3RZERO,
  eKN_DBG_AC3RSPAN,
  eKN_DBG_AC4RZERO,
  eKN_DBG_AC4RSPAN,

// Dcratio
  eKN_DBG_DCRATIO,
  eKN_DBG_DCRATIO1,
  eKN_DBG_DCRATIO2,
  eKN_DBG_DCRATIO3,
// Acratio
  eKN_DBG_ACVRATIO,
  eKN_DBG_ACIRATIO,
  eKN_DBG_ACRATIO1,
  eKN_DBG_ACRATIO2,
  eKN_DBG_ACRATIO3,
  eKN_DBG_ACRATIO4,
  eKN_MAX,
  
};
KEY_REG sKeySet[] =
{
//  bPageBack           bPageGo             bNo     ibDotP          wMul    bMode               *pbKey          *pibKey   *pwKey                      *piwKey   *plKey    *pilKey   *pfKey              fKey      fMin              fMax
// Password
  { eST_DBG_EXIT,       eST_DBG_PASSWORD,   1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sSet.wPass,                0,        0,        0,        0,                        0,        eSV_PASS_MIN,     eSV_PASS_MAX      },    // 

// Ethernet
  { eST_DBG_ETHER,      eST_DBG_IP,         4,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16_IP,  0,              0,        &sDsp.wIpAddr[0],           0,        0,        0,        0,                        0,        eSV_ETH_MIN,      eSV_ETH_MAX       },    // IP Address       255.255.255.255
  { eST_DBG_ETHER,      eST_DBG_SUB,        4,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16_IP,  0,              0,        &sDsp.wSubMask[0],          0,        0,        0,        0,                        0,        eSV_ETH_MIN,      eSV_ETH_MAX       },    // Subnet mask      255.255.255.255
  { eST_DBG_ETHER,      eST_DBG_DEF,        4,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16_IP,  0,              0,        &sDsp.wDefGate[0],          0,        0,        0,        0,                        0,        eSV_ETH_MIN,      eSV_ETH_MAX       },    // Default gateway  255.255.255.255
  { eST_DBG_ETHER,      eST_DBG_PORT,       1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wPortNum,             0,        0,        0,        0,                        0,        eSV_POT_MIN,      eSV_POT_MAX       },    // Port number      0~65535
  { eST_DBG_ETHER,      eST_DBG_LOC,        4,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16_IP,  0,              0,        &sDsp.wLocIpAddr[0],        0,        0,        0,        0,                        0,        eSV_ETH_MIN,      eSV_ETH_MAX       },    // Local ip address 255.255.255.255
  { eST_DBG_ETHER,      eST_DBG_MAC,        18,     eKEY_DOT_1000,  1,      eKEY_MD_UINT16_MAC, 0,              0,        &sSet.wMac[0],              0,        0,        0,        0,                        0,        eSV_ETH_MIN,      eSV_ETH_MAX       },    // MAC 10:11:12:13:14:15

// System
  { eST_DBG_SYS,        eST_DBG_DEBOUNCE,   1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wDebo,                0,        0,        0,        0,                        0,        eSV_DEBO_MIN,     eSV_DEBO_MAX      },    // Debounce
  { eST_DBG_SYS,        eST_DBG_TRIPNUM,    1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wTrig,                0,        0,        0,        0,                        0,        eSV_TRIG_MIN,     eSV_TRIG_MAX      },    // Trig Number
  { eST_DBG_SYS,        eST_DBG_TRIPCURR,   2,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sDsp.wTrip[0],             0,        0,        0,        0,                        0,        eSV_TRIP_MIN,     eSV_TRIP_MAX      },    // Trig Coil

// List/Fault
  { eST_DBG_FAULT,      eST_DBG_NO,         1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sFat.wNo,                  0,        0,        0,        0,                        0,        1,                26                },    // Fault 파형 No

// Etc
//  { eST_DBG_ETC,        eST_DBG_NEWPASS,    1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sSet.wPass,                0,        0,        0,        0,                  0,        eSV_PASS_MIN,     eSV_PASS_MAX      },    // 
//  { eST_DBG_ETC,        eST_DBG_RE_ENTPASS, 1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sSet.wPass,                0,        0,        0,        0,                  0,        eSV_PASS_MIN,     eSV_PASS_MAX      },    // 
//  { eST_DBG_ETC,        eST_DBG_SERIAL,     32,     eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wSerial[0],           0,        0,        0,        0,                        0,        0,                0                 },    //
  { eST_DBG_ETC,        eST_DBG_MODEL,      16,     eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wModel[0],            0,        0,        0,        0,                        0,        0,                0                 },    //
  { eST_DBG_ETC,        eST_DBG_SERIAL,     32,     eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sDsp.wSerial[0],           0,        0,        0,        0,                        0,        0,                0                 },    //
  { eST_DBG_ETC,        eST_DBG_100MS,      1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sSet.wNo100ms,             0,        0,        0,        0,                        0,        eSV_NO100MS_MIN,  eSV_NO100MS_MAX   },    // 
  { eST_DBG_ETC,        eST_DBG_500MS,      1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        &sSet.wNo500ms,             0,        0,        0,        0,                        0,        eSV_NO500MS_MIN,  eSV_NO500MS_MAX   },    // 

// Time
  { eST_DBG_TIME,       eST_DBG_TIME,       1,      eKEY_DOT_1000,  1,      eKEY_MD_TIME,       0,              0,        (UINT16 *)&sSet.Time.bYY,   0,        0,        0,        0,                        0,        eSV_TIM_YY_MIN,   eSV_TIM_YY_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_YEAR,       1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bYY,   0,        0,        0,        0,                        0,        eSV_TIM_YY_MIN,   eSV_TIM_YY_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_MON,        1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bMM,   0,        0,        0,        0,                        0,        eSV_TIM_MM_MIN,   eSV_TIM_MM_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_DAY,        1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bDD,   0,        0,        0,        0,                        0,        eSV_TIM_DD_MIN,   eSV_TIM_DD_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_HOUR,       1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bhh,   0,        0,        0,        0,                        0,        eSV_TIM_hh_MIN,   eSV_TIM_hh_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_MIN,        1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bmm,   0,        0,        0,        0,                        0,        eSV_TIM_mm_MIN,   eSV_TIM_mm_MAX    },    // 
  { eST_DBG_TIME,       eST_DBG_SEC,        1,      eKEY_DOT_1000,  1,      eKEY_MD_UINT16,     0,              0,        (UINT16 *)&sSet.Time.bss,   0,        0,        0,        0,                        0,        eSV_TIM_ss_MIN,   eSV_TIM_ss_MAX    },    // 

// Dccali
  { eST_DBG_DCALL_ZERO, eST_DBG_DCALLRZERO, 3,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[1],              0,        0,        0,        0,                        0,        eSV_DCZER_MIN,    eSV_DCZER_MAX     },    // 0~1
  { eST_DBG_DCALL_SPAN, eST_DBG_DCALLRSPAN, 3,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[1],              0,        0,        0,        0,                        0,        eSV_DCSPR_MIN,    eSV_DCSPR_MAX     },    // 0.1~6
  { eST_DBG_DC1_ZERO,   eST_DBG_DC1RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[1],              0,        0,        0,        0,                        0,        eSV_DCZER_MIN,    eSV_DCZER_MAX     },    // 1
  { eST_DBG_DC1_SPAN,   eST_DBG_DC1RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[1],              0,        0,        0,        0,                        0,        eSV_DCSPR_MIN,    eSV_DCSPR_MAX     },    // 5
  { eST_DBG_DC2_ZERO,   eST_DBG_DC2RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[2],              0,        0,        0,        0,                        0,        eSV_DCZER_MIN,    eSV_DCZER_MAX     },    // 1
  { eST_DBG_DC2_SPAN,   eST_DBG_DC2RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[2],              0,        0,        0,        0,                        0,        eSV_DCSPR_MIN,    eSV_DCSPR_MAX     },    // 5
  { eST_DBG_DC3_ZERO,   eST_DBG_DC3RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[3],              0,        0,        0,        0,                        0,        eSV_DCZER_MIN,    eSV_DCZER_MAX     },    // 1
  { eST_DBG_DC3_SPAN,   eST_DBG_DC3RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[3],              0,        0,        0,        0,                        0,        eSV_DCSPR_MIN,    eSV_DCSPR_MAX     },    // 5

// Accali
  { eST_DBG_ACALL_ZERO, eST_DBG_ACVRZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[4],              0,        0,        0,        0,                        0,        eSV_ACVZER_MIN,   eSV_ACVZER_MAX    },    // 0~10V
  { eST_DBG_ACALL_SPAN, eST_DBG_ACVRSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[4],              0,        0,        0,        0,                        0,        eSV_ACVSPR_MIN,   eSV_ACVSPR_MAX    },    // 10~200V
  { eST_DBG_ACALL_ZERO, eST_DBG_ACIRZERO,   3,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[5],              0,        0,        0,        0,                        0,        eSV_ACIZER_MIN,   eSV_ACIZER_MAX    },    // 0~10A
  { eST_DBG_ACALL_SPAN, eST_DBG_ACIRSPAN,   3,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[5],              0,        0,        0,        0,                        0,        eSV_ACISPR_MIN,   eSV_ACISPR_MAX    },    // 1~20A
  { eST_DBG_AC1_ZERO,   eST_DBG_AC1RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[4],              0,        0,        0,        0,                        0,        eSV_ACVZER_MIN,   eSV_ACVZER_MAX    },    // 0~10V
  { eST_DBG_AC1_SPAN,   eST_DBG_AC1RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[4],              0,        0,        0,        0,                        0,        eSV_ACVSPR_MIN,   eSV_ACVSPR_MAX    },    // 10~200V
  { eST_DBG_AC2_ZERO,   eST_DBG_AC2RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[5],              0,        0,        0,        0,                        0,        eSV_ACIZER_MIN,   eSV_ACIZER_MAX    },    // 0~10A
  { eST_DBG_AC2_SPAN,   eST_DBG_AC2RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[5],              0,        0,        0,        0,                        0,        eSV_ACISPR_MIN,   eSV_ACISPR_MAX    },    // 1~20A
  { eST_DBG_AC3_ZERO,   eST_DBG_AC3RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[6],              0,        0,        0,        0,                        0,        eSV_ACIZER_MIN,   eSV_ACIZER_MAX    },    // 0~10A
  { eST_DBG_AC3_SPAN,   eST_DBG_AC3RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[6],              0,        0,        0,        0,                        0,        eSV_ACISPR_MIN,   eSV_ACISPR_MAX    },    // 1~20A
  { eST_DBG_AC4_ZERO,   eST_DBG_AC4RZERO,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wZeR[7],              0,        0,        0,        0,                        0,        eSV_ACIZER_MIN,   eSV_ACIZER_MAX    },    // 0~10A
  { eST_DBG_AC4_SPAN,   eST_DBG_AC4RSPAN,   1,      eKEY_DOT_1000,  10,     eKEY_MD_UINT16,     0,              0,        &sSet.wSpR[7],              0,        0,        0,        0,                        0,        eSV_ACISPR_MIN,   eSV_ACISPR_MAX    },    // 1~20A

// Dcratio
  { eST_DBG_DC_RATIO,   eST_DBG_DCRATIO,    3,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_TC1],   0,        eSV_DCRATIO_MIN,  eSV_DCRATIO_MAX   },
  { eST_DBG_DC_RATIO,   eST_DBG_DCRATIO1,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_TC1],   0,        eSV_DCRATIO_MIN,  eSV_DCRATIO_MAX   },
  { eST_DBG_DC_RATIO,   eST_DBG_DCRATIO2,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_TC2],   0,        eSV_DCRATIO_MIN,  eSV_DCRATIO_MAX   },
  { eST_DBG_DC_RATIO,   eST_DBG_DCRATIO3,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_CC],    0,        eSV_DCRATIO_MIN,  eSV_DCRATIO_MAX   },
// Acratio
  { eST_DBG_AC_RATIO,   eST_DBG_ACVRATIO,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_V],     0,        eSV_ACVRATIO_MIN, eSV_ACVRATIO_MAX  },
  { eST_DBG_AC_RATIO,   eST_DBG_ACIRATIO,   3,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_IA],    0,        eSV_ACIRATIO_MIN, eSV_ACIRATIO_MAX  },
  { eST_DBG_AC_RATIO,   eST_DBG_ACRATIO1,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_V],     0,        eSV_ACVRATIO_MIN, eSV_ACVRATIO_MAX  },
  { eST_DBG_AC_RATIO,   eST_DBG_ACRATIO2,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_IA],    0,        eSV_ACIRATIO_MIN, eSV_ACIRATIO_MAX  },
  { eST_DBG_AC_RATIO,   eST_DBG_ACRATIO3,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_IB],    0,        eSV_ACIRATIO_MIN, eSV_ACIRATIO_MAX  },
  { eST_DBG_AC_RATIO,   eST_DBG_ACRATIO4,   1,      eKEY_DOT_1000,  1,      eKEY_MD_FLOAT,      0,              0,        0,                          0,        0,        0,        &sSet.fRatio[eADC_IC],    0,        eSV_ACIRATIO_MIN, eSV_ACIRATIO_MAX  },
};

//float   fValue[6];
char    *pbChr[32];
char    *pbChr2[32];
void Debug_Make( DEBUG_REG *pSci )
{
  UINT16  i, j, k;
  char    i_bData;
  UINT16  i_wData;

  if( pSci->Cnt.bTxEnd != 0 )
    return;

  for( ; pSci->Cnt.bRx != pSci->Cnt.bRxEnd; )
  {
    pSci->bTxData[0] = 0;

    i_bData = pSci->bRxData[pSci->Cnt.bRxEnd++];
    pSci->Cnt.bRxEnd %= eSCI_BUFFER;

    if( pSci->Stp.bType != eST_DBG_CHAR && ( i_bData >= 'a' && i_bData <= 'z' ) )
      i_bData -= ( 'a' - 'A' );
// Debug Start
    switch( pSci->Stp.bType )
    {
    default:
    case eST_DBG_LOGO:
    case eST_DBG_VIEW:
    break;
    case eST_DBG_NORMAL:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_RESET )     pSci->Stp.bType = eST_DBG_RESET;
        else if( pSci->bCmd == eK_SETTING ){  pSci->Stp.bView = eST_LINE_HELP_STA;    sKey = sKeySet[eKN_DBG_PASSWORD];  Number_Start( pSci );  }
//        else if( pSci->bCmd == eK_SETTING ){  pSci->Stp.bView = eST_LINE_HELP_STA;    pSci->Stp.bType = eST_DBG_SETTING;    }
        else if( pSci->bCmd == eK_DEBUG )  {  pSci->Stp.bView = eST_LINE_STA;         pSci->Stp.bType = eST_DBG_DEBUG;      }
        else if( pSci->bCmd == eK_CLEAR )  {  pSci->Stp.bType = eST_DBG_BACK;         sKey.bPageBack = eST_DBG_EXIT;        }
        else if( pSci->bCmd == eK_LOGO )      pSci->Stp.bType = eST_DBG_LOGO;
        else if( pSci->bCmd == eK_VIEW )   {  pSci->Stp.bView = 0;                    pSci->Stp.bType = eST_DBG_VIEW;       }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_SETTING || i_bData == eK_DEBUG || i_bData == eK_RESET || i_bData == eK_CLEAR || i_bData == eK_LOGO || i_bData == eK_VIEW )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_CLEAR:   // 사용하지 않음
    case eST_DBG_RESET:
    case eST_DBG_HELP:    // 사용하지 않음
    case eST_DBG_EXIT:    // 사용하지 않음
    case eST_DBG_BACK:    // 사용하지 않음
    break;
    case eST_DBG_PASSWORD:
    break;
    case eST_DBG_SETTING:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_ETHER )     pSci->Stp.bType = eST_DBG_ETHER;
        else if( pSci->bCmd == eK_SYS )       pSci->Stp.bType = eST_DBG_SYS;
        else if( pSci->bCmd == eK_LIST )      pSci->Stp.bType = eST_DBG_LIST;
        else if( pSci->bCmd == eK_ETC )       pSci->Stp.bType = eST_DBG_ETC;
        else if( pSci->bCmd == eK_FACT ){     pSci->Stp.bView = eST_LINE_STA;   pSci->Stp.bType = eST_DBG_FACT;   }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_ETHER || i_bData == eK_SYS || i_bData == eK_LIST || i_bData == eK_ETC || i_bData == eK_FACT )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_ETHER:
#if(1)    // 20220606 이 부분은 동작 확인 해야 됨
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SETTING; }
        else if( pSci->bCmd == eK_IP )  {                             sKey = sKeySet[eKN_DBG_IP];       Number_Start( pSci );             }
        else if( pSci->bCmd == eK_SUB ) {                             sKey = sKeySet[eKN_DBG_SUB];      Number_Start( pSci );             }
        else if( pSci->bCmd == eK_DEF ) {                             sKey = sKeySet[eKN_DBG_DEF];      Number_Start( pSci );             }
        else if( pSci->bCmd == eK_PORT ){                             sKey = sKeySet[eKN_DBG_PORT];     Number_Start( pSci );             }
//        else if( pSci->bCmd == eK_LOC ) {                             sKey = sKeySet[eKN_DBG_LOC];      Number_Start( pSci );             }
        else if( sDsp.wLv == eST_LV1 && pSci->bCmd == eK_MAC )
                                        {     pSci->Stp.bView = 0;    sKey = sKeySet[eKN_DBG_MAC];      Char_Start( pSci );               }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_IP || i_bData == eK_SUB || i_bData == eK_DEF || i_bData == eK_PORT )
//        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_IP || i_bData == eK_SUB || i_bData == eK_DEF || i_bData == eK_PORT || i_bData == eK_LOC )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
#else
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )
          sprintf( pSci->bTxData, "\n\r %s\n\rTHOMAS%s ", Debug_THelpListFull( pSci->Stp.bType ), Debug_TCursor( pSci, pSci->Stp.bType ) );
        else if( pSci->bCmd == eK_EXIT )
        {
          pSci->Stp.bView = 0;
          pSci->Stp.bType = eST_DBG_BACK;
          sKey.bPageBack = eST_DBG_EXIT;
        }
        else if( pSci->bCmd == eK_BACK )
        {
          pSci->Stp.bView = 0;
          pSci->Stp.bType = eST_DBG_BACK;
          sKey.bPageBack = eST_DBG_SETTING;
        }
        else if( pSci->bCmd == eK_IP )
        {
          sKey = sKeySet[eKN_DBG_IP];
          Number_Start( pSci );
        }
        else if( pSci->bCmd == eK_SUB )
        {
          sKey = sKeySet[eKN_DBG_SUB];
          Number_Start( pSci );
        }
        else if( pSci->bCmd == eK_DEF )
        {
          sKey = sKeySet[eKN_DBG_DEF];
          Number_Start( pSci );
        }
        else if( pSci->bCmd == eK_PORT )
        {
          sKey = sKeySet[eKN_DBG_PORT];
          Number_Start( pSci );
        }
//        else if( pSci->bCmd == eK_LOC )
//        {
//          sKey = sKeySet[eKN_DBG_LOC];
//          Number_Start( pSci );
//        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_IP || i_bData == eK_SUB || i_bData == eK_DEF || i_bData == eK_PORT )
//        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_IP || i_bData == eK_SUB || i_bData == eK_DEF || i_bData == eK_PORT || i_bData == eK_LOC )
          sprintf( pSci->bTxData, "\r                       \rTHOMAS%s %s", Debug_TCursor( pSci, pSci->Stp.bType ), Debug_TList( pSci->Stp.bType, i_bData ) );
      }
#endif
    break;
    case eST_DBG_LIST:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SETTING; }
        else if( pSci->bCmd == eK_EVENT ){    pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_EVENT;  }
        else if( pSci->bCmd == eK_FAULT ){    pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_FAULT;  }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_EVENT || i_bData == eK_FAULT )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_SYS:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SETTING; }
        else if( pSci->bCmd == eK_DEBOUNCE ){                         sKey = sKeySet[eKN_DBG_DEBOUNCE]; Number_Start( pSci );             }
        else if( pSci->bCmd == eK_TRIPNUM ) {                         sKey = sKeySet[eKN_DBG_TRIPNUM];  Number_Start( pSci );             }
        else if( pSci->bCmd == eK_TRIPCURR ){                         sKey = sKeySet[eKN_DBG_TRIPCURR]; Number_Start( pSci );             }
        else if( pSci->bCmd == eK_RATIO )   {                         pSci->Stp.bType = eST_DBG_RATIO;  }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_DEBOUNCE || i_bData == eK_TRIPNUM || i_bData == eK_TRIPCURR || i_bData == eK_DCRATIO )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_ETC:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;      }
        else if( pSci->bCmd == eK_BACK )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SETTING;   }
        else if( pSci->bCmd == eK_TIME )      pSci->Stp.bType = eST_DBG_TIME;
        else if( pSci->bCmd == eK_PASS )    { sKey = sKeySet[eKN_DBG_PASSWORD]; sKey.bPageBack = eST_DBG_ETC; sKey.bPageGo = eST_DBG_NEWPASS; Number_Start( pSci ); }
        else if( pSci->bCmd == eK_MODEL )   { pSci->Stp.bView = 0;    sKey = sKeySet[eKN_DBG_MODEL];    Char_Start( pSci );                 }
        else if( pSci->bCmd == eK_SERIAL )  { pSci->Stp.bView = 0;    sKey = sKeySet[eKN_DBG_SERIAL];   Char_Start( pSci );                 }
        else if( pSci->bCmd == eK_100MS )   {                         sKey = sKeySet[eKN_DBG_100MS];    Number_Start( pSci );               }
        else if( pSci->bCmd == eK_500MS )   {                         sKey = sKeySet[eKN_DBG_500MS];    Number_Start( pSci );               }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_TIME || i_bData == eK_PASS || i_bData == eK_MODEL || i_bData == eK_SERIAL || i_bData == eK_100MS || i_bData == eK_500MS )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_FACT:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;      }
        else if( pSci->bCmd == eK_BACK )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SETTING;   }
        else if( pSci->bCmd == eK_ACCALI ){   pSci->Stp.bType = eST_DBG_ACCALI; pSci->bCmdCount = 0;    for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;  }
        else if( pSci->bCmd == eK_DCCALI ){   pSci->Stp.bType = eST_DBG_DCCALI; pSci->bCmdCount = 0;    for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;  }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_ACCALI || i_bData == eK_DCCALI )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_IP:
    case eST_DBG_SUB:
    case eST_DBG_DEF:
    case eST_DBG_PORT:
    case eST_DBG_LOC:
    case eST_DBG_MAC:
    case eST_DBG_DEBOUNCE:
    case eST_DBG_TRIPNUM:
    case eST_DBG_TRIPCURR:
//    break;
    case eST_DBG_MODEL:
    case eST_DBG_SERIAL:
    case eST_DBG_100MS:
    case eST_DBG_500MS:
    break;

    case eST_DBG_EVENT:
    case eST_DBG_FAULT:
      if( i_bData == eK_ENT || i_bData == eK_BACKSLASH )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
//        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )    { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_LIST;    }
#if(1)
        else if( pSci->Stp.bType == eST_DBG_EVENT )
        {
          if( pSci->bCmd == eK_E_ERASE )    { pSci->Stp.bView = 0;    pMram->wEv = sCnt.wEv = eEVENT_EMPTY;   EventWr( eEV_ERASE );       }
          else if( pSci->bCmd == eK_E_LIST ){ pSci->Stp.bView = 0;                                                                        }
        }
        else if( pSci->Stp.bType == eST_DBG_FAULT )
        {
          if( pSci->bCmd == eK_F_ERASE )    { pSci->Stp.bView = 0;    pMram->wFaNum = pMram->wFaMb = pMram->wFaEnd = sCnt.wFaNum = sCnt.wFaMb = sCnt.wFa = sCnt.wFaEnd = eFAULT_EMPTY; }
          else if( pSci->bCmd == eK_F_LIST ){ pSci->Stp.bView = 0;                                                                        }
          else if( sDsp.wLv == eST_LV1 )
          {
            if( i_bData == eK_BACKSLASH )   sTest.b1Line = 1;
            else                            sTest.b1Line = 0;
            if( pSci->bCmd == eK_NO ){   pSci->Stp.bView = eST_LINE_HELP_STA;    sKey = sKeySet[eKN_DBG_NO];   Number_Start( pSci );   }
            else
            {
                   if( pSci->bCmd == eK_NUM1 )  sFat.wList = eK_NUM1;
              else if( pSci->bCmd == eK_NUM2 )  sFat.wList = eK_NUM2;
              else if( pSci->bCmd == eK_NUM3 )  sFat.wList = eK_NUM3;
              else if( pSci->bCmd == eK_NUM4 )  sFat.wList = eK_NUM4;
              else if( pSci->bCmd == eK_NUM5 )  sFat.wList = eK_NUM5;
              else if( pSci->bCmd == eK_NUM6 )  sFat.wList = eK_NUM6;
              else if( pSci->bCmd == eK_NUM7 )  sFat.wList = eK_NUM7;
              else if( pSci->bCmd == eK_NUM8 )  sFat.wList = eK_NUM8;
              else                              sFat.wList = 0;
              if( sFat.wList )
              {
                pSci->Stp.bView = 0;
                sFat.wPit = 0;
                if( sFat.wNo == 0 || sFat.wNo > 26 )
                  sFat.wNo = 1;
              }
            }
          }
        }
#else
        else if( pSci->bCmd == eK_E_LIST )  { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_E_LIST; sKey.bPageBack = eST_DBG_EVENT;   }
        else if( pSci->bCmd == eK_E_ERASE )   pMram->wEvt = sCnt.wEv = 0;
        else if( pSci->bCmd == eK_F_LIST )  { pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_F_LIST; sKey.bPageBack = eST_DBG_FAULT;   }
        else if( pSci->bCmd == eK_F_ERASE )   pMram->wFa = sCnt.wFa = pMram->wFaEnd = sCnt.wFaEnd = 0;
#endif
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_E_LIST || i_bData == eK_E_ERASE || i_bData == eK_F_LIST || i_bData == eK_F_ERASE )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        else if( sDsp.wLv == eST_LV1 && pSci->Stp.bType == eST_DBG_FAULT && ( i_bData == eK_NO || i_bData == eK_NUM1 || i_bData == eK_NUM2 || i_bData == eK_NUM3 || i_bData == eK_NUM4 || i_bData == eK_NUM5 || i_bData == eK_NUM6 || i_bData == eK_NUM7 || i_bData == eK_NUM8 ) )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_E_ERASE:
    case eST_DBG_F_ERASE:
    break;
    case eST_DBG_E_LIST:
    case eST_DBG_F_LIST:
    case eST_DBG_NO:
    break;
    case eST_DBG_TIME:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_ETC;     }
        else if( pSci->bCmd == eK_YEAR ){                             sKey = sKeySet[eKN_DBG_YEAR];     Number_Start( pSci );             }
        else if( pSci->bCmd == eK_MON ) {                             sKey = sKeySet[eKN_DBG_MON];      Number_Start( pSci );             }
        else if( pSci->bCmd == eK_DAY ) {                             sKey = sKeySet[eKN_DBG_DAY];      Number_Start( pSci );             }
        else if( pSci->bCmd == eK_HOUR ){                             sKey = sKeySet[eKN_DBG_HOUR];     Number_Start( pSci );             }
        else if( pSci->bCmd == eK_MIN ) {                             sKey = sKeySet[eKN_DBG_MIN];      Number_Start( pSci );             }
        else if( pSci->bCmd == eK_SEC ) {                             sKey = sKeySet[eKN_DBG_SEC];      Number_Start( pSci );             }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_YEAR || i_bData == eK_MON || i_bData == eK_DAY || i_bData == eK_HOUR || i_bData == eK_MIN || i_bData == eK_SEC )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_NEWPASS:
    case eST_DBG_RE_ENTPASS:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_HELP;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK ){     pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_ETC;     }
        else if( pSci->bCmd == eK_PASS ){     sKey = sKeySet[eKN_DBG_PASSWORD];   sKey.bPageBack = eST_DBG_ETC, sKey.bPageGo = eST_DBG_NEWPASS, Number_Start( pSci );   }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_PASS )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_DEBUG:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )  {   pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )  {   pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_DCCALI )    pSci->Stp.bType = eST_DBG_DCCALI;
        else if( pSci->bCmd == eK_ACCALI )    pSci->Stp.bType = eST_DBG_ACCALI;
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_DCCALI || i_bData == eK_ACCALI )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_DCCALI:
    case eST_DBG_ACCALI:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_FACT;    }
        else if( pSci->Stp.bType == eST_DBG_DCCALI )
        {
          if( pSci->bCmd == eK_DCALL )        pSci->Stp.bType = eST_DBG_DCALL;
          else if( pSci->bCmd == eK_DC1 )     pSci->Stp.bType = eST_DBG_DC1;
          else if( pSci->bCmd == eK_DC2 )     pSci->Stp.bType = eST_DBG_DC2;
          else if( pSci->bCmd == eK_DC3 )     pSci->Stp.bType = eST_DBG_DC3;
          else if( pSci->bCmd == eK_DC_RATIO )pSci->Stp.bType = eST_DBG_DC_RATIO;
        }
        else if( pSci->Stp.bType == eST_DBG_ACCALI )
        {
          if( pSci->bCmd == eK_ACALL )        pSci->Stp.bType = eST_DBG_ACALL;
          else if( pSci->bCmd == eK_AC1 )     pSci->Stp.bType = eST_DBG_AC1;
          else if( pSci->bCmd == eK_AC2 )     pSci->Stp.bType = eST_DBG_AC2;
          else if( pSci->bCmd == eK_AC3 )     pSci->Stp.bType = eST_DBG_AC3;
          else if( pSci->bCmd == eK_AC4 )     pSci->Stp.bType = eST_DBG_AC4;
          else if( pSci->bCmd == eK_PH )      pSci->Stp.bType = eST_DBG_PH;
          else if( pSci->bCmd == eK_AC_RATIO )pSci->Stp.bType = eST_DBG_AC_RATIO;
        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
             if( pSci->Stp.bType == eST_DBG_DCCALI )
        {
          if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_DCALL || i_bData == eK_DC1 || i_bData == eK_DC2 || i_bData == eK_DC3 || i_bData == eK_DCRATIO )
            List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        }
        else if( pSci->Stp.bType == eST_DBG_ACCALI )
        {
          if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_ACALL || i_bData == eK_AC1 || i_bData == eK_AC2 || i_bData == eK_AC3 || i_bData == eK_AC4 || i_bData == eK_ACRATIO || i_bData == eK_PH )
            List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        }
      }
    break;
    case eST_DBG_DCALL:
    case eST_DBG_DC1:
    case eST_DBG_DC2:
    case eST_DBG_DC3:
    case eST_DBG_ACALL:
    case eST_DBG_AC1:
    case eST_DBG_AC2:
    case eST_DBG_AC3:
    case eST_DBG_AC4:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT ){     pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )
        {
          if( pSci->Stp.bType == eST_DBG_DCALL || pSci->Stp.bType == eST_DBG_DC1 || pSci->Stp.bType == eST_DBG_DC2 || pSci->Stp.bType == eST_DBG_DC3 )
            sKey.bPageBack = eST_DBG_DCCALI;
          else                                    sKey.bPageBack = eST_DBG_ACCALI;
          pSci->Stp.bType = eST_DBG_BACK;
        }
        else if( pSci->bCmd == eK_ZERO )
        {
               if( pSci->Stp.bType == eST_DBG_DCALL ) pSci->Stp.bType = eST_DBG_DCALL_ZERO;
          else if( pSci->Stp.bType == eST_DBG_DC1 )   pSci->Stp.bType = eST_DBG_DC1_ZERO;
          else if( pSci->Stp.bType == eST_DBG_DC2 )   pSci->Stp.bType = eST_DBG_DC2_ZERO;
          else if( pSci->Stp.bType == eST_DBG_DC3 )   pSci->Stp.bType = eST_DBG_DC3_ZERO;
          else if( pSci->Stp.bType == eST_DBG_ACALL ) pSci->Stp.bType = eST_DBG_ACALL_ZERO;
          else if( pSci->Stp.bType == eST_DBG_AC1 )   pSci->Stp.bType = eST_DBG_AC1_ZERO;
          else if( pSci->Stp.bType == eST_DBG_AC2 )   pSci->Stp.bType = eST_DBG_AC2_ZERO;
          else if( pSci->Stp.bType == eST_DBG_AC3 )   pSci->Stp.bType = eST_DBG_AC3_ZERO;
          else if( pSci->Stp.bType == eST_DBG_AC4 )   pSci->Stp.bType = eST_DBG_AC4_ZERO;
        }
        else if( pSci->bCmd == eK_SPAN )
        {
               if( pSci->Stp.bType == eST_DBG_DCALL ) pSci->Stp.bType = eST_DBG_DCALL_SPAN;
          else if( pSci->Stp.bType == eST_DBG_DC1 )   pSci->Stp.bType = eST_DBG_DC1_SPAN;
          else if( pSci->Stp.bType == eST_DBG_DC2 )   pSci->Stp.bType = eST_DBG_DC2_SPAN;
          else if( pSci->Stp.bType == eST_DBG_DC3 )   pSci->Stp.bType = eST_DBG_DC3_SPAN;
          else if( pSci->Stp.bType == eST_DBG_ACALL ) pSci->Stp.bType = eST_DBG_ACALL_SPAN;
          else if( pSci->Stp.bType == eST_DBG_AC1 )   pSci->Stp.bType = eST_DBG_AC1_SPAN;
          else if( pSci->Stp.bType == eST_DBG_AC2 )   pSci->Stp.bType = eST_DBG_AC2_SPAN;
          else if( pSci->Stp.bType == eST_DBG_AC3 )   pSci->Stp.bType = eST_DBG_AC3_SPAN;
          else if( pSci->Stp.bType == eST_DBG_AC4 )   pSci->Stp.bType = eST_DBG_AC4_SPAN;
        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_ZERO || i_bData == eK_SPAN )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_PH:
      if( i_bData == eK_ENT )
      {
        pSci->bCmdTy = pSci->Stp.bType;
        pSci->bCmdSub = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmdSub == eK_HELP )        List_Help( pSci );
        else if( pSci->bCmdSub == eK_EXIT ){  pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmdSub == eK_BACK ){                          sKey.bPageBack = eST_DBG_ACCALI;  pSci->Stp.bType = eST_DBG_BACK;   }
        else if( pSci->bCmdSub == eK_SAVE )
        {
          sSet.fPh[eADC_V] = 0.0;
//          sSet.fPh[eADC_V] = sInt.f500Real[eINT_VP];
          sSet.fPh[eADC_IA] = sInt.f500Real[eINT_IAP];
          sSet.fPh[eADC_IB] = sInt.f500Real[eINT_IBP];
          sSet.fPh[eADC_IC] = sInt.f500Real[eINT_ICP];
          Conv_MramWrXCs( (UINT16 *)&pMram->fPh[4*2*2], 4*2,  (UINT16 *)&sSet.fPh[4],   (UINT16 *)&pMram->wPhXCs,     (UINT16 *)&sSet.wPhXCs      );
        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_SAVE )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_DCALL_ZERO:
    case eST_DBG_DCALL_SPAN:
    case eST_DBG_DC1_ZERO:
    case eST_DBG_DC1_SPAN:
    case eST_DBG_DC2_ZERO:
    case eST_DBG_DC2_SPAN:
    case eST_DBG_DC3_ZERO:
    case eST_DBG_DC3_SPAN:
    case eST_DBG_ACALL_ZERO:
    case eST_DBG_ACALL_SPAN:
    case eST_DBG_AC1_ZERO:
    case eST_DBG_AC1_SPAN:
    case eST_DBG_AC2_ZERO:
    case eST_DBG_AC2_SPAN:
    case eST_DBG_AC3_ZERO:
    case eST_DBG_AC3_SPAN:
    case eST_DBG_AC4_ZERO:
    case eST_DBG_AC4_SPAN:
      if( i_bData == eK_ENT )
      {
        pSci->bCmdTy = pSci->Stp.bType;
        pSci->bCmdSub = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmdSub == eK_HELP )        List_Help( pSci );
        else if( pSci->bCmdSub == eK_EXIT ){  pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmdSub == eK_BACK )
        {
          switch( pSci->Stp.bType )
          {
          case eST_DBG_DCALL_ZERO:
          case eST_DBG_DCALL_SPAN:  sKey.bPageBack = eST_DBG_DCALL;   break;
          case eST_DBG_DC1_ZERO:
          case eST_DBG_DC1_SPAN:    sKey.bPageBack = eST_DBG_DC1;     break;
          case eST_DBG_DC2_ZERO:
          case eST_DBG_DC2_SPAN:    sKey.bPageBack = eST_DBG_DC2;     break;
          case eST_DBG_DC3_ZERO:
          case eST_DBG_DC3_SPAN:    sKey.bPageBack = eST_DBG_DC3;     break;
          case eST_DBG_ACALL_ZERO:
          case eST_DBG_ACALL_SPAN:  sKey.bPageBack = eST_DBG_ACALL;   break;
          case eST_DBG_AC1_ZERO:
          case eST_DBG_AC1_SPAN:    sKey.bPageBack = eST_DBG_AC1;     break;
          case eST_DBG_AC2_ZERO:
          case eST_DBG_AC2_SPAN:    sKey.bPageBack = eST_DBG_AC2;     break;
          case eST_DBG_AC3_ZERO:
          case eST_DBG_AC3_SPAN:    sKey.bPageBack = eST_DBG_AC3;     break;
          case eST_DBG_AC4_ZERO:
          case eST_DBG_AC4_SPAN:    sKey.bPageBack = eST_DBG_AC4;     break;
          }
          pSci->Stp.bType = eST_DBG_BACK;
        }
        else if( pSci->bCmdSub == eK_SAVE )
        {
          switch( pSci->Stp.bType )
          {
          case eST_DBG_DCALL_ZERO:
            sSet.fZe[1] = sInt.f500Real[eINT_TC1];
            sSet.fZe[2] = sInt.f500Real[eINT_TC2];
            sSet.fZe[3] = sInt.f500Real[eINT_CC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[1*2*2], 3*2,  (UINT16 *)&sSet.fZe[1],   (UINT16 *)&pMram->wZeDcXCs,   (UINT16 *)&sSet.wZeDcXCs    );
          break;
          case eST_DBG_DCALL_SPAN:
            sSet.fSp[1] = sInt.f500Real[eINT_TC1];
            sSet.fSp[2] = sInt.f500Real[eINT_TC2];
            sSet.fSp[3] = sInt.f500Real[eINT_CC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[1*2*2], 3*2,  (UINT16 *)&sSet.fSp[1],   (UINT16 *)&pMram->wSpDcXCs,   (UINT16 *)&sSet.wSpDcXCs    );
          break;
          case eST_DBG_DC1_ZERO:
            sSet.fZe[1] = sInt.f500Real[eINT_TC1];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[1*2*2], 3*2,  (UINT16 *)&sSet.fZe[1],   (UINT16 *)&pMram->wZeDcXCs,   (UINT16 *)&sSet.wZeDcXCs    );
          break;
          case eST_DBG_DC1_SPAN:
            sSet.fSp[1] = sInt.f500Real[eINT_TC1];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[1*2*2], 3*2,  (UINT16 *)&sSet.fSp[1],   (UINT16 *)&pMram->wSpDcXCs,   (UINT16 *)&sSet.wSpDcXCs    );
          break;
          case eST_DBG_DC2_ZERO:
            sSet.fZe[2] = sInt.f500Real[eINT_TC2];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[1*2*2], 3*2,  (UINT16 *)&sSet.fZe[1],   (UINT16 *)&pMram->wZeDcXCs,   (UINT16 *)&sSet.wZeDcXCs    );
          break;
          case eST_DBG_DC2_SPAN:
            sSet.fSp[2] = sInt.f500Real[eINT_TC2];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[1*2*2], 3*2,  (UINT16 *)&sSet.fSp[1],   (UINT16 *)&pMram->wSpDcXCs,   (UINT16 *)&sSet.wSpDcXCs    );
          break;
          case eST_DBG_DC3_ZERO:
            sSet.fZe[3] = sInt.f500Real[eINT_CC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[1*2*2], 3*2,  (UINT16 *)&sSet.fZe[1],   (UINT16 *)&pMram->wZeDcXCs,   (UINT16 *)&sSet.wZeDcXCs    );
          break;
          case eST_DBG_DC3_SPAN:
            sSet.fSp[3] = sInt.f500Real[eINT_CC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[1*2*2], 3*2,  (UINT16 *)&sSet.fSp[1],   (UINT16 *)&pMram->wSpDcXCs,   (UINT16 *)&sSet.wSpDcXCs    );
          break;
          case eST_DBG_ACALL_ZERO:
            sSet.fZe[4] = sInt.f500Real[eINT_V];
            sSet.fZe[5] = sInt.f500Real[eINT_IA];
            sSet.fZe[6] = sInt.f500Real[eINT_IB];
            sSet.fZe[7] = sInt.f500Real[eINT_IC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2], 4*2,  (UINT16 *)&sSet.fZe[4],   (UINT16 *)&pMram->wZeAcXCs,   (UINT16 *)&sSet.wZeAcXCs    );
          break;
          case eST_DBG_ACALL_SPAN:
            sSet.fSp[4] = sInt.f500Real[eINT_V];
            sSet.fSp[5] = sInt.f500Real[eINT_IA];
            sSet.fSp[6] = sInt.f500Real[eINT_IB];
            sSet.fSp[7] = sInt.f500Real[eINT_IC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2], 4*2,  (UINT16 *)&sSet.fSp[4],   (UINT16 *)&pMram->wSpAcXCs,   (UINT16 *)&sSet.wSpAcXCs    );
          break;
          case eST_DBG_AC1_ZERO:
            sSet.fZe[4] = sInt.f500Real[eINT_V];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2], 4*2,  (UINT16 *)&sSet.fZe[4],   (UINT16 *)&pMram->wZeAcXCs,   (UINT16 *)&sSet.wZeAcXCs    );
          break;
          case eST_DBG_AC1_SPAN:
            sSet.fSp[4] = sInt.f500Real[eINT_V];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2], 4*2,  (UINT16 *)&sSet.fSp[4],   (UINT16 *)&pMram->wSpAcXCs,   (UINT16 *)&sSet.wSpAcXCs    );
          break;
          case eST_DBG_AC2_ZERO:
            sSet.fZe[5] = sInt.f500Real[eINT_IA];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2], 4*2,  (UINT16 *)&sSet.fZe[4],   (UINT16 *)&pMram->wZeAcXCs,   (UINT16 *)&sSet.wZeAcXCs    );
          break;
          case eST_DBG_AC2_SPAN:
            sSet.fSp[5] = sInt.f500Real[eINT_IA];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2], 4*2,  (UINT16 *)&sSet.fSp[4],   (UINT16 *)&pMram->wSpAcXCs,   (UINT16 *)&sSet.wSpAcXCs    );
          break;
          case eST_DBG_AC3_ZERO:
            sSet.fZe[6] = sInt.f500Real[eINT_IB];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2], 4*2,  (UINT16 *)&sSet.fZe[4],   (UINT16 *)&pMram->wZeAcXCs,   (UINT16 *)&sSet.wZeAcXCs    );
          break;
          case eST_DBG_AC3_SPAN:
            sSet.fSp[6] = sInt.f500Real[eINT_IB];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2], 4*2,  (UINT16 *)&sSet.fSp[4],   (UINT16 *)&pMram->wSpAcXCs,   (UINT16 *)&sSet.wSpAcXCs    );
          break;
          case eST_DBG_AC4_ZERO:
            sSet.fZe[7] = sInt.f500Real[eINT_IC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fZe[4*2*2], 4*2,  (UINT16 *)&sSet.fZe[4],   (UINT16 *)&pMram->wZeAcXCs,   (UINT16 *)&sSet.wZeAcXCs    );
          break;
          case eST_DBG_AC4_SPAN:
            sSet.fSp[7] = sInt.f500Real[eINT_IC];
            Conv_MramWrXCs( (UINT16 *)&pMram->fSp[4*2*2], 4*2,  (UINT16 *)&sSet.fSp[4],   (UINT16 *)&pMram->wSpAcXCs,   (UINT16 *)&sSet.wSpAcXCs    );
          break;
          }
        }
        else if( !( pSci->bCmdSub == eK_VRANGE && pSci->bCmdSub == eK_RANGE ) )
        {
          switch( pSci->Stp.bType )
          {
          case eST_DBG_DCALL_ZERO:    sKey = sKeySet[eKN_DBG_DCALLRZERO]; break;
          case eST_DBG_DC1_ZERO:      sKey = sKeySet[eKN_DBG_DC1RZERO];   break;
          case eST_DBG_DC2_ZERO:      sKey = sKeySet[eKN_DBG_DC2RZERO];   break;
          case eST_DBG_DC3_ZERO:      sKey = sKeySet[eKN_DBG_DC3RZERO];   break;
          case eST_DBG_DCALL_SPAN:    sKey = sKeySet[eKN_DBG_DCALLRSPAN]; break;
          case eST_DBG_DC1_SPAN:      sKey = sKeySet[eKN_DBG_DC1RSPAN];   break;
          case eST_DBG_DC2_SPAN:      sKey = sKeySet[eKN_DBG_DC2RSPAN];   break;
          case eST_DBG_DC3_SPAN:      sKey = sKeySet[eKN_DBG_DC3RSPAN];   break;
          case eST_DBG_ACALL_ZERO:
            if( pSci->bCmdSub == eK_VRANGE )  sKey = sKeySet[eKN_DBG_ACVRZERO];
            else                              sKey = sKeySet[eKN_DBG_ACIRZERO];
          break;
          case eST_DBG_AC1_ZERO:      sKey = sKeySet[eKN_DBG_AC1RZERO];   break;
          case eST_DBG_AC2_ZERO:      sKey = sKeySet[eKN_DBG_AC2RZERO];   break;
          case eST_DBG_AC3_ZERO:      sKey = sKeySet[eKN_DBG_AC3RZERO];   break;
          case eST_DBG_AC4_ZERO:      sKey = sKeySet[eKN_DBG_AC4RZERO];   break;
          case eST_DBG_ACALL_SPAN:
            if( pSci->bCmdSub == eK_VRANGE )  sKey = sKeySet[eKN_DBG_ACVRSPAN];
            else                              sKey = sKeySet[eKN_DBG_ACIRSPAN];
          break;
          case eST_DBG_AC1_SPAN:      sKey = sKeySet[eKN_DBG_AC1RSPAN];   break;
          case eST_DBG_AC2_SPAN:      sKey = sKeySet[eKN_DBG_AC2RSPAN];   break;
          case eST_DBG_AC3_SPAN:      sKey = sKeySet[eKN_DBG_AC3RSPAN];   break;
          case eST_DBG_AC4_SPAN:      sKey = sKeySet[eKN_DBG_AC4RSPAN];   break;
          default:
          break;
          }
          Number_Start( pSci );
        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_VRANGE || i_bData == eK_RANGE || i_bData == eK_SAVE )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_RATIO:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_SYS;     }
        else if( pSci->bCmd == eK_RATIO1 ){ sKey = sKeySet[eKN_DBG_ACRATIO1];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO1;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO2 ){ sKey = sKeySet[eKN_DBG_ACRATIO2];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO2;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO3 ){ sKey = sKeySet[eKN_DBG_ACRATIO3];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO3;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO4 ){ sKey = sKeySet[eKN_DBG_ACRATIO4];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO4;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO5 ){ sKey = sKeySet[eKN_DBG_DCRATIO1];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO5;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO6 ){ sKey = sKeySet[eKN_DBG_DCRATIO2];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO6;   Number_Start( pSci );   }
        else if( pSci->bCmd == eK_RATIO7 ){ sKey = sKeySet[eKN_DBG_DCRATIO3];   sKey.bPageBack = pSci->Stp.bType;   sKey.bPageGo = eST_DBG_RATIO7;   Number_Start( pSci );   }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_RATIO1 || i_bData == eK_RATIO2 || i_bData == eK_RATIO3 || i_bData == eK_RATIO4 || i_bData == eK_RATIO5 || i_bData == eK_RATIO6 || i_bData == eK_RATIO7 )
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
      }
    break;
    case eST_DBG_DC_RATIO:
    case eST_DBG_AC_RATIO:
      if( i_bData == eK_ENT )
      {
        pSci->bCmd = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        pSci->bCmdData[pSci->bCmdCount++] = i_bData;
        pSci->Stp.bView = eST_LINE_RUN;
        if( pSci->bCmd == eK_HELP )           List_Help( pSci );
        else if( pSci->bCmd == eK_EXIT )  {   pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmd == eK_BACK )
        {
          if( pSci->Stp.bType == eST_DBG_DC_RATIO )  sKey.bPageBack = eST_DBG_DCCALI;
          else                                       sKey.bPageBack = eST_DBG_ACCALI;
          pSci->Stp.bType = eST_DBG_BACK;
        }
        else if( pSci->Stp.bType == eST_DBG_DC_RATIO )
        {
               if( pSci->bCmd == eK_DCRATIO  )  { sKey = sKeySet[eKN_DBG_DCRATIO];    Number_Start( pSci );   }
          else if( pSci->bCmd == eK_DCRATIO1 )  { sKey = sKeySet[eKN_DBG_DCRATIO1];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_DCRATIO2 )  { sKey = sKeySet[eKN_DBG_DCRATIO2];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_DCRATIO3 )  { sKey = sKeySet[eKN_DBG_DCRATIO3];   Number_Start( pSci );   }
        }
        else if( pSci->Stp.bType == eST_DBG_AC_RATIO )
        {
               if( pSci->bCmd == eK_ACVRATIO )  { sKey = sKeySet[eKN_DBG_ACVRATIO];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_ACIRATIO )  { sKey = sKeySet[eKN_DBG_ACIRATIO];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_ACRATIO1 )  { sKey = sKeySet[eKN_DBG_ACRATIO1];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_ACRATIO2 )  { sKey = sKeySet[eKN_DBG_ACRATIO2];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_ACRATIO3 )  { sKey = sKeySet[eKN_DBG_ACRATIO3];   Number_Start( pSci );   }
          else if( pSci->bCmd == eK_ACRATIO4 )  { sKey = sKeySet[eKN_DBG_ACRATIO4];   Number_Start( pSci );   }
        }
      }
      else
      {
        pSci->bCmdData[pSci->bCmdCount++] = pSci->bCmdTp = i_bData;
        if( pSci->Stp.bType == eST_DBG_DC_RATIO )
        {
          if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_DCRATIO || i_bData == eK_DCRATIO1 || i_bData == eK_DCRATIO2 || i_bData == eK_DCRATIO3 )
            List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        }
        else
        {
          if( i_bData == eK_ENT || i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK || i_bData == eK_ACRATIO || i_bData == eK_ACRATIO1 || i_bData == eK_ACRATIO2 || i_bData == eK_ACRATIO3 || i_bData == eK_ACRATIO4 )
            List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        }
      }
    break;
    case eST_DBG_NUMBER:
      if( sKey.bPageGo == eST_DBG_PASSWORD && i_bData == eK_BACKSLASH && pSci->bCmdCount == 4 )
      {
// -> Password
        Char2Float( pSci, (float *)&sKey.fValue );
//        sKey.fKey = fValue[0];

        if( (UINT16)sKey.fKey == ePASS_LV1 )
        {
          sDsp.wLv = eST_LV1;
          pSci->Stp.bView = eST_LINE_HELP;
          pSci->Stp.bType = eST_DBG_SETTING;
          sKey.bPageGo = eST_DBG_NORMAL;
          List_Char( pSci, pSci->Stp.bType );
        }
        else
        {
          pSci->bCmdCount = 0;
          for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
          List_ShotKey( pSci, pSci->Stp.bType, i_bData );
        }
// <- Password
      }
      else if( i_bData == eK_ENT )
      {
        pSci->bCmdTy = pSci->Stp.bType;
        pSci->bCmdNum = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        if( pSci->bCmdNum == eK_HELP )        List_Help( pSci );
        else if( pSci->bCmdNum == eK_EXIT ){  pSci->Stp.bView = 0;    pSci->Stp.bType = eST_DBG_BACK;   sKey.bPageBack = eST_DBG_EXIT;    }
        else if( pSci->bCmdNum == eK_BACK ){  pSci->Stp.bType = sKey.bPageBack;   }
//        else if( pSci->bCmdNum == eK_BACK ){  pSci->Stp.bType = sKey.bPageBack;   sprintf( pSci->bTxData, "\r                              " ); }
        else if( pSci->bCmdCount != 0 )
        {
          Char2Float( pSci, (float *)&sKey.fValue );
//          sKey.fKey = fValue[0];
          switch( sKey.bPageGo )
          {
// -> Password
          case eST_DBG_PASSWORD:
/*
            Char2Float( pSci, (float *)&sKey.fValue );
//            sKey.fKey = fValue[0];
*/
            if( (UINT16)sKey.fKey == sSet.wPass && pSci->bCmdCount == 4 )
            {
              sDsp.wLv = eST_LV2;
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = eST_DBG_SETTING;
              sKey.bPageGo = eST_DBG_NORMAL;
              List_Char( pSci, pSci->Stp.bType );
            }
            else
            {
              pSci->bCmdCount = 0;
              for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
              List_ShotKey( pSci, pSci->Stp.bType, i_bData );
            }
          break;
// <- Password
// -> Ethernet
          case eST_DBG_IP:
            if( Key_MinMax( &sKey ) )
            {
//              sDsp.wIpAddr[0] = (UINT16)fValue[0];    sDsp.wIpAddr[0] <<= 8;    sDsp.wIpAddr[0] += (UINT16)fValue[1];
//              sDsp.wIpAddr[1] = (UINT16)fValue[2];    sDsp.wIpAddr[1] <<= 8;    sDsp.wIpAddr[1] += (UINT16)fValue[3];
              Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,    9,    (UINT16 *)&sDsp.wIpAddr,  (UINT16 *)&pMram->wEthXCs,    (UINT16 *)&sDsp.wEthXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_SUB:
            if( Key_MinMax( &sKey ) )
            {
//              sDsp.wSubMask[0] = (UINT16)fValue[0];   sDsp.wSubMask[0] <<= 8;   sDsp.wSubMask[0] += (UINT16)fValue[1];
//              sDsp.wSubMask[1] = (UINT16)fValue[2];   sDsp.wSubMask[1] <<= 8;   sDsp.wSubMask[1] += (UINT16)fValue[3];
              Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,    9,    (UINT16 *)&sDsp.wIpAddr,  (UINT16 *)&pMram->wEthXCs,    (UINT16 *)&sDsp.wEthXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_DEF:
            if( Key_MinMax( &sKey ) )
            {
//              sDsp.wDefGate[0] = (UINT16)fValue[0];   sDsp.wDefGate[0] <<= 8;   sDsp.wDefGate[0] += (UINT16)fValue[1];
//              sDsp.wDefGate[1] = (UINT16)fValue[2];   sDsp.wDefGate[1] <<= 8;   sDsp.wDefGate[1] += (UINT16)fValue[3];
              Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,    9,    (UINT16 *)&sDsp.wIpAddr,  (UINT16 *)&pMram->wEthXCs,    (UINT16 *)&sDsp.wEthXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_PORT:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wPortNum = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,    9,    (UINT16 *)&sDsp.wIpAddr,  (UINT16 *)&pMram->wEthXCs,    (UINT16 *)&sDsp.wEthXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_LOC:
            if( Key_MinMax( &sKey ) )
            {
//              sDsp.wLocIpAddr[0] = (UINT16)fValue[0];   sDsp.wLocIpAddr[0] <<= 8;   sDsp.wLocIpAddr[0] += (UINT16)fValue[1];
//              sDsp.wLocIpAddr[1] = (UINT16)fValue[2];   sDsp.wLocIpAddr[1] <<= 8;   sDsp.wLocIpAddr[1] += (UINT16)fValue[3];
              Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,    9,    (UINT16 *)&sDsp.wIpAddr,  (UINT16 *)&pMram->wEthXCs,    (UINT16 *)&sDsp.wEthXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- Ethernet
// -> List/Fault/No
          case eST_DBG_NO:
            if( Key_MinMax( &sKey ) )
            {
              sFat.wNo = (UINT16)sKey.fKey;
              pSci->Stp.bView = 0;
              pSci->Stp.bType = sKey.bPageBack;
//              sKey.bPageBack = eST_DBG_EXIT;
//              pSci->Stp.bView = eST_LINE_HELP;
//              sKey.bPageBack = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- List/Fault/No
// -> eTc
          case eST_DBG_DEBOUNCE:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wDebo = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wDebo,      1,    (UINT16 *)&sDsp.wDebo,    (UINT16 *)&pMram->wDeboXCs,   (UINT16 *)&sDsp.wDeboXCs    );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_TRIPNUM:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wTrig = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wTrig,      1,    (UINT16 *)&sDsp.wTrig,    (UINT16 *)&pMram->wTrigXCs,   (UINT16 *)&sDsp.wTrigXCs    );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_TRIPCURR:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wTrip[0] = sDsp.wTrip[1] = sDsp.wTrip[2] = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wTrip,      3,    (UINT16 *)&sDsp.wTrip,    (UINT16 *)&pMram->wTripXCs,   (UINT16 *)&sDsp.wTripXCs    );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- eTc
// -> eTc/Pass
          case eST_DBG_NEWPASS:
            if( Key_MinMax( &sKey ) )
            {
              for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
              sKey.bPageGo = eST_DBG_RE_ENTPASS;
              sSetTemp.wPass = sKey.fKey;
            }
          break;
          case eST_DBG_RE_ENTPASS:
            if( Key_MinMax( &sKey ) && sSetTemp.wPass == sKey.fKey )
            {
              sSet.wPass = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wPass,      1,    (UINT16 *)&sSet.wPass,    (UINT16 *)&pMram->wPassXCs,   (UINT16 *)&sSet.wPassXCs    );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              sKey.bPageGo = eST_DBG_NORMAL;
              List_Char( pSci, pSci->Stp.bType );
            }
            else
            {
              for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
              sKey.bPageGo = eST_DBG_NEWPASS;
            }
          break;
          case eST_DBG_100MS:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wTrig = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wNo100ms,      2,    (UINT16 *)&sSet.wNo100ms,    (UINT16 *)&pMram->wNoXCs,     (UINT16 *)&sSet.wNoXCs      );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_500MS:
            if( Key_MinMax( &sKey ) )
            {
              sDsp.wTrig = (UINT16)sKey.fKey;
              Conv_MramWrXCs( (UINT16 *)&pMram->wNo100ms,      2,    (UINT16 *)&sSet.wNo100ms,    (UINT16 *)&pMram->wNoXCs,     (UINT16 *)&sSet.wNoXCs      );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- eTc/Pass
// -> eTc/Time
          case eST_DBG_YEAR:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bYY = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
          case eST_DBG_MON:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bMM = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
          case eST_DBG_DAY:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bDD = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
          case eST_DBG_HOUR:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bhh = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
          case eST_DBG_MIN:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bmm = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
          case eST_DBG_SEC:
            if( Key_MinMax( &sKey ) )
            {
              sSet.Time = sDsp.Time;
              sSet.Time.bss = (UINT8)DEC2BCD( (UINT16)sKey.fKey );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
              sRtc.bTimeWrite = 1;
            }
          break;
// <- eTc/Time
// -> Calibration
          case eST_DBG_DCALLRZERO:
            if( Key_MinMax( &sKey ) )
            {
              sSet.wZeR[3] = sSet.wZeR[2] = sSet.wZeR[1];
              Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[1*2],  3,    (UINT16 *)&sSet.wZeR[1],  (UINT16 *)&pMram->wZeRDcXCs,  (UINT16 *)&sSet.wZeRDcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_DCALLRSPAN:
            if( Key_MinMax( &sKey ) )
            {
              sSet.wSpR[3] = sSet.wSpR[2] = sSet.wSpR[1];
              Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[1*2],  3,    (UINT16 *)&sSet.wSpR[1],  (UINT16 *)&pMram->wSpRDcXCs,  (UINT16 *)&sSet.wSpRDcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_DC1RZERO:
          case eST_DBG_DC2RZERO:
          case eST_DBG_DC3RZERO:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[1*2],  3,    (UINT16 *)&sSet.wZeR[1],  (UINT16 *)&pMram->wZeRDcXCs,  (UINT16 *)&sSet.wZeRDcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_DC1RSPAN:
          case eST_DBG_DC2RSPAN:
          case eST_DBG_DC3RSPAN:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[1*2],  3,    (UINT16 *)&sSet.wSpR[1],  (UINT16 *)&pMram->wSpRDcXCs,  (UINT16 *)&sSet.wSpRDcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_ACVRZERO:
          case eST_DBG_AC1RZERO:
          case eST_DBG_AC2RZERO:
          case eST_DBG_AC3RZERO:
          case eST_DBG_AC4RZERO:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[4*2],  4,    (UINT16 *)&sSet.wZeR[4],  (UINT16 *)&pMram->wZeRAcXCs,  (UINT16 *)&sSet.wZeRAcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_ACVRSPAN:
          case eST_DBG_AC1RSPAN:
          case eST_DBG_AC2RSPAN:
          case eST_DBG_AC3RSPAN:
          case eST_DBG_AC4RSPAN:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[4*2],  4,    (UINT16 *)&sSet.wSpR[4],  (UINT16 *)&pMram->wSpRAcXCs,  (UINT16 *)&sSet.wSpRAcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_ACIRZERO:
            if( Key_MinMax( &sKey ) )
            {
              sSet.wZeR[7] = sSet.wZeR[6] = sSet.wZeR[5];
              Conv_MramWrXCs( (UINT16 *)&pMram->wZeR[4*2],  4,    (UINT16 *)&sSet.wZeR[4],  (UINT16 *)&pMram->wZeRAcXCs,  (UINT16 *)&sSet.wZeRAcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_ACIRSPAN:
            if( Key_MinMax( &sKey ) )
            {
              sSet.wSpR[7] = sSet.wSpR[6] = sSet.wSpR[5];
              Conv_MramWrXCs( (UINT16 *)&pMram->wSpR[4*2],  4,    (UINT16 *)&sSet.wSpR[4],  (UINT16 *)&pMram->wSpRAcXCs,  (UINT16 *)&sSet.wSpRAcXCs   );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- Calibration
// -> dcRatio
          case eST_DBG_DCRATIO:
            if( Key_MinMax( &sKey ) )
            {
              sSet.fRatio[3] = sSet.fRatio[2] = sSet.fRatio[1];
              Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[1*2*2],  3*2,    (UINT16 *)&sSet.fRatio[1],  (UINT16 *)&pMram->wDcRatioXCs, (UINT16 *)&sSet.wDcRatioXCs  );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_RATIO5:
          case eST_DBG_RATIO6:
          case eST_DBG_RATIO7:
          case eST_DBG_DCRATIO1:
          case eST_DBG_DCRATIO2:
          case eST_DBG_DCRATIO3:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[1*2*2],  3*2,    (UINT16 *)&sSet.fRatio[1],  (UINT16 *)&pMram->wDcRatioXCs, (UINT16 *)&sSet.wDcRatioXCs  );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- dcRatio
// -> acRatio
          case eST_DBG_RATIO1:
          case eST_DBG_RATIO2:
          case eST_DBG_RATIO3:
          case eST_DBG_RATIO4:
          case eST_DBG_ACVRATIO:
          case eST_DBG_ACRATIO1:
          case eST_DBG_ACRATIO2:
          case eST_DBG_ACRATIO3:
          case eST_DBG_ACRATIO4:
            if( Key_MinMax( &sKey ) )
            {
              Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[4*2*2],  4*2,    (UINT16 *)&sSet.fRatio[4],  (UINT16 *)&pMram->wAcRatioXCs, (UINT16 *)&sSet.wAcRatioXCs  );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
          case eST_DBG_ACIRATIO:
            if( Key_MinMax( &sKey ) )
            {
              sSet.fRatio[7] = sSet.fRatio[6] = sSet.fRatio[5];
              Conv_MramWrXCs( (UINT16 *)&pMram->fRatio[4*2*2],  4*2,    (UINT16 *)&sSet.fRatio[4],  (UINT16 *)&pMram->wAcRatioXCs, (UINT16 *)&sSet.wAcRatioXCs  );
              pSci->Stp.bView = eST_LINE_RUN;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
          break;
// <- acRatio
          default:
          break;
          }
        }
      }
      else    // Space, Number
      {
        if( i_bData == eK_HELP || i_bData == eK_EXIT || i_bData == eK_BACK )
        {
          pSci->bCmdCount = 0;
          for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
          pSci->bCmdTp = i_bData;
          List_ShotKey( pSci, sKey.bPageGo, i_bData );
        }
        else if( pSci->bCmdCount >= 1 && i_bData == eK_BS )
        {
          pSci->bCmdCount--;
          pSci->bCmdData[pSci->bCmdCount] = 0x00;
          List_ShotKey( pSci, sKey.bPageGo, i_bData );
        }
        else if( ( i_bData >= '0' && i_bData <= '9' ) || i_bData == '.' )
        {
          pSci->bCmdTp = pSci->bCmdNum = 0x00;
          pSci->bCmdData[pSci->bCmdCount++] = i_bData;
          if( pSci->bCmdCount >= eTERMINAL_DATA || ( ( sKey.bPageGo == eST_DBG_PASSWORD || sKey.bPageGo == eST_DBG_NEWPASS || sKey.bPageGo == eST_DBG_RE_ENTPASS ) && pSci->bCmdCount >= 5 ) )
          {
            pSci->bCmdCount = 0;
            for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
            pSci->bCmdTp = i_bData;
          }
          List_ShotKey( pSci, sKey.bPageGo, i_bData );
        }
      }
    break;
    case eST_DBG_CHAR:
      if( i_bData == eK_ENT )
      {
        pSci->bCmdTy = pSci->Stp.bType;
        pSci->bCmdNum = pSci->bCmdTp;
        pSci->bCmdTp = 0;
        if( pSci->bCmdCount != 0 )    // 저장된 내용이 없어도 저장 할 것이라면 이거 지워야 됨
        {
          switch( sKey.bPageGo )
          {
          case eST_DBG_MAC:
            k = 0;
            sKey.fValue[0] = 0;
            sKey.fValue[1] = 0;
            sKey.fValue[2] = 0;
            sKey.fValue[3] = 0;
            sKey.fValue[4] = 0;
            sKey.fValue[5] = 0;
            for( i=0; i<6; i++ )
            {
//              if( pSci->bCmdData[k] == ':' ){ i--;  k++;  fValue[i-1] = (float)i_wData; }
//              else
              {
                i_wData = 0;
                for( j=0; j<3; j++ )
                {
                  i_bData = pSci->bCmdData[k++];
                  if( i_bData == ':' || i_bData == 0x00 )
                  {
                      sKey.fValue[i] = (float)i_wData;
                    break;
                  }
                  else if( i_bData >= '0' && i_bData <= '9' )
                  {
                    i_wData <<= 4;
                    i_wData +=  i_bData - '0';
                  }
                  else if( i_bData >= 'A' && i_bData <= 'F' )
                  {
                    i_wData <<= 4;
                    i_wData +=  i_bData - 'A' +10;
                  }
                }
              }
            }
            sKey.bNo = 6;
            if( i == 6 && Key_MinMax( &sKey ) )
            {
              sSet.wMac[0]  = (UINT16)sKey.fValue[0] << 8;
              sSet.wMac[0] |= (UINT16)sKey.fValue[1] << 0;
              sSet.wMac[1]  = (UINT16)sKey.fValue[2] << 8;
              sSet.wMac[1] |= (UINT16)sKey.fValue[3] << 0;
              sSet.wMac[2]  = (UINT16)sKey.fValue[4] << 8;
              sSet.wMac[2] |= (UINT16)sKey.fValue[5] << 0;
              Conv_MramWrXCs( (UINT16 *)&pMram->wMac[0],        3,    (UINT16 *)&sSet.wMac[0],    (UINT16 *)&pMram->wMacXCs,      (UINT16 *)&sSet.wMacXCs     );
              pSci->Stp.bView = eST_LINE_HELP;
              pSci->Stp.bType = sKey.bPageBack;
              List_Char( pSci, pSci->Stp.bType );
            }
            else
            {
              pSci->bCmdCount = 0;
              for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
              List_ShotKey( pSci, pSci->Stp.bType, i_bData );
            }
          break;
// -> eTc/Model
          case eST_DBG_MODEL:
            Char2WordChar( pSci, (float *)&sKey.fValue );
            Conv_MramWr   ( (UINT16 *)&pMram->wModel,         8,    (UINT16 *)&sDsp.wModel  );
            pSci->Stp.bView = eST_LINE_HELP;
            pSci->Stp.bType = sKey.bPageBack;
            List_Char( pSci, pSci->Stp.bType );
          break;
// <- eTc/Model
// -> eTc/Serial
          case eST_DBG_SERIAL:
            Char2WordChar( pSci, (float *)&sKey.fValue );
            Conv_MramWr   ( (UINT16 *)&pMram->wSerial,         16,    (UINT16 *)&sDsp.wSerial  );
            pSci->Stp.bView = eST_LINE_HELP;
            pSci->Stp.bType = sKey.bPageBack;
            List_Char( pSci, pSci->Stp.bType );
          break;
// <- eTc/Serial
          }
        }
      }
      else    // Space, Char
      {
        if( i_bData == eK_ESC )
        {
          if( pSci->bCmdData[0] == 0 ){ pSci->Stp.bView = 0;  pSci->Stp.bType = eST_DBG_BACK;   }
          else
          {
            pSci->bCmdCount = 0;
            for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
            pSci->bCmdTp = i_bData;
            List_ShotKey( pSci, sKey.bPageGo, i_bData );
          }
        }
        else if( pSci->bCmdCount >= 1 && i_bData == eK_BS )
        {
          pSci->bCmdCount--;
          pSci->bCmdData[pSci->bCmdCount] = 0x00;
          sprintf( pSci->bTxData, "\r                                                \rTHOMAS%s %s", Debug_TCursor( pSci, sKey.bPageGo ), pSci->bCmdData );
        }
        else if( sKey.bPageGo == eST_DBG_MAC )
        {
          if( ( i_bData >= 'a' && i_bData <= 'z' ) )
            i_bData -= ( 'a' - 'A' );
          if( ( i_bData >= '0' && i_bData <= '9' ) || ( i_bData >= 'A' && i_bData <= 'F' ) || i_bData <= ':' )
          {
            pSci->bCmdTp = pSci->bCmdNum = 0x00;
            pSci->bCmdData[pSci->bCmdCount++] = i_bData;
            if( pSci->bCmdCount >= sKey.bNo )
            {
              pSci->bCmdCount = 0;
              for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
              pSci->bCmdTp = i_bData;
            }
            sprintf( pSci->bTxData, "\r                                                \rTHOMAS%s %s", Debug_TCursor( pSci, sKey.bPageGo ), pSci->bCmdData );
          }
        }
        else if( ( i_bData >= '!' && i_bData <= '~' ) )
        {
          pSci->bCmdTp = pSci->bCmdNum = 0x00;
          pSci->bCmdData[pSci->bCmdCount++] = i_bData;
          if( pSci->bCmdCount >= sKey.bNo )
          {
            pSci->bCmdCount = 0;
            for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
            pSci->bCmdTp = i_bData;
          }
          sprintf( pSci->bTxData, "\r                                                \rTHOMAS%s %s", Debug_TCursor( pSci, sKey.bPageGo ), pSci->bCmdData );
//          List_ShotKey( pSci, sKey.bPageGo, i_bData );
        }
      }
    break;
    }

    pSci->Cnt.bTxEnd = strlen( pSci->bTxData );
    if( pSci->Cnt.bTxEnd != 0 )
    {
      pSci->Cnt.bTxEnd += 1;
      SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
      SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int
    }

    if( i_bData == eK_ENT )
    {
      pSci->bCmdCount = 0;
      i_bData = 0;
    }
  }

  if( pSci->Cnt.bTxEnd != 0 )
    return;

  UINT16  i_wValue[8];
  float   i_fValue[8];
  UINT16  *pwWave;
  UINT16  i_wNo;
// Debug View Start
  if( pSci->Stp.bType != 0 )
  {
    pSci->bTxData[0] = 0;
    switch( pSci->Stp.bType )
    {
    case eST_DBG_NORMAL:
      pSci->Stp.bView = eST_LINE_RUN;
    break;
    case eST_DBG_LOGO:
      switch( pSci->Stp.bView++ )
      {
      case 0 :    sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );   break;  // line 24
//      case 0 :    sprintf( pSci->bTxData, "\n\r%c%c%u%c", 0x1B, 0x5B, 100, 'T' );   break;  // line 24
      case 1 :    Terminal_Goto( pSci, 0, 0 );    break;
      case 2 :    sprintf( pSci->bTxData, "************************************************\n\r" );   break;
      case 3 :    sprintf( pSci->bTxData, "**                 Thomas R&D                 **\n\r" );   break;
      case 4 :    sprintf( pSci->bTxData, "**             ACQ(CBAMD) Program             **\n\r" );   break;
      case 5 :    sprintf( pSci->bTxData, "**             %4u.%2u.%2u ver%2u.%02u            **\n\r",
                  BCD2DEC( (UINT16)( sDsp.lYYYYMMDD >> 16 ) ), BCD2DEC( ( sDsp.lYYYYMMDD >> 8 ) & 0x00FF ), BCD2DEC( ( sDsp.lYYYYMMDD ) & 0x00FF ),
                  ( sDsp.wVersion >> 8 ) & 0x00FF, sDsp.wVersion & 0x00FF );
      break;
      case 6 :    sprintf( pSci->bTxData, "************************************************\n\r\n\r" );
                  pSci->Stp.bType = eST_DBG_EXIT;
      break;
      default:
      break;
      }
    break;
    case eST_DBG_VIEW:
      switch( pSci->Stp.bView++ )
      {
      case 0 :    sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );   break;  // line 24
      case 1 :    Terminal_Goto( pSci, 0, 0 );                        break;
      case 2 :    Debug_Normal( pSci, eST_DBG_NORMAL );               break;
      case 3 :    sprintf( pSci->bTxData, "\n\r\n\r************************************************" );               break;
      case 4 :    sprintf( pSci->bTxData, "\n\r Model  : %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
                                                        ( sDsp.wModel[0] >>8 ) &0x00FF, ( sDsp.wModel[0] ) &0x00FF, ( sDsp.wModel[1] >>8 ) &0x00FF, ( sDsp.wModel[1] ) &0x00FF,
                                                        ( sDsp.wModel[2] >>8 ) &0x00FF, ( sDsp.wModel[2] ) &0x00FF, ( sDsp.wModel[3] >>8 ) &0x00FF, ( sDsp.wModel[3] ) &0x00FF,
                                                        ( sDsp.wModel[4] >>8 ) &0x00FF, ( sDsp.wModel[4] ) &0x00FF, ( sDsp.wModel[5] >>8 ) &0x00FF, ( sDsp.wModel[5] ) &0x00FF,
                                                        ( sDsp.wModel[6] >>8 ) &0x00FF, ( sDsp.wModel[6] ) &0x00FF, ( sDsp.wModel[7] >>8 ) &0x00FF, ( sDsp.wModel[7] ) &0x00FF
                          );
      break;
      case 5 :    sprintf( pSci->bTxData, "\n\r Serial : %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 
                                                        ( sDsp.wSerial[0 ] >>8 ) &0x00FF, ( sDsp.wSerial[0 ] ) &0x00FF, ( sDsp.wSerial[1 ] >>8 ) &0x00FF, ( sDsp.wSerial[1 ] ) &0x00FF,
                                                        ( sDsp.wSerial[2 ] >>8 ) &0x00FF, ( sDsp.wSerial[2 ] ) &0x00FF, ( sDsp.wSerial[3 ] >>8 ) &0x00FF, ( sDsp.wSerial[3 ] ) &0x00FF,
                                                        ( sDsp.wSerial[4 ] >>8 ) &0x00FF, ( sDsp.wSerial[4 ] ) &0x00FF, ( sDsp.wSerial[5 ] >>8 ) &0x00FF, ( sDsp.wSerial[5 ] ) &0x00FF,
                                                        ( sDsp.wSerial[6 ] >>8 ) &0x00FF, ( sDsp.wSerial[6 ] ) &0x00FF, ( sDsp.wSerial[7 ] >>8 ) &0x00FF, ( sDsp.wSerial[7 ] ) &0x00FF,
                                                        ( sDsp.wSerial[8 ] >>8 ) &0x00FF, ( sDsp.wSerial[8 ] ) &0x00FF, ( sDsp.wSerial[9 ] >>8 ) &0x00FF, ( sDsp.wSerial[9 ] ) &0x00FF,
                                                        ( sDsp.wSerial[10] >>8 ) &0x00FF, ( sDsp.wSerial[10] ) &0x00FF, ( sDsp.wSerial[11] >>8 ) &0x00FF, ( sDsp.wSerial[11] ) &0x00FF,
                                                        ( sDsp.wSerial[12] >>8 ) &0x00FF, ( sDsp.wSerial[12] ) &0x00FF, ( sDsp.wSerial[13] >>8 ) &0x00FF, ( sDsp.wSerial[13] ) &0x00FF,
                                                        ( sDsp.wSerial[14] >>8 ) &0x00FF, ( sDsp.wSerial[14] ) &0x00FF, ( sDsp.wSerial[15] >>8 ) &0x00FF, ( sDsp.wSerial[15] ) &0x00FF
                          );
      break;
      case 6 :    sprintf( pSci->bTxData, "\n\r TIME   : %02u/%02u/%02u %02u:%02u:%02u", BCD2DEC( sDsp.Time.bYY ), BCD2DEC( sDsp.Time.bMM ), BCD2DEC( sDsp.Time.bDD ), BCD2DEC( sDsp.Time.bhh ), BCD2DEC( sDsp.Time.bmm ), BCD2DEC( sDsp.Time.bss ) );    break;
      case 7 :    sprintf( pSci->bTxData, "\n\r Sys/Debo/ %ums", sDsp.wDebo );    break;
      case 8 :    sprintf( pSci->bTxData, "\n\r Sys/tripNum/ %ums", sDsp.wTrig ); break;
      case 9 :    sprintf( pSci->bTxData, "\n\r Sys/Tripcurr/ %u.%uA", sDsp.wTrip[0] /10, sDsp.wTrip[0] %10 );     break;
      case 10:    sprintf( pSci->bTxData, "\n\r Sys/Ratio/ V:%.02fV IA:%.02fA IB:%.02fA IC:%.02fA TC1:%.02fA TC2:%.02fA CC:%.02fA", sSet.fRatio[eADC_V], sSet.fRatio[eADC_IA], sSet.fRatio[eADC_IB], sSet.fRatio[eADC_IC], sSet.fRatio[eADC_TC1], sSet.fRatio[eADC_TC2], sSet.fRatio[eADC_CC] );     break;
      case 11:    sprintf( pSci->bTxData, "\n\r Ether/Ip/ %u.%u.%u.%u", ( sDsp.wIpAddr[0] >>8 ) &0x00FF, ( sDsp.wIpAddr[0] ) &0x00FF, ( sDsp.wIpAddr[1] >>8 ) &0x00FF, ( sDsp.wIpAddr[1] ) &0x00FF );     break;
      case 12:    sprintf( pSci->bTxData, "\n\r Ether/Sub/ %u.%u.%u.%u", ( sDsp.wSubMask[0] >>8 ) &0x00FF, ( sDsp.wSubMask[0] ) &0x00FF, ( sDsp.wSubMask[1] >>8 ) &0x00FF, ( sDsp.wSubMask[1] ) &0x00FF );     break;
      case 13:    sprintf( pSci->bTxData, "\n\r Ether/Def/ %u.%u.%u.%u", ( sDsp.wDefGate[0] >>8 ) &0x00FF, ( sDsp.wDefGate[0] ) &0x00FF, ( sDsp.wDefGate[1] >>8 ) &0x00FF, ( sDsp.wDefGate[1] ) &0x00FF );     break;
      case 14:    sprintf( pSci->bTxData, "\n\r Ether/Port/ %u", sDsp.wPortNum );     break;
      case 15:    sprintf( pSci->bTxData, "\n\r Ether/Loc/ %u.%u.%u.%u", ( sDsp.wLocIpAddr[0] >>8 ) &0x00FF, ( sDsp.wLocIpAddr[0] ) &0x00FF, ( sDsp.wLocIpAddr[1] >>8 ) &0x00FF, ( sDsp.wLocIpAddr[1] ) &0x00FF );     break;
      case 16:    sprintf( pSci->bTxData, "\n\r Ether/Mac/ %02X:%02X:%02X:%02X:%02X:%02X", ( sSet.wMac[0] >>8 ) &0x00FF, ( sSet.wMac[0] ) &0x00FF, ( sSet.wMac[1] >>8 ) &0x00FF, ( sSet.wMac[1] ) &0x00FF, ( sSet.wMac[2] >>8 ) &0x00FF, ( sSet.wMac[2] ) &0x00FF );     break;
      case 17:    sprintf( pSci->bTxData, "\n\r************************************************" );               break;
      case 18:    Terminal_Goto( pSci, 0, 0 );
                  pSci->Stp.bType = eST_DBG_EXIT;
      break;
      default:
      break;
      }
    break;
    case eST_DBG_EXIT:
      Debug_Normal( pSci, eST_DBG_NORMAL );
      pSci->Stp.bType = eST_DBG_NORMAL;
      sKey.bPageBack = sKey.bPageGo = eST_DBG_NORMAL;
    break;
    case eST_DBG_BACK:
      switch( pSci->Stp.bView++ )
      {
      case 0 :    sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );   break;  // line 24
//      case 0 :    sprintf( pSci->bTxData, "\n\r%c%c%u%c", 0x1B, 0x5B, 100, 'T' );   break;  // line 24
      case 1 :    Terminal_Goto( pSci, 0, 0 );
                  pSci->Stp.bType = sKey.bPageBack;
                  if( pSci->Stp.bType == eST_DBG_EXIT )   sDsp.wLv = eST_LV_OFF;
                  if( Debug_View( ) )   pSci->Stp.bView = eST_LINE_RUN;
                  else                  pSci->Stp.bView = eST_LINE_HELP;
      break;
      default:
      break;
      }
    break;
    case eST_DBG_E_ERASE:
    case eST_DBG_EVENT:
//    case eST_DBG_E_LIST:
      switch( pSci->Stp.bView++ )
      {
      case 0 :    sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );   break;  // line 24
//      case 0 :    sprintf( pSci->bTxData, "\n\r%c%c%u%c", 0x1B, 0x5B, 100, 'T' );   break;  // line 24
      case 1 :    Terminal_Goto( pSci, 0, 0 );    break;
      case 2 :    if( sCnt.wEv == eEVENT_EMPTY )
                  {
                    sprintf( pSci->bTxData, "\n\r Event Empty" );
                    pSci->Stp.bView = eST_LINE_END;
                  }
                  else
                  {
                    sEvt.wEv = sCnt.wEv;
                    sEvt.wNo = 0;
//                                               100 22/05/27 17:26:30:999 Power On
                    sprintf( pSci->bTxData, "\n\r No YY/MM/DD hh:mm:dd:ms  Type" );   break;
                  }
      break;
      case 3 :    if( sEvt.wEv >= eEVENT_MAX )
                  {
                    if( sEvt.wEv == eEVENT_MAX )    sEvt.wEv = ( eEVENT_MAX *2 ) -1;
                    else                            sEvt.wEv--;
                    if( ++sEvt.wNo >= eEVENT_MAX )  pSci->Stp.bView = eST_LINE_END;
                    else                            pSci->Stp.bView = 3;
                  }
                  else
                  {
                    if( --sEvt.wEv == 0 )           pSci->Stp.bView = eST_LINE_END;
                    else                            pSci->Stp.bView = 3;
                    sEvt.wNo++;
                  }
                  EventRd( );
                  sprintf( pSci->bTxData, "\n\r%03u %02X/%02X/%02X %02X:%02X:%02X:%03u %s",
                                              sEvt.wNo, sEvt.Time.bYY, sEvt.Time.bMM, sEvt.Time.bDD,
                                              sEvt.Time.bhh, sEvt.Time.bmm, sEvt.Time.bss, sEvt.Time.wms,
                                              List_Evt( sEvt.wType )
                          );
      break;
      case eST_LINE_END:
        Debug_Normal( pSci, pSci->Stp.bType );
      break;
      case eST_LINE_WAIT:
        pSci->Stp.bView = eST_LINE_WAIT;
      break;
      default:
      break;
      }
    break;
    case eST_DBG_F_ERASE:
    case eST_DBG_FAULT:
//    case eST_DBG_F_LIST:
      switch( pSci->Stp.bView++ )
      {
      case 0 :    sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );   break;  // line 24
//      case 0 :    sprintf( pSci->bTxData, "\n\r%c%c%u%c", 0x1B, 0x5B, 100, 'T' );   break;  // line 24
      case 1 :    Terminal_Goto( pSci, 0, 0 );
                  if( sDsp.wLv == eST_LV1 && sFat.wList )
                    pSci->Stp.bView = 10;
      break;
      case 2 :    if( sCnt.wFa == eFAULT_EMPTY )
                  {
                    sprintf( pSci->bTxData, "\n\r Fault Empty" );
                    pSci->Stp.bView = eST_LINE_END;
                  }
                  else
                  {
                    sFatRd.wFa = sCnt.wFa;
                    sFatRd.wNo = 0;
// Type : Trip: 0xAA(B접점이 Off에서 On 변화), Close: 0x55(A접전이 Off에서 On으로 변화)
// ContA(B, C) (Contact Duty A(B, C)) : Trip Coil에 전류가 인가되는 기간 중 A(B, C)상 최대 전류
// TC1PC(2) : Trip coil 1(2) 최대 전류
// TC1CF(2) : Trip coil 1(2) 여자 시간 - 여자 시작~끝 지점까지의 시간 - Trip coil 1(2)에 전류가 지속된 ms 단위 시간
// CC PC : Close coil 최대 전류
// CC CF : Close coil 여자 시간 - 여자 시작~끝 지점까지의 시간 - Close coil에 전류가 지속된 ms 단위 시간
// CC A : Close coil 여자 시작부터 A접점이 off에서 on으로 변화하기까지의 시간
// TC B : Trip coil 여자 시작부터 B접점이 off에서 on으로 변화하기까지의 시간
// TCA/CCA : TCB/CCB : TCC/CCC
//           TCA(차단 시간) : trip coil 여자 시작부터 A상 전류가 없어진 시점까지의 시간
//           CCA(투입 시간) : close coil 여자 시작부터 A상 전류가 나타나는 시점까지의 시간

//                                               100 22/05/27 17:26:30:999 Trip   123.4A 123.4A 123.4A  12.12A 300ms 12.12A 300ms 12.12A 300ms  300ms 300ms  300ms  300ms  300ms
                    sprintf( pSci->bTxData, "\n\r No YY/MM/DD hh:mm:dd:ms  Type   ContDA ContDB ContDC   TC1PC TC1CF  TC2PC TC2CF  CC PC CC CF   CC A  TC B  TC/CCA TC/CCB TC/CCC" );
                  }
      break;
      case 3 :    if( sFatRd.wFa >= eFAULT_MAX )
                  {
                    if( sFatRd.wFa == eFAULT_MAX )
                      sFatRd.wFa = ( eFAULT_MAX *2 ) -1;
                    else
                      sFatRd.wFa--;
                    if( ++sFatRd.wNo >= 20 )
//                    if( ++sFatRd.wNo >= eFAULT_MAX )
                      pSci->Stp.bView = eST_LINE_END;
                    else
                      pSci->Stp.bView = 3;
                  }
                  else
                  {
                    if( --sFatRd.wFa == 0 )
                    {
                      ++sFatRd.wNo;
                      pSci->Stp.bView = eST_LINE_END;
                    }
                    else
                    {
                      if( ++sFatRd.wNo >= 20 )
  //                    if( ++sFatRd.wNo >= eFAULT_MAX )
                        pSci->Stp.bView = eST_LINE_END;
                      else
                        pSci->Stp.bView = 3;
                    }
//                    sFatRd.wNo++;
                  }
                  FaultRd( );
#if(1)
//                                               100 22/05/27 17:26:30:999 Trip   123.4A 123.4A 123.4A  12.12A 300ms 12.12A 300ms 12.12A 300ms  300ms 300ms  300ms  300ms  300ms
                    sprintf( pSci->bTxData, "\n\r%03u %02X/%02X/%02X %02X:%02X:%02X:%03u %s  %5.1fA %5.1fA %5.1fA  %5.02fA %3.0fms %5.02fA %3.0fms %5.02fA %3.0fms  %3.0fms %3.0fms  %3.0fms  %3.0fms  %3.0fms",
                                              sFatRd.wNo, sFatRd.Time.bYY, sFatRd.Time.bMM, sFatRd.Time.bDD,
                                              sFatRd.Time.bhh, sFatRd.Time.bmm, sFatRd.Time.bss, sFatRd.Time.wms,
                                              List_Fat( sFatRd.wType ),
                                              sFatRd.fContDA, sFatRd.fContDB, sFatRd.fContDC,
                                              sFatRd.fTc1Pc, sFatRd.fTc1Cf, sFatRd.fTc2Pc, sFatRd.fTc2Cf, sFatRd.fCc_Pc,sFatRd.fCc_Cf,
                                              sFatRd.fCc_A, sFatRd.fTc_B,
                                              sFatRd.fTc_Cc_A, sFatRd.fTc_Cc_B, sFatRd.fTc_Cc_C
#else
UINT16 *pwFault;
                  pwFault = (UINT16 *)&pFault->No[sFatRd.wFa].wNo;
//                                               100 22/05/27 17:26:30:999 Trip   123.4A 123.4A 123.4A  12.12A 300ms 12.12A 300ms 12.12A 300ms  300ms 300ms  300ms   300ms   300ms
                    sprintf( pSci->bTxData, "\n\r%03u %02X/%02X/%02X %02X:%02X:%02X:%03u %s   %5.1fA %5.1fA %5.1fA  %4.02fA %3.0fms %4.02fA %3.0fms %4.02fA %3.0fms  %3.0fms %3.0fms  %3.0fms  %3.0fms  %3.0fms",
                                              sFatRd.wNo, sFatRd.Time.bYY, sFatRd.Time.bMM, sFatRd.Time.bDD,
                                              sFatRd.Time.bhh, sFatRd.Time.bmm, sFatRd.Time.bss, sFatRd.Time.wms,
                                              List_Fat( sFatRd.wType ),
                                              pwFault[eFA_CONTDA_H] <<8 + pwFault[eFA_CONTDA_L], pwFault[eFA_CONTDB_H] <<8 + pwFault[eFA_CONTDB_L], pwFault[eFA_CONTDC_H] <<8 + pwFault[eFA_CONTDC_L],
                                              pwFault[eFA_TC1PC_H] <<8 + pwFault[eFA_TC1PC_L], pwFault[eFA_TC1CF_H] <<8 + pwFault[eFA_TC1CF_L],
                                              pwFault[eFA_TC2PC_H] <<8 + pwFault[eFA_TC2PC_L], pwFault[eFA_TC2CF_H] <<8 + pwFault[eFA_TC2CF_L],
                                              pwFault[eFA_CC_PC_H] <<8 + pwFault[eFA_CC_PC_L], pwFault[eFA_CC_CF_H] <<8 + pwFault[eFA_CC_CF_L],
                                              pwFault[eFA_CC_A_H] <<8 + pwFault[eFA_CC_A_H], pwFault[eFA_TC_B_H] <<8 + pwFault[eFA_TC_B_L],
                                              pwFault[eFA_TC_CC_AH] <<8 + pwFault[eFA_TC_CC_AL], pwFault[eFA_TC_CC_BH] <<8 + pwFault[eFA_TC_CC_BL], pwFault[eFA_TC_CC_CH] <<8 + pwFault[eFA_TC_CC_CL]
#endif
                          );
      break;
      case 10:
                       if( sFat.wList == eK_NUM1 )   sprintf( pSci->bTxData, "\n\r TC1" );
                  else if( sFat.wList == eK_NUM2 )   sprintf( pSci->bTxData, "\n\r TC2" );
                  else if( sFat.wList == eK_NUM3 )   sprintf( pSci->bTxData, "\n\r CC" );
                  else if( sFat.wList == eK_NUM4 )   sprintf( pSci->bTxData, "\n\r V" );
                  else if( sFat.wList == eK_NUM5 )   sprintf( pSci->bTxData, "\n\r IA" );
                  else if( sFat.wList == eK_NUM6 )   sprintf( pSci->bTxData, "\n\r IB" );
                  else if( sFat.wList == eK_NUM7 )   sprintf( pSci->bTxData, "\n\r IC" );
                  else if( sFat.wList == eK_NUM8 )   sprintf( pSci->bTxData, "\n\r Cont" );
      break;
      case 11:
                  if( sCnt.wFa < sFat.wNo )   i_wNo = eFAULT_MAX + sCnt.wFa - sFat.wNo;
                  else                        i_wNo = sCnt.wFa - sFat.wNo;
                  i_wNo %= eFAULT_MAX;
                       if( sFat.wList == eK_NUM1 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwTripCoil1;
                  else if( sFat.wList == eK_NUM2 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwTripCoil2;
                  else if( sFat.wList == eK_NUM3 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwCloseCoil;
                  else if( sFat.wList == eK_NUM4 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwVolt;
                  else if( sFat.wList == eK_NUM5 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwCurr[0];
                  else if( sFat.wList == eK_NUM6 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwCurr[1];
                  else if( sFat.wList == eK_NUM7 )   pwWave = (UINT16 *)pWave->No[i_wNo].iwCurr[2];
                  
                  if( sFat.wList == eK_NUM8 )
                  {
                    pwWave = (UINT16 *)pWave->No[i_wNo].wContact;
                    if( sTest.b1Line )
                    {
                      sprintf( pSci->bTxData, "\n\r0x%02X 0x%02X",
                               ( pwWave[sFat.wPit] >> 8 ) & 0x00FF, ( pwWave[sFat.wPit] ) & 0x00FF );
                      sFat.wPit += 2;
                    }
                    else
                    {
                      sprintf( pSci->bTxData, "\n\r%04u 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
                               sFat.wPit *2, ( pwWave[sFat.wPit] >> 8 ) & 0x00FF, ( pwWave[sFat.wPit] ) & 0x00FF, ( pwWave[sFat.wPit +2] >> 8 ) & 0x00FF, ( pwWave[sFat.wPit +2] ) & 0x00FF, ( pwWave[sFat.wPit +4] >> 8 ) & 0x00FF, ( pwWave[sFat.wPit +4] ) & 0x00FF, ( pwWave[sFat.wPit +6] >> 8 ) & 0x00FF, ( pwWave[sFat.wPit +6] ) & 0x00FF );
                      sFat.wPit += 8;
                    }
                    if( sFat.wPit >= ( eWAVE_NUM /2 ) ){ pSci->Stp.bView = eST_LINE_END; sFat.wList = 0; }
                    else                                 pSci->Stp.bView = 11;
                  }
                  else
                  {
                    if( sTest.b1Line )
                    {
                      sprintf( pSci->bTxData, "\n\r%7d",
                               pwWave[sFat.wPit] );
                      sFat.wPit += 2;
                    }
                    else
                    {
                      sprintf( pSci->bTxData, "\n\r%04u %7d %7d %7d %7d %7d %7d %7d %7d",
                               sFat.wPit, pwWave[sFat.wPit], pwWave[sFat.wPit +2], pwWave[sFat.wPit +4], pwWave[sFat.wPit +6], pwWave[sFat.wPit +8], pwWave[sFat.wPit +10], pwWave[sFat.wPit +12], pwWave[sFat.wPit +14] );
                      sFat.wPit += 16;
                    }
                    if( sFat.wPit >= eWAVE_NUM ){ pSci->Stp.bView = eST_LINE_END; sFat.wList = 0; }
                    else                          pSci->Stp.bView = 11;
                  }
      break;
      case eST_LINE_END:
        Debug_Normal( pSci, pSci->Stp.bType );
      break;
      default:
        NOP;
      case eST_LINE_WAIT:
        pSci->Stp.bView = eST_LINE_WAIT;
      break;
      }
    break;

    case eST_DBG_PASSWORD:
    case eST_DBG_SETTING:
    case eST_DBG_ETHER:
    case eST_DBG_IP:
    case eST_DBG_SUB:
    case eST_DBG_DEF:
    case eST_DBG_PORT:
    case eST_DBG_LOC:
    case eST_DBG_LIST:
    case eST_DBG_SYS:
    case eST_DBG_ETC:
    case eST_DBG_DEBOUNCE:
    case eST_DBG_TRIPNUM:
    case eST_DBG_TRIPCURR:
    case eST_DBG_TIME:
    case eST_DBG_NEWPASS:
    case eST_DBG_RE_ENTPASS:
    case eST_DBG_MODEL:
    case eST_DBG_SERIAL:
    case eST_DBG_100MS:
    case eST_DBG_500MS:
    case eST_DBG_NO:
    case eST_DBG_DEBUG:
    case eST_DBG_FACT:
    case eST_DBG_DCCALI:
    case eST_DBG_ACCALI:
    case eST_DBG_DCALL:
    case eST_DBG_DC1:
    case eST_DBG_DC2:
    case eST_DBG_DC3:
    case eST_DBG_ACALL:
    case eST_DBG_AC1:
    case eST_DBG_AC2:
    case eST_DBG_AC3:
    case eST_DBG_AC4:
    case eST_DBG_DCALL_ZERO:
    case eST_DBG_DCALL_SPAN:
    case eST_DBG_DC1_ZERO:
    case eST_DBG_DC1_SPAN:
    case eST_DBG_DC2_ZERO:
    case eST_DBG_DC2_SPAN:
    case eST_DBG_DC3_ZERO:
    case eST_DBG_DC3_SPAN:
    case eST_DBG_ACALL_ZERO:
    case eST_DBG_ACALL_SPAN:
    case eST_DBG_AC1_ZERO:
    case eST_DBG_AC1_SPAN:
    case eST_DBG_AC2_ZERO:
    case eST_DBG_AC2_SPAN:
    case eST_DBG_AC3_ZERO:
    case eST_DBG_AC3_SPAN:
    case eST_DBG_AC4_ZERO:
    case eST_DBG_AC4_SPAN:
    case eST_DBG_PH:
    case eST_DBG_RATIO:
    case eST_DBG_DC_RATIO:
    case eST_DBG_DCRATIO:
    case eST_DBG_AC_RATIO:
    case eST_DBG_ACVRATIO:
    case eST_DBG_ACIRATIO:
    case eST_DBG_NUMBER:
      switch( pSci->Stp.bView++ )
      {
      case eST_LINE_STA:
        sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
        pSci->Stp.bView = eST_LINE_RUN;
      break;
      case eST_LINE_HELP_STA:
        sprintf( pSci->bTxData, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
      break;
      case eST_LINE_HELP:
        Terminal_Goto( pSci, 0, 0 );
        pSci->Stp.bView = eST_LINE_END;
      break;
      case eST_LINE_RUN:
        Terminal_Goto( pSci, 0, 0 );
      break;
      case eST_LINE_LINE_END:
        pSci->Stp.bView = eST_LINE_END;
      case eST_LINE_LINE4:
      case eST_LINE_LINE3:
      case eST_LINE_LINE2:
      case eST_LINE_LINE1:  sprintf( pSci->bTxData, "+--------+----------+----------+----------+----------+----------+----------+----------+\n\r" );  break;
//                                                   |        |0123456789|0123456789|0123456789|0123456789|0123456789|0123456789|0123456789|
      case eST_LINE_TIME:
                            sprintf( pSci->bTxData, "| %02u/%02u/%02u %02u:%02u:%02u |   Temp:%7.02f℃   DI1:%s DI2:%s   -5V:%c -15V:%c +15V:%c +24V:%c   |\n\r",
                                                      BCD2DEC( sDsp.Time.bYY ), BCD2DEC( sDsp.Time.bMM ), BCD2DEC( sDsp.Time.bDD ), 
                                                      BCD2DEC( sDsp.Time.bhh ), BCD2DEC( sDsp.Time.bmm ), BCD2DEC( sDsp.Time.bss ), 
                                                      sDsp.fValue[eCAL_DSP_TEMP],
                                                      sIn.wInput & eST_B_IN_DI1 ? "Hi" : "Lo", sIn.wInput & eST_B_IN_DI2 ? "Hi" : "Lo",
                                                      sSta.lError & eST_B_IN_N5V ? 'X' : 'O', sSta.lError & eST_B_IN_N15V ? 'X' : 'O',
                                                      sSta.lError & eST_B_IN_P15V ? 'X' : 'O', sSta.lError & eST_B_IN_P24V ? 'X' : 'O'
                                      );
      break;
//      case eST_LINE_LINE?:  sprintf( pSci->bTxData, "+--------+----------+----------+----------+----------+----------+----------+----------+\n\r" );  break;
      case eST_LINE_INFO:   sprintf( pSci->bTxData, "|        |     V    |    IA    |    IB    |    IC    |TripCoil1 |TripCoil2 |CloseCoil |\n\r" );  break;
//      case eST_LINE_LINE?:  sprintf( pSci->bTxData, "+--------+----------+----------+----------+----------+----------+----------+----------+\n\r" );  break;
      case eST_LINE_VALUE:
        i_fValue[0] = sDsp.fValue[eCAL_DSP_V]  ;
        i_fValue[1] = sDsp.fValue[eCAL_DSP_IA] ;
        i_fValue[2] = sDsp.fValue[eCAL_DSP_IB] ;
        i_fValue[3] = sDsp.fValue[eCAL_DSP_IC] ;
        i_fValue[4] = sDsp.fValue[eCAL_DSP_TC1];
        i_fValue[5] = sDsp.fValue[eCAL_DSP_TC2];
        i_fValue[6] = sDsp.fValue[eCAL_DSP_CC] ;
                            sprintf( pSci->bTxData, "| Value  |%8.02fV |%8.02fA |%8.02fA |%8.02fA |%8.02fA |%8.02fA |%8.02fA |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3],
                                                              i_fValue[4], i_fValue[5],
                                                              i_fValue[6]
                                      );
      break;
      case eST_LINE_PHASE:
        i_fValue[0] = sDsp.fValue[eCAL_DSP_VP] ;
        i_fValue[1] = sDsp.fValue[eCAL_DSP_IAP];
        i_fValue[2] = sDsp.fValue[eCAL_DSP_IBP];
        i_fValue[3] = sDsp.fValue[eCAL_DSP_ICP];
        i_fValue[4] = sDsp.fVValue[eADC_TC1];
        i_fValue[5] = sDsp.fVValue[eADC_TC2];
        i_fValue[6] = sDsp.fVValue[eADC_CC];
                            sprintf( pSci->bTxData, "| Phase  | %7.02f°| %7.02f°| %7.02f°| %7.02f°|%8.02fV |%8.02fV |%8.02fV |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3],
                                                              i_fValue[4], i_fValue[5],
                                                              i_fValue[6]
                                      );
      break;
      case eST_LINE_LINE_DBG:    sprintf( pSci->bTxData, "+--------+----------+----------+----------+----------+----------+----------+----------+\n\r" );
        if( pSci->Stp.bType == eST_DBG_DEBUG )
          pSci->Stp.bView = eST_LINE_END;
        else
          pSci->Stp.bView = eST_LINE_ZEROR;
      break;
      case eST_LINE_ZEROR:
        i_wValue[0] = (UINT16)( sSet.wZeR[eADC_V] );
        i_wValue[1] = (UINT16)( sSet.wZeR[eADC_IA] );
        i_wValue[2] = (UINT16)( sSet.wZeR[eADC_IB] );
        i_wValue[3] = (UINT16)( sSet.wZeR[eADC_IC] );
        i_wValue[4] = (UINT16)( sSet.wZeR[eADC_TC1] );
        i_wValue[5] = (UINT16)( sSet.wZeR[eADC_TC2] );
        i_wValue[6] = (UINT16)( sSet.wZeR[eADC_CC] );
                            sprintf( pSci->bTxData, "| RangeZ |  %4u.%01uV |  %4u.%01uA |  %4u.%01uA |  %4u.%01uA |  %4u.%01uV |  %4u.%01uV |  %4u.%01uV |\n\r",
                                                                i_wValue[0] /10, i_wValue[0] %10, i_wValue[1] /10, i_wValue[1] %10,
                                                                i_wValue[2] /10, i_wValue[2] %10, i_wValue[3] /10, i_wValue[3] %10,
                                                                i_wValue[4] /10, i_wValue[4] %10, i_wValue[5] /10, i_wValue[5] %10,
                                                                i_wValue[6] /10, i_wValue[6] %10
                                      );
      break;
      case eST_LINE_SPANR:
          i_wValue[0] = (UINT16)( sSet.wSpR[eADC_V] );
          i_wValue[1] = (UINT16)( sSet.wSpR[eADC_IA] );
          i_wValue[2] = (UINT16)( sSet.wSpR[eADC_IB] );
          i_wValue[3] = (UINT16)( sSet.wSpR[eADC_IC] );
          i_wValue[4] = (UINT16)( sSet.wSpR[eADC_TC1] );
          i_wValue[5] = (UINT16)( sSet.wSpR[eADC_TC2] );
          i_wValue[6] = (UINT16)( sSet.wSpR[eADC_CC] );
                            sprintf( pSci->bTxData, "| RangeS |  %4u.%01uV |  %4u.%01uA |  %4u.%01uA |  %4u.%01uA |  %4u.%01uV |  %4u.%01uV |  %4u.%01uV |\n\r",
                                                                i_wValue[0] /10, i_wValue[0] %10, i_wValue[1] /10, i_wValue[1] %10,
                                                                i_wValue[2] /10, i_wValue[2] %10, i_wValue[3] /10, i_wValue[3] %10,
                                                                i_wValue[4] /10, i_wValue[4] %10, i_wValue[5] /10, i_wValue[5] %10,
                                                                i_wValue[6] /10, i_wValue[6] %10
                                        );
      break;
//      case eST_LINE_LINE?:   sprintf( pSci->bTxData, "+--------+----------+----------+----------+----------+----------+----------+----------+\n\r" );   break;
      case eST_LINE_ZERO:
        i_fValue[0] = sSet.fZe[eADC_V]  ;
        i_fValue[1] = sSet.fZe[eADC_IA] ;
        i_fValue[2] = sSet.fZe[eADC_IB] ;
        i_fValue[3] = sSet.fZe[eADC_IC] ;
        i_fValue[4] = sSet.fZe[eADC_TC1];
        i_fValue[5] = sSet.fZe[eADC_TC2];
        i_fValue[6] = sSet.fZe[eADC_CC] ;
                            sprintf( pSci->bTxData, "|  Zero  | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3],
                                                              i_fValue[4], i_fValue[5],
                                                              i_fValue[6]
                                      );
      break;
      case eST_LINE_SPAN:
        i_fValue[0] = sSet.fSp[eADC_V]  ;
        i_fValue[1] = sSet.fSp[eADC_IA] ;
        i_fValue[2] = sSet.fSp[eADC_IB] ;
        i_fValue[3] = sSet.fSp[eADC_IC] ;
        i_fValue[4] = sSet.fSp[eADC_TC1];
        i_fValue[5] = sSet.fSp[eADC_TC2];
        i_fValue[6] = sSet.fSp[eADC_CC] ;
                            sprintf( pSci->bTxData, "|  Span  | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f | %8.02f |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3],
                                                              i_fValue[4], i_fValue[5],
                                                              i_fValue[6]
                                      );
      break;
      case eST_LINE_PH:
        i_fValue[0] = sSet.fPh[eADC_V] ;
        i_fValue[1] = sSet.fPh[eADC_IA];
        i_fValue[2] = sSet.fPh[eADC_IB];
        i_fValue[3] = sSet.fPh[eADC_IC];
                            sprintf( pSci->bTxData, "| Phase  | %7.02f°| %7.02f°| %7.02f°| %7.02f°|          |          |          |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3]
                                      );
      break;
      case eST_LINE_RATIO:
        i_fValue[0] = sSet.fRatio[eADC_V] ;
        i_fValue[1] = sSet.fRatio[eADC_IA];
        i_fValue[2] = sSet.fRatio[eADC_IB];
        i_fValue[3] = sSet.fRatio[eADC_IC];
        i_fValue[4] = sSet.fRatio[eADC_TC1];
        i_fValue[5] = sSet.fRatio[eADC_TC2];
        i_fValue[6] = sSet.fRatio[eADC_CC];
                            sprintf( pSci->bTxData, "| Ratio  |%8.02fV |%8.02fA |%8.02fA |%8.02fA |   %5.02fA |   %5.02fA |   %5.02fA |\n\r",
                                                              i_fValue[0], i_fValue[1],
                                                              i_fValue[2], i_fValue[3],
                                                              i_fValue[4], i_fValue[5],
                                                              i_fValue[6]
                                      );
      break;
//      case eST_LINE_LINE_END:
      case eST_LINE_END:
        Debug_Normal( pSci, pSci->Stp.bType );
      break;
      case eST_LINE_WAIT:
        pSci->Stp.bView = eST_LINE_WAIT;
      break;
      default:
      break;
      }
    break;
    case eST_DBG_CHAR:
      switch( pSci->Stp.bView++ )
      {
      case 0:
        Terminal_Goto( pSci, 0, 0 );
      break;
      case 1:
        Debug_Normal( pSci, pSci->Stp.bType );
        pSci->Stp.bView = eST_LINE_WAIT;
      break;
      case eST_LINE_WAIT:
        pSci->Stp.bView = eST_LINE_WAIT;
      break;
      default:
      break;
      }
    break;
    default:
    break;
    }
    pSci->Cnt.bTxEnd = strlen( pSci->bTxData );
    if( pSci->Cnt.bTxEnd != 0 )
    {
      pSci->Cnt.bTxEnd += 1;
      SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
      SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int
    }
  }
}


void Number_Start( DEBUG_REG *pSci )
{
  UINT16  i;

  pSci->Stp.bType = eST_DBG_NUMBER;
  pSci->bCmdCount = 0;
  for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
}
void Char_Start( DEBUG_REG *pSci )
{
  UINT16  i;

  pSci->Stp.bType = eST_DBG_CHAR;
  pSci->bCmdCount = 0;
  for( i=0; i<eTERMINAL_DATA; i++ )   pSci->bCmdData[i] = 0;
}
void List_Help( DEBUG_REG *pSci )
{
  sprintf( pSci->bTxData, "\n\r%s                                                \n\rTHOMAS%s ", Debug_THelpListFull( pSci->Stp.bType ), Debug_TCursor( pSci, pSci->Stp.bType ) );
}
void List_Char( DEBUG_REG *pSci, UINT8 i_bType )
{
  sprintf( pSci->bTxData, "\r                                                \rTHOMAS%s %s", Debug_TCursor( pSci, i_bType ), pSci->bCmdData );
}
void List_ShotKey( DEBUG_REG *pSci, UINT8 i_bType, UINT8 i_bData )
{
  sprintf( pSci->bTxData, "\r                                                \rTHOMAS%s %s", Debug_TCursor( pSci, i_bType ), Debug_TList( i_bType, i_bData ) );
}

void Terminal_Goto( DEBUG_REG *pSci, UINT8 i_bStartX, UINT8 i_bStartY )
{
  UINT8   i_bEndX = 0, i_bEndY = 0;

  while( i_bStartX >= 10 )
  {
    i_bStartX -= 10;
    i_bEndX++;
  }
  while( i_bStartY >= 10 )
  {
    i_bStartY -= 10;
    i_bEndY++;
  }

  sprintf( pSci->bTxData, "%c%c%c%c;%c%cH", 0x1B, 0x5B, '0'+i_bEndY, '0'+i_bStartY, '0'+i_bEndX, '0'+i_bStartX );

}

UINT16 BCD2DEC( UINT16 i_wBcd )
{
  UINT16  i_wDec;

  i_wDec  = ( i_wBcd >> 12 ) *1000;
  i_wDec += ( ( i_wBcd >> 8 ) & 0x0F ) *100;
  i_wDec += ( ( i_wBcd >> 4 ) & 0x0F ) *10;
  i_wDec += ( i_wBcd & 0x0F );

  return i_wDec;
}
UINT16 DEC2BCD( UINT16 i_wDec )
{
  UINT16  i_wData, i_wBcd;

  i_wData = i_wDec / 1000;  i_wDec %= 1000;
  i_wBcd  = ( i_wData << 12 );
  i_wData = i_wDec / 100;   i_wDec %= 100;
  i_wBcd += ( i_wData << 8 );
  i_wData = i_wDec / 10;   i_wDec %= 10;
  i_wBcd += ( i_wData << 4 );
  i_wData = i_wDec;
  i_wBcd += ( i_wData << 0 );

  return i_wBcd;
}


char* Debug_TList( UINT16 i_wType, UINT8 i_bData )
{
  switch( i_wType )
  {
  default:            return "";
  case eST_DBG_NORMAL:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_RESET:            return "Reset";
    case eK_SETTING:          return "Setting";
    case eK_DEBUG:            return "Debug";
    case eK_CLEAR:            return "Clear";
    case eK_LOGO:             return "Logo";
    case eK_VIEW:             return "View";
    }
//  break;
  case eST_DBG_PASSWORD:
  break;
  case eST_DBG_SETTING:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_ETHER:            return "Ether";     // Ethernet
    case eK_LIST:             return "List";      // Event, Fault
    case eK_SYS:              return "Sys";       // System
    case eK_ETC:              return "eTc";       // Etc
    case eK_FACT:             return "Fact";      // Factory
    }
//  break;
  case eST_DBG_DEBUG:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    }
//  break;
  case eST_DBG_ETHER:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_IP:               return "Ip";        // IP Address 
    case eK_SUB:              return "Sub";       // Subnet mask Address
    case eK_DEF:              return "Def";       // Default gateway
    case eK_PORT:             return "Port";      // Default gateway
//    case eK_LOC:              return "Loc";       // Local unit IP Address
    case eK_MAC:              
      if( sDsp.wLv == eST_LV1 ) return "Mac";       // Mac
      else                      return "";
    }
//  break;
  case eST_DBG_LIST:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_EVENT:            return "Event";     // Event List
    case eK_FAULT:            return "Fault";     // Fault List
    }
//  break;
  case eST_DBG_SYS:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_DEBOUNCE:         return "Debounce";  // Debounce
    case eK_TRIPNUM:          return "tripNum";   // trip Number
    case eK_TRIPCURR:         return "TripCurr";  // Trip Current
    case eK_RATIO:            return "Ratio";     // Ratio
    }
//  break;
  case eST_DBG_ETC:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_TIME:             return "Time";      // Time
    case eK_PASS:             return "Pass";      // Password
    case eK_MODEL:            return "Model";     // Model
    case eK_SERIAL:           return "Serial";    // Serial
    case eK_100MS:            return "100ms";     // 100ms
    case eK_500MS:            return "500ms";     // 500ms
    }
//  break;
  case eST_DBG_TIME:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_YEAR:             return "Year";      // Year
    case eK_MON:              return "Mon";       // Mon
    case eK_DAY:              return "Day";       // Day
    case eK_HOUR:             return "hOur";      // Hour
    case eK_MIN:              return "mIn";       // Min
    case eK_SEC:              return "Sec";       // Sec
    }
//  break;
  case eST_DBG_FACT:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_DCCALI:           return "Dccali";    // DC Calibration
    case eK_ACCALI:           return "Accali";    // AC Calibration
    }
//  break;
  case eST_DBG_DCCALI:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_DCALL:            return "dcAll";
    case eK_DC1:              return "dc1";
    case eK_DC2:              return "dc2";
    case eK_DC3:              return "dc3";
    case eK_DC_RATIO:         return "Ratio";
    }
//  break;
  case eST_DBG_ACCALI:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_ACALL:            return "acAll";
    case eK_AC1:              return "ac1";
    case eK_AC2:              return "ac2";
    case eK_AC3:              return "ac3";
    case eK_AC4:              return "ac4";
    case eK_AC_RATIO:         return "Ratio";
    case eK_PH:               return "Ph";
    }
//  break;
  case eST_DBG_DCALL:
  case eST_DBG_DC1:
  case eST_DBG_DC2:
  case eST_DBG_DC3:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_ZERO:             return "Zero";
    case eK_SPAN:             return "Span";
//    case eK_DCRATIO:          return "Ratio";
    }
//  break;
  case eST_DBG_ACALL:
  case eST_DBG_AC1:
  case eST_DBG_AC2:
  case eST_DBG_AC3:
  case eST_DBG_AC4:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_ZERO:             return "Zero";
    case eK_SPAN:             return "Span";
    case eK_AC2:              return "Ph";
    }
//  break;
  case eST_DBG_DCALL_ZERO:
  case eST_DBG_DCALL_SPAN:
  case eST_DBG_DC1_ZERO:
  case eST_DBG_DC1_SPAN:
  case eST_DBG_DC2_ZERO:
  case eST_DBG_DC2_SPAN:
  case eST_DBG_DC3_ZERO:
  case eST_DBG_DC3_SPAN:
  case eST_DBG_AC1_ZERO:
  case eST_DBG_AC1_SPAN:
  case eST_DBG_AC2_ZERO:
  case eST_DBG_AC2_SPAN:
  case eST_DBG_AC3_ZERO:
  case eST_DBG_AC3_SPAN:
  case eST_DBG_AC4_ZERO:
  case eST_DBG_AC4_SPAN:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_RANGE:            return "Range";
    case eK_SAVE:             return "Save";
    }
  case eST_DBG_ACALL_ZERO:
  case eST_DBG_ACALL_SPAN:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_VRANGE:           return "Vrange";
    case eK_RANGE:            return "iRange";
    case eK_SAVE:             return "Save";
    }
  case eST_DBG_PH:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_SAVE:             return "Save";
    }
//  break;
  case eST_DBG_NEWPASS:
  case eST_DBG_RE_ENTPASS:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    }
//  break;
  case eST_DBG_EVENT:
  case eST_DBG_FAULT:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
//    case eK_F_ERASE:
    case eK_E_ERASE:          return "Erase";
//    case eK_F_LIST:
    case eK_E_LIST:           return "List";
    case eK_NO:               return "No";
    case eK_NUM1:             return "TC1";
    case eK_NUM2:             return "TC2";
    case eK_NUM3:             return "CC";
    case eK_NUM4:             return "V";
    case eK_NUM5:             return "IA";
    case eK_NUM6:             return "IB";
    case eK_NUM7:             return "IC";
    case eK_NUM8:             return "Cont";
    }
//  break;
  case eST_DBG_E_ERASE:
  case eST_DBG_F_ERASE:       return "";
  case eST_DBG_E_LIST:
  case eST_DBG_F_LIST:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    }
//  break;
  case eST_DBG_RATIO:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_RATIO1:           return "Ratio1";
    case eK_RATIO2:           return "Ratio2";
    case eK_RATIO3:           return "Ratio3";
    case eK_RATIO4:           return "Ratio4";
    case eK_RATIO5:           return "Ratio5";
    case eK_RATIO6:           return "Ratio6";
    case eK_RATIO7:           return "Ratio7";
    }
//  break;
  case eST_DBG_DC_RATIO:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_DCRATIO:          return "Ratio";
    case eK_DCRATIO1:         return "ratio1";
    case eK_DCRATIO2:         return "ratio2";
    case eK_DCRATIO3:         return "ratio3";
    }
//  break;
//  case eST_DBG_RATIO: // Setting/Sys/Ratio 에 만들어야 됨
  case eST_DBG_AC_RATIO:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    case eK_ACVRATIO:         return "Vratio";
    case eK_ACIRATIO:         return "iRatio";
    case eK_ACRATIO1:         return "ratio1";
    case eK_ACRATIO2:         return "ratio2";
    case eK_ACRATIO3:         return "ratio3";
    case eK_ACRATIO4:         return "ratio4";
    }
//  break;
  case eST_DBG_IP:
  case eST_DBG_SUB:
  case eST_DBG_DEF:
  case eST_DBG_PORT:
  case eST_DBG_LOC:
  case eST_DBG_DEBOUNCE:
  case eST_DBG_TRIPNUM:
  case eST_DBG_TRIPCURR:
//  case eST_DBG_DC_RATIO:
  case eST_DBG_100MS:
  case eST_DBG_500MS:
  case eST_DBG_NO:
  case eST_DBG_YEAR:
  case eST_DBG_MON:
  case eST_DBG_DAY:
  case eST_DBG_HOUR:
  case eST_DBG_MIN:
  case eST_DBG_SEC:
  case eST_DBG_DCALLRZERO:
  case eST_DBG_DCALLRSPAN:
  case eST_DBG_DC1RZERO:
  case eST_DBG_DC1RSPAN:
  case eST_DBG_DC2RZERO:
  case eST_DBG_DC2RSPAN:
  case eST_DBG_DC3RZERO:
  case eST_DBG_DC3RSPAN:
  case eST_DBG_ACVRZERO:
  case eST_DBG_ACVRSPAN:
  case eST_DBG_ACIRZERO:
  case eST_DBG_ACIRSPAN:
  case eST_DBG_AC1RZERO:
  case eST_DBG_AC1RSPAN:
  case eST_DBG_AC2RZERO:
  case eST_DBG_AC2RSPAN:
  case eST_DBG_AC3RZERO:
  case eST_DBG_AC3RSPAN:
  case eST_DBG_AC4RZERO:
  case eST_DBG_AC4RSPAN:
  case eST_DBG_RATIO1:
  case eST_DBG_RATIO2:
  case eST_DBG_RATIO3:
  case eST_DBG_RATIO4:
  case eST_DBG_RATIO5:
  case eST_DBG_RATIO6:
  case eST_DBG_RATIO7:
  case eST_DBG_ACVRATIO:
  case eST_DBG_ACIRATIO:
  case eST_DBG_ACRATIO1:
  case eST_DBG_ACRATIO2:
  case eST_DBG_ACRATIO3:
  case eST_DBG_ACRATIO4:
  case eST_DBG_DCRATIO:
  case eST_DBG_DCRATIO1:
  case eST_DBG_DCRATIO2:
  case eST_DBG_DCRATIO3:
  case eST_DBG_NUMBER:
    switch( i_bData )
    {
    default:
    case 0x00:                return "";
    case eK_HELP:             return "Help";
    case eK_EXIT:             return "eXit";
    case eK_BACK:             return "Back";
    }
//  break;
  case eST_DBG_MODEL:
  case eST_DBG_SERIAL:
  case eST_DBG_CHAR:          return "ESC";
//  break;
  }
  return "";
}
char* Debug_TCursor( DEBUG_REG *pSci, UINT16 i_wType )
{
  switch( i_wType )
  {
  default:
  case eST_DBG_NORMAL:        return ">";

  case eST_DBG_PASSWORD:      return "/Password>";

  case eST_DBG_SETTING:       return "/Setting>";
  case eST_DBG_DEBUG:         return "/Debug>";
  
  case eST_DBG_ETHER:         return "/Ether>";
  case eST_DBG_LIST:          return "/List>";
  case eST_DBG_SYS:           return "/Sys>";
  case eST_DBG_ETC:           return "/eTc>";
  case eST_DBG_FACT:          return "/Fact>";

  case eST_DBG_IP:            return "/Ether/Ip>";
  case eST_DBG_SUB:           return "/Ether/Sub>";
  case eST_DBG_DEF:           return "/Ether/Def>";
  case eST_DBG_PORT:          return "/Ether/Port>";
  case eST_DBG_LOC:           return "/Ether/Loc>";
  case eST_DBG_MAC:           return "/Ether/Mac>";

  case eST_DBG_EVENT:         return "/List/Event>";
  case eST_DBG_FAULT:         return "/List/Fault>";

  case eST_DBG_DEBOUNCE:      return "/Sys/Debounce>";
  case eST_DBG_TRIPNUM:       return "/Sys/tripNum>";
  case eST_DBG_TRIPCURR:      return "/Sys/TripCurr>";
  case eST_DBG_RATIO:         return "/Sys/Ratio>";

  case eST_DBG_TIME:          return "/eTc/Time>";
  case eST_DBG_NEWPASS:       return "/eTc/NewPass>";
  case eST_DBG_RE_ENTPASS:    return "/eTc/ReEntPass>";
  case eST_DBG_MODEL:         return "/eTc/Model>";
  case eST_DBG_SERIAL:        return "/eTc/Serial>";
  case eST_DBG_100MS:         return "/eTc/100ms>";
  case eST_DBG_500MS:         return "/eTc/500ms>";

  case eST_DBG_NO:            return "/Fault/No>";

  case eST_DBG_YEAR:          return "/eTc/Year>";
  case eST_DBG_MON:           return "/eTc/Mon>";
  case eST_DBG_DAY:           return "/eTc/Day>";
  case eST_DBG_HOUR:          return "/eTc/hOur>";
  case eST_DBG_MIN:           return "/eTc/mIn>";
  case eST_DBG_SEC:           return "/eTc/Sec>";

  case eST_DBG_DCCALI:        return "/Dccali>";
  case eST_DBG_ACCALI:        return "/Accali>";
  case eST_DBG_DCALL:         return "/Dcall>";
  case eST_DBG_DC1:           return "/Dc1>";
  case eST_DBG_DC2:           return "/Dc2>";
  case eST_DBG_DC3:           return "/Dc3>";
  case eST_DBG_ACALL:         return "/Acall>";
  case eST_DBG_AC1:           return "/Ac1>";
  case eST_DBG_AC2:           return "/Ac2>";
  case eST_DBG_AC3:           return "/Ac3>";
  case eST_DBG_AC4:           return "/Ac4>";
  case eST_DBG_DCALL_ZERO:    return "/dcZero>";
  case eST_DBG_DCALL_SPAN:    return "/dcSpan>";
  case eST_DBG_DC1_ZERO:      return "/dc1Zero>";
  case eST_DBG_DC1_SPAN:      return "/dc1Span>";
  case eST_DBG_DC2_ZERO:      return "/dc2Zero>";
  case eST_DBG_DC2_SPAN:      return "/dc2Span>";
  case eST_DBG_DC3_ZERO:      return "/dc3Zero>";
  case eST_DBG_DC3_SPAN:      return "/dc3Span>";
  case eST_DBG_ACALL_ZERO:    return "/acZero>";
  case eST_DBG_ACALL_SPAN:    return "/acSpan>";
  case eST_DBG_AC1_ZERO:      return "/ac1Zero>";
  case eST_DBG_AC1_SPAN:      return "/ac1Span>";
  case eST_DBG_AC2_ZERO:      return "/ac2Zero>";
  case eST_DBG_AC2_SPAN:      return "/ac2Span>";
  case eST_DBG_AC3_ZERO:      return "/ac3Zero>";
  case eST_DBG_AC3_SPAN:      return "/ac3Span>";
  case eST_DBG_AC4_ZERO:      return "/ac4Zero>";
  case eST_DBG_AC4_SPAN:      return "/ac4Span>";
  case eST_DBG_PH:            return "/Phase>";

  case eST_DBG_DCALLRZERO:    return "/dcZero/Range>";
  case eST_DBG_DCALLRSPAN:    return "/dcSpan/Range>";
  case eST_DBG_DC1RZERO:      return "/dc1Zero/Range>";
  case eST_DBG_DC1RSPAN:      return "/dc1Span/Range>";
  case eST_DBG_DC2RZERO:      return "/dc2Zero/Range>";
  case eST_DBG_DC2RSPAN:      return "/dc2Span/Range>";
  case eST_DBG_DC3RZERO:      return "/dc3Zero/Range>";
  case eST_DBG_DC3RSPAN:      return "/dc3Span/Range>";

  case eST_DBG_ACVRZERO:      return "/acZero/Vrange>";
  case eST_DBG_ACVRSPAN:      return "/acSpan/Vrange>";
  case eST_DBG_ACIRZERO:      return "/acZero/Range>";
  case eST_DBG_ACIRSPAN:      return "/acSpan/Range>";
  case eST_DBG_AC1RZERO:      return "/ac1Zero/Range>";
  case eST_DBG_AC1RSPAN:      return "/ac1Span/Range>";
  case eST_DBG_AC2RZERO:      return "/ac2Zero/Range>";
  case eST_DBG_AC2RSPAN:      return "/ac2Span/Range>";
  case eST_DBG_AC3RZERO:      return "/ac3Zero/Range>";
  case eST_DBG_AC3RSPAN:      return "/ac3Span/Range>";
  case eST_DBG_AC4RZERO:      return "/ac4Zero/Range>";
  case eST_DBG_AC4RSPAN:      return "/ac4Span/Range>";

  case eST_DBG_RATIO1:        return "/Sys/Ratio1>";
  case eST_DBG_RATIO2:        return "/Sys/Ratio2>";
  case eST_DBG_RATIO3:        return "/Sys/Ratio3>";
  case eST_DBG_RATIO4:        return "/Sys/Ratio4>";
  case eST_DBG_RATIO5:        return "/Sys/Ratio5>";
  case eST_DBG_RATIO6:        return "/Sys/Ratio6>";
  case eST_DBG_RATIO7:        return "/Sys/Ratio7>";

  case eST_DBG_AC_RATIO:      return "/Accali/Ratio>";
  case eST_DBG_ACVRATIO:      return "/Accali/Vratio>";
  case eST_DBG_ACIRATIO:      return "/Accali/iRatio>";
  case eST_DBG_ACRATIO1:      return "/Accali/ratio1>";
  case eST_DBG_ACRATIO2:      return "/Accali/ratio2>";
  case eST_DBG_ACRATIO3:      return "/Accali/ratio3>";
  case eST_DBG_ACRATIO4:      return "/Accali/ratio3>";

  case eST_DBG_DC_RATIO:      return "/Dccali/Ratio>";
  case eST_DBG_DCRATIO:       return "/Dccali/ratio>";
  case eST_DBG_DCRATIO1:      return "/Dccali/ratio1>";
  case eST_DBG_DCRATIO2:      return "/Dccali/ratio2>";
  case eST_DBG_DCRATIO3:      return "/Dccali/ratio3>";

  case eST_DBG_NUMBER:        return "";

  case eST_DBG_CHAR:          return "";
  }
}
char* Debug_THelpList( UINT16 i_wType, char *i_pbChr )
{
  switch( i_wType )
  {
  default:
  case eST_DBG_NORMAL:        return "?, R, L, V, C, S, D           ";

  case eST_DBG_PASSWORD:      return "Password ****                 ";
  case eST_DBG_SETTING:
#if(1)
    if( sDsp.wLv == eST_LV1 )       return "?, X, B, S, E, L, T, F        ";    // Level 1
    else if( sDsp.wLv == eST_LV2 )  return "?, X, B, S, E, L, T           ";    // Level 2
//    else                      return "?, X, B, E, L, T,             ";    // Level 3
#else
    return "?, X, B, S, E, L, T, F           ";    // Level 1
#endif
  case eST_DBG_DEBUG:         return "?, X, B                       ";

  case eST_DBG_ETHER:
      if( sDsp.wLv == eST_LV1 ) return "?, X, B, I, S, D, P, M        ";
      else                      return "?, X, B, I, S, D, P           ";
//  case eST_DBG_ETHER:         return "?, X, B, I, S, D, P, L, M     ";
  case eST_DBG_LIST:          return "?, X, B, E, F                 ";
  case eST_DBG_SYS:           return "?, X, B, D, N, T, R           ";
  case eST_DBG_ETC:           return "?, X, B, T, P, M, S, 1, 5     ";

  case eST_DBG_TIME:          return "?, X, B, Y, M, D, O, I, S     ";

  case eST_DBG_FACT:          return "?, X, B, A, D                 ";
  case eST_DBG_DCCALI:        return "?, X, B, A, 1~3, R            ";
  case eST_DBG_ACCALI:        return "?, X, B, A, 1~4, R, P         ";
  case eST_DBG_DCALL:
  case eST_DBG_DC1:
  case eST_DBG_DC2:
  case eST_DBG_DC3:           return "?, X, B, Z, S                 ";
  case eST_DBG_ACALL:
  case eST_DBG_AC1:
  case eST_DBG_AC2:
  case eST_DBG_AC3:
  case eST_DBG_AC4:           return "?, X, B, Z, S                 ";
  case eST_DBG_DCALL_ZERO:
  case eST_DBG_DCALL_SPAN:
  case eST_DBG_DC1_ZERO:
  case eST_DBG_DC1_SPAN:
  case eST_DBG_DC2_ZERO:
  case eST_DBG_DC2_SPAN:
  case eST_DBG_DC3_ZERO:
  case eST_DBG_DC3_SPAN:
  case eST_DBG_AC1_ZERO:
  case eST_DBG_AC1_SPAN:
  case eST_DBG_AC2_ZERO:
  case eST_DBG_AC2_SPAN:
  case eST_DBG_AC3_ZERO:
  case eST_DBG_AC3_SPAN:
  case eST_DBG_AC4_ZERO:
  case eST_DBG_AC4_SPAN:      return "?, X, B, R, S                 ";
  case eST_DBG_ACALL_ZERO:
  case eST_DBG_ACALL_SPAN:    return "?, X, B, V, R, S              ";
  case eST_DBG_PH:            return "?, X, B, S                    ";

  case eST_DBG_NEWPASS:       return "New Password ****             ";
  case eST_DBG_RE_ENTPASS:    return "Re-Enter Password ****        ";

  case eST_DBG_EVENT:
  case eST_DBG_FAULT:         return "?, X, B, E, L                 ";
  case eST_DBG_E_LIST:
  case eST_DBG_F_LIST:        return "?, X, B                       ";

  case eST_DBG_RATIO:         return "?, X, B, 1~7                  ";
  case eST_DBG_DC_RATIO:      return "?, X, B, R, 1~3               ";
  case eST_DBG_AC_RATIO:      return "?, X, B, V, R, 1~4            ";

  case eST_DBG_E_ERASE:
  case eST_DBG_F_ERASE:

  case eST_DBG_IP:
  case eST_DBG_SUB:
  case eST_DBG_DEF:
  case eST_DBG_PORT:
  case eST_DBG_LOC:

  case eST_DBG_DEBOUNCE:
  case eST_DBG_TRIPNUM:
  case eST_DBG_TRIPCURR:

  case eST_DBG_100MS:
  case eST_DBG_500MS:

  case eST_DBG_NO:

  case eST_DBG_YEAR:
  case eST_DBG_MON:
  case eST_DBG_DAY:
  case eST_DBG_HOUR:
  case eST_DBG_MIN:
  case eST_DBG_SEC:

  case eST_DBG_DCALLRZERO:
  case eST_DBG_DCALLRSPAN:
  case eST_DBG_DC1RZERO:
  case eST_DBG_DC1RSPAN:
  case eST_DBG_DC2RZERO:
  case eST_DBG_DC2RSPAN:
  case eST_DBG_DC3RZERO:
  case eST_DBG_DC3RSPAN:

  case eST_DBG_ACVRZERO:
  case eST_DBG_ACVRSPAN:
  case eST_DBG_ACIRZERO:
  case eST_DBG_ACIRSPAN:
  case eST_DBG_AC1RZERO:
  case eST_DBG_AC1RSPAN:
  case eST_DBG_AC2RZERO:
  case eST_DBG_AC2RSPAN:
  case eST_DBG_AC3RZERO:
  case eST_DBG_AC3RSPAN:
  case eST_DBG_AC4RZERO:
  case eST_DBG_AC4RSPAN:

  case eST_DBG_RATIO1:
  case eST_DBG_RATIO2:
  case eST_DBG_RATIO3:
  case eST_DBG_RATIO4:
  case eST_DBG_RATIO5:
  case eST_DBG_RATIO6:
  case eST_DBG_RATIO7:
  case eST_DBG_ACVRATIO:
  case eST_DBG_ACIRATIO:
  case eST_DBG_ACRATIO1:
  case eST_DBG_ACRATIO2:
  case eST_DBG_ACRATIO3:
  case eST_DBG_ACRATIO4:
  case eST_DBG_DCRATIO:
  case eST_DBG_DCRATIO1:
  case eST_DBG_DCRATIO2:
  case eST_DBG_DCRATIO3:

#if(1)
// ETHER ( IP, SUB, DEF, LOC : 0~255 ) ( PORT : 0~65535 )
// ETC ( DSBOU : 10~1000sec ) ( TRIPNUM : 0~300ms ) ( PASS : 0000~9999 )
// TIME ( YEAR : 0~99 ) ( MON : 1~12 ) ( DAY : 1~31 ) ( HOUR : 0~23 ) ( MIN : 0~59 ) ( SEC : 0~59 )
// DCZERO, DCSPAN, ACZERO, ACSPAN ( VRange, Range )
  case eST_DBG_NUMBER:
    sprintf( i_pbChr, "?, X, B, %.1f~%.1f  %s                 ", sKey.fMin/sKey.wMul, sKey.fMax/sKey.wMul, Setting_View( sKey.bPageGo, (char *)pbChr2 ) );
    return i_pbChr;
#else
  case eST_DBG_NUMBER:        return "?, X, B, NUMBER               ";
#endif
  case eST_DBG_MAC:
  case eST_DBG_MODEL:
  case eST_DBG_SERIAL:
  case eST_DBG_CHAR:
    if( sKey.bPageGo == eST_DBG_MAC )
      sprintf( i_pbChr, "ESC, %u~%u  %s                   ", (UINT16)sKey.fMin, (UINT16)sKey.fMax, Setting_View( sKey.bPageGo, (char *)pbChr2 ) );
    else
      sprintf( i_pbChr, "ESC                                " );

    return i_pbChr;
  }
}
char* Debug_THelpListFull( UINT16 i_wType )
{
  switch( i_wType )
  {
  default:
  case eST_DBG_NORMAL:        return "Help, Reset, Logo, View, Clear, Setting, Debug";

  case eST_DBG_PASSWORD:      return "Password ****                 ";
  case eST_DBG_SETTING:
#if(1)
    if( sDsp.wLv == eST_LV1 )       return "Help, eXit, Back, Sys, Ether, List, eTc, Fact";    // Level 1
    else if( sDsp.wLv == eST_LV2 )  return "Help, eXit, Back, Sys, Ether, List, eTc";    // Level 2
//    else                      return "?, X, B, E, L, T,             ";    // Level 3
#else
                              return "Help, eXit, Back, Sys, Ether, List, eTc, Fact";
#endif
//      return "Help, eXit, Back, Ether, List, eTc";
  case eST_DBG_DEBUG:         return "Help, eXit, Back";

  case eST_DBG_ETHER:
      if( sDsp.wLv == eST_LV1 ) return "Help, eXit, Back, Ip, Sub, Def, Port, Mac";
      else                      return "Help, eXit, Back, Ip, Sub, Def, Port";
//  case eST_DBG_ETHER:         return "Help, eXit, Back, Ip, Sub, Def, Port, Loc, Mac";
  case eST_DBG_LIST:          return "Help, eXit, Back, Event, Fault";
  case eST_DBG_SYS:           return "Help, eXit, Back, Debounce, tripNum, Tripcurr, Ratio";
  case eST_DBG_ETC:           return "Help, eXit, Back, Time, Pass, Model, Serial, 100ms, 500ms";

  case eST_DBG_TIME:          return "Help, eXit, Back, Year, Mon, Day, hOur, mIn, Sec";

  case eST_DBG_FACT:          return "Help, eXit, Back, Accali, Dccali";
  case eST_DBG_DCCALI:        return "Help, eXit, Back, dcAll, dc1~3, Ratio";
  case eST_DBG_ACCALI:        return "Help, eXit, Back, acAll, ac1~4, Ratio, Phase";
  case eST_DBG_DCALL:
  case eST_DBG_DC1:
  case eST_DBG_DC2:
  case eST_DBG_DC3:           return "Help, eXit, Back, Zero, Span";
  case eST_DBG_ACALL:
  case eST_DBG_AC1:
  case eST_DBG_AC2:
  case eST_DBG_AC3:
  case eST_DBG_AC4:           return "Help, eXit, Back, Zero, Span";
  case eST_DBG_DCALL_ZERO:
  case eST_DBG_DCALL_SPAN:
  case eST_DBG_DC1_ZERO:
  case eST_DBG_DC1_SPAN:
  case eST_DBG_DC2_ZERO:
  case eST_DBG_DC2_SPAN:
  case eST_DBG_DC3_ZERO:
  case eST_DBG_DC3_SPAN:
  case eST_DBG_AC1_ZERO:
  case eST_DBG_AC1_SPAN:
  case eST_DBG_AC2_ZERO:
  case eST_DBG_AC2_SPAN:
  case eST_DBG_AC3_ZERO:
  case eST_DBG_AC3_SPAN:
  case eST_DBG_AC4_ZERO:
  case eST_DBG_AC4_SPAN:      return "Help, eXit, Back, Range, Save";
  case eST_DBG_ACALL_ZERO:
  case eST_DBG_ACALL_SPAN:    return "Help, eXit, Back, Vrange, Range, Save";
  case eST_DBG_PH:            return "Help, eXit, Back, Save";

  case eST_DBG_NEWPASS:       return "New Password ****";
  case eST_DBG_RE_ENTPASS:    return "Re-Enter Password ****";

  case eST_DBG_EVENT:
  case eST_DBG_FAULT:         return "Help, eXit, Back, Erase, List";
  case eST_DBG_E_ERASE:
  case eST_DBG_F_ERASE:       return "Help, eXit, Back";

  case eST_DBG_RATIO:         return "Help, eXit, Back, ratio(1~7)";
  case eST_DBG_DC_RATIO:      return "Help, eXit, Back, Ratio, ratio(1~3)";
  case eST_DBG_AC_RATIO:      return "Help, eXit, Back, Vratio, iRatio, ratio(1~4)";

  case eST_DBG_E_LIST:
  case eST_DBG_F_LIST:

  case eST_DBG_IP:
  case eST_DBG_SUB:
  case eST_DBG_DEF:
  case eST_DBG_PORT:
  case eST_DBG_LOC:

  case eST_DBG_DEBOUNCE:
  case eST_DBG_TRIPNUM:
  case eST_DBG_TRIPCURR:

  case eST_DBG_100MS:
  case eST_DBG_500MS:

  case eST_DBG_NO:

  case eST_DBG_YEAR:
  case eST_DBG_MON:
  case eST_DBG_DAY:
  case eST_DBG_HOUR:
  case eST_DBG_MIN:
  case eST_DBG_SEC:

  case eST_DBG_DCALLRZERO:
  case eST_DBG_DCALLRSPAN:
  case eST_DBG_DC1RZERO:
  case eST_DBG_DC1RSPAN:
  case eST_DBG_DC2RZERO:
  case eST_DBG_DC2RSPAN:
  case eST_DBG_DC3RZERO:
  case eST_DBG_DC3RSPAN:

  case eST_DBG_ACVRZERO:
  case eST_DBG_ACVRSPAN:
  case eST_DBG_ACIRZERO:
  case eST_DBG_ACIRSPAN:
  case eST_DBG_AC1RZERO:
  case eST_DBG_AC1RSPAN:
  case eST_DBG_AC2RZERO:
  case eST_DBG_AC2RSPAN:
  case eST_DBG_AC3RZERO:
  case eST_DBG_AC3RSPAN:
  case eST_DBG_AC4RZERO:
  case eST_DBG_AC4RSPAN:

  case eST_DBG_RATIO1:
  case eST_DBG_RATIO2:
  case eST_DBG_RATIO3:
  case eST_DBG_RATIO4:
  case eST_DBG_RATIO5:
  case eST_DBG_RATIO6:
  case eST_DBG_RATIO7:
  case eST_DBG_ACVRATIO:
  case eST_DBG_ACIRATIO:
  case eST_DBG_ACRATIO1:
  case eST_DBG_ACRATIO2:
  case eST_DBG_ACRATIO3:
  case eST_DBG_ACRATIO4:
  case eST_DBG_DCRATIO:
  case eST_DBG_DCRATIO1:
  case eST_DBG_DCRATIO2:
  case eST_DBG_DCRATIO3:

  case eST_DBG_NUMBER:        return "Help, eXit, Back, NUMBER";

  case eST_DBG_MAC:
  case eST_DBG_MODEL:
  case eST_DBG_SERIAL:
  case eST_DBG_CHAR:          return "ESC";
  }
}
char* Setting_View( UINT16 i_wType, char *i_pbChr )
{
  i_pbChr[0] = 0x00;

  switch( i_wType )
  {
  case eST_DBG_E_LIST:
  case eST_DBG_F_LIST:

  case eST_DBG_IP:          sprintf( i_pbChr, "%u.%u.%u.%u", ( sDsp.wIpAddr[0] >>8 ) &0x00FF, ( sDsp.wIpAddr[0] ) &0x00FF, ( sDsp.wIpAddr[1] >>8 ) &0x00FF, ( sDsp.wIpAddr[1] ) &0x00FF );              break;
  case eST_DBG_SUB:         sprintf( i_pbChr, "%u.%u.%u.%u", ( sDsp.wSubMask[0] >>8 ) &0x00FF, ( sDsp.wSubMask[0] ) &0x00FF, ( sDsp.wSubMask[1] >>8 ) &0x00FF, ( sDsp.wSubMask[1] ) &0x00FF );          break;
  case eST_DBG_DEF:         sprintf( i_pbChr, "%u.%u.%u.%u", ( sDsp.wDefGate[0] >>8 ) &0x00FF, ( sDsp.wDefGate[0] ) &0x00FF, ( sDsp.wDefGate[1] >>8 ) &0x00FF, ( sDsp.wDefGate[1] ) &0x00FF );          break;
  case eST_DBG_PORT:        sprintf( i_pbChr, "%u", sDsp.wPortNum );          break;
  case eST_DBG_LOC:         sprintf( i_pbChr, "%u.%u.%u.%u", ( sDsp.wLocIpAddr[0] >>8 ) &0x00FF, ( sDsp.wLocIpAddr[0] ) &0x00FF, ( sDsp.wLocIpAddr[1] >>8 ) &0x00FF, ( sDsp.wLocIpAddr[1] ) &0x00FF );  break;
  case eST_DBG_MAC:         sprintf( i_pbChr, "%02X:%02X:%02X:%02X:%02X:%02X", ( sSet.wMac[0] >>8 ) &0x00FF, ( sSet.wMac[0] ) &0x00FF, ( sSet.wMac[1] >>8 ) &0x00FF, ( sSet.wMac[1] ) &0x00FF, ( sSet.wMac[2] >>8 ) &0x00FF, ( sSet.wMac[2] ) &0x00FF );     break;

  case eST_DBG_DEBOUNCE:    sprintf( i_pbChr, "%ums", sDsp.wDebo );           break;
  case eST_DBG_TRIPNUM:     sprintf( i_pbChr, "%ums", sDsp.wTrig );           break;
  case eST_DBG_TRIPCURR:    sprintf( i_pbChr, "%u.%uA", sDsp.wTrip[0] /10, sDsp.wTrip[0] %10 );     break;

  case eST_DBG_100MS:       sprintf( i_pbChr, "%uea", sSet.wNo100ms );        break;
  case eST_DBG_500MS:       sprintf( i_pbChr, "%uea", sSet.wNo500ms );        break;

  case eST_DBG_NO:          sprintf( i_pbChr, "NO.%u", sFat.wNo );            break;

  case eST_DBG_YEAR:
  case eST_DBG_MON:
  case eST_DBG_DAY:
  case eST_DBG_HOUR:
  case eST_DBG_MIN:
  case eST_DBG_SEC:         sprintf( i_pbChr, "%02u/%02u/%02u %02u:%02u:%02u", BCD2DEC( sDsp.Time.bYY ), BCD2DEC( sDsp.Time.bMM ), BCD2DEC( sDsp.Time.bDD ), BCD2DEC( sDsp.Time.bhh ), BCD2DEC( sDsp.Time.bmm ), BCD2DEC( sDsp.Time.bss ) );    break;

  case eST_DBG_DCALLRZERO:  sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_TC1] /10, sSet.wZeR[eADC_TC1] %10 );  break;
  case eST_DBG_DCALLRSPAN:  sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_TC1] /10, sSet.wSpR[eADC_TC1] %10 );  break;
  case eST_DBG_DC1RZERO:    sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_TC1] /10, sSet.wZeR[eADC_TC1] %10 );  break;
  case eST_DBG_DC1RSPAN:    sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_TC1] /10, sSet.wSpR[eADC_TC1] %10 );  break;
  case eST_DBG_DC2RZERO:    sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_TC2] /10, sSet.wZeR[eADC_TC2] %10 );  break;
  case eST_DBG_DC2RSPAN:    sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_TC2] /10, sSet.wSpR[eADC_TC2] %10 );  break;
  case eST_DBG_DC3RZERO:    sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_CC ] /10, sSet.wZeR[eADC_CC ] %10 );  break;
  case eST_DBG_DC3RSPAN:    sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_CC ] /10, sSet.wSpR[eADC_CC ] %10 );  break;

  case eST_DBG_ACVRZERO:    sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_V]  /10, sSet.wZeR[eADC_V]  %10 );    break;
  case eST_DBG_ACVRSPAN:    sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_V]  /10, sSet.wSpR[eADC_V]  %10 );    break;
  case eST_DBG_ACIRZERO:    sprintf( i_pbChr, "%u.%uA", sSet.wZeR[eADC_IA] /10, sSet.wZeR[eADC_IA] %10 );    break;
  case eST_DBG_ACIRSPAN:    sprintf( i_pbChr, "%u.%uA", sSet.wSpR[eADC_IA] /10, sSet.wSpR[eADC_IA] %10 );    break;
  case eST_DBG_AC1RZERO:    sprintf( i_pbChr, "%u.%uV", sSet.wZeR[eADC_V]  /10, sSet.wZeR[eADC_V]  %10 );    break;
  case eST_DBG_AC1RSPAN:    sprintf( i_pbChr, "%u.%uV", sSet.wSpR[eADC_V]  /10, sSet.wSpR[eADC_V]  %10 );    break;
  case eST_DBG_AC2RZERO:    sprintf( i_pbChr, "%u.%uA", sSet.wZeR[eADC_IA] /10, sSet.wZeR[eADC_IA] %10 );    break;
  case eST_DBG_AC2RSPAN:    sprintf( i_pbChr, "%u.%uA", sSet.wSpR[eADC_IA] /10, sSet.wSpR[eADC_IA] %10 );    break;
  case eST_DBG_AC3RZERO:    sprintf( i_pbChr, "%u.%uA", sSet.wZeR[eADC_IB] /10, sSet.wZeR[eADC_IB] %10 );    break;
  case eST_DBG_AC3RSPAN:    sprintf( i_pbChr, "%u.%uA", sSet.wSpR[eADC_IB] /10, sSet.wSpR[eADC_IB] %10 );    break;
  case eST_DBG_AC4RZERO:    sprintf( i_pbChr, "%u.%uA", sSet.wZeR[eADC_IC] /10, sSet.wZeR[eADC_IC] %10 );    break;
  case eST_DBG_AC4RSPAN:    sprintf( i_pbChr, "%u.%uA", sSet.wSpR[eADC_IC] /10, sSet.wSpR[eADC_IC] %10 );    break;

  case eST_DBG_RATIO1:      sprintf( i_pbChr, "%8.02fV", sSet.fRatio[eADC_V]   );  break;
  case eST_DBG_RATIO2:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IA]  );  break;
  case eST_DBG_RATIO3:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IB]  );  break;
  case eST_DBG_RATIO4:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IC]  );  break;
  case eST_DBG_RATIO5:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_TC1] );  break;
  case eST_DBG_RATIO6:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_TC2] );  break;
  case eST_DBG_RATIO7:      sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_CC ] );  break;
  case eST_DBG_ACVRATIO:    sprintf( i_pbChr, "%8.02fV", sSet.fRatio[eADC_V]   );  break;
  case eST_DBG_ACIRATIO:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IA]  );  break;
  case eST_DBG_ACRATIO1:    sprintf( i_pbChr, "%8.02fV", sSet.fRatio[eADC_V]   );  break;
  case eST_DBG_ACRATIO2:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IA]  );  break;
  case eST_DBG_ACRATIO3:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IB]  );  break;
  case eST_DBG_ACRATIO4:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_IC]  );  break;
  case eST_DBG_DCRATIO:     sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_TC1] );  break;
  case eST_DBG_DCRATIO1:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_TC1] );  break;
  case eST_DBG_DCRATIO2:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_TC2] );  break;
  case eST_DBG_DCRATIO3:    sprintf( i_pbChr, "%8.02fA", sSet.fRatio[eADC_CC ] );  break;
  default:
  break;
  }
  return i_pbChr;
}

void Debug_Normal( DEBUG_REG *pSci, UINT16 i_wType )
{
  *pbChr[0] = 0x00;
  if( ( sKey.bPageGo == eST_DBG_PASSWORD || sKey.bPageGo == eST_DBG_NEWPASS || sKey.bPageGo == eST_DBG_RE_ENTPASS ) && !( pSci->bCmdTp == eK_EXIT || pSci->bCmdTp == eK_BACK || pSci->bCmdTp == eK_EXIT ) && pSci->bCmdData[0] != 0 )
    sprintf( pSci->bTxData, "\n\r %s                         \n\r                                    \rTHOMAS%s %c%c%c%c", Debug_THelpList( sKey.bPageGo, (char *)pbChr ), Debug_TCursor( pSci, sKey.bPageGo ), pSci->bCmdCount == 1 ? pSci->bCmdData[0] : '*', pSci->bCmdCount == 2 ? pSci->bCmdData[1] : '*', pSci->bCmdCount == 3 ? pSci->bCmdData[2] : '*', pSci->bCmdCount == 4 ? pSci->bCmdData[3] : '*' );
  else if( i_wType == eST_DBG_NUMBER || i_wType == eST_DBG_CHAR )
  {
    if( pSci->bCmdTp == eK_EXIT || pSci->bCmdTp == eK_BACK || pSci->bCmdTp == eK_EXIT )
      sprintf( pSci->bTxData, "\n\r %s                         \n\r                                    \rTHOMAS%s %s", Debug_THelpList( sKey.bPageGo, (char *)pbChr ), Debug_TCursor( pSci, sKey.bPageGo ), Debug_TList( i_wType, pSci->bCmdTp ) );
    else
      sprintf( pSci->bTxData, "\n\r %s                         \n\r                                    \rTHOMAS%s %s", Debug_THelpList( sKey.bPageGo, (char *)pbChr ), Debug_TCursor( pSci, sKey.bPageGo ), pSci->bCmdData );
  }
  else
    sprintf( pSci->bTxData, "\n\r %s                         \n\r                                    \rTHOMAS%s %s", Debug_THelpList( i_wType, (char *)pbChr ), Debug_TCursor( pSci, i_wType ), Debug_TList( i_wType, pSci->bCmdTp ) );
}




void Char2WordChar( DEBUG_REG *pSci, float *i_pfValue )
{
  UINT16 i, j = 0;

  for( i=0; i<pSci->bCmdCount; i++ )
  {
    sKey.pwKey[j]  = (UINT16)( pSci->bCmdData[i] << 8 );
    i++;
    sKey.pwKey[j] += (UINT16)( pSci->bCmdData[i] );
    j++;
  }
  sKey.pwKey[j] = 0x00;
}

void Char2Float( DEBUG_REG *pDbg, float *i_pfValue )
{
  UINT16 i, j = 0, k = 0;

  i_pfValue[0] = 0;
  i_pfValue[1] = 0;
  i_pfValue[2] = 0;
  i_pfValue[3] = 0;
  i_pfValue[4] = 0;
  i_pfValue[5] = 0;

  if( sKey.bMode == eKEY_MD_TIME )
  {
    for( i=0; i<pDbg->bCmdCount; i++ )
    {
      if( pDbg->bCmdData[i] == '/' || pDbg->bCmdData[i] == ' ' || pDbg->bCmdData[i] == ':' )
      {
        j++;
        k = 0;
      }
      else
      {
        i_pfValue[j] *= 10;
        i_pfValue[j] += ( pDbg->bCmdData[i] -'0' );
        k++;
      }
    }
  }
  else
  {
    for( i=0; i<pDbg->bCmdCount; i++ )
    {
      if( pDbg->bCmdData[i] == '.' )
      {
        j++;
        k = 0;
      }
      else
      {
        i_pfValue[j] *= 10;
        i_pfValue[j] += ( pDbg->bCmdData[i] -'0' );
        k++;
      }
    }

    if( j == 1 )
    {
      if( i_pfValue[1] != 0 )
      {
             if( k >= 5 )   i_pfValue[0] += ( i_pfValue[1] / 100000 );
        else if( k >= 4 )   i_pfValue[0] += ( i_pfValue[1] / 10000 );
        else if( k >= 3 )   i_pfValue[0] += ( i_pfValue[1] / 1000 );
        else if( k >= 2 )   i_pfValue[0] += ( i_pfValue[1] / 100 );
        else if( k >= 1 )   i_pfValue[0] += ( i_pfValue[1] / 10 );
      }
    }

    sKey.fKey = i_pfValue[0];
  }

}

UINT8 Key_MinMax( KEY_REG *pKey )
{
  UINT16  i = 0;
  UINT8   i_bNo = 0;

#if(1)
  if( pKey->bMode != eKEY_MD_UINT16_B && pKey->bMode != eKEY_MD_TIME )
  {
    if( pKey->bMode == eKEY_MD_UINT16_IP || pKey->bMode == eKEY_MD_UINT16_MAC )
    {
      if( pKey->bMode == eKEY_MD_UINT16_IP )  i_bNo = 4;
      else                                    i_bNo = 6;
      for( i=0; i<i_bNo; i++ )
      {
        pKey->fValue[i] *= pKey->wMul;
        if( pKey->fMin > pKey->fValue[i] || pKey->fMax < pKey->fValue[i] )
          return 0;
      }
    }
    else
    {
      pKey->fKey *= pKey->wMul;
      if( pKey->fMin > pKey->fKey || pKey->fMax < pKey->fKey )
        return 0;
    }
  }

  switch( pKey->bMode )
  {
  case eKEY_MD_UINT8:     for( i=0; i<pKey->bNo; i++ ){ *pKey->pbKey  = (UINT8)pKey->fKey;    pKey->pbKey++;  }   break;
  case eKEY_MD_INT8:      for( i=0; i<pKey->bNo; i++ ){ *pKey->pibKey = (INT8)pKey->fKey;     pKey->pibKey++; }   break;
  case eKEY_MD_UINT16:    for( i=0; i<pKey->bNo; i++ ){ *pKey->pwKey  = (UINT16)pKey->fKey;   pKey->pwKey++;  }   break;
  case eKEY_MD_INT16:     for( i=0; i<pKey->bNo; i++ ){ *pKey->piwKey = (INT16)pKey->fKey;    pKey->piwKey++; }   break;
  case eKEY_MD_UINT32:    for( i=0; i<pKey->bNo; i++ ){ *pKey->plKey  = (UINT32)pKey->fKey;   pKey->plKey++;  }   break;
  case eKEY_MD_INT32:     for( i=0; i<pKey->bNo; i++ ){ *pKey->pilKey = (INT32)pKey->fKey;    pKey->pilKey++; }   break;
  case eKEY_MD_FLOAT:     for( i=0; i<pKey->bNo; i++ ){ *pKey->pfKey  = pKey->fKey;           pKey->pfKey++;  }   break;
  case eKEY_MD_UINT16_IP:
  case eKEY_MD_UINT16_MAC:
    if( pKey->bMode == eKEY_MD_UINT16_IP )  i_bNo = 4;
    else                                    i_bNo = 6;
    for( i=0; i<2; i++ )
    {
      *pKey->pwKey  = ( (UINT16)pKey->fValue[i*2] << 8 ) | (UINT16)pKey->fValue[(i*2)+1];
      pKey->pwKey++;
    }
  break;
  case eKEY_MD_UINT16_B:
    if( sKey.fKey )   *sKey.pwKey |=  ( BIT0 << sKey.bNo );
    else              *sKey.pwKey &= ~( BIT0 << sKey.bNo );
  break;
  case eKEY_MD_TIME:
// 여기에 시계 관련 설정 된 값을 검증하는 부분 추가해야 됨
// 시계 설정 규격 : 22.11.07 20:33:00    
         if( eSV_TIM_YY_MIN > sKey.fValue[0] || eSV_TIM_YY_MAX < sKey.fValue[0] ) return 0;   // YY
    else if( eSV_TIM_MM_MIN > sKey.fValue[1] || eSV_TIM_MM_MAX < sKey.fValue[1] ) return 0;   // MM
    else if( eSV_TIM_DD_MIN > sKey.fValue[2] || eSV_TIM_DD_MAX < sKey.fValue[2] ) return 0;   // DD
    else if( eSV_TIM_hh_MIN > sKey.fValue[3] || eSV_TIM_hh_MAX < sKey.fValue[3] ) return 0;   // hh
    else if( eSV_TIM_mm_MIN > sKey.fValue[4] || eSV_TIM_mm_MAX < sKey.fValue[4] ) return 0;   // mm
    else if( eSV_TIM_ss_MIN > sKey.fValue[5] || eSV_TIM_ss_MAX < sKey.fValue[5] ) return 0;   // ss

    sSet.Time.bYY = (UINT8)DEC2BCD( (UINT16)sKey.fValue[0] );
    sSet.Time.bMM = (UINT8)DEC2BCD( (UINT16)sKey.fValue[1] );
    sSet.Time.bDD = (UINT8)DEC2BCD( (UINT16)sKey.fValue[2] );
    sSet.Time.bhh = (UINT8)DEC2BCD( (UINT16)sKey.fValue[3] );
    sSet.Time.bmm = (UINT8)DEC2BCD( (UINT16)sKey.fValue[4] );
    sSet.Time.bss = (UINT8)DEC2BCD( (UINT16)sKey.fValue[5] );
  break;
  }
  return 1;

#else

  if( pKey->bNo == 4 || pKey->bNo == 6 )
  {
    for( i=0; i<pKey->bNo; i++ )
    {
      if( pKey->fMin > fValue[i] || pKey->fMax < fValue[i] )
        return 0;
    }
  }
  else
  {
    if( pKey->fMin > pKey->fKey || pKey->fMax < pKey->fKey )
      return 0;
  }

  pKey->fKey *= pKey->wMul;
  switch( pKey->bMode )
  {
  case eKEY_MD_UINT8:   *pKey->pbKey  = (UINT8)pKey->fKey;  break;
  case eKEY_MD_INT8:    *pKey->pibKey = (INT8)pKey->fKey;   break;
  case eKEY_MD_UINT16:  *pKey->pwKey  = (UINT16)pKey->fKey; break;
  case eKEY_MD_INT16:   *pKey->piwKey = (INT16)pKey->fKey;  break;
  case eKEY_MD_UINT32:  *pKey->plKey  = (UINT32)pKey->fKey; break;
  case eKEY_MD_INT32:   *pKey->pilKey = (INT32)pKey->fKey;  break;
  case eKEY_MD_FLOAT:   *pKey->pfKey  = pKey->fKey;         break;
  }
  return 1;
#endif
}



/******************************* TIGERWIN END OF FILE *******************************/
