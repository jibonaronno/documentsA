/*
 * HolterSettings.h
 *
 * Created: 2023-05-11 오후 5:20:15
 *  Author: Ronny
 */


#ifndef HOLTERSETTINGS_H_
#define HOLTERSETTINGS_H_

#include <stdint.h>
#include <stdbool.h>

#define HOLTER_HW_VER_BIN   0x10    /*0x10 means v1.0, etc*/
#define DISABLE_1CH_RECORDS

//! [Types]
typedef enum {LEnglish, LSpanish, LFrench, LRussian, LTurkish, LKorean, LUzbek, LanguageCount} TLanguages;
typedef enum { ecgCh_1=1, ecgCh_3bip=3, ecgCh_std8=8 } EcgChannels_t;
typedef enum {HT_V0, HT_VInvalid} THolterSettingsVersion;
typedef enum {HT_250HZ=250, HT_500HZ=500, HT_1000HZ=1000} THolterSamplingFreq;
typedef enum {HTMODE_HIGHRES, HTMODE_STANDARD, HTMODE_LONGDURATION} THolterMode;
typedef enum {HT_STD, HT_FRANK} TLeadPlacement;
typedef enum {PCMK_NONE, PCMK_ATTRIAL, PCMK_VENTRICULAR, PCMK_DOUBLE} TPcacemakerType;
typedef enum {HT_BATTERY_ALKALINE, HT_BATTERY_NIMH} TBatteryType;

#define HT_CURRENT_SETTING_VERSION  HT_V0

#pragma pack(push, 1)

typedef enum {
    FW_OK               = 0,    // When the current firmware has been working for more than 1 power on cycle (more common state)
    FW_SCHEDULE_UPGRADE = 1,    // When a firmware upgrade process is about to begin
    FW_NEWFIRMWARE      = 2     // When a new firmware has been upgraded (probably some settings conversions are needed)
} FwStatus_t;

// Any change in this structure (TTSMDevData) must be reflected in the boot-loader's file "Devices.h"
typedef struct {
    unsigned short  version;        // 2 bytes  [settings version (format structure)]
    uint16_t    firmwareversion;    // 2 bytes
    uint16_t    Reserved;           // 2 bytes  [Reserved]
    uint16_t    BL_Version;         // 2 bytes
    FwStatus_t   Fw_Status;         // 1 byte   [Firmware status]
    uint8_t     HChksum;            // 1 byte   [HeaderChecksum]
} DeviceData_t;
// NEVER change "DeviceData_t" structure

typedef struct {
    uint32_t                SerialNumber;
    THolterSettingsVersion  SettingsVersion;
    TLanguages              Language;
    EcgChannels_t           ChannelNumber;
    THolterSamplingFreq     SamplingFreq;
    THolterMode             Mode;
    TPcacemakerType         Pacemaker;
    uint16_t                RecordID;
    uint8_t                 RecordTime;
    TLeadPlacement          LeadPlacement;
    TBatteryType            BatteryType;
    bool                    AccelerometerEnabled;
    char                    PatientId[14]; /* null terminated string 13 chars + '\0' */
} HolterSettings_t;

typedef struct {
    DeviceData_t    DevData;
    HolterSettings_t HolterSettings;
} THolterSettingsV1;

#pragma pack(pop)

extern HolterSettings_t *HolterSettings_RAM_CPY;
void HolterSettingsSave(void);
void HolterSettingsLoad(void);

THolterSamplingFreq ModeToSamplingFreq(THolterMode _mode);
THolterMode SamplingFreqToMode(THolterSamplingFreq _sampfreq);
EcgChannels_t IndexToChannels(uint32_t index);
int ChannelsToIndex(EcgChannels_t channels);

#endif /* HOLTERSETTINGS_H_ */