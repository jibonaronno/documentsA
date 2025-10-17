#include "License.h"
#include <stdio.h>      /* for sprintf */
#include <string.h>
#include "SdAccessHelper.h"
#include "trismed/drivers/DataPartition.h"
#include "Md5.h"        /* to hash the hardware id */
#include "e_dcrypt.h"   /* to decrypt the license */
#include "trismed/gui/GUI.h"

static uint8_t LicenseRamCopy[licFecturesCount] = {0};
static licFeaturesSet currentLicenseFeatures = licF_None;

#define FLASH_LIC_HEADER        "HLIC"

#pragma pack(push, 1)
typedef struct {
    char        head[4];        /* always HLIC */
    uint32_t    size_bytes;     /* bytes after size_bytes (not include) to checksum (not included) */
} flashLicenceHeader;

struct license_t {
    flashLicenceHeader licHead;
    uint8_t features[licFecturesCount];
    uint8_t checksum;
};

struct serialLicensePartitionContent {
    uint32_t other;
    uint32_t serialNo;
    struct license_t license;
};
#pragma pack(pop)

static void LicenseUpdateFeaturesSet(void) {
    bool hasRealTime = LicenseCheckOption(licRealtime);
    bool hasHolter = LicenseCheckOption(licHolter);
    if(hasHolter && hasRealTime) {
        currentLicenseFeatures = licF_Holter_Realtime;
        } else {
        if(hasHolter) {
            currentLicenseFeatures = licF_Holter;
            } else if(hasRealTime) {
            currentLicenseFeatures = licF_Realtime;
            } else {
            currentLicenseFeatures = licF_None;
        }
    }
}


#define LICENCE_FLASH_SIZE (sizeof(flashLicenceHeader) + 1 + licFecturesCount)

struct serialLicensePartitionContent *licFlashPartPtr;

static char CheckSumCalc(char* start, int32_t length) {
    char chksum = 0;
    for(int i=0; i<length; i++) {
        chksum += (*start) ^ i;
        start++;
    }
    return chksum;
}

static void SaveLicenseToFlash(void) {
    flashLicenceHeader *pHeader = (flashLicenceHeader*)&licFlashPartPtr->license.licHead;

    strncpy(pHeader->head, FLASH_LIC_HEADER, strlen(FLASH_LIC_HEADER));
    pHeader->size_bytes = licFecturesCount;

    for(int i=0; i<licFecturesCount; i++) {
        licFlashPartPtr->license.features[i] = LicenseRamCopy[i];
    }

    char chksum = CheckSumCalc((char*)pHeader, sizeof(flashLicenceHeader) + pHeader->size_bytes);
    licFlashPartPtr->license.checksum = chksum;
    
    partitionWritePage(serialLicensePartition, 0, licFlashPartPtr);
}

void LoadLicenseFromFlash(void) {
    flashLicenceHeader *pHeader;
    char* pchar;
    bool loaded = false;
    licFlashPartPtr = (struct serialLicensePartitionContent *) partitionReadPage(serialLicensePartition, 0);
    pchar = (char*)&licFlashPartPtr->license;
    pHeader = (flashLicenceHeader*)&licFlashPartPtr->license.licHead;
    memset(LicenseRamCopy, 0, sizeof(uint8_t)*licFecturesCount); /* all options disabled */
    if(strstr(pchar, FLASH_LIC_HEADER) == pchar) { /* starts with HLIC */
        if(CheckSumCalc(pchar, sizeof(flashLicenceHeader) + pHeader->size_bytes) ==  pchar[sizeof(flashLicenceHeader) + pHeader->size_bytes]) { /*checksum matches*/
            for(uint32_t i=0; i<licFecturesCount && i<pHeader->size_bytes; i++) {
                LicenseRamCopy[i] = pchar[sizeof(flashLicenceHeader)+i]; /* every option disabled */
            }
            loaded = true;
        }
    }
    LicenseUpdateFeaturesSet();
    if(!loaded) {
        /* create default license */
        SaveLicenseToFlash();
    }
}

/*
    License file after decoding: <Cardicode300H>1</Cardicode300H>
    At this point the only option is Accelerometer.
    Additional options can be added BEFORE cc300h_Option_Id_Counter
    The PC tool Cardicode300H License Generator.exe must be modified to add new options.
*/

#define LIC_START "<Cardicode300H_HT600>"
#define LIC_END "</Cardicode300H_HT600>"

static bool ImportLicense(char* filename) {
    FRESULT fr;     /* Return value */
#define LBUFSIZE 100
    char buff[LBUFSIZE];
    UINT bytesRead;
    fr = f_open(&HTFileDesc, filename, FA_READ);
    if(fr == FR_OK) {
        f_read(&HTFileDesc, buff, sizeof(buff), &bytesRead);
        f_close(&HTFileDesc);

        char key[33] = {0};   /* Md5 hash of the key will be stored here later, so we need 33 characters for this. */
        int32_t md5Bin[4];
        uint32_t serialNo = *(uint32_t*)(SERIAL_LIC_PARTITION_ADDRESS + 4);
        sprintf(key, "HT%09lu", serialNo);
        md5(key, strlen(key), md5Bin);
        char *pDigest = (char*)(md5Bin);
        for(int i = 0; i < 16; ++i) /* we have to do this one by one to get the right order */
            sprintf(&key[i*2], "%02x", (unsigned int)pDigest[i]);

        Crypt_Decode(key, buff);

        char* strPtr;
        strPtr = strstr(buff, LIC_START);
        if(strPtr == buff) {    /* license start found */
            strPtr = strstr(buff, LIC_END);
            if(strPtr != NULL) { /* found the end of the license */
                int offset = strlen(LIC_START);
                for(int i=0; i<licFecturesCount; i++) {
                    LicenseRamCopy[i] = buff[offset+i]-0x30;
                }
                return true;
            }
        }
    }
    return false;
}

enum licenseUpdateResult_t LicenseCheckForUpdate(void) {
    /* TODO:
    * - Check for license new licenses, decrypt it and update it on flash
    * - Load the licensed options from flash
    */
    FRESULT fr;     /* Return value */
    DIR dj;         /* Directory object */
    FILINFO fno;    /* File information */
    enum licenseUpdateResult_t result = licUpdateNotFound;
    
    LoadLicenseFromFlash();

    HTfr = f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
    fr = f_findfirst(&dj, &fno, "", "*.lic"); /* start searching for licenses */
    while(fr == FR_OK && fno.fname[0]) {         /* Repeat while an item is found */
        if(ImportLicense(fno.fname)) {
            LicenseUpdateFeaturesSet();
            ////f_unlink(fno.fname); /* remove the imported license */
            SaveLicenseToFlash();
            result = licImported;
            break;      /* license imported, we are done here */
        } else {
            fr = f_findnext(&dj, &fno);               /* Search for next item */
            result = licInvalid;
        }
    }
    f_closedir(&dj);
    return result;
}

bool LicenseCheckOption(t_Option_Id option) {
    return LicenseRamCopy[option] != 0u;
}

licFeaturesSet LicenseGetFeaturesSet(void) {
    return currentLicenseFeatures;
}

static licFeatureStatus_t licFeatureStatus[licFecturesCount+1];

licFeatureStatus_t* LicenseGetAllStatus(void) {
    licFeatureStatus[licFecturesCount].name = NULL;
    
    licFeatureStatus[licRealtime].name = &str_Stress;
    licFeatureStatus[licHolter].name = &str_Holter;
    licFeatureStatus[licRealtime].active = LicenseRamCopy[licRealtime];
    licFeatureStatus[licHolter].active = LicenseRamCopy[licHolter];
    return licFeatureStatus;
}
