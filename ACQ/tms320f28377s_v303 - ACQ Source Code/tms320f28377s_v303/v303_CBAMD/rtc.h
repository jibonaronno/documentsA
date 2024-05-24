/* *************************************************************************
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : rtc.h
 *
 * *************************************************************************/ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H

/* Includes ------------------------------------------------------------------*/
#include "tigerwin.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define eRTC_READ       BIT0
#define eRTC_SEC        0x80
#define eRTC_MINU       0x82
#define eRTC_HOUR       0x84
#define eRTC_DATE       0x86
#define eRTC_MONT       0x88
#define eRTC_DAY        0x8A
#define eRTC_YEAR       0x8C
#define eRTC_WP         0x8E
#define eRTC_CHAR       0x90

#define eCHARGER_ON         0xA0
#define eCHARGER_OFF        0x50
#define eCHARGER_D1         0x04
#define eCHARGER_D2         0x08
#define eCHARGER_2K         0x01
#define eCHARGER_4K         0x02
#define eCHARGER_8K         0x03
#define eCHARGER_CHARGE     ( eCHARGER_ON | eCHARGER_D1 | eCHARGER_2K )


enum
{
    eRTC_INIT,
    eRTC_SYNC,
    eRTC_NORMAL,
};
typedef struct _RTC_STEP
{
    UINT8               bRtc;
} RTC_STEP;
typedef struct _RTC_COUNT
{
    UINT16              wRtc;
} RTC_COUNT;
typedef struct _RTC_REG
{
    RTC_STEP            Stp;
    RTC_COUNT           Cnt;
    BOOL                bTimeWriteDnp;
    BOOL                bTimeRead;
    BOOL                bTimeWrite;
    BOOL                bTimeCharge;
    BOOL                bTimeBackUp;
    BOOL                bTimeBackUpRead;
} RTC_REG;
extern RTC_REG      sRtc;


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void Init_Rtc( void );
extern void Init_Time( TIME_REG *pTime );
extern void Rtc_Make( void );

extern void Init_Reg_Rtc( void );

extern void Utc2Rtc( UINT16 i_wUtc, TIME_REG *i_pTime, INT32 *i_pilUtc );
extern void Rtc2Utc( UINT16 i_wUtc, INT32 *i_pilUtc, TIME_REG *pTime );

#endif /* __RTC_H */

