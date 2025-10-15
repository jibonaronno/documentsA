/*
 * SdAccessHelper.h
 *
 * Created: 2023-05-15 오후 3:13:36
 *  Author: Ronny
 */


#ifndef SDACCESSHELPER_H_
#define SDACCESSHELPER_H_

#include <asf.h>
#include <stdbool.h>
#include "trismed/thirdparty/fatfs/fatfs/src/ff.h"

#ifdef LUN_ID_SD_MMC_0_MEM
#undef LUN_ID_SD_MMC_0_MEM
#define LUN_ID_SD_MMC_0_MEM ""
#endif

extern FRESULT HTfr;
extern FATFS fs;
extern FIL HTFileDesc;
extern UINT writenBytes;

bool InitFilesystem(void);
void FormatSDCard(onProgressCallback_t progessCallback);

#endif /* SDACCESSHELPER_H_ */