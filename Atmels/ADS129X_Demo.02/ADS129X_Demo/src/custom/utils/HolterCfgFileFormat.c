/*
 * HolterCfgFileFormat.c
 *
 * Created: 2023-05-15 오후 2:27:02
 *  Author: Ronny
 */

#include "HolterCfgFileFormat.h"
#include <string.h>
#include "trismed/utils/HolterSettings.h"
#include "SdAccessHelper.h"

#define HT_CONFIGURATION_FILE_NAME  "TCCFG.hti"
#define HT_CFG_SIGNATURE            "HTI"

THT_ConfigFile_RAM HT_ConfigFile;

void ReadConfigFile(void) {
    HTfr = f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
    HTfr = f_open(&HTFileDesc, HT_CONFIGURATION_FILE_NAME, FA_READ);
    if(HTfr == FR_OK) {
        f_read(&HTFileDesc, &HT_ConfigFile.Data, sizeof(THTConfigFile), &writenBytes);

        if(strstr(HT_ConfigFile.Data.signatureArray, HT_CFG_SIGNATURE)) {
            HT_ConfigFile.isValid = true;
            //if(!HT_ConfigFile.Data.already_used) {
            HolterSettings_RAM_CPY->ChannelNumber = (EcgChannels_t) HT_ConfigFile.Data.channels;
            HolterSettings_RAM_CPY->Pacemaker = (TPcacemakerType) HT_ConfigFile.Data.pacemakerType;
            HolterSettings_RAM_CPY->SamplingFreq = ModeToSamplingFreq((THolterMode)HT_ConfigFile.Data.recordMode);
            HolterSettings_RAM_CPY->Mode = (THolterMode)HT_ConfigFile.Data.recordMode;
            HolterSettings_RAM_CPY->RecordTime = HT_ConfigFile.Data.specifiedDuration;
            HolterSettings_RAM_CPY->LeadPlacement = (TLeadPlacement) HT_ConfigFile.Data.leadPlacement;
            if(strlen(HT_ConfigFile.Data.patientId) == 0 || strlen(HT_ConfigFile.Data.patientId) > 11) {
                strcpy(HT_ConfigFile.Data.patientId, HolterSettings_RAM_CPY->PatientId);
            } else {
                strcpy(HolterSettings_RAM_CPY->PatientId, HT_ConfigFile.Data.patientId);
            }
            HolterSettingsSave();
            //}
        } else {
            HT_ConfigFile.isValid = false;
        }
    } else {
        HT_ConfigFile.isValid = false;
    }
    f_close(&HTFileDesc);
    if(!HT_ConfigFile.isValid || HT_ConfigFile.Data.already_used) {
        WriteConfigFile(true);    // create the file using the current values from "HolterSettings_RAM_CPY"
    }
    f_mount(NULL, LUN_ID_SD_MMC_0_MEM, 1);
}

void WriteConfigFile(bool _useCurrentValues) {
    if(_useCurrentValues) {
        strncpy(HT_ConfigFile.Data.signatureArray, HT_CFG_SIGNATURE, strlen(HT_CFG_SIGNATURE));
        HT_ConfigFile.Data.already_used = false;
        HT_ConfigFile.Data.channels = HolterSettings_RAM_CPY->ChannelNumber;
        HT_ConfigFile.Data.pacemakerType = HolterSettings_RAM_CPY->Pacemaker;
        HT_ConfigFile.Data.recordMode = SamplingFreqToMode(HolterSettings_RAM_CPY->SamplingFreq);
        HT_ConfigFile.Data.recordMode = HolterSettings_RAM_CPY->Mode;
        HT_ConfigFile.Data.specifiedDuration = HolterSettings_RAM_CPY->RecordTime;
        HT_ConfigFile.Data.leadPlacement = HolterSettings_RAM_CPY->LeadPlacement;
        HT_ConfigFile.isValid = true;
        strcpy(HT_ConfigFile.Data.patientId, HolterSettings_RAM_CPY->PatientId);
    }
    if(HT_ConfigFile.isValid) {
        f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
        HTfr = f_open(&HTFileDesc, HT_CONFIGURATION_FILE_NAME, FA_CREATE_ALWAYS + FA_WRITE);
        if(HTfr == FR_OK) {
            f_write(&HTFileDesc, &HT_ConfigFile.Data, sizeof(THTConfigFile), &writenBytes);
        }
        f_close(&HTFileDesc);
        f_mount(NULL, LUN_ID_SD_MMC_0_MEM, 1);
    }
}
