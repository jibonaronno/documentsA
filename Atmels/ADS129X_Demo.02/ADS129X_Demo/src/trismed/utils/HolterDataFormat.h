/*
 * HolterDataFormat.h
 *
 * Created: 2023-05-15 오전 10:46:56
 *  Author: Ronny
 */

#ifndef HOLTERDATAFORMAT_H_
#define HOLTERDATAFORMAT_H_

#include "trismed/drivers/ADS129x.h"
#include "trismed/utils/Task.h"
#include "trismed/thirdparty/fatfs/fatfs/src/ff.h"

#define PCM_DEBOUNDE_MS 120 /*Minimum pacemaker to pacemaker spikes in ms*/
#define SAVEWHEN_NBUFF_FULL 12

#pragma pack(push, 1)
typedef struct {
    uint8_t     filetypeID[3];      //3
    uint8_t     formatVersion;      //1
    uint32_t    u32_HeadID;         //4
    uint16_t    gain;               //2
    uint16_t    sampling_freq;      //2
    uint8_t     pacemaker_type;     //1
    uint8_t     No_of_Channels;     //1
    int32_t     AbsoluteSample[8];  //32
    /* IAR 9.x changed time_t to 64bits, breaking this header,
     time_t time has been changed to uint32_t here */
    uint32_t    StartingDateTime;   //4
    char        PatientID[13];      //13 [starts at 33h]
    uint8_t     HW_Ver;             //1
    uint8_t     FW_Ver;             //1
    uint8_t     StopCode;           //1
    uint8_t     BattaryWarning;     //1
    uint8_t     LeadPlacement;      //1
    uint8_t     SpecfiedDuration;   //1
    uint8_t     BattaryType;        //1
    uint8_t     Accelerometer;      //1
    uint8_t     ADC_Bits;           //1
    uint8_t     Imported;           //1
    uint8_t     RecordMode;         //1 [ends at 49h]
} ECGFileHeader;
#pragma pack(pop)

/* FrameHeader Bits Definition */
// 4byte ID
// 1byte cantsamples
// 1byte Channels Status

// 5bit sample size                     [MSB]
// 1bit event
// 1bit pause
// 1bit no used                         [LSB]

// 4 bits no used                       [MSB]
// 4bit Number of accelerometer samples in the frame [0 to 15]  [LSB]

#pragma pack(push, 1)
typedef union {
    unsigned char misc[2];
    struct {
        uint8_t PF : 1;
        uint8_t P : 1;
        uint8_t E : 1;
        uint8_t SampleWidth : 5;

        uint8_t AccSamples : 4;
        uint8_t T : 1;
        uint8_t Reserved : 3;
    } fields;
} TFrameMisc;

typedef struct {
    uint32_t u32_HeadID;
    uint8_t cantsamples;
    uint8_t channelsstatus;
    TFrameMisc  misc;
} TSignalFrame;

typedef struct  {
    uint16_t byteindex;
    uint8_t bufferindex;
} frameheaderstartposition;
#pragma pack(pop)

typedef enum {
    STOPC_NOSTOP=-1,
    STOPC_UNKNONW,
    STOPC_TIME,
    STOPC_USER,
    STOPC_ERROR,
    STOPC_BATTERY,
    STOPC_OVERRUN,
    STOPC_WRONGHANDLING
} TStopCode;

void Compress(ADS1298_Frame *datain);
void InitializeCompressor(uint32_t resumeLocation);
typedef enum {RECORD_NONE=0, RECORD_TRUNCATE, RECORD_RESUME} TRecordStatus;
TRecordStatus RecordResume(uint32_t resumeLocation, onProgressCallback_t truncateProgressCallback);

taksStatus_t RecordSaveTask(void);
void RecordStop(TStopCode reason);
void RecordSetPause(bool lPause);
bool RecordIsPaused(void);
TStopCode RecordGetStopReason(void);
taksStatus_t FinalizeRecord(onProgressCallback_t truncateProgressCallback);

uint32_t GetSavedSamples(void);
uint32_t GetElectrodesStatus(void);
void SetEvent(void);

#endif /* HOLTERDATAFORMAT_H_ */