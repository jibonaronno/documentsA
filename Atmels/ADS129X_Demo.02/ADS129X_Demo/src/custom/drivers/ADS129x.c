#include "ADS129x.h"
#include "board.h"
#include "spi_dma.h"
#include "TMOUT.h"
#include "trismed/utils/signal-preprocessor.h"
#include "trismed/utils/CircularQueue.h"

#include <stdbool.h>
#include <string.h>
#include <assert.h>

//#define WITH_EXTERNAL_MUX_FOR_PACEMAKER

#ifdef WITH_TEST
#include <stdio.h>
#endif

/*#define SEND_RLD_ON_V6*/

#define ADS1294_DEV_ID    0x90u
#define ADS1296_DEV_ID    0x91u
#define ADS1298_DEV_ID    0x92u
#define ADS1198_DEV_ID    0xB6u

typedef enum {
    Addr_ID         = 0x00,
    Addr_CONFIG1    = 0x01,
    Addr_CONFIG2    = 0x02,
    Addr_CONFIG3    = 0x03,
    Addr_LOFF       = 0x04,
    Addr_CH1SET     = 0x05,
    Addr_CH2SET     = 0x06,
    Addr_CH3SET     = 0x07,
    Addr_CH4SET     = 0x08,
    Addr_CH5SET     = 0x09,
    Addr_CH6SET     = 0x0A,
    Addr_CH7SET     = 0x0B,
    Addr_CH8SET     = 0x0C,
    Addr_RLD_SENSP  = 0x0D,
    Addr_RLD_SENSN  = 0x0E,
    Addr_LOFF_SENSP = 0x0F,
    Addr_LOFF_SENSN = 0x10,
    Addr_LOFF_FLIP  = 0x11,
    Addr_LOFF_STATP = 0x12,
    Addr_LOFF_STATN = 0x13,
    Addr_GPIO       = 0x14,
    Addr_PACE       = 0x15,
    Addr_RESP       = 0x16,
    Addr_CONFIG4    = 0x17,
    Addr_WCT1       = 0x18,
    Addr_WCT2       = 0x19
} ADS129X_REG_ADDR;

#pragma pack(push, 1)
typedef struct {
    unsigned char cmd;
    unsigned char data[32];
    uint16_t totalsize;
} ADS1298_CMD;
#pragma pack(pop)

#define  RDATAC 0x10u
#define  SDATAC 0x11u
#define  START  0x08u
#define  STOP   0x0Au

#define ADS1298_WRITE_REGISTER  0x40u
#define ADS1298_READ_REGISTER   0x20u

/** LOFF defines -> */
#define COMP_TH_95  0x00u
#define COMP_TH_925 0x20u
#define COMP_TH_90  0x40u
#define COMP_TH_875 0x60u
#define COMP_TH_85  0x80u
#define COMP_TH_80  0xA0u
#define COMP_TH_75  0xC0u
#define COMP_TH_70  0xE0u

#define VLEAD_OFF_EN    0x10u    /* [1] = Pull-up/down, [0] = Current source (default is 0) */
/** Current source method for leadoff detection increases the input impedance
*  by a factor of 10, so it is highly recommended.
*/

#define ILEAD_OFF_6nA   0x00u
#define ILEAD_OFF_12nA  0x04u
#define ILEAD_OFF_18nA  0x08u
#define ILEAD_OFF_24nA  0x0Cu

#define FLEAD_OFF_NO    0x00u
#define FLEAD_OFF_AC    0x01u
#define FLEAD_OFF_NEVER 0x02u
#define FLEAD_OFF_DC    0x03u
/** LOFF defines <- */

/** CONFIG1 defines -> */
#define HR  0x80u   /* This bit determines whether the device runs in Low-Power or High-Resolution mode.
0 = Low-Power mode (default)
1 = High-Resolution mode */
#define DAISY_EN        0x40u   /* This bit determines which mode is enabled.
0 = Daisy-chain mode (default)
1 = Multiple readback mode */
#define CLK_EN          0x20u   /* This bit determines if the internal oscillator signal is connected to the CLK pin when the CLKSEL pin = 1.
0 = Oscillator clock output disabled (default)
1 = Oscillator clock output enabled */

/* For High-Resolution mode, fMOD = fCLK/4. For low power mode, fMOD = fCLK/8.
These bits determine the output data rate of the device. */
#define LOW_RES_FREQ_16K    0x00u
#define LOW_RES_FREQ_8K     0x01u
#define LOW_RES_FREQ_4K     0x02u
#define LOW_RES_FREQ_2K     0x03u
#define LOW_RES_FREQ_1K     0x04u
#define LOW_RES_FREQ_500    0x05u
#define LOW_RES_FREQ_250    0x06u

#define HIGH_RES_FREQ_32K   0x00u
#define HIGH_RES_FREQ_16K   0x01u
#define HIGH_RES_FREQ_8K    0x02u
#define HIGH_RES_FREQ_4K    0x03u
#define HIGH_RES_FREQ_2K    0x04u
#define HIGH_RES_FREQ_1K    0x05u
#define HIGH_RES_FREQ_500   0x06u

/** CONFIG1 defines <- */

/** CONFIG2 defines -> */
#define WCT_CHOP    0x20u   /* This bit determines whether the chopping frequency of WCT amplifiers is variable or fixed.
0 = Chopping frequency varies, see Table 13
1 = Chopping frequency constant at fMOD/16 */
#define INT_TEST    0x10u   /* This bit determines the source for the Test signal.
0 = Test signals are driven externally (default)
1 = Test signals are generated internally */
#define TEST_AMP    0x04u   /* These bits determine the calibration signal amplitude.
0 = 1 * -(VREFP - VREFN)/2.4mV (default)
1 = 2 * -(VREFP - VREFN)/2.4mV */
#define TEST_FREQ_FCLK_221  0x00u
#define TEST_FREQ_FCLK_220  0x01u
#define TEST_FREQ_DC        0X03u    /* These bits determine the calibration signal frequency.
00 = Pulsed at fCLK/221 (default)
01 = Pulsed at fCLK/220
10 = Not used
11 = At dc */
/** CONFIG2 defines <- */

/** CONFIG3 defines -> */
#define CONFIG3_ALWAYS_1    0x40u
#define PD_REFBUF   (0x80u | CONFIG3_ALWAYS_1)    /* 1 => Enable internal refference buffer (default is 0 => powered down) */
#define VREF_4V     (0x20u | CONFIG3_ALWAYS_1)    /* 1 => Use external 4V voltage reference (default is 0 => internal 2.4V) */
#define RLD_MEAS    (0x10u | CONFIG3_ALWAYS_1)    /* 1 => Route RLD to be meassured throug anoter channel ADC (default is 0 => open) */
#define RLDREF_INT  (0x08u | CONFIG3_ALWAYS_1)    /* 1 => RLDREF signal (AVDD - AVSS)/2 generated internally (default is 0 =>  external) */
#define PD_RLD      (0x04u | CONFIG3_ALWAYS_1)    /* 1 => RLD buffer is enabled (default is 0 => powered down) */
#define RLD_LOFF_SENS   0x02u | CONFIG3_ALWAYS_1    /* 1 => Allows RLD lead connection (default is 0 => not allowed) */
/*Note: During normal operation, the ADS129x RLD lead-off at power-up function cannot be used because it is necessary to power off the RLD amplifier.*/
/* RLD_STAT (0x01) is read only and it can only be used together with RLD_LOFF_SENS */
/** CONFIG3 defines <- */

#define VREF_2_4V       (CONFIG3_ALWAYS_1 | 0x00u)

#ifdef USE_VREF_4V
#define USED_VREF (VREF_4V)
#else
#define USED_VREF (VREF_2_4V)
#endif

t_vRef GetBoardReference(void) {
#if USED_VREF == VREF_2_4V
#pragma message("Firmware for AVcc = 3.3V with vRef=2.4V!!!")
    return vRef2_4V;
#else
#warning Firmware for AVcc = 5V with vRef=4V!!!
    return vRef4V;
#endif
}

/** CONFIG4 defines -> */
#define RESP_FREQ2   0x80u
#define RESP_FREQ1   0x40u
#define RESP_FREQ0   0x20u
/*
    000 = 64kHz modulation clock
    001 = 32kHz modulation clock
    010 = 16kHz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.
    011 = 8kHz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.
    100 = 4kHz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.
    101 = 2kHz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.
    110 = 1kHz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.
    111 = 500Hz square wave on GPIO3 and GPIO04. Output on GPIO4 is 180 degree out of phase with GPIO3.

    Modes 000 and 001 are modulation frequencies in internal and external respiration modes.
    In internal respiration mode, the control signals appear at the RESP_MODP and RESP_MODN
    terminals. All other bit settings generate square waves as described above on GPIO4 and GPIO3.
*/
#define SINGLE_SHOT  0x08u      /* 1 => Single-shot conversion Enabled (default is 0 =>  Continuous mode is Enabled) */
#define WTC_TO_RLD   0x04u      /* 1 => Connects the WCT to the RLD (default is 0 => WTC not connected to RLD) */
#define PD_LOFF_COMP 0x02u      /* 1 => Lead-off comparator are Enabled (default is 0 => Lead-off comparator power-down) */
/** CONFIG4 defines <- */

static volatile bool ADS1298_Acquiring = false;

static ADS1298_CMD ads1298cmd;
static volatile bool ADS1298_Send_Finnished;
static volatile bool ADS1298_Receive_Finnished;
static int activeChannels;

static unsigned int pacemakerChannel = 0u;
static bool adsPacemakerEnabled = false;

#define SIGNAL_DELAY_SAMPLES (3)
static struct circular_buffer cbSignalDelayBuffer;   /* circular queue descriptor */

void ADS1298_Ready_ISR(const uint32_t id, const uint32_t index);

void ADS1298_SetPacemaker(bool enabled, unsigned int channel /* 0 to 7*/) {
    pacemakerChannel = channel;
    adsPacemakerEnabled = enabled;
    static ADS1298_Frame cbSignalDelayBuff[SIGNAL_DELAY_SAMPLES]; /* buffer for the circular_queue */
    memset(cbSignalDelayBuff, 0, sizeof(cbSignalDelayBuff));
    /* reinitialize the circular queue */
    cb_create_static(&cbSignalDelayBuffer, (void*) &cbSignalDelayBuff, SIGNAL_DELAY_SAMPLES, sizeof(ADS1298_Frame));
}

#define ADS1298_VERIFY_REGISTERS
#define USE_HRES    /* High-resolution mode performs better on CMRR */
#ifdef USE_HRES
#pragma message("Using high resolution mode")
#define FREQ_1KHZ    (HR | HIGH_RES_FREQ_1K)
#define FREQ_4KHZ   (HR | HIGH_RES_FREQ_4K)
#define FREQ_8KHZ   (HR | HIGH_RES_FREQ_8K)
#define FREQ_16KHZ   (HR | HIGH_RES_FREQ_16K)
#define FREQ_32KHZ   (HR | HIGH_RES_FREQ_32K)
#define FREQ_500HZ    (HR | HIGH_RES_FREQ_500)
#else
#define FREQ_1KHZ    LOW_RES_FREQ_1K
#define FREQ_500HZ    LOW_RES_FREQ_500
#endif    /* USE_HRES */
#define FREQ_250HZ    (LOW_RES_FREQ_250)

/*
The number of bits in the data output depends on the number of channels and the number of bits per channel.
For the ADS1298/8R, the number of data outputs is (24 status bits + 24 bits x 8 channels) = 216 bits. The format
of the 24 status bits is: (1100 + LOFF_STATP + LOFF_STATN + bits[4:7] of the GPIO register). The data format
for each channel data are twos complement and MSB first. When channels are powered down using the user
register setting, the corresponding channel output is set to '0'. However, the sequence of channel outputs
remains the same.

Read 27 bytes on each DRDY interrupt
*/

#if ADS1298_GAIN == 1
#define CHXSET    0x10u
#elif ADS1298_GAIN == 2
#define CHXSET    0x20u
#elif ADS1298_GAIN == 3
#define CHXSET    0x30u
#elif ADS1298_GAIN == 4
#define CHXSET    0x40u
#elif ADS1298_GAIN == 6
#define CHXSET    0x00u
#elif ADS1298_GAIN == 8
#define CHXSET    0x50u
#elif ADS1298_GAIN == 12
#define CHXSET    0x60u
#else
#error Unsupported Gain, the gain must be: 1, 2, 3, 4, 6, 8 or 12
#endif

#define CALIBRATION_SIGNAL  (0x05u | CHXSET)
#define RLD_SIGNAL (0x02u | 0x10u/*CHXSET*/)

static onNewDataHandler newDataHandler = NULL;

void ADS1298_SetOnNewDataHandler(onNewDataHandler handler) {
    newDataHandler = handler;
}

enum wctSource { wctInternal=0, wctExternal } ;

typedef enum {
    ADS1298_SF_250=0, ADS1298_SF_500, ADS1298_SF_1000, ADS1298_SF_4K, ADS1298_SF_8K, ADS1298_SF_16K
} ADS1298_SAMPLING_FREQ;
ADS1298_SAMPLING_FREQ ADS1298_current_sf;
static int SamplingFrequency = 500;
uint32_t signmask = 0x00800000;
uint32_t signExtendmask = 0xFFFFFFFF;

struct ads129xDevice {
    uint8_t devID;
    uint8_t csNum;
    uint8_t channels;
    uint8_t bits;
    enum wctSource wct;
    bool isMain;
    uint8_t frameSizeInBytes;
};

struct paceChannelConfig_t {
    uint8_t chipId;
    uint8_t eMux; /* 0-> OUT2, 1 => OUT1 */
    uint8_t adsMux;
};

/* Pacemaker signal addressing for 1chip 8ch board */
const struct paceChannelConfig_t paceOutMap_1chip8ch_Only[8] = {
    /* chip, external MUX control (ADS_GPIO3), ADS pacemaker MUX */
    { 0u, 0u, 0u << 1 },       /* CH1 (I)  */
    { 0u, 1u, 0u << 3 },       /* CH2 (II) */
    { 0u, 0u, 1u << 1 },       /* CH3 (V1) */
    { 0u, 1u, 1u << 3 },       /* CH4 (V2) */
    { 0u, 0u, 2u << 1 },       /* CH5 (V3) */
    { 0u, 1u, 2u << 3 },       /* CH6 (V4) */
    { 0u, 0u, 3u << 1 },       /* CH7 (V5) */
    { 0u, 1u, 3u << 3 },       /* CH8 (V6) */
};

/* Pacemaker signal addressing for 2chips 4ch each board (total 8ch) */
const struct paceChannelConfig_t paceOutMap_2chips4ch_total8ch[8] = {
    /* chip, external MUX control (PA0 to PA2), ADS pacemaker MUX */
    { 0u, 1u, 0u << 1 },       /* CH1 (I)  */
    { 0u, 0u, 0u << 3 },       /* CH2 (II) */
    { 0u, 1u, 1u << 1 },       /* CH3 (V1) */
    { 0u, 0u, 1u << 3 },       /* CH4 (V2) */
    { 1u, 3u, 0u << 1 },       /* CH5 (V3) */
    { 1u, 2u, 0u << 3 },       /* CH6 (V4) */
    { 1u, 3u, 1u << 1 },       /* CH7 (V5) */
    { 1u, 2u, 1u << 3 },       /* CH8 (V6) */
};

static uint8_t rxChip=0;

enum muxControl_t { muxAdsGpio, muxDirectGpio };

struct ads129xSystem_t {
    struct ads129xDevice adsDevices[ADS129X_CASCADED_DEVS];
    uint adsChipsFound;
    uint totalChannels;
    enum muxControl_t paceMuxType;
    const struct paceChannelConfig_t* paceChannelConfig;
};

static struct ads129xSystem_t ads129xSystem = {
    {
        /* as many elements as ADS129X_CASCADED_DEVS */
        {
            /* First chip will provide clock and WCT to the rest */
            .isMain = true,
            .csNum = 1,
            .wct = wctInternal
        },
        {
            .isMain = false,
            .csNum = 0,
            .wct = wctExternal
        }
    },
    0,      /* total channels (automatically detected) */
    0,      /* chips found (automatically detected) */
    muxDirectGpio,  /* control used for analog mux */
    NULL    /* paceChannelConfig: pacemaker channel addressing information */
};

void Ads129x_Send_CMD(uint8_t devIdx, ADS1298_CMD * _ads1298cmd);
void Ads129x_ReadRegs(uint8_t devIdx, ADS129X_REG_ADDR _ads_register, uint8_t* _outvalues, uint8_t _count);
bool Ads129x_WriteRegs(uint8_t devIdx, ADS129X_REG_ADDR _ads_register, const uint8_t* _values, uint8_t _count);
void Ads129x_Async_Recive_Data(uint8_t devIdx, uint8_t* rxBuf, uint8_t* txBuff, uint8_t count);
unsigned char Ads129x_Recive_Data(uint8_t devIdx, ADS1298_CMD * _ads1298cmd);

static void AdsStopDevice(void);
static bool DetectAdsDevice(uint8_t devIdx);
static void UpdateAds129xSystem(void);
static void SetChipChannels(uint8_t devIdx, uint8_t channels, bool calibration);
static void ADS1298_SetChannels(int lchannels, bool calibration);
static void ADS1298_ConfigurePacemakerDetection(void);


#define REGS_COUNT (Addr_WCT2+1)
static void Ads1x9x_PrintRegs(uint8_t devIdx);
static void Ads1x9x_PrintRegs(uint8_t devIdx) {
    uint8_t regs[REGS_COUNT];

    const char* regNames[REGS_COUNT] = {
        "ID",
        "CONFIG1",
        "CONFIG2",
        "CONFIG3",
        "LOFF",
        "CH1SET",
        "CH2SET",
        "CH3SET",
        "CH4SET",
        "CH5SET",
        "CH6SET",
        "CH7SET",
        "CH8SET",
        "RLD_SENSP",
        "RLD_SENSN",
        "LOFF_SENSP",
        "LOFF_SENSN",
        "LOFF_FLIP",
        "LOFF_STATP",
        "LOFF_STATN",
        "GPIO",
        "PACE",
        "RESP",
        "CONFIG4",
        "WCT1",
        "WCT2"
    };

    Ads129x_ReadRegs(devIdx, Addr_ID, regs, REGS_COUNT);
#if 0
    printf("Dev %d registers:\n", devIdx);
    for(int reg=0; reg<REGS_COUNT; reg++) {
        printf("Dev %d %s 0x%.2x\n", devIdx, regNames[reg], regs[reg]);
    }
    printf("-------------------------\n");
#else
    (void) (regNames);
#endif
}

void Ads129x_Send_CMD(uint8_t devIdx, ADS1298_CMD * _ads1298cmd) {
    ADS1298_Send_Finnished = false;
    spi_dma_transfer((uint8_t*) _ads1298cmd, NULL, _ads1298cmd->totalsize, ads129xSystem.adsDevices[devIdx].csNum);
    while (!spi_dma_done()) {
    }
}

void Ads129x_Async_Recive_Data(uint8_t devIdx, uint8_t* rxBuf, uint8_t* txBuff, uint8_t count) {
    rxChip = devIdx;
    ADS1298_Receive_Finnished=false;
    spi_dma_transfer((uint8_t*) txBuff, rxBuf, count, ads129xSystem.adsDevices[devIdx].csNum);
}

unsigned char Ads129x_Recive_Data(uint8_t devIdx, ADS1298_CMD * _ads1298cmd) {
    ADS1298_Receive_Finnished=false;
    spi_dma_transfer((uint8_t*) _ads1298cmd, _ads1298cmd->data, _ads1298cmd->totalsize, ads129xSystem.adsDevices[devIdx].csNum);
    while (!ADS1298_Receive_Finnished /*|| !ADS1298_Send_Finnished*/) {}; // wait for the transaction to finish
    return true;
}

void Ads129x_ReadRegs(uint8_t devIdx, ADS129X_REG_ADDR _ads_register, uint8_t* _outvalues, uint8_t _count) {
    ADS1298_CMD lads1298cmd;
    lads1298cmd.cmd = ADS1298_READ_REGISTER + _ads_register;
    lads1298cmd.data[0]=_count-1;           // read _count registers (_count-1)
    memset(&lads1298cmd.data[1], 0, _count); // always send 0
    lads1298cmd.totalsize=_count+2;         // total transfer size in bytes
    Ads129x_Recive_Data(devIdx, &lads1298cmd);
    memcpy((void*)_outvalues, (void*)&lads1298cmd.data[2], _count);
}

bool Ads129x_WriteRegs(uint8_t devIdx, ADS129X_REG_ADDR _ads_register, const uint8_t* _values, uint8_t _count) {
    ADS1298_CMD lads1298cmd;
    lads1298cmd.cmd = ADS1298_WRITE_REGISTER + _ads_register;
    lads1298cmd.data[0]=_count-1;           // write _count registers (_count-1)
    memcpy(&lads1298cmd.data[1], _values, _count); //values to write
    lads1298cmd.totalsize=_count+2;         // total transfer size in bytes
    Ads129x_Send_CMD(devIdx, &lads1298cmd);
#ifdef ADS1298_VERIFY_REGISTERS
    ADS129X_REG_ADDR adsreadaddress = _ads_register;
    uint8_t rvalue;
    while(adsreadaddress <= _ads_register + (_count-1)) {
        Ads129x_ReadRegs(devIdx, adsreadaddress, &rvalue, 1);
        if(_values[adsreadaddress-_ads_register] != rvalue) {
            return false;
        }
        adsreadaddress++;
    }
    return true;
#else
    return true;
#endif
}

inline static void AdsStopDevice(void) {
    TMOUT_CounterHandle localtimeouthandle;
    for(int devIdx=0; devIdx<ADS129X_CASCADED_DEVS; devIdx++) {
        ads1298cmd.cmd = SDATAC;
        ads1298cmd.totalsize = 1;
        Ads129x_Send_CMD(devIdx, &ads1298cmd);

        localtimeouthandle = TMOUT_GetCounter(40/TMOUT_TICK_PERIOD_MS); /* set up timeout counter */
        while (!(TMOUT_CounterExpired(localtimeouthandle)));
        TMOUT_LeaveCounter(&localtimeouthandle);     //free up the timer counter so it can be reused later
    }

#if 0
    for(int devIdx=0; devIdx<ADS129X_CASCADED_DEVS; devIdx++) {
        ads1298cmd.cmd = STOP;
        ads1298cmd.totalsize = 1;
        Ads129x_Send_CMD(devIdx, &ads1298cmd);

        localtimeouthandle = TMOUT1_GetCounter(40/TMOUT1_TICK_PERIOD_MS); /* set up timeout counter */
        while (!(TMOUT_CounterExpired(localtimeouthandle)));
        TMOUT_LeaveCounter(&localtimeouthandle);     //free up the timer counter so it can be reused later
    }
#endif
}

#define ADS_TYPE_MASK (0xF0)
#define ADS119X (0xB0)
#define ADS129X (0x90)
#define ADS129XR (0xD0)

bool DetectAdsDevice(uint8_t devIdx) {
    TMOUT_CounterHandle localtimeouthandle;
    uint8_t lConfig1 = 0u;
    uint8_t lConfig2 = WCT_CHOP | INT_TEST;
    uint8_t lConfig3 = PD_REFBUF | RLDREF_INT;

    AdsStopDevice();
    Ads129x_ReadRegs(devIdx, Addr_ID, &ads1298cmd.data[2], 1);
    ads129xSystem.adsDevices[devIdx].devID = ads1298cmd.data[2];
    if(devIdx == 0 && ads129xSystem.adsDevices[devIdx].isMain == true) {
        /* Reset and initialize the cascade */
        lConfig1 = CLK_EN;
        lConfig3 |= PD_RLD;
    }
    uint8_t devType = ads129xSystem.adsDevices[devIdx].devID & ADS_TYPE_MASK;
    switch(devType) {
    case ADS119X:
        ads129xSystem.adsDevices[devIdx].bits = 16;
        break;
    case ADS129X:
    case ADS129XR:
        ads129xSystem.adsDevices[devIdx].bits = 24;
        break;
    default:
        ads129xSystem.adsDevices[devIdx].bits = 0;
        return false;
    }
    switch(ads129xSystem.adsDevices[devIdx].devID) {
    case ADS1294_DEV_ID:
        ads129xSystem.adsDevices[devIdx].channels = 4;
        break;
    case ADS1296_DEV_ID:
        ads129xSystem.adsDevices[devIdx].channels = 6;
        break;
    case ADS1298_DEV_ID:
        ads129xSystem.adsDevices[devIdx].channels = 8;
        break;
    default:
        ads129xSystem.adsDevices[devIdx].channels = 0;
        break;
    }
    ads129xSystem.adsDevices[devIdx].frameSizeInBytes = 3 + (ads129xSystem.adsDevices[devIdx].channels * ads129xSystem.adsDevices[devIdx].bits/8);
    Ads129x_WriteRegs(devIdx, Addr_CONFIG3, &lConfig3, 1);        /* CONFIG3 */
    localtimeouthandle = TMOUT_GetCounter(40/TMOUT_TICK_PERIOD_MS); /* set up timeout counter */
    while (!(TMOUT_CounterExpired(localtimeouthandle)));
    TMOUT_LeaveCounter(&localtimeouthandle);     //free up the timer counter so it can be reused later
    switch(SamplingFrequency) {
    case 250:
        ADS1298_current_sf=ADS1298_SF_250;
        lConfig1 |= FREQ_250HZ;
        break;
    case 500:
        ADS1298_current_sf=ADS1298_SF_500;
        lConfig1 |= FREQ_500HZ;
        break;
    case 1000:
        ADS1298_current_sf=ADS1298_SF_1000;
        lConfig1 |= FREQ_1KHZ;
        break;
#ifdef USE_HRES
    case 4000:
        ADS1298_current_sf=ADS1298_SF_4K;
        lConfig1 |= FREQ_4KHZ;
        break;
    case 8000:
        ADS1298_current_sf=ADS1298_SF_8K;
        lConfig1 |= FREQ_8KHZ;
        break;
    case 16000:
        ADS1298_current_sf=ADS1298_SF_16K;
        lConfig1 |= FREQ_16KHZ;
        break;
#endif
    default:
        break;
    }
    Ads129x_WriteRegs(devIdx, Addr_CONFIG1, &lConfig1, 1);      //CONFIG1
    bool result = Ads129x_WriteRegs(devIdx, Addr_CONFIG2, &lConfig2, 1);        //CONFIG2
    localtimeouthandle = TMOUT_GetCounter(60/TMOUT_TICK_PERIOD_MS); /* set up timeout counter */
    while (!(TMOUT_CounterExpired(localtimeouthandle)));
    TMOUT_LeaveCounter(&localtimeouthandle);     //free up the timer counter so it can be reused later
    return result;
}

static uint32_t discardFirstSamples = 50;

void ADS1298_Start(void) {
    discardFirstSamples = 50;
#ifdef SIGNAL_PREPROCESSOR_H_
    SignalPreprocesorInit(activeChannels);
#endif
    SET_ADS1298_PWD;
    for(int i=0; i<5000; i++) {
        asm("nop");
    }
    ADS1298_Acquiring=true;
    ads1298cmd.cmd = RDATAC;
    ads1298cmd.totalsize = 1;
    for(uint currentChip = 0u; currentChip < ads129xSystem.adsChipsFound; currentChip++) {
        Ads129x_Send_CMD(currentChip, &ads1298cmd);
    }
    SET_ADS1298_START;
}

void ADS1298_ModuleInit(void) {
    pio_set_output(ADS_PD_PORT, ADS_PD_PIO, 1, 0, 0);
    pio_set_output(ADS_START_PORT, ADS_START_PIO, 0, 0, 0);
    pio_set_output(ADS_RESET_PORT, ADS_RESET_PIO, 1, 0, 0);

#if ADS129X_CASCADED_DEVS == 1
    pio_set_output(PACE_RESET_PORT, PACE_RESET_PIO, 0, 0, 0);
#endif

    ADS1298_Send_Finnished = true;
    ADS1298_Receive_Finnished = true;
    spi_dma_init();
    RegisterSpiEvent(ADS1298_BlockReceived, spiEvRxDone);
    RegisterSpiEvent(ADS1298_BlockSent, spiEvTxDone);

    pio_set_input(ADS_READY_PORT, ADS_DRDY_PIO, PIO_PULLUP);
    pio_handler_set(PIOA, ID_PIOA, ADS_DRDY_PIO, PIO_IT_FALL_EDGE, ADS1298_Ready_ISR);
    pio_enable_interrupt(PIOA, ADS_DRDY_PIO);

    pio_set_input(PACEMAKER_PORT, PACEMAKER_PIO, PIO_DEFAULT);

    NVIC_EnableIRQ(PIOA_IRQn);
    //ADS1298_Start();
#ifdef PACEMAKER_ANY_CHANNEL
#warning with HR
    ADS1298_Init(8000, false, 8);
#else
    ADS1298_Init(500, false, 8);
#endif
}

void ADS1298_Stop(void) {
    CLR_ADS1298_START;
    AdsStopDevice();
    //SET_ADS1298_PWD;
    ADS1298_Acquiring = false;
}

static void ADS1298_ConfigurePacemakerDetection(void) {
    uint8_t adsMuxValue = 0u;
    uint8_t gpioValue;
    bool resultOk = true;
    /* TODO: when there is more than 1 chip, PD_PACE bit at Addr_PACE
       can be set to 0 in the chips that are not being used for pacemaker
       detection (may save some energy). */
    if(adsPacemakerEnabled) {
        if(ads129xSystem.paceChannelConfig != NULL) {
            adsMuxValue = 0x01u | ads129xSystem.paceChannelConfig[pacemakerChannel].adsMux;
            switch(ads129xSystem.paceMuxType) {
            case muxAdsGpio:
                Ads129x_ReadRegs(0, Addr_GPIO, &gpioValue, 1u);
                gpioValue &= (uint8_t)(0xBB); /* clear data of GPIO3 and configure it for output */
                gpioValue |= (ads129xSystem.paceChannelConfig[pacemakerChannel].eMux == 1u) ? (1u << 6u) : (0u << 6u);
                while(!resultOk) {
                    resultOk = Ads129x_WriteRegs(ads129xSystem.paceChannelConfig[pacemakerChannel].chipId, Addr_GPIO, &gpioValue, 1u);
                }
                break;
            default:
                break;
            }
        }
    } else {
        adsMuxValue = 0u;
    }
    resultOk = false;
    while(!resultOk) {
        resultOk = Ads129x_WriteRegs(ads129xSystem.paceChannelConfig[pacemakerChannel].chipId, Addr_PACE, &adsMuxValue, 1u);
    }
}

static void UpdateAds129xSystem(void) {
    ads129xSystem.totalChannels = 0;
    for(uint i=0; i<ads129xSystem.adsChipsFound; i++) {
        ads129xSystem.totalChannels += ads129xSystem.adsDevices[i].channels;
    }
    switch(ads129xSystem.adsChipsFound) {
    case 1:
        ads129xSystem.paceChannelConfig = paceOutMap_1chip8ch_Only;
        ads129xSystem.paceMuxType = muxAdsGpio;
        break;
    case 2:
        ads129xSystem.paceChannelConfig = paceOutMap_1chip8ch_Only;
        ads129xSystem.paceMuxType = muxAdsGpio;
        break;
    default:
        ads129xSystem.paceMuxType = muxDirectGpio;
        ads129xSystem.paceChannelConfig = NULL;
        break;
    }
}

void ADS1298_Init(int _sampling_freq, int channelsCount, bool calibration) {
    bool error = true;
    SamplingFrequency = _sampling_freq;
    TMOUT_CounterHandle localtimeouthandle = TMOUT_GetCounter(40u/(unsigned int)TMOUT_TICK_PERIOD_MS); /* get a timer counter */
    signmask = 0x00800000;
    signExtendmask = 0xFFFFFFFF;
#if ADS1298_GAIN == 4
    signExtendmask <<= 22;
    signmask >>=2;
#elif ADS1298_GAIN == 2
    signExtendmask <<= 23;
    signmask >>=1;
#elif ADS1298_GAIN == 1
    signExtendmask <<= 24;
#endif
    while(error) {
        error = false;
        SET_ADS1298_PWD;
        CLR_ADS1298_START;
        SET_ADS1298_RESET;
        TMOUT_SetCounter(localtimeouthandle, 80u/(unsigned int)TMOUT_TICK_PERIOD_MS); /* reset the timer to new different timeout */
        while (!TMOUT_CounterExpired(localtimeouthandle)) {
        }
        CLR_ADS1298_RESET;
        TMOUT_SetCounter(localtimeouthandle, 80u/(unsigned int)TMOUT_TICK_PERIOD_MS); /* reset the expired timer to a different timeout */
        while (!TMOUT_CounterExpired(localtimeouthandle)) {
        }
        SET_ADS1298_RESET;
        /* We have to delay around 1us (tCSH = 18 tCLK = 10ms ) before continue */
        TMOUT_SetCounter(localtimeouthandle, 40u/(unsigned int)TMOUT_TICK_PERIOD_MS); /* reset the expired timer to a different timeout */
        while (!(TMOUT_CounterExpired(localtimeouthandle))) {
        }
        ADS1298_Stop(); /* send SDATAC */

        TMOUT_SetCounter(localtimeouthandle, 20u/(unsigned int)TMOUT_TICK_PERIOD_MS); /* reset the expired timer to a different timeout */
        while (!(TMOUT_CounterExpired(localtimeouthandle))) {
        }

        ads129xSystem.adsChipsFound = 0;
        while(ads129xSystem.adsChipsFound < ADS129X_CASCADED_DEVS) {
            if(DetectAdsDevice(ads129xSystem.adsChipsFound)) {
                ads129xSystem.adsChipsFound++;
            } else {
                if(ads129xSystem.adsChipsFound > 0) {
                    error = false;
                    break;
                }
            }
        }
        UpdateAds129xSystem();
        if(ads129xSystem.adsChipsFound > 0) {
            ADS1298_SetChannels(channelsCount, calibration);
            ADS1298_ConfigurePacemakerDetection();
            for(uint i=0u; i<ads129xSystem.adsChipsFound; i++) {
                Ads1x9x_PrintRegs(i);
            }
            error = false;
            break;
        }
    }
    TMOUT_LeaveCounter(&localtimeouthandle);        /* free up the timer counter so it can be reused later */
}

static void SetChipChannels(uint8_t devIdx, uint8_t channels, bool calibration) {
    for(int i=0; i<ads129xSystem.adsDevices[devIdx].channels; i++) {
        if(calibration) {
            ads1298cmd.data[i] = i<channels?CALIBRATION_SIGNAL:0xA0u;
        } else {
            ads1298cmd.data[i] = i<channels?CHXSET:0xA0u;
        }
    }
    Ads129x_WriteRegs(devIdx, Addr_CH1SET, &ads1298cmd.data[0],
                      ads129xSystem.adsDevices[devIdx].channels);    /* CH1SET to CH8SET */
    /* configure Leadoff P and N SENS */
    switch(channels) {
    case 0:
        ads1298cmd.data[0]=0x00;    /* Addr_LOFF_SENSP */
        ads1298cmd.data[1]=0x00;    /* Addr_LOFF_SENSN */
        break;
    case 3:
        ads1298cmd.data[0]=0x07;    /* Addr_LOFF_SENSP */
        ads1298cmd.data[1]=0x07;    /* Addr_LOFF_SENSN */
        break;
    case 4:
        if(devIdx == 0) {
            ads1298cmd.data[0]=0x0f;    /* Addr_LOFF_SENSP */
            ads1298cmd.data[1]=RA_SENSN;/* Addr_LOFF_SENSN */
        } else {
            ads1298cmd.data[0]=0x0f;    /* Addr_LOFF_SENSP */
            ads1298cmd.data[1]=0x00;    /* Addr_LOFF_SENSN */
        }
        break;
    case 8:
        if(devIdx == 0) {
            ads1298cmd.data[0]=0xff;    /* Addr_LOFF_SENSP */
            ads1298cmd.data[1]=RA_SENSN;/* Addr_LOFF_SENSN */
        }
        break;
    default:
        assert("unsupported number of channels!!");
        break;
    }
    Ads129x_WriteRegs(devIdx, Addr_LOFF_SENSP, &ads1298cmd.data[0], 2); //Addr_LOFF_SENSP

    uint8_t value = 0x00u;
    Ads129x_WriteRegs(devIdx, Addr_LOFF_FLIP, &value, 1u);

    if(ads129xSystem.adsDevices[devIdx].wct == wctInternal) {
        ads1298cmd.data[0]=0x08u;    /* WCT1 (L -> IN1P) */
        ads1298cmd.data[1]=0xCAu;    /* WCT2 (R F -> IN1N IN2P) */
        Ads129x_WriteRegs(devIdx, Addr_WCT1, &ads1298cmd.data[0], 2u);

        if(channels == 3) {
            //RLD biased from +1 +2 +3 and -1 -2 -3
            ads1298cmd.data[0]=0x07;  //RLD_SENSP     (+1, +2, +3)
            ads1298cmd.data[1]=0x07;  //RLD_SENSN     (-1 -2 -3)
        } else {
            //RLD biased from L R F
            ads1298cmd.data[0]=0x03u;    /* RLD_SENSP  (L -> IN1P, F -> IN2P) */
            ads1298cmd.data[1]=0x01u;    /* RLD_SENSN  (R -> IN1N) */
        }
        Ads129x_WriteRegs(devIdx, Addr_RLD_SENSP, &ads1298cmd.data[0], 2);  //RLD_SENSP
    } else {
        ads1298cmd.data[0]=0x00u;    /* all power down */
        ads1298cmd.data[1]=0x00u;    /* all power down */
        Ads129x_WriteRegs(devIdx, Addr_WCT1, &ads1298cmd.data[0], 2u);

        /* See Figure 45. RLD Connection for Multiple Devices */
        ads1298cmd.data[0]=0x00u;    /* no RLD on this chip */
        ads1298cmd.data[1]=0x00u;    /* no RLD on this chip */
        Ads129x_WriteRegs(devIdx, Addr_RLD_SENSP, &ads1298cmd.data[0], 2);  //RLD_SENSP
        /* Note: PD_RLD is already '0' for not primary devices by function DetectAdsDevice */
    }
}

static void ADS1298_SetChannels(int lchannels, bool calibration) {
    uint8_t value;
    activeChannels = lchannels;
    TMOUT_CounterHandle localtimeouthandle;

    Ads129x_ReadRegs(0, Addr_GPIO, &value, 1u);
    value &= ~(1<<1); /* clear data of GPIO2 direction bit to configure it for output */
    if(lchannels == 3) {
        value |= (uint8_t)0x20u; /* GPIO2 high for 3 channels */
    } else {
        value &= (uint8_t)~0x2Au; /* GPIO2 high for 8 channels */
    }
    Ads129x_WriteRegs(0, Addr_GPIO, &value, 1u);

    int remainingChannels = activeChannels;
    for(uint currentChip = 0u; currentChip < ads129xSystem.adsChipsFound; currentChip++) {
        int channels = remainingChannels;
        if(remainingChannels > ads129xSystem.adsDevices[currentChip].channels) {
            channels = ads129xSystem.adsDevices[currentChip].channels;
        }
        if(remainingChannels > 0) {
            remainingChannels-=channels;
        }
        SetChipChannels(currentChip, channels, calibration);
        value = COMP_TH_95/*COMP_TH_70*/ | ILEAD_OFF_6nA | FLEAD_OFF_DC;        /* LOFF by DC (current) */
        if(!Ads129x_WriteRegs(currentChip, Addr_LOFF, &value, 1)) continue;     /* LOFF */
        value = 0x02;   //CONFIG4 Leadoff comparators ON
        if(!Ads129x_WriteRegs(currentChip, Addr_CONFIG4, &value, 1)) continue;      //CONFIG4
        localtimeouthandle = TMOUT_GetCounter(40/TMOUT_TICK_PERIOD_MS); /* set up timeout counter */
        while (!(TMOUT_CounterExpired(localtimeouthandle)));
        TMOUT_LeaveCounter(&localtimeouthandle);     //free up the timer counter so it can be reused later
    }
}

#define MAX_DATABYTES_TO_READ   31
volatile uint8_t adsdataraw[MAX_DATABYTES_TO_READ];
const unsigned char constZeroes[MAX_DATABYTES_TO_READ] = {0};
ADS1298_Frame ads1298inputframe;

void ADS1298_Ready_ISR(const uint32_t id, const uint32_t index) {
    if(ADS1298_Acquiring) {
        if ((id == ID_PIOA) && (index == ADS_DRDY_PIO)) {
            if(GET_ADS1298_DRDY) { /* data is ready */
                if(rxChip == 0) {
                    ADS1298_Receive_Finnished = false;
                    Ads129x_Async_Recive_Data(rxChip, (uint8_t*) adsdataraw, (uint8_t*) constZeroes, ads129xSystem.adsDevices[rxChip].frameSizeInBytes);
                    // We are done here
                    // The data will be ready for read in "ADS1298_BlockReceived"
                }
            }
        }
    }
}

/*#define ALL_ELECTRODES_GOOD*/
#define DIVIDE_24BIT_SIGNED_BY_6(x) do {\
    int32_t sign = ((x & 0x800000) != 0) ? 0xFF000000 : 0;\
    int32_t temp = sign | x;\
    temp = temp/6;\
    x = temp;\
} while (0)

#define DIVIDE_24BIT_SIGNED_BY_8(x) do {\
    int32_t sign = ((x & 0x800000) != 0) ? 0xFF000000 : 0;\
    int32_t temp = sign | x;\
    temp = temp/8;\
    x = temp;\
} while (0)

static uint32_t pcmkDebounce_samples = 40;
static uint32_t pcmkDebounceCounter = 0;
static inline void PaceDebounceInit(void) {
    pcmkDebounceCounter = pcmkDebounce_samples;
}

static inline bool PaceUpdateDebouncePassed(void) {
    if(pcmkDebounceCounter) {
        --pcmkDebounceCounter;
        return false;
    }
    return true;
}

static inline bool PaceDebouncePassed(void) {
    return pcmkDebounceCounter==0;
}

static ADS1298_Frame sampleBeforePaceSpike;
#define PACE_CLEANUP_SAMPLES (4)
static uint8_t samplesToClean = 0;

static inline void PaceStartSignalCleanUp(void) {
    samplesToClean = PACE_CLEANUP_SAMPLES;
}

static inline void PaceSignalCleanUp(void) {
    if(samplesToClean) {
        samplesToClean--;
        memcpy(((ADS1298_Frame*)(cb_at(&cbSignalDelayBuffer, 1)))->Leads, ((ADS1298_Frame*)(cb_at(&cbSignalDelayBuffer, 0)))->Leads, sizeof(sampleBeforePaceSpike.Leads));
    }
}

void ADS1298_BlockReceived(void) {
    int startChannel = 0; /* only works if there are only 2 chips */
    int rawByteIdx = 3;

    if(ADS1298_Acquiring) {
        if(rxChip > 0) {
            startChannel = ads129xSystem.adsDevices[0].channels;    /* this works only for 2 chips */
        }

        for(int lead=0; lead<ads129xSystem.adsDevices[rxChip].channels; lead++) {
            ads1298inputframe.Leads[startChannel] = adsdataraw[rawByteIdx+2] + (adsdataraw[rawByteIdx+1]<<8) + (adsdataraw[rawByteIdx]<<16);
            startChannel++;
            rawByteIdx+=3;
        }

        if(rxChip == 0 && ads129xSystem.adsChipsFound > 1) {
            ads1298inputframe.Status = 0;
            ads1298inputframe.Status = adsdataraw[2] + (adsdataraw[1]<<8) + (adsdataraw[0]<<16);
        } else {
            if(ads129xSystem.adsChipsFound > 1) {
                ads1298inputframe.Status |= ((adsdataraw[2]&0xf0)<<4) + ((adsdataraw[1]&0xf0)<<12);
            } else {
                ads1298inputframe.Status = 0;
                ads1298inputframe.Status = adsdataraw[2] + (adsdataraw[1]<<8) + (adsdataraw[0]<<16);
            }
            if(adsPacemakerEnabled) {
                if(PaceUpdateDebouncePassed() && ((ads1298inputframe.Status & (ADS_RA|ADS_LL|ADS_LA))==0) &&/*!(ads1298inputframe.Status & ADS_GPIO1)*/PACEMAKER_SPIKE) {
#if ADS129X_CASCADED_DEVS == 1
                    CLR_PACE_RESET;
#endif
                    ads1298inputframe.Status |= 0x01;
                    cb_push_back(&cbSignalDelayBuffer, &ads1298inputframe);
                    PaceDebounceInit();
                    PaceStartSignalCleanUp();
                } else {
                    cb_push_back(&cbSignalDelayBuffer, &ads1298inputframe);
                    PaceSignalCleanUp();
                    ads1298inputframe.Status &= ~0x01;
#if ADS129X_CASCADED_DEVS == 1
                    SET_PACE_RESET;
#endif
                }
                memcpy(ads1298inputframe.Leads, ((ADS1298_Frame*)(cb_at(&cbSignalDelayBuffer, 0)))->Leads, sizeof(sampleBeforePaceSpike.Leads));
            } else {
                ads1298inputframe.Status &= ~0x01;
            }
        }

        if(++rxChip < ads129xSystem.adsChipsFound) {
            Ads129x_Async_Recive_Data(rxChip, (uint8_t*) adsdataraw, (uint8_t*) constZeroes, ads129xSystem.adsDevices[rxChip].frameSizeInBytes);
            ADS1298_Receive_Finnished = false;
        } else {
            rxChip = 0;
            ADS1298_Receive_Finnished = true;
        }
        if(ADS1298_Receive_Finnished) {    /*  decode the data and compress it */
#if ADS1298_GAIN == 8
#pragma message("Adjusting gain back to 1")
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[0]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[1]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[2]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[3]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[4]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[5]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[6]);
            DIVIDE_24BIT_SIGNED_BY_8(ads1298inputframe.Leads[7]);
#elif ADS1298_GAIN == 6
#pragma message("Adjusting gain back to 1")
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[0]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[1]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[2]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[3]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[4]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[5]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[6]);
            DIVIDE_24BIT_SIGNED_BY_6(ads1298inputframe.Leads[7]);
#elif ADS1298_GAIN == 4
#pragma message("Adjusting gain back to 1")
            ads1298inputframe.Leads[0] >>= 2;
            ads1298inputframe.Leads[1] >>= 2;
            ads1298inputframe.Leads[2] >>= 2;
            ads1298inputframe.Leads[3] >>= 2;
            ads1298inputframe.Leads[4] >>= 2;
            ads1298inputframe.Leads[5] >>= 2;
            ads1298inputframe.Leads[6] >>= 2;
            ads1298inputframe.Leads[7] >>= 2;
#elif ADS1298_GAIN == 2
#pragma message("Adjusting gain back to 1")
            ads1298inputframe.Leads[0] >>= 1;
            ads1298inputframe.Leads[1] >>= 1;
            ads1298inputframe.Leads[2] >>= 1;
            ads1298inputframe.Leads[3] >>= 1;
            ads1298inputframe.Leads[4] >>= 1;
            ads1298inputframe.Leads[5] >>= 1;
            ads1298inputframe.Leads[6] >>= 1;
            ads1298inputframe.Leads[7] >>= 1;
#elif ADS1298_GAIN == 1
#warning "Using Gain = 1, dynmic range is bigger but CMRR might will be slightly lower!!!"
#else
#error Gain not allowed!!!
#endif
#if ADS1298_GAIN != 6
            for(uint8_t li=0u; li<8u; li++) {
                if(ads1298inputframe.Leads[li] & signmask) ads1298inputframe.Leads[li] += signExtendmask;   // sign extension for int32_t
            }
#endif

#ifdef ALL_ELECTRODES_GOOD
            ads1298inputframe.Status &= ~(ADS_V6 | ADS_V5 | ADS_V4 | ADS_V3 | ADS_V2 | ADS_V1 | ADS_LL | ADS_LA | ADS_RA);
#endif

#ifdef SEND_RLD_ON_V6
            ads1298inputframe.Status &= ~ADS_V6;
#endif
#ifdef SIGNAL_PREPROCESSOR_H_
            if(SignalPreprocessorProcessSample(&ads1298inputframe)) {
#endif

#ifdef PACEMAKER_ANY_CHANNEL
                Pace_NewSample(ads1298inputframe.Leads);
                if(Downsample(&ads1298inputframe)) {
#endif
                    if(newDataHandler != NULL && SignalPreprocessorHasData()) {
#ifdef SIGNAL_PREPROCESSOR_H_
                        ads1298inputframe = SignalProcessorGetSample();
#endif
                        if(discardFirstSamples == 0) {
                            newDataHandler(&ads1298inputframe);
                        } else {
                            discardFirstSamples--;
                        }
                    }
#ifdef PACEMAKER_ANY_CHANNEL
                }
#endif
#ifdef SIGNAL_PREPROCESSOR_H_
            }
#endif
        }
    } else {
        ADS1298_Receive_Finnished = true;
    }
}

void ADS1298_BlockSent(void) {
    ADS1298_Send_Finnished = true;
}

void ADS1298_ConfigureRLD(uint16_t rld_sensp_sensn) {
    /* RLD biased from L R F */
    if((rld_sensp_sensn != 0u)) {
        ads1298cmd.data[0]=(uint8_t)rld_sensp_sensn;        /* RLD_SENSP  (L -> IN1P, F -> IN2P) */
        ads1298cmd.data[1]=(uint8_t)(rld_sensp_sensn>>8);   /* RLD_SENSN  (R -> IN1N) */
    } else {
        ads1298cmd.data[0] = 0u;
        ads1298cmd.data[1] = 0u;
    }
    Ads129x_WriteRegs(0, Addr_RLD_SENSP, &ads1298cmd.data[0], 2u);
}
