/*
 * HolterDataFormat.c
 *
 * Created: 2023-05-15 오전 10:46:45
 *  Author: Ronny
 */
#include "HolterDataFormat.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <asf.h>
#include "trismed/drivers/ADS129x.h"
#include "trismed/drivers/Display/DBuffer.h" /* to use 'diskbuffer' array */
#include "trismed/drivers/SupplyController.h"
#include "trismed/utils/HolterSettings.h"
#include "trismed/utils/fastqueue.h"
#include "trismed/drivers/Accelerometer/Accelerometer.h"
#include "trismed/drivers/Trismed-Rtc.h"
#include "HolterCfgFileFormat.h"
#include "SdAccessHelper.h"
#include "trismed/applications/appLed.h"

#define MAX_SAMPLES_PER_FRAME   70          // up to MAX_SAMPLES_PER_FRAME * NUM_CHANNELS can go inside a frame

#define HTS_FORMAT_VERSON 0x01
#define DATA_FILETYPE_ID "HTS"
#define HOLTER_FILENAME "tcdata.hts"


volatile unsigned char WritingFile=0;   //this will lock modifying 'buffersReady' from ADS1298 interrupt

unsigned int buffReadyOut_IDX=0;
volatile unsigned int buffersReady=0;
volatile uint32_t samples_to_save = 0; /* maximum 4294967295 (UINT_MAX), which is
                               enough to record for 49.7103 days at 1kHz */

time_t    RecordEndingTime;
volatile int32_t prevsamples[2][8];
volatile unsigned char prevsamples_index_in=0;
volatile unsigned char prevsamples_index_out=0;

unsigned char current_FrameSamplesBits = 0; // current bits per output sample (will be updated)
int32_t maxdiff;    // maximum difference in the current sample among every channel

uint16_t sampleofcurrentframe = 0;  // current sample number inside the frame (0 to MAX_SAMPLES_PER_FRAME-1)

bool PutSamplesInFrame(ADS1298_Frame *datain);
void PutPacemakerInfo(unsigned char _spike);
void SaveByteAllignedData(uint32_t _value);
void SerializeSample(uint32_t _sample);
void UpdateCurrentFrameInfo(void);
void FilterLeadsStatus(uint32_t _status);
void FixSignalsOrder(ADS1298_Frame *datain);
void MakeNewFrame(ADS1298_Frame *datain, unsigned char _FrameSamplesBits);

static void TruncateRecordFile(void);

frameheaderstartposition current_frameheaderstartposition;

#define FRAMESTART_QUEUE_SIZE   800*sizeof(frameheaderstartposition)

static uint8_t _framestart_buffer[FRAMESTART_QUEUE_SIZE];
FastQueue framestart_queue;


extern inline void SET_HEAD0_HEAD_ID (TSignalFrame *_var);
inline void SET_HEAD0_HEAD_ID (TSignalFrame *_var) {
    _var->u32_HeadID =  (HolterSettings_RAM_CPY->RecordID<<16) + (HolterSettings_RAM_CPY->SerialNumber&0xffff);
    _var->misc.misc[0] = 0;
    _var->misc.misc[1] = 0;
}

bool Resuming = false;
uint8_t filling_buffer_index = 0u;

/** Bits packing engine --> */
unsigned char   used_bits;
unsigned char   BitsToRotate;
volatile uint32_t   filling_byte_index = 0;
#define GET_HIBYTE_UINT32(_val)     (0xFF &(_val>>24))
#define GET_HIBYTEM_UINT32(_val)    (0xFF &(_val>>16))
#define GET_HIBYTEL_UINT32(_val)    (0xFF &(_val>>8))
#define GET_LOBYTE_UINT32(_val)     (0xFF &(_val))

volatile unsigned int buffersFilledDuringWriting;

volatile uint8_t filledandpending;
bool NextFrameIsFirstIn2KBlock = true;
bool ThisFrameIsFirstIn2KBlock;

#define UPDATE_FILLING_BUFFERS_INDEXES()            \
if(++filling_byte_index >= ACCESS_BUFFER_SIZE) {    \
    filling_byte_index = 0;                         \
    filledandpending++;                             \
    NextFrameIsFirstIn2KBlock = true;               \
    if(++filling_buffer_index >= NUMBEROFDISKBUFFERS) \
    filling_buffer_index = 0;                       \
    if(filling_buffer_index == buffReadyOut_IDX) { \
        ResetCpu(); \
    } \
    WdtFeed(); \
}

#define UPDATE_BUFFERS_INDEXES_FRAME()              \
filling_byte_index += sizeof(TSignalFrame);         \
if(filling_byte_index >= ACCESS_BUFFER_SIZE) {      \
    filling_byte_index -= ACCESS_BUFFER_SIZE;       \
    filledandpending++;                             \
    if(++filling_buffer_index == NUMBEROFDISKBUFFERS) \
    filling_buffer_index = 0;                       \
}

void PutPacemakerInfo(unsigned char _spike) {
#ifdef NO_VARIABLE_SAMPLE_WIDTH
#warning Compression is Disabled, this is not a final release software
#else
    BitsToRotate = (8 - used_bits) - 1;
    _spike <<= BitsToRotate;
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] |= _spike;
    used_bits++;
    if(used_bits == 8) {
        UPDATE_FILLING_BUFFERS_INDEXES();
        diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index]=0;
        used_bits=0;
    }
#endif //NO_VARIABLE_SAMPLE_WIDTH
}

void SerializeSample(uint32_t _sample) {
#ifdef NO_VARIABLE_SAMPLE_WIDTH
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTE_UINT32(_sample));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTEM_UINT32(_sample));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTEL_UINT32(_sample));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_LOBYTE_UINT32(_sample));
    UPDATE_FILLING_BUFFERS_INDEXES();
#else
    char savedbits=0;
    char remainingbits=current_FrameSamplesBits;
    BitsToRotate = 32 - current_FrameSamplesBits;
    _sample <<= BitsToRotate;
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] |= (GET_HIBYTE_UINT32(_sample)>>used_bits);
    savedbits = 8-used_bits;
    used_bits+=savedbits;
    remainingbits = current_FrameSamplesBits-savedbits;
    if(used_bits==8) used_bits=0;
    while(remainingbits) {
        UPDATE_FILLING_BUFFERS_INDEXES();
        diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index]=0;
        diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] |= GET_HIBYTE_UINT32(_sample<<savedbits);
        savedbits += (current_FrameSamplesBits-savedbits)>=8?8:(current_FrameSamplesBits-savedbits);
        used_bits = remainingbits<8?remainingbits:0;
        remainingbits = current_FrameSamplesBits-savedbits;
    }
    if(used_bits == 0) {
        UPDATE_FILLING_BUFFERS_INDEXES();
        diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index]=0;
    }
#endif //NO_VARIABLE_SAMPLE_WIDTH
}

void SaveByteAllignedData(uint32_t _value) {
    if(used_bits) {
        UPDATE_FILLING_BUFFERS_INDEXES();
        used_bits = 0;
    }
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_LOBYTE_UINT32(_value));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTEL_UINT32(_value));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTEM_UINT32(_value));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index] = (GET_HIBYTE_UINT32(_value));
    UPDATE_FILLING_BUFFERS_INDEXES();
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index]=0;
}

/** Bits packing engine <-- */
#define ACC_BUFFER_SIZE 3*100
static uint8_t _Acc_buffer[ACC_BUFFER_SIZE];
static FastQueue fqAccQueue;

typedef enum {UPDATE_ABSOLUTEVALUES_IN_FILEHEADER, COMPRESSING} COMPRESSOR_STATE;
COMPRESSOR_STATE compressor_state = UPDATE_ABSOLUTEVALUES_IN_FILEHEADER;
extern bool exitAlwaysFromLPMAfterInterrupts;
volatile uint32_t saved_samples = 0;
static bool WithAccelerometer = false;
static uint16_t accBytesToSave;
static volatile uint16_t accSamplesToSave = 0;
static uint16_t lAccSamplesToSave;

volatile bool event = false;
volatile bool pause = false;
volatile bool eventScreenFeedback = false;

uint32_t GetSavedSamples(void) {
    return saved_samples;
}

void SetEvent(void) {
    event = true;
}

void UpdateCurrentFrameInfo(void) {
    uint8_t tmpbufferindex;
    unsigned int tmp1;
    if(current_frameheaderstartposition.bufferindex!=0xff) {
        if(WithAccelerometer) {
            accBytesToSave = fqAccQueue.count;
            lAccSamplesToSave = accSamplesToSave;
            if(lAccSamplesToSave>0) {
                if(accBytesToSave != lAccSamplesToSave*3) {
                    accBytesToSave = lAccSamplesToSave*3;
                }
                if(accBytesToSave > 3*15) {
                    accBytesToSave = lAccSamplesToSave*3;
                    assert("mangetta");
                }
                if(current_frameheaderstartposition.byteindex+7 >= ACCESS_BUFFER_SIZE) {
                    tmpbufferindex = current_frameheaderstartposition.bufferindex+1;
                    if(tmpbufferindex >= NUMBEROFDISKBUFFERS)
                        tmpbufferindex=0;
                    diskbuffer.diskbuffer[tmpbufferindex][7-(ACCESS_BUFFER_SIZE - current_frameheaderstartposition.byteindex)] |= lAccSamplesToSave;
                } else
                    diskbuffer.diskbuffer[current_frameheaderstartposition.bufferindex][current_frameheaderstartposition.byteindex + 7] |= lAccSamplesToSave;

                /* Save the acc data byte aligned after the last sample */
                if(used_bits) {
                    /* align to byte boundary */
                    used_bits = 0;
                    UPDATE_FILLING_BUFFERS_INDEXES();
                }
                if(filling_byte_index + accBytesToSave >= ACCESS_BUFFER_SIZE) {
                    /* split memmove into two steps */
                    int firsthalf = (ACCESS_BUFFER_SIZE-filling_byte_index);
                    FQgetdata(&fqAccQueue, 0, (char*)&diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index], firsthalf, true);
                    accBytesToSave -= firsthalf;
                    filling_byte_index = ACCESS_BUFFER_SIZE-1;
                    UPDATE_FILLING_BUFFERS_INDEXES();
                }
                if(accBytesToSave) {
                    /* last or only step of memmove */
                    FQgetdata(&fqAccQueue, 0, (char*)&diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index], accBytesToSave, true);
                    filling_byte_index+=accBytesToSave;
                }
                accSamplesToSave -= lAccSamplesToSave;
            }
        }
        if(ThisFrameIsFirstIn2KBlock || Resuming) {
            SaveByteAllignedData(saved_samples);
            SaveByteAllignedData(get_rtc_time());
            ThisFrameIsFirstIn2KBlock = false;
        }

        Resuming = false;
        if(current_frameheaderstartposition.byteindex+4 >= ACCESS_BUFFER_SIZE) {
            tmpbufferindex = current_frameheaderstartposition.bufferindex+1;
            if(tmpbufferindex >= NUMBEROFDISKBUFFERS)
                tmpbufferindex=0;
            diskbuffer.diskbuffer[tmpbufferindex][4-(ACCESS_BUFFER_SIZE - current_frameheaderstartposition.byteindex)] = sampleofcurrentframe;
        } else
            diskbuffer.diskbuffer[current_frameheaderstartposition.bufferindex][current_frameheaderstartposition.byteindex + 4] = sampleofcurrentframe;
        FQpush(&framestart_queue, (char*)&current_frameheaderstartposition, sizeof(frameheaderstartposition));

        if( current_frameheaderstartposition.bufferindex != filling_buffer_index ) {
            if( WritingFile ) {
                tmp1 = filledandpending;
                buffersFilledDuringWriting+=tmp1;
            } else {
                tmp1 = buffersFilledDuringWriting;
                tmp1 += filledandpending;
                buffersReady += tmp1;
                buffersFilledDuringWriting=0;
                if(buffersReady >= SAVEWHEN_NBUFF_FULL) {
                    ///////////////////exitAlwaysFromLPMAfterInterrupts=true;
                    //////////Cpu_SetOperationMode(DOM_RUN, NULL, NULL);  //~9mA
                }
            }
            filledandpending=0;
        }
    }
}

#define LEADS_ON_DELAY_MSEC     500
uint16_t leadson_delay_samples;   // to compare with it later (calculated according to the current sampling rate)
uint16_t leadson_delay[8];

#define ADQ_LEADOFF_SAFE_DELAY  1/*100*/
uint32_t adq_previous_status;
static uint32_t adq_leadoff_safe_delay = ADQ_LEADOFF_SAFE_DELAY;
uint8_t currentframe_loff_status=0xff;

uint32_t GetElectrodesStatus(void) {
    return adq_previous_status;
}

//_status has:  1100 + LOFF_STATP + LOFF_STATN + bits[4:7] of the GPIO register
void FilterLeadsStatus(uint32_t _status) {
    if(adq_previous_status != (_status)) {
        adq_leadoff_safe_delay--;
        if(adq_leadoff_safe_delay == 0) {
            adq_leadoff_safe_delay = ADQ_LEADOFF_SAFE_DELAY;

            if(HolterSettings_RAM_CPY->ChannelNumber == ecgCh_std8) {
                currentframe_loff_status = ((_status&(ADS_RA+ADS_LA))?0:0x1) +
                                           ((_status&(ADS_RA+ADS_LL))?0:0x2) +
                                           ((_status&(ADS_V1))?0:0x04) +
                                           ((_status&(ADS_V2))?0:0x08) +
                                           ((_status&(ADS_V3))?0:0x10) +
                                           ((_status&(ADS_V4))?0:0x20) +
                                           ((_status&(ADS_V5))?0:0x40) +
                                           ((_status&(ADS_V6))?0:0x80);
            } else {    //HT_CH3
                currentframe_loff_status = 0xf8 + ((_status&(ELECTRODE_1PLUS+ELECTRODE_1MINUS))?0:0x01) +
                                           ((_status&(ELECTRODE_2PLUS+ELECTRODE_2MINUS))?0:0x02) +
                                           ((_status&(ELECTRODE_3PLUS+ELECTRODE_3MINUS))?0:0x04);
            }
            adq_previous_status = _status;
        }
    }
}

void MakeNewFrame(ADS1298_Frame *datain, unsigned char _FrameSamplesBits) {
    sampleofcurrentframe=0;
    if(used_bits) {
        used_bits=0;    // the frame header starts byte aligned
        UPDATE_FILLING_BUFFERS_INDEXES();
    }
    current_frameheaderstartposition.bufferindex = filling_buffer_index;
    current_frameheaderstartposition.byteindex = filling_byte_index;

    TSignalFrame framehead;
    framehead.channelsstatus = currentframe_loff_status;                    //TODO: Use actual LEADS status (not electrodes status)
    framehead.cantsamples=0;
    SET_HEAD0_HEAD_ID(&framehead);
    framehead.misc.fields.SampleWidth = _FrameSamplesBits;

    if(Resuming)
        framehead.misc.fields.PF = 1;
    if(pause == true)
        framehead.misc.fields.P = 1;
    if(event) {
        framehead.misc.fields.E = 1;
        event = false;
        eventScreenFeedback = true;
    }
    if(NextFrameIsFirstIn2KBlock) {
        NextFrameIsFirstIn2KBlock = false;
        framehead.misc.fields.T = 1;
        ThisFrameIsFirstIn2KBlock = true;
    }

    if(filling_byte_index + sizeof(TSignalFrame) >= ACCESS_BUFFER_SIZE) {   // split memmove into two steps
        int firsthalf = (ACCESS_BUFFER_SIZE-filling_byte_index);
        memmove((void*)&diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index],
                (void*) &framehead, firsthalf);
        // updating buffers indexes ->
        filling_byte_index=0;
        filledandpending++;
        if( ++filling_buffer_index == NUMBEROFDISKBUFFERS )
            filling_buffer_index = 0;
        // updating buffers indexes <-
        unsigned char *lcharpointer = (unsigned char*)(&framehead);
        lcharpointer += firsthalf;
        memmove((void*)&diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index],
                (void*) (lcharpointer), sizeof(TSignalFrame)-firsthalf);
        filling_byte_index = sizeof(TSignalFrame)-firsthalf;
    } else {
        memmove((void*)&diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index],
                (void*) &framehead, sizeof(TSignalFrame));
        UPDATE_BUFFERS_INDEXES_FRAME();
    }
    used_bits=0;
    diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index]=0;
    current_FrameSamplesBits = _FrameSamplesBits;   // update the compressed samples width in bits
    PutSamplesInFrame(datain);
}

#define PACE_RESET_MIN_TIME
bool PutSamplesInFrame(ADS1298_Frame *datain) {
    if(sampleofcurrentframe < MAX_SAMPLES_PER_FRAME) {
#ifdef NO_VARIABLE_SAMPLE_WIDTH
#else
        if(HolterSettings_RAM_CPY->Pacemaker) {
            PutPacemakerInfo(datain->Status & 0x01);
        }
#endif
        for(int li=0; li<HolterSettings_RAM_CPY->ChannelNumber; li++) {
            SerializeSample(datain->Leads[li]);
        }
        sampleofcurrentframe++;
        return true;
    } else {
        UpdateCurrentFrameInfo();
        return false;
    }
}

const uint8_t leads_ok_8ch[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

#ifdef DELAY_COMPRESSION_TO_CLEAN_LEADOFF

#define DELAYED_MSECS   256 /* 200 msec at 1KHz = 200 samples */

#if DELAYED_MSECS % 2 || DELAYED_MSECS % 4
#pragma error "DELAYED_MSECS must be divisible by 2 and 4"
#endif

#define MAX_DELAYED_SIGNAL_SZ_BYTES  (sizeof(ADS1298_Frame)*DELAYED_MSECS)

#define CURRENT_DELAYED_SIGNAL_SZ_BYTES MAX_DELAYED_SIGNAL_SZ_BYTES * HolterSettings_RAM_CPY->SamplingFreq / HT_1000HZ

static uint8_t _SignalDelay_buffer[MAX_DELAYED_SIGNAL_SZ_BYTES];
static FastQueue fqSignalDelay;

uint32_t sample_when_lead_went_off[8];
uint8_t delay_prev_channels_status = 0xff;  // 0  per bit means off

#define DELAY_SAMPLE_READY FQisFull(fqSignalDelay)

void DELAY_SAMPLE_PUSH (ADS1298_Frame *sampleframe) {
    FQpush(fqSignalDelay, (char*)sampleframe, sizeof(ADS1298_Frame));
}


void DELAY_SAMPLE_POP (ADS1298_Frame *sampleframe, uint8_t _channels_status) {
    FQpop(fqSignalDelay, (char*)sampleframe, sizeof(ADS1298_Frame));
    int myinc=0;
    int li = 1;
    if(delay_prev_channels_status != _channels_status) {
        for(li=1; li<=0x80; li=li<<1) {
            if((((delay_prev_channels_status&li) != (_channels_status&li))) && !(li&_channels_status))
                sample_when_lead_went_off[myinc] = sampleframe->Leads[myinc];
            myinc++;
        }
        myinc=0;
        delay_prev_channels_status = _channels_status;
    }
#if 1
    for(li=1; li<0x100; li=li<<1) {
        if(!(_channels_status & li))
            leadson_delay[myinc] = leadson_delay_samples;
        else if(leadson_delay[myinc]>0) leadson_delay[myinc]--;
        if(leadson_delay[myinc]) {
            sampleframe->Leads[myinc] = sample_when_lead_went_off[myinc];
        }
        myinc++;
    }
#else
    for(li=1; li<0x100; li=li<<1) {
        if(!(_channels_status & li))
            sampleframe->Leads[myinc] = sample_when_lead_went_off[myinc];
        myinc++;
    }
#endif
}

#endif

static void AccDataReadyCallback(uint8_t *xyz) {
    FQpush(&fqAccQueue, (char *)xyz, 3);
    accSamplesToSave++;
}

TStopCode stopreasson = STOPC_NOSTOP;
taksStatus_t recordSaveTaskStatus = taskWorking;

volatile uint16_t PCM_DEBOUNCE_SAMPLES;
void InitializeCompressor(uint32_t resumeLocation) {
    WithAccelerometer = HolterSettings_RAM_CPY->AccelerometerEnabled;
#ifdef DELAY_COMPRESSION_TO_CLEAN_LEADOFF
    BUILD_BUG_ON((MAX_DELAYED_SIGNAL_SZ_BYTES % sizeof(ADS1298_Frame)));
#endif
    filling_buffer_index = 0;
    buffReadyOut_IDX = 0;
    filling_byte_index=0;
    uint32_t fbufstart;
    uint32_t fpostowritenextframe;
    current_frameheaderstartposition.bufferindex=0xff;
    NextFrameIsFirstIn2KBlock = true;
    stopreasson = STOPC_NOSTOP;
    recordSaveTaskStatus = taskWorking;
    if(resumeLocation != 0u) {
        compressor_state = COMPRESSING;
        fpostowritenextframe = HTFileDesc.fptr;
        fbufstart = resumeLocation;
        fbufstart = ((uint32_t)(fbufstart/ACCESS_BUFFER_SIZE))*ACCESS_BUFFER_SIZE;

        f_lseek(&HTFileDesc, fbufstart);
        f_read(&HTFileDesc, &diskbuffer.diskbuffer[filling_buffer_index][filling_byte_index], ACCESS_BUFFER_SIZE, &writenBytes);
        f_lseek(&HTFileDesc, fbufstart);
        filling_byte_index = fpostowritenextframe - fbufstart;  // current index in the local buffer
    } else {
        if(HolterSettings_RAM_CPY->RecordTime == 0)
            samples_to_save = UINT_MAX;
        else
            samples_to_save = (HolterSettings_RAM_CPY->RecordTime * 60 * 60 * HolterSettings_RAM_CPY->SamplingFreq);
        f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
        HTfr = f_open(&HTFileDesc, HOLTER_FILENAME, FA_CREATE_ALWAYS + FA_WRITE);
        // 'f_expand' to pre-allocate a continuous 4GB file size (faster than 'f_lseek')
        HTfr = f_expand(&HTFileDesc, (uint32_t)((4u*1024u*1024u*1024u)-1u), 1);
        HTfr = f_close(&HTFileDesc);
        f_mount(NULL, LUN_ID_SD_MMC_0_MEM, 1);
        f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
        HTfr = f_open(&HTFileDesc, HOLTER_FILENAME, FA_WRITE+FA_READ);
        HTfr = f_lseek(&HTFileDesc, 0);
        saved_samples = 0;
        compressor_state = UPDATE_ABSOLUTEVALUES_IN_FILEHEADER;
    }
    prevsamples_index_in = 0;
    prevsamples_index_out = 0;
    sampleofcurrentframe = 0;
    used_bits = 0;
    buffersFilledDuringWriting=0;
    buffersReady=0;
    current_FrameSamplesBits=0;
    filledandpending=0;
    pause = false;
    FQInit(&framestart_queue,  _framestart_buffer, FRAMESTART_QUEUE_SIZE);
    FQInit(&fqAccQueue, _Acc_buffer, ACC_BUFFER_SIZE);
    accSamplesToSave = 0;

#ifdef DELAY_COMPRESSION_TO_CLEAN_LEADOFF
    FQInit(&fqSignalDelay, _SignalDelay_buffer, CURRENT_DELAYED_SIGNAL_SZ_BYTES);
    delay_prev_channels_status = 0xff;  // 0  per bit means off
#endif
    adq_previous_status = 0;
    currentframe_loff_status=0xff;
    for(int li=0; li<8; li++)
        leadson_delay[li]=0;
    leadson_delay_samples = LEADS_ON_DELAY_MSEC * HolterSettings_RAM_CPY->SamplingFreq / HT_1000HZ;
    PCM_DEBOUNCE_SAMPLES = PCM_DEBOUNDE_MS  * HolterSettings_RAM_CPY->SamplingFreq / HT_1000HZ;
    if(WithAccelerometer) {
        Accelerometer()->SetCallaback(AccDataReadyCallback);
    }
    Accelerometer()->SetEnable(WithAccelerometer);
}

static ECGFileHeader *fileheader;
static unsigned char samplemaxbits=0;

extern int GetBatteryPercent(void);

void RecordSetPause(bool lPause) {
    pause = lPause;
}

bool RecordIsPaused(void) {
    return pause;
}

void FixSignalsOrder(ADS1298_Frame *datain) {
    if(HolterSettings_RAM_CPY->ChannelNumber == ecgCh_3bip) {
        datain->Leads[3] = datain->Leads[0];
        datain->Leads[0] = datain->Leads[1];
        datain->Leads[1] = datain->Leads[2];
        datain->Leads[2] = datain->Leads[3];
    }
}

time_t recoding_current_starttime;
#define FIX_RTC_EVERY       60  /* seconds */
uint32_t fix_rtc_counter = 0;
time_t RecoveryRecordStartTime;

void Compress(ADS1298_Frame *datain) {
    maxdiff=0;                      // initialize the maximum difference holder variable
    samplemaxbits=0;
    switch(compressor_state) {
    case UPDATE_ABSOLUTEVALUES_IN_FILEHEADER:
        buffersFilledDuringWriting=0;
        current_frameheaderstartposition.bufferindex=0xff;  //set invalid buffer index (no frame yet in the file)
        prevsamples_index_out = 0;
        prevsamples_index_in = 0;
        fileheader = (ECGFileHeader*) (&diskbuffer.diskbuffer[0][0]);
        for(uint8_t li=0u; li<HolterSettings_RAM_CPY->ChannelNumber; li++) {
            fileheader->AbsoluteSample[li] = datain->Leads[li];
            prevsamples[prevsamples_index_in][li] = datain->Leads[li];
        }
        fileheader->No_of_Channels = HolterSettings_RAM_CPY->ChannelNumber;
        double gain = round((2.4/(8388608/*2^23*/-1)) * 1000000.0 * 100000.0);
        fileheader->gain = (uint16_t)(gain);
        fileheader->sampling_freq = HolterSettings_RAM_CPY->SamplingFreq;
#ifdef NO_VARIABLE_SAMPLE_WIDTH
        fileheader->pacemaker_type = 0;
#else
        fileheader->pacemaker_type = HolterSettings_RAM_CPY->Pacemaker;
#endif      //NO_VARIABLE_SAMPLE_WIDTH
        fileheader->BattaryType = HolterSettings_RAM_CPY->BatteryType;
        fileheader->Accelerometer = WithAccelerometer ? Accelerometer()->GetType() : 0; /* 0: no accelerometer */;

        if(GetBatteryPercent() <= 85) {
            fileheader->BattaryWarning = 1;
        } else {
            fileheader->BattaryWarning = 0;
        }

        fileheader->FW_Ver = ENCODED_FW_VERSION;
        fileheader->HW_Ver = HOLTER_HW_VER_BIN;
        fileheader->LeadPlacement = HolterSettings_RAM_CPY->LeadPlacement;
        fileheader->StopCode = STOPC_BATTERY;                   //Always initialize with Stop Code Battery!!
        fileheader->SpecfiedDuration = HolterSettings_RAM_CPY->RecordTime;
        memcpy(fileheader->PatientID, HolterSettings_RAM_CPY->PatientId, 13);
        fileheader->ADC_Bits = 24;                  // ADS1298 has 24 bits ADC
        fileheader->Imported = 0;                   // New record has never been imported;
        fileheader->RecordMode = HolterSettings_RAM_CPY->Mode;

        fileheader->StartingDateTime =  get_rtc_time();
        RecoveryRecordStartTime = fileheader->StartingDateTime;
        if(HolterSettings_RAM_CPY->RecordTime == 0)
            RecordEndingTime = UINT_MAX;
        else
            RecordEndingTime = RecoveryRecordStartTime + (HolterSettings_RAM_CPY->RecordTime * 60 * 60);

        memcpy(fileheader->filetypeID, DATA_FILETYPE_ID, 3);
        fileheader->formatVersion = HTS_FORMAT_VERSON;
        fileheader->u32_HeadID =  (HolterSettings_RAM_CPY->RecordID<<16) + (HolterSettings_RAM_CPY->SerialNumber&0xffff);
        prevsamples_index_in=1;
        compressor_state = COMPRESSING;
        filling_byte_index += sizeof(ECGFileHeader);
        used_bits = 0;
        break;
    case COMPRESSING:
        FilterLeadsStatus(datain->Status);
#ifdef DELAY_COMPRESSION_TO_CLEAN_LEADOFF

        DELAY_SAMPLE_PUSH(datain);
        if(!(DELAY_SAMPLE_READY)) break;
        DELAY_SAMPLE_POP(datain, currentframe_loff_status);

#endif  //DELAY_COMPRESSION_TO_CLEAN_LEADOFF
        for(uint8_t li=0; li<HolterSettings_RAM_CPY->ChannelNumber; li++) {
            if(Resuming) {
                prevsamples[prevsamples_index_out][li] = datain->Leads[li]; // make a soft transition during after resuming test
            }
            prevsamples[prevsamples_index_in][li] = datain->Leads[li];
            datain->Leads[li]-= prevsamples[prevsamples_index_out][li];
            maxdiff |= abs(datain->Leads[li]);
        }
        if(prevsamples_index_in==0) {
            prevsamples_index_in = 1;
            prevsamples_index_out = 0;
        } else {
            prevsamples_index_in = 0;
            prevsamples_index_out = 1;
        }
#ifdef NO_VARIABLE_SAMPLE_WIDTH
        samplemaxbits=32;
#else
        while(maxdiff!=0) {
            maxdiff >>= 1;
            samplemaxbits++;
        }
        if(samplemaxbits < 9)
            samplemaxbits = 9;
        samplemaxbits++;

#endif  //NO_VARIABLE_SAMPLE_WIDTH
        if(samplemaxbits > current_FrameSamplesBits) {
            UpdateCurrentFrameInfo();
            MakeNewFrame(datain, samplemaxbits);            //create a new frame with the 'samplemaxbits'
        } else {
            if(!PutSamplesInFrame(datain))
                MakeNewFrame(datain, samplemaxbits);    // Make a new frame with the same
        }
        saved_samples++;
        if(samples_to_save) samples_to_save--;
        break;
    }
}

#define MAX_TO_RESUME_RECORD    3   /* in minutes */

TRecordStatus RecordResume(uint32_t resumeLocation, onProgressCallback_t truncateProgressCallback) {
    TRecordStatus result = RECORD_NONE; /* No record to resume or truncate */
    bool resuming = resumeLocation != 0;
    if(resuming) {
        time_t mycurrenttime;
        time_t shutdown_time;
        uint32_t offtime;
        uint32_t expected_samples;
        TSignalFrame lastframeheader;
        InitFilesystem();
        ECGFileHeader fileheadertoupdate;
        HTfr = f_mount(&fs, LUN_ID_SD_MMC_0_MEM, 1);
        HTfr = f_open(&HTFileDesc, HOLTER_FILENAME, FA_READ + FA_WRITE);
        if(HTfr == FR_OK) {
            f_read(&HTFileDesc, &fileheadertoupdate, sizeof(ECGFileHeader), &writenBytes);
            RecoveryRecordStartTime = fileheadertoupdate.StartingDateTime;
            f_lseek(&HTFileDesc, 0);
            f_lseek(&HTFileDesc, resumeLocation);
            f_read(&HTFileDesc, &lastframeheader, sizeof(TSignalFrame), &writenBytes);
            double dSamplesStartd = ceil((double)(lastframeheader.cantsamples * ((lastframeheader.misc.fields.SampleWidth * fileheadertoupdate.No_of_Channels) + (fileheadertoupdate.pacemaker_type?1:0))) / 8);
            uint32_t samplesstart = (uint32_t) (dSamplesStartd);
            if(lastframeheader.misc.fields.AccSamples != 0) {
                samplesstart += lastframeheader.misc.fields.AccSamples *3;
            }

            f_lseek(&HTFileDesc, HTFileDesc.fptr + samplesstart);
            f_read(&HTFileDesc, (void*)&saved_samples, sizeof(uint32_t), &writenBytes);
            f_read(&HTFileDesc, &shutdown_time, sizeof(uint32_t), &writenBytes);

            mycurrenttime = get_rtc_time();
            offtime = mycurrenttime - shutdown_time;
            expected_samples = offtime*HolterSettings_RAM_CPY->SamplingFreq + saved_samples;
            if(HolterSettings_RAM_CPY->RecordTime == 0)
                samples_to_save = UINT_MAX-expected_samples;
            else
                samples_to_save = (HolterSettings_RAM_CPY->RecordTime * 60 * 60 * HolterSettings_RAM_CPY->SamplingFreq)-expected_samples;

            offtime /= 60;  // offtime in minutes
            if(offtime < MAX_TO_RESUME_RECORD) {
                if(HolterSettings_RAM_CPY->RecordTime == 0)
                    RecordEndingTime = UINT_MAX;
                else
                    RecordEndingTime = RecoveryRecordStartTime + (HolterSettings_RAM_CPY->RecordTime * 60 * 60);
                saved_samples = expected_samples;
                Resuming = true;
                result = RECORD_RESUME;
            } else {
                expected_samples = HTFileDesc.fptr;
                fileheadertoupdate.StopCode = STOPC_WRONGHANDLING;
                f_lseek(&HTFileDesc, 0);
                f_write(&HTFileDesc, &fileheadertoupdate, sizeof(ECGFileHeader), &writenBytes);
                f_lseek(&HTFileDesc, expected_samples);
                f_setProgressCallback(truncateProgressCallback);
                TruncateRecordFile();
                f_setProgressCallback(NULL);
                Resuming = false;
                result = RECORD_TRUNCATE;
            }
        }
    }
    return result;
}

taksStatus_t FinalizeRecord(onProgressCallback_t truncateProgressCallback) {
    f_setProgressCallback(truncateProgressCallback);
    TruncateRecordFile();
    f_setProgressCallback(NULL);
    return taskDone;
}

static void TruncateRecordFile(void) {
    f_truncate(&HTFileDesc);
    f_close(&HTFileDesc);
}

typedef enum {rstWaitingData, rstSaveDataBuffers, rstEndRecord} rstState;

rstState recordSaveTaskState = rstWaitingData;
bool FileGotTooBig = false;
uint32_t lastframeat;
static FRESULT savetashresult;
frameheaderstartposition writenheaderposs, tmpwritenheaderpos;
bool event_flashing = false;

void RecordStop(TStopCode reason) {
    stopreasson = STOPC_USER;
}

TStopCode RecordGetStopReason(void) {
    return stopreasson;
}

taksStatus_t RecordSaveTask(void) {
    switch(recordSaveTaskState) {
    case rstWaitingData:
        if(buffersReady >= SAVEWHEN_NBUFF_FULL) {
            recordSaveTaskStatus = taskWorking;
            recordSaveTaskState = rstSaveDataBuffers;
        } else if(((samples_to_save == 0) && (RecordEndingTime < get_rtc_time())) || stopreasson != STOPC_NOSTOP || FileGotTooBig) {
            recordSaveTaskState = rstEndRecord;
        }
        break;
    case rstSaveDataBuffers:
        cpu_irq_enter_critical();
        WritingFile=1;
        cpu_irq_leave_critical();
        LedSetAction(laOn);
        while(buffersReady) {
            if(HTFileDesc.fptr > (UINT_MAX - (2u*1024u+10u))) {
                FileGotTooBig = true;
                break;
            }
            savetashresult = f_write(&HTFileDesc,diskbuffer.diskbuffer[buffReadyOut_IDX], ACCESS_BUFFER_SIZE, &writenBytes);
            if(savetashresult != FR_OK) {
                // something went wrong with the SD card
                LED_ON();
                ResetCpu(); // Reset the CPU and resume recording asap
            } else {
                WdtFeed();    // Reset watchdog timer (everything OK)
            }
            Accelerometer()->MainTask();

            FQgetdata(&framestart_queue, 0, (char*) &tmpwritenheaderpos, sizeof(frameheaderstartposition), false);
            writenheaderposs = tmpwritenheaderpos;
            lastframeat = (HTFileDesc.fptr - ACCESS_BUFFER_SIZE) + writenheaderposs.byteindex;
            WRITE_RESUME_LOCATION(lastframeat);
            do {
                if(FQgetdata(&framestart_queue, 0, (char*) &tmpwritenheaderpos, sizeof(frameheaderstartposition), false)) {
                    if(tmpwritenheaderpos.bufferindex == buffReadyOut_IDX) {
                        FQremove(&framestart_queue, sizeof(frameheaderstartposition));
                    } else {
                        break;
                    }
                } else
                    break;
            } while(tmpwritenheaderpos.bufferindex == buffReadyOut_IDX);
            buffersReady--;
            if(++buffReadyOut_IDX == NUMBEROFDISKBUFFERS)
                buffReadyOut_IDX = 0;
        }
        if(savetashresult == FR_OK) {
            LedSetAction(laOff);
        }
        cpu_irq_enter_critical();
        WritingFile=0;
        cpu_irq_leave_critical();
        recordSaveTaskState = rstWaitingData;
        break;
    case rstEndRecord:
        WdtSetResetTime(20000);
        if(((samples_to_save == 0) && (RecordEndingTime < get_rtc_time())) || (FileGotTooBig == true)) {
            stopreasson = STOPC_TIME;
        } else {
            UpdateCurrentFrameInfo();
        }
        ADS1298_SetOnNewDataHandler(NULL);
        ADS1298_Stop();
        if(FileGotTooBig == false) {
            unsigned int tmp1 = buffersFilledDuringWriting;
            tmp1 += filledandpending;
            buffersReady += tmp1;
            while(buffersReady) {
                savetashresult = f_write(&HTFileDesc, diskbuffer.diskbuffer[buffReadyOut_IDX], ACCESS_BUFFER_SIZE, &writenBytes);
                buffersReady--;
                if(++buffReadyOut_IDX == NUMBEROFDISKBUFFERS) buffReadyOut_IDX = 0;
            }
            f_write(&HTFileDesc, diskbuffer.diskbuffer[buffReadyOut_IDX], filling_byte_index+1, &writenBytes);
        }
        EnableDoubleBuffering(true);
//TODO: do some code cleanup in buffer flushing (previous 10 lines)
        WRITE_RESUME_LOCATION(0); // the test ended completely
        recordSaveTaskStatus = taskDone;
        recordSaveTaskState = rstWaitingData;
        break;
    }
    return recordSaveTaskStatus;
}