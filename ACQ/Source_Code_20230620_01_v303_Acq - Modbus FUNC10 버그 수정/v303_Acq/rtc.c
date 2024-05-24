/* *************************************************************************
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : rtc.c
 *
 * *************************************************************************/ 



/* Includes ------------------------------------------------------------------*/
#include <F28x_Project.h>
#include <time.h>

#include "main.h"
#include "tigerwin.h"
#include "rtc.h"
#include "sci.h"
#include "emif.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

RTC_REG      sRtc;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Init_Rtc( void );

BOOL Time_ErrorCheck( TIME_REG *pTime );
void Init_Time( TIME_REG *pTime );

void Rtc_Make( void );
BOOL Rtc_TimeReadSec( void );
void Rtc_TimeRead( TIME_REG *pTime );
void Rtc_TempSave( void );
void Rtc_TempLoad( void );
void Rtc_TimeWrite( TIME_REG *pTime );
void Rtc_ChargeWrite( void );
void Rtc_TimeBackUp( TIME_REG *pTime );
void Rtc_TimeBackUpRead( TIME_REG *pTime );
UINT8 Rtc_Read( UINT8 i_bAddress );
UINT8 Rtc_Write( UINT8 i_bAddress, UINT8 i_bData );
void Rtc_DataWrite( UINT8 i_bTime );
UINT8 Rtc_DataRead( void );

void Rtc2Utc( UINT16 i_wUtc, INT32 *i_pilUtc, TIME_REG *pTime );
void Utc2Rtc( UINT16 i_wUtc, TIME_REG *i_pTime, INT32 *i_pilUtc );
UINT16 Time_MonthRead( UINT16 i, UINT8 i_bSum );


/* Private functions ---------------------------------------------------------*/


#define RTC_IO_OUT     GPIO_Setup( IO_RTC_IO   , GPIO_MUX_CPU1, 0, GPIO_OUTPUT, GPIO_PUSHPULL );	  // 64       io      0       // RTC IO
#define RTC_IO_IN      GPIO_Setup( IO_RTC_IO   , GPIO_MUX_CPU1, 0, GPIO_INPUT, GPIO_PUSHPULL );	  // 64       io      0       // RTC IO
  

void Init_Rtc( void )
{
  RTC_CE_LO;
  RTC_SCK_LO;
  RTC_IO_LO;
}

BOOL Time_ErrorCheck( TIME_REG *pTime )
{
  BOOL    i_bFault = 0;

  if( pTime->bYY >> 4 >= 10 )
    i_bFault = 1;
  else if( ( pTime->bYY & 0x0F ) >= 10 )
    i_bFault = 1;
  else if( pTime->bMM >> 4 >= 2 )
    i_bFault = 1;
  else if( ( pTime->bMM & 0x0F ) >= 10 )
    i_bFault = 1;
  else if( pTime->bDD >> 4 >= 4 )
    i_bFault = 1;
  else if( ( pTime->bDD & 0x0F ) >= 10 )
    i_bFault = 1;
  else if( pTime->bhh >> 4 >= 3 )
    i_bFault = 1;
  else if( ( pTime->bhh & 0x0F ) >= 10 )
    i_bFault = 1;
  else if( pTime->bmm >> 4 >= 6 )
    i_bFault = 1;
  else if( ( pTime->bmm & 0x0F ) >= 10 )
    i_bFault = 1;
  else if( pTime->bss >> 4 >= 6 )
    i_bFault = 1;
  else if( ( pTime->bss & 0x0F ) >= 10 )
    i_bFault = 1;

  if( i_bFault )
    Init_Time( &sDsp.Time );

  return i_bFault;
}
void Init_Time( TIME_REG *pTime )
{
  pTime->bYY = 0x22;
  pTime->bMM = 0x03;
  pTime->bDD = 0x22;
  pTime->bhh = 0x19;
  pTime->bmm = 0x20;
  pTime->bss = 0x00;
  pTime->bwe = 0x05;        // 화
  pTime->wms = 0;
}

#define eRTC_SYNC_ERROR     (1200 *4)       // 1.2sec
void Rtc_Make( void )
{
  UINT8   i_bChar;

  switch( sRtc.Stp.bRtc )
  {
  case eRTC_INIT:
    Rtc_TimeRead( &sDsp.Time );
    Rtc_TempSave( );
    i_bChar = Rtc_Read( eRTC_CHAR );
    sRtc.Stp.bRtc++;
    Rtc_TempSave( );
//    i_bData = eCHARGER_CHARGE;
//    if( sDsp.Time.bChar != eCHARGER_CHARGE || Time_ErrorCheck( &sReal ) )
    if( i_bChar != eCHARGER_CHARGE )
      sRtc.bTimeCharge = 1;
  break;
  case eRTC_SYNC:
    Rtc_TempSave( );
    Rtc_TimeRead( &sDsp.Time );
    Rtc2Utc( 9, &sDsp.ilUtc, &sDsp.Time );
    sRtc.bTimeRead = 0;
    if( ++sRtc.Cnt.wRtc <= eRTC_SYNC_ERROR )
    {
      if( sDspTemp.Time.bss != sDsp.Time.bss )
      {
        sDspTemp.Time.bss = sDsp.Time.bss;
        sRtc.Stp.bRtc++;

        memcpy( &sSetTemp.Time, &sDsp.Time, 6 );

// 20220527 백업을 받기는 하지만 msec 단위로 저장하는게 아니므로 의미가 없어 제거함
//        Rtc_TimeBackUpRead( &sDsp.Time );
        sDsp.lUtcMs = sDsp.Time.wms = 0;

        sDspTemp.ilUtc  = sDsp.ilUtc;
        sDspTemp.lUtcMs = sDsp.lUtcMs;

        Conv_MramRd( (UINT16 *)&pMram->ilUtc, 2, (UINT16 *)&sDsp.ilUtc );
        Conv_MramRd( (UINT16 *)&pMram->lUtcMs, 2, (UINT16 *)&sDsp.lUtcMs );
        EventWr( eEV_PWR_OFF );
        sDsp.ilUtc  = sDspTemp.ilUtc;
        sDsp.lUtcMs = sDspTemp.lUtcMs;
        EventWr( eEV_PWR_ON );

        sSta.bPowerStart = 1;
//        sDspTemp.Time.wms = 0;
//        Event_SaveTemp( eEVENT_MESS_POWER_OFF, 0 );

//        memcpy( &sDsp.Time, &sSetTemp.Time, 6 );

/*
        if( sSta.wReset == 0 )
          Event_SaveTemp( eEVENT_MESS_POWER_ON, 0 );
        else
          Event_SaveTemp( eEVENT_MESS_RESET, 0 );
*/
      }
    }
    else
    {
//      sRtc.bTimeWrite = 1;
      Init_Time( &sDsp.Time );
      Rtc2Utc( 9, &sDsp.ilUtc, &sDsp.Time );
      sRtc.Stp.bRtc++;
      Rtc_TimeWrite( &sDsp.Time );

      sSta.bPowerStart = 1;
    }
  break;
  case eRTC_NORMAL:
    if( sRtc.bTimeWriteDnp )
    {
      sRtc.bTimeWriteDnp = 0;
      Rtc_TimeWrite( &sDsp.Time );
    }
    else if( sRtc.bTimeRead )    // 143usec
    {
      if( Rtc_TimeReadSec( ) )
      {
        sRtc.bTimeRead = 0;
        Rtc_TimeRead( &sDsp.Time );
        sDsp.ilUtc++;
        if( sDspTemp.Time.bDD != sDsp.Time.bDD )
          Rtc2Utc( 9, &sDsp.ilUtc, &sDsp.Time );
        Rtc_TempSave( );
        if( Time_ErrorCheck( &sDsp.Time ) )
          sRtc.bTimeWrite = 1;
        sDsp.Time.wms = 0;
      }
      sRtc.bTimeBackUp = 1;
    }
    else if( sRtc.bTimeWrite )
    {
      sRtc.bTimeWrite = 0;
//      Utc2Rtc( 9, &sSet.Time, &sDsp.ilUtc );    // 통신에서 받아서 sSet.Time을 설정하고 sRtc.bTimeWrite 1로 바꿔 저장하게..
      Rtc_TimeWrite( &sSet.Time );
      sDsp.Time = sSet.Time;
      Rtc2Utc( 9, &sDsp.ilUtc, &sDsp.Time );
    }
    else if( sRtc.bTimeCharge )
    {
      sRtc.bTimeCharge = 0;
      Rtc_ChargeWrite( );
    }
    else if( sRtc.bTimeBackUp )
    {
      sRtc.bTimeBackUp = 0;
      Rtc_TimeBackUp( &sDsp.Time );
    }
    else if( sRtc.bTimeBackUpRead )
    {
      sRtc.bTimeBackUpRead = 0;
      Rtc_TimeBackUpRead( &sSetTemp.Time );
    }
  break;
  }
}

BOOL Rtc_TimeReadSec( void )
{
  RTC_IO_OUT;
  if( sDsp.Time.bss != Rtc_Read( eRTC_SEC ) )
    return 1;

  return 0;
}
void Rtc_TimeRead( TIME_REG *pTime )
{
  RTC_IO_OUT;
  pTime->bss = Rtc_Read( eRTC_SEC  );
  pTime->bmm = Rtc_Read( eRTC_MINU );
  pTime->bhh = Rtc_Read( eRTC_HOUR );
  pTime->bDD = Rtc_Read( eRTC_DATE );
  pTime->bMM = Rtc_Read( eRTC_MONT );
  pTime->bYY = Rtc_Read( eRTC_YEAR );
}
void Rtc_TempSave( void )
{
  sDspTemp.Time.bYY = sDsp.Time.bYY;
  sDspTemp.Time.bMM = sDsp.Time.bMM;
  sDspTemp.Time.bDD = sDsp.Time.bDD;
  sDspTemp.Time.bhh = sDsp.Time.bhh;
  sDspTemp.Time.bmm = sDsp.Time.bmm;
  sDspTemp.Time.bss = sDsp.Time.bss;
  sDspTemp.Time.bwe = sDsp.Time.bwe;
}
void Rtc_TempLoad( void )
{
  sDsp.Time.bYY = sDspTemp.Time.bYY;
  sDsp.Time.bMM = sDspTemp.Time.bMM;
  sDsp.Time.bDD = sDspTemp.Time.bDD;
  sDsp.Time.bhh = sDspTemp.Time.bhh;
  sDsp.Time.bmm = sDspTemp.Time.bmm;
  sDsp.Time.bss = sDspTemp.Time.bss;
  sDsp.Time.bwe = sDspTemp.Time.bwe;
}
void Rtc_TimeWrite( TIME_REG *pTime )
{
  RTC_IO_OUT;
  Rtc_Write( eRTC_WP,   0x00 );
  pTime->wms = 0;
  Rtc_Write( eRTC_SEC,  pTime->bss );
  Rtc_Write( eRTC_MINU, pTime->bmm );
  Rtc_Write( eRTC_HOUR, pTime->bhh );
  Rtc_Write( eRTC_DATE, pTime->bDD );
  Rtc_Write( eRTC_MONT, pTime->bMM );
  Rtc_Write( eRTC_YEAR, pTime->bYY );
  Rtc_Write( eRTC_WP,   0x80 );
}
void Rtc_ChargeWrite( void )
{
// 초기 0x5C로 설정 되어 있음
// b1010xxyy
// xx
  Rtc_Write( eRTC_WP,   0x00 );
  Rtc_Write( eRTC_CHAR,  eCHARGER_CHARGE );
  Rtc_Write( eRTC_WP,   0x80 );
}
void Rtc_TimeBackUp( TIME_REG *pTime )
{
  RTC_IO_OUT;
  Rtc_Write( eRTC_WP,   0x00 );
  pTime->wms = 0;
  Rtc_Write( eRTC_SEC|0x40,  pTime->bss );
  Rtc_Write( eRTC_MINU|0x40, pTime->bmm );
  Rtc_Write( eRTC_HOUR|0x40, pTime->bhh );
  Rtc_Write( eRTC_DATE|0x40, pTime->bDD );
  Rtc_Write( eRTC_MONT|0x40, pTime->bMM );
  Rtc_Write( eRTC_YEAR|0x40, pTime->bYY );
  Rtc_Write( eRTC_WP,   0x80 );
}
void Rtc_TimeBackUpRead( TIME_REG *pTime )
{
  RTC_IO_OUT;
  pTime->bss = Rtc_Read( eRTC_SEC|0x40  );
  pTime->bmm = Rtc_Read( eRTC_MINU|0x40 );
  pTime->bhh = Rtc_Read( eRTC_HOUR|0x40 );
  pTime->bDD = Rtc_Read( eRTC_DATE|0x40 );
  pTime->bMM = Rtc_Read( eRTC_MONT|0x40 );
  pTime->bYY = Rtc_Read( eRTC_YEAR|0x40 );
}

UINT8 Rtc_Read( UINT8 i_bAddress )
{
  UINT8   i_bData;

  RTC_CE_HI;
  Rtc_DataWrite( i_bAddress | eRTC_READ );
  i_bData = Rtc_DataRead( );
  RTC_CE_LO;

  return i_bData;
}

UINT8 Rtc_Write( UINT8 i_bAddress, UINT8 i_bData )
{
  RTC_CE_HI;
  Rtc_DataWrite( i_bAddress );
  Rtc_DataWrite( i_bData );
  RTC_CE_LO;

  return i_bData;
}

#define eRTC_DATA_WRITE     8
#define eRTC_DATA_READ      8
void Rtc_DataWrite( UINT8 i_bTime )
{
  UINT16  i;
  UINT8   i_bAddress;

  i_bAddress = BIT0;
  for( i=0; i<eRTC_DATA_WRITE; i++ )
  {
    RTC_SCK_LO;
    if( i_bTime & i_bAddress )
      RTC_IO_HI;
    else
      RTC_IO_LO;
//    NOP;  NOP;  NOP;  NOP;  NOP;
    RTC_SCK_HI;
    i_bAddress <<= 1;
//    NOP;  NOP;  NOP;  NOP;  NOP;
  }
  RTC_IO_LO;
  RTC_SCK_LO;
}

UINT8 Rtc_DataRead( void )
{
  UINT16  i;
  UINT8   i_bAddress;
  UINT8   i_bData = 0;

  i_bAddress = BIT0;
  RTC_SCK_LO;
//  NOP;  NOP;  NOP;  NOP;  NOP;
  RTC_IO_IN;
//  NOP;  NOP;  NOP;  NOP;  NOP;
  for( i=0; i<eRTC_DATA_READ; i++ )
  {
    RTC_SCK_HI;
//    NOP;  NOP;  NOP;  NOP;  NOP;
    if( RTC_IO )
      i_bData |= i_bAddress;
//    NOP;  NOP;  NOP;  NOP;  NOP;
    i_bAddress <<= 1;
    RTC_SCK_LO;
//    NOP;  NOP;  NOP;  NOP;  NOP;
  }
  RTC_IO_LO;
//  NOP;  NOP;  NOP;  NOP;  NOP;
  RTC_IO_OUT;
//  NOP;  NOP;  NOP;  NOP;  NOP;

  return i_bData;
}

void Init_Reg_Rtc( void )
{
  sRtc.bTimeRead = 0;
  sRtc.bTimeWrite = 0;
  sRtc.bTimeCharge = 0;

}



struct tm * timeinfo;
void Rtc2Utc( UINT16 i_wUtc, INT32 *i_pilUtc, TIME_REG *i_pTime )
{
  INT64   i_llTime;
//  INT32   i_ilUtc;
  TIME_REG  i_Time;

  i_Time.bss = ( ( i_pTime->bss >> 4 ) *10 ) + ( i_pTime->bss & 0x0F );
  i_Time.bmm = ( ( i_pTime->bmm >> 4 ) *10 ) + ( i_pTime->bmm & 0x0F );
  i_Time.bhh = ( ( i_pTime->bhh >> 4 ) *10 ) + ( i_pTime->bhh & 0x0F );
  i_Time.bDD = ( ( i_pTime->bDD >> 4 ) *10 ) + ( i_pTime->bDD & 0x0F );
  i_Time.bMM = ( ( i_pTime->bMM >> 4 ) *10 ) + ( i_pTime->bMM & 0x0F );
  i_Time.bYY = ( ( i_pTime->bYY >> 4 ) *10 ) + ( i_pTime->bYY & 0x0F );

  if( i_Time.bYY < 70 )
    timeinfo->tm_year = (int)i_Time.bYY +100;
  else
    timeinfo->tm_year = (int)i_Time.bYY;
  timeinfo->tm_mon  = (int)i_Time.bMM -1;
  timeinfo->tm_mday = (int)i_Time.bDD;
  timeinfo->tm_hour = (int)i_Time.bhh;
  timeinfo->tm_min  = (int)i_Time.bmm;
  timeinfo->tm_sec  = (int)i_Time.bss;

  _tz.timezone = 0;
  _tz.daylight = 0;
  i_llTime = __mktime64(timeinfo);
  i_llTime -= ( i_wUtc *60 *60 );
  *i_pilUtc = (INT32)( i_llTime );
}

void Utc2Rtc( UINT16 i_wUtc, TIME_REG *i_pTime, INT32 *i_pilUtc )
{
  INT64   i_llTime = (INT64)*i_pilUtc + ( i_wUtc *60 *60 );
  TIME_REG  i_Time;
//  struct tm * timeinfo;

  timeinfo = __gmtime64(&i_llTime);
  i_Time.bYY = (UINT8)timeinfo->tm_year %100;
  i_Time.bMM = (UINT8)timeinfo->tm_mon +1;
  i_Time.bDD = (UINT8)timeinfo->tm_mday;
  i_Time.bhh = (UINT8)timeinfo->tm_hour;
  i_Time.bmm = (UINT8)timeinfo->tm_min;
  i_Time.bss = (UINT8)timeinfo->tm_sec;
  i_Time.bwe = (UINT8)timeinfo->tm_wday;    // 0: 일

  i_pTime->wms  = 0;
  i_pTime->bwe  = i_Time.bwe;
#if(1)
  i_pTime->bss  = DEC2BCD( i_Time.bss );
  i_pTime->bmm  = DEC2BCD( i_Time.bmm );
  i_pTime->bhh  = DEC2BCD( i_Time.bhh );
  i_pTime->bDD  = DEC2BCD( i_Time.bDD );
  i_pTime->bMM  = DEC2BCD( i_Time.bMM );
  i_pTime->bYY  = DEC2BCD( i_Time.bYY );
#else
  i_pTime->bss  = ( ( i_Time.bss / 10 ) << 4 );
  i_pTime->bss |= ( i_Time.bss % 10 );
  i_pTime->bmm  = ( ( i_Time.bmm / 10 ) << 4 );
  i_pTime->bmm |= ( i_Time.bmm % 10 );
  i_pTime->bhh  = ( ( i_Time.bhh / 10 ) << 4 );
  i_pTime->bhh |= ( i_Time.bhh % 10 );
  i_pTime->bDD  = ( ( i_Time.bDD / 10 ) << 4 );
  i_pTime->bDD |= ( i_Time.bDD % 10 );
  i_pTime->bMM  = ( ( i_Time.bMM / 10 ) << 4 );
  i_pTime->bMM |= ( i_Time.bMM % 10 );
  i_pTime->bYY  = ( ( i_Time.bYY / 10 ) << 4 );
  i_pTime->bYY |= ( i_Time.bYY % 10 );
#endif
}


/******************************* TIGERWIN END OF FILE *******************************/
