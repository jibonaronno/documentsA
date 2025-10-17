/*
 * SdAccessHelper.c
 *
 * Created: 2023-05-15 오후 3:13:26
 *  Author: Ronny
 */

#include "SdAccessHelper.h"
#include <string.h>
#include <asf.h>
#include "trismed/drivers/TMOUT.h"
#include "trismed/drivers/Display/DBuffer.h"

#ifdef LUN_ID_SD_MMC_0_MEM
#undef LUN_ID_SD_MMC_0_MEM
#define LUN_ID_SD_MMC_0_MEM ""
#endif

FRESULT HTfr;
FATFS fs;
FIL HTFileDesc;
UINT writenBytes;

#define HT_VOLUMEN_NAME             "TCHOLTER"

static TMOUT_CounterHandle sdTimeout;
#define SD_INIT_TIMEOUT_MS 3000

bool InitFilesystem(void) {
    Ctrl_status status;
    /* Initialize SD MMC stack */
    sd_mmc_init();
    /* Wait card present and ready */
    sdTimeout = TMOUT_GetCounter(MS_TO_TICKS(SD_INIT_TIMEOUT_MS));
    do {
        status = sd_mmc_test_unit_ready(0);
        if (CTRL_FAIL == status) {
            //printf("Card install FAIL\n\r");
            //printf("Please unplug and re-plug the card.\n\r");
            while ((CTRL_NO_PRESENT != sd_mmc_check(0)) && !TMOUT_CounterExpired(sdTimeout)) {
                nop();
            }
        }
    } while (CTRL_GOOD != status && !TMOUT_CounterExpired(sdTimeout));
    TMOUT_LeaveCounter(&sdTimeout);
    return CTRL_GOOD == status;
}

#ifdef FF_USE_LABEL
#define _USE_LABEL FF_USE_LABEL
#endif

void FormatSDCard(onProgressCallback_t progessCallback) {
    do {
        HTfr = f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);

#ifdef FF_USE_LABEL
        MKFS_PARM fmt_opt = {FM_SFD | FM_FAT32, 0, 64*1024, 0, 0};
        f_setProgressCallback(progessCallback);
        HTfr = f_mkfs("", &fmt_opt, diskbuffer.reserved, sizeof(diskbuffer.reserved));
        f_setProgressCallback(NULL);
#else
        HTfr = f_mkfs("", 0, 32*1024);
#endif
        HTfr = f_mount(NULL, LUN_ID_SD_MMC_0_MEM, 1);
        HTfr = f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
    } while(HTfr);
#if _USE_LABEL == 1
    char lstr[20];
    f_getlabel("", lstr, 0);
    if(strcmp(lstr, HT_VOLUMEN_NAME)) {
        f_setlabel(HT_VOLUMEN_NAME);
    }
#else
#warning _USE_LABEL is 0 or undefined, it may be and old version of FatFs.
#endif
}
