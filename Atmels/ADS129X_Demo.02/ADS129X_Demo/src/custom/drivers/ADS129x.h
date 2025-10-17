#ifndef ADS129X_H
#define ADS129X_H

#include <stdint.h>
#include <stdbool.h>

/* #define USE_VREF_4V */

#ifdef USE_VREF_4V
#define ADS_VREF        (4.0)
#else
#define ADS_VREF        (2.4)
#endif

#define MV_TO_ADC(mv) (int)((mv)/(1000.0f*ADS_VREF/8388607.0f))

#define AMP_IN_LEADS 8

/** ADS1298_Status (uint32_t only bits 0-23 are used)
*  1 => electrode is off, 0 => electrode connected
*  bits  23                                                            0
*       +---------------------------------------------------------------+
*       | 1 | 1 | 0 | 0 | LOFF_STATP[7:0] | LOFF_STATN[7:0] | GPIO[7:4] |
*       +---------------------------------------------------------------+
*/
#define ADS_V6  ((uint32_t)(0x080000u))
#define ADS_V5  ((uint32_t)(0x040000u))
#define ADS_V4  ((uint32_t)(0x020000u))
#define ADS_V3  ((uint32_t)(0x010000u))
#define ADS_V2  ((uint32_t)(0x008000u))
#define ADS_V1  ((uint32_t)(0x004000u))
#define ADS_LL  ((uint32_t)(0x002000u))
#define ADS_LA  ((uint32_t)(0x001000u))
#if 1
#define ADS_RA  ((uint32_t)(0x000010u))
#define RA_SENSN    (0x01)
#else
#define ADS_RA  ((uint32_t)(0x000020u))
#define RA_SENSN    (0x02)
#endif
#define ADS_GPIO1   ((uint32_t)(0x000001u))   /* Pacemaker spike */
#define ADS_GPIO2   ((uint32_t)(0x000002u))   /* Pacemaker polarity */
/* ADS1298's GPIOs declarations (not used) */
#define ADS_GPIO3   ((uint32_t)(0x000004u))
#define ADS_GPIO4   ((uint32_t)(0x000008u))

#define OFFSET_DETECTED (ADS_GPIO3)

#define     ELECTRODE_1MINUS    0x000020u   /*IN2N bit 1 from LOFF_STATN register*/
#define     ELECTRODE_1PLUS     0x002000u   /*IN2P bit 1 from LOFF_STATP register*/
#define     ELECTRODE_2MINUS    0x000040u   /*IN3N bit 2 from LOFF_STATN register*/
#define     ELECTRODE_2PLUS     0x004000u   /*IN3P bit 2 from LOFF_STATP register*/
#define     ELECTRODE_3MINUS    0x000010u   /*IN1N bit 0 from LOFF_STATN register*/
#define     ELECTRODE_3PLUS     0x001000u   /*IN1P bit 0 from LOFF_STATP register*/

/*
 This gain must be one of the following values: 1, 2, 3, 4, 6, 8 or 12
 Gains different from 1 will be adjusted to 1 before sending.
 This is required to make sure that 10mVp-p can fit in 16bits variables.
*/
#define ADS1298_GAIN    4   /* Using gain of 4 to increase CMRR */

/* To be called when a data block has been sent to ADS1298 */
void ADS1298_BlockSent(void);
/* To be called when the data block is received */
void ADS1298_BlockReceived(void);
/* To reconfigure RLD circuit based on the connected limbs electrodes */
void ADS1298_ConfigureRLD(uint16_t rld_sensp_sensn);

typedef struct {
    uint32_t Status;
    int32_t Leads[8];
} ADS1298_Frame;

void ADS1298_ModuleInit(void);
void ADS1298_Init(int _sampling_freq, int channelsCount, bool calibration);
void ADS1298_Start(void);
void ADS1298_Stop(void);
void ADS1298_SetPacemaker(bool enabled, unsigned int channel);

typedef enum {
    vRef2_4V,   /* using internal reference 2.4V */
    vRef4V      /* using internal reference 4V */
} t_vRef;

t_vRef GetBoardReference(void);

typedef void (*onNewDataHandler)(ADS1298_Frame *data);
void ADS1298_SetOnNewDataHandler(onNewDataHandler handler);

#endif /*ADS129X_H*/