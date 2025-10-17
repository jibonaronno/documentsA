#ifndef __FILTER_H__
#define __FILTER_H__

#include "trismed/drivers/ADS129x.h"

/* General type conversion for MATLAB generated C-code  */
#include <stdint.h>	

void HP1Hz_Filter(int32_t *_data);
void AC60_Filter(int32_t *_data);

void Filter005_Init(void);
void Filter005_Filter(ADS1298_Frame *sample, bool isCalibration);
void Filter005_SetLeadReset(int lead);
#endif      /*__FILTER_H__*/