/*
 * HolterSettings.c
 *
 * Created: 2023-05-11 오후 5:20:06
 *  Author: Ronny
 */

#include "HolterSettings.h"
#include <string.h>
#include "trismed/drivers/DataPartition.h"
#include "trismed/utils/HolterCfgFileFormat.h"

HolterSettings_t *HolterSettings_RAM_CPY;
struct dataPartitionContent* pDataPartition;

void HolterSettingsSave(void) {
    dataPartition_Update(pDataPartition);
    WriteConfigFile(true);  // create the file using the current values from "HolterSettings_RAM_CPY"
}

static uint32_t UniqueId[4];
uint16_t ReadUniqueId(uint32_t *uniqueId);

__attribute__((section("data.ram"))) uint16_t ReadUniqueId(uint32_t *uniqueId) {
        cpu_irq_disable();
        const uint32_t rc = flash_read_unique_id(uniqueId, 4);
        cpu_irq_enable();
        return rc;
}

void HolterSettingsLoad(void) {
    pDataPartition = dataPartition_Read();
    HolterSettings_RAM_CPY = (HolterSettings_t*) pDataPartition->reserved;
    HolterSettings_RAM_CPY->SerialNumber = *((uint32_t*)(0x004FF004));
    if(HolterSettings_RAM_CPY->SettingsVersion >= HT_VInvalid ||
            strlen(HolterSettings_RAM_CPY->PatientId) > 13 ||
            HolterSettings_RAM_CPY->Language >= LanguageCount
      ) {
        HolterSettings_RAM_CPY->BatteryType = HT_BATTERY_ALKALINE;
        HolterSettings_RAM_CPY->SettingsVersion = HT_CURRENT_SETTING_VERSION;
        HolterSettings_RAM_CPY->Language = LEnglish;
        HolterSettings_RAM_CPY->ChannelNumber = ecgCh_std8;
        HolterSettings_RAM_CPY->Mode = HTMODE_STANDARD;
        HolterSettings_RAM_CPY->Pacemaker = PCMK_NONE;
        HolterSettings_RAM_CPY->SamplingFreq = HT_500HZ;
        HolterSettings_RAM_CPY->RecordID = 0;
        HolterSettings_RAM_CPY->LeadPlacement = HT_STD;
        HolterSettings_RAM_CPY->RecordTime = 24;
        HolterSettings_RAM_CPY->AccelerometerEnabled = false;
        ReadUniqueId(UniqueId);
        HolterSettings_RAM_CPY->SerialNumber = *((uint32_t*)(0x004FF004));
        memset(HolterSettings_RAM_CPY->PatientId, 0, sizeof(HolterSettings_RAM_CPY->PatientId));
        strcpy(HolterSettings_RAM_CPY->PatientId, "001");
        dataPartition_Update(pDataPartition);
    }
}

THolterSamplingFreq ModeToSamplingFreq(THolterMode _mode) {
    switch(_mode) {
    case HTMODE_HIGHRES:
        return HT_1000HZ;
    case HTMODE_STANDARD:
        return HT_500HZ;
    case HTMODE_LONGDURATION:
        return HT_250HZ;
    }
    return HT_500HZ;
}

THolterMode SamplingFreqToMode(THolterSamplingFreq _sampfreq) {
    switch(_sampfreq) {
    case HT_1000HZ:
        return HTMODE_HIGHRES;
    case HT_500HZ:
        return HTMODE_STANDARD;
    case HT_250HZ:
        return HTMODE_LONGDURATION;
    }
    return HTMODE_STANDARD;
}

EcgChannels_t IndexToChannels(uint32_t index) {
    switch(index) {
#ifdef DISABLE_1CH_RECORDS
    case 0:
        return ecgCh_3bip;
#else
    case 0:
        return ecgCh_1;
    case 1:
        return ecgCh_3bip;
#endif
    default:
        return ecgCh_std8;
    }
}

int ChannelsToIndex(EcgChannels_t channels) {
    switch(channels) {
#ifdef DISABLE_1CH_RECORDS
    case ecgCh_3bip:
        return 0;
    default:
        return 1;
#else
    case ecgCh_1:
        return 0;
    case ecgCh_3bip:
        return 1;
    default:
        return 2;
#endif
    }
}
