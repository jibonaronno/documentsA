/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : emif.h
 *
 * *************************************************************************/ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EMIF_H
#define __EMIF_H

/* Includes ------------------------------------------------------------------*/
//#include "main.h"

/* Exported types ------------------------------------------------------------*/



/* Exported constants --------------------------------------------------------*/
enum
{
  eMR_NUM_SORT        = 4,        // UINT64
  eMR_NUM_MAGIC       = 1,        // UINT16
  eMR_NUM_CLEAR       = 1,        // UINT16
  eMR_NUM_VER         = 1,        // UINT16
  eMR_NUM_YYYYMMDD    = 2,        // UINT32
  eMR_NUM_MODEL       = 8,        // UINT8 *16 (UINT16 *8)
  eMR_NUM_SERIAL      = 16,       // UINT8 *32 (UINT16 *16)
  eMR_NUM_VERSION     = 1,        // UINT16
  eMR_NUM_TRIG        = 1,        // UINT16
  eMR_LEN_TRIG        = 1,        // 
  eMR_NUM_DEBO        = 1,        // UINT16
  eMR_LEN_DEBO        = 1,        // 
  eMR_NUM_NO100MS     = 1,        // UINT16
  eMR_NUM_NO500MS     = 1,        // UINT16
  eMR_LEN_NO          = 2,        // 
  eMR_NUM_ZER         = 8,        // UINT16 *8
  eMR_LEN_ZER         = 8,        // 
  eMR_NUM_SPR         = 8,        // UINT16 *8
  eMR_LEN_SPR         = 8,        // 
  eMR_NUM_ZE          = 16,       // float *8 (UINT16 *16) 
  eMR_LEN_ZE          = 16,       // 
  eMR_NUM_SP          = 16,       // float *8 (UINT16 *16)
  eMR_LEN_SP          = 16,       // 
  eMR_NUM_PH          = 16,       // float *8 (UINT16 *16)    // 4개만 필요하지만 다 만듬
  eMR_LEN_PH          = 16,       // 
  eMR_NUM_ETC_XCS     = 1,        // UINT16
  eMR_NUM_ZER_XCS     = 1,        // UINT16
  eMR_NUM_SPR_XCS     = 1,        // UINT16
  eMR_NUM_ZE_XCS      = 1,        // UINT16
  eMR_NUM_SP_XCS      = 1,        // UINT16
  eMR_NUM_PH_XCS      = 1,        // UINT16

  eMR_PIT_SORT        = 0,                                      // UINT64
  eMR_PIT_MAGIC       = eMR_PIT_SORT      + eMR_NUM_SORT,       // UINT16
  eMR_PIT_CLEAR       = eMR_PIT_MAGIC     + eMR_NUM_MAGIC,      // UINT16
  eMR_PIT_VER         = eMR_PIT_CLEAR     + eMR_NUM_CLEAR,      // UINT16
  eMR_PIT_YYYYMMDD    = eMR_PIT_VER       + eMR_NUM_VER,        // UINT32
  eMR_PIT_MODEL       = eMR_PIT_YYYYMMDD  + eMR_NUM_YYYYMMDD,   // UINT8 *16(UINT16 *8)
  eMR_PIT_SERIAL      = eMR_PIT_MODEL     + eMR_NUM_MODEL,      // UINT8 *32(UINT16 *16)
  eMR_PIT_VERSION     = eMR_PIT_SERIAL    + eMR_NUM_SERIAL,     // UINT16
  eMR_PIT_TRIGTIME    = eMR_PIT_VERSION   + eMR_NUM_VERSION,    // UINT16
  eMR_PIT_DEBOUNCE    = eMR_PIT_TRIGTIME  + eMR_NUM_TRIG,       // UINT16
  eMR_PIT_NO100MS     = eMR_PIT_DEBOUNCE  + eMR_NUM_DEBO,       // UINT16
  eMR_PIT_NO500MS     = eMR_PIT_NO100MS   + eMR_NUM_NO100MS,    // UINT16
  eMR_PIT_ZER         = eMR_PIT_NO500MS   + eMR_NUM_NO500MS,    // UINT16 *8
  eMR_PIT_SPR         = eMR_PIT_ZER       + eMR_NUM_ZER,        // UINT16 *8
  eMR_PIT_ZE          = eMR_PIT_SPR       + eMR_NUM_SPR,        // float *8 (UINT16 *16) 
  eMR_PIT_SP          = eMR_PIT_ZE        + eMR_NUM_ZE,         // float *8 (UINT16 *16)
  eMR_PIT_PH          = eMR_PIT_SP        + eMR_NUM_SP,         // float *8 (UINT16 *16)    // 4개만 필요하지만 다 만듬
  eMR_PIT_ETC_XCS     = 128,                                    // UINT16
  eMR_PIT_ZER_XCS     = eMR_PIT_ETC_XCS   + eMR_NUM_ETC_XCS,    // UINT16
  eMR_PIT_SPR_XCS     = eMR_PIT_ZER_XCS   + eMR_NUM_ZER_XCS,    // UINT16
  eMR_PIT_ZE_XCS      = eMR_PIT_SPR_XCS   + eMR_NUM_SPR_XCS,    // UINT16
  eMR_PIT_SP_XCS      = eMR_PIT_ZE_XCS    + eMR_NUM_ZE_XCS,     // UINT16
  eMR_PIT_PH_XCS      = eMR_PIT_SP_XCS    + eMR_NUM_SP_XCS,     // UINT16
//                      eMR_PIT_PH_XCS    + eMR_NUM_PH_XCS,                
};
#if(0)
#define eMR_ADD_MAGIC       = ( eMR_PIT_MAGIC      *2 )
#define eMR_ADD_CLEAR       = ( eMR_PIT_CLEAR      *2 )
#define eMR_ADD_VER         = ( eMR_PIT_VER        *2 )
#define eMR_ADD_YYYMMDD     = ( eMR_PIT_YYYYMMDD   *2 )
#define eMR_ADD_MODEL       = ( eMR_PIT_MODEL      *2 )
#define eMR_ADD_SERIAL      = ( eMR_PIT_SERIAL     *2 )
#define eMR_ADD_VERSION     = ( eMR_PIT_VERSION    *2 )
#define eMR_ADD_TRIGTIME    = ( eMR_PIT_TRIGTIME   *2 )
#define eMR_ADD_DEBOUNCE    = ( eMR_PIT_DEBOUNCE   *2 )
#define eMR_ADD_NO100MS     = ( eMR_PIT_NO100MS    *2 )
#define eMR_ADD_NO500MS     = ( eMR_PIT_NO500MS    *2 )
#define eMR_ADD_ZER         = ( eMR_PIT_ZER        *2 )
#define eMR_ADD_SPR         = ( eMR_PIT_SPR        *2 )
#define eMR_ADD_ZE          = ( eMR_PIT_ZE         *2 )
#define eMR_ADD_SP          = ( eMR_PIT_SP         *2 )
#define eMR_ADD_PH          = ( eMR_PIT_PH         *2 )
#define eMR_NUM_ETC_XCS     = ( eMR_NUM_ETC_XCS    *2 )
#define eMR_NUM_ZER_XCS     = ( eMR_NUM_ZER_XCS    *2 )
#define eMR_NUM_SPR_XCS     = ( eMR_NUM_SPR_XCS    *2 )
#define eMR_NUM_ZE_XCS      = ( eMR_NUM_ZE_XCS     *2 )
#define eMR_NUM_SP_XCS      = ( eMR_NUM_SP_XCS     *2 )
#define eMR_NUM_PH_XCS      = ( eMR_NUM_PH_XCS     *2 )
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern void Init_EM1( void );

extern void Emif_MagicCheck( void );

extern void Conv_MramRd( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam );
extern void Conv_MramWr( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam );
extern void Conv_MramRdXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs );
extern void Conv_MramWrXCs( UINT16 *i_pwMram, UINT16 i_wLen, UINT16 *i_pwRam, UINT16 *i_pwMramXCs, UINT16 *i_pwXCs );


#endif /* __EMIF_H */

