/* *************************************************************************
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : main.h
 *
 * *************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H


#define eADC_READ_TIME      6        // 3회 연속 읽기 시                        // eADC_READ_3 1 일때 사용



//#define eFREQ60Hz_TIME      ( (float)1 /60 /64 )    //
//#define eFREQ50Hz_TIME      ( (float)1 /50 /64 )    //
//#define eCOUNT_1USEC        ( 200000000 / ( 1000000 *2 ) )

#define eADC_NO_MAX     3
enum
{
  eADC_TEMP,
  eADC_TC1,
  eADC_TC2,
  eADC_CC,
  eADC_V,
  eADC_IA,
  eADC_IB,
  eADC_IC,
  eADC_MAX,
};
//#define eADC_MAX        8

typedef unsigned short  BOOL; /* byte  8-Bit data */
//typedef bool            BOOL; /* byte  8-Bit data */
typedef unsigned short  UINT8; /* byte  8-Bit data */
typedef unsigned short  UINT16; /* word 16-Bit data */
typedef unsigned long   UINT32; /* long 32-Bit data */
typedef long long       INT64;  /* long 32-Bit data */
typedef char            INT8; /* byte  8-Bit data */
typedef short           INT16; /* word 16-Bit data */
typedef long            INT32; /* long 32-Bit data */

typedef unsigned char   uint8_t; /* byte  8-Bit data */
typedef short           int8_t; /* byte  8-Bit data */
//typedef long            int32_t; /* long 32-Bit data */


#define NOP         asm("   NOP     ")

#define FALSE       0
#define TRUE        1

#define BIT31       0x80000000
#define BIT30       0x40000000
#define BIT29       0x20000000
#define BIT28       0x10000000
#define BIT27       0x08000000
#define BIT26       0x04000000
#define BIT25       0x02000000
#define BIT24       0x01000000
#define BIT23       0x00800000
#define BIT22       0x00400000
#define BIT21       0x00200000
#define BIT20       0x00100000
#define BIT19       0x00080000
#define BIT18       0x00040000
#define BIT17       0x00020000
#define BIT16       0x00010000
#define BIT15       0x00008000
#define BIT14       0x00004000
#define BIT13       0x00002000
#define BIT12       0x00001000
#define BIT11       0x00000800
#define BIT10       0x00000400
#define BIT9        0x00000200
#define BIT8        0x00000100
#define BIT7        0x00000080
#define BIT6        0x00000040
#define BIT5        0x00000020
#define BIT4        0x00000010
#define BIT3        0x00000008
#define BIT2        0x00000004
#define BIT1        0x00000002
#define BIT0        0x00000001
#define ALL8BITS    0xFF
#define ALL16BITS   0xFFFF
#define ALL32BITS   0xFFFFFFFF

typedef union
{
  UINT16  u16;              // element specifier for accessing whole u16
  INT16   i16;              // element specifier for accessing whole i16
  struct
  {
#ifdef LITTLE_ENDIAN        // Byte-order is little endian
    UINT8   u8L;            // element specifier for accessing low u8
    UINT8   u8H;            // element specifier for accessing high u8
#else                       // Byte-order is big endian
    UINT8   u8H;            // element specifier for accessing low u8
    UINT8   u8L;            // element specifier for accessing high u8
#endif
  } s16;                    // element spec. for acc. struct with low or high u8
} nt16;
typedef union
{
  UINT32  u32;              // element specifier for accessing whole u32
  INT32   i32;              // element specifier for accessing whole i32
  struct
  {
#ifdef LITTLE_ENDIAN        // Byte-order is little endian
    UINT16  u16L;           // element specifier for accessing low u16
    UINT16  u16H;           // element specifier for accessing high u16
#else                       // Byte-order is big endian
    UINT16  u16H;           // element specifier for accessing low u16
    UINT16  u16L;           // element specifier for accessing high u16
#endif
  } s32;                    // element spec. for acc. struct with low or high u16
} nt32;

union W2B
{
  UINT16  b16;
  UINT8   b8[2];
};

union L2B
{
  UINT32  b32;
  UINT16  b16[2];
  UINT8   b8[4];
};

union LL2B
{
  UINT32  b32[2];
  UINT16  b16[4];
  UINT8   b8[8];
};

#define  MAIN_CLOCK_MHz    200.0          // 200MHz

//#define FREQ_60Hz        1            // Main Freq 1 = 60Hz | 0 = 50Hz
//#define FREQ_60Hz_CLOCK     (float)1000000/60/64  // 60Hz 1/60=0.016666/128=130.208 usec
//#define FREQ_50Hz_CLOCK     (float)1000000/50/64  // 50Hz 1/50=0.02/128=156.25 usec
//#define FREQ_60Hz_CLOCK     (float)1000000/60/128   // 60Hz 1/60=0.016666/128=130.208 usec
//#define FREQ_50Hz_CLOCK     (float)1000000/50/128   // 50Hz 1/50=0.02/128=156.25 usec

enum FREQ
{
  eFREQ_60Hz,
  eFREQ_50Hz    //,
};

enum GpioPinMapping
{
// Pin Name              Number   In/Out             GPIO
//                                /Mux    Index
  P0,                 // 0        o       0       // NC
  I_nLINK_LED,        // 1        i       0       // nLinkLED
  I_nTX_LED,          // 2        i       0       // nTxLED
  O_J0,               // 3        o       0       // J0
  O_J1,               // 4        o       0       // J1
  O_J2,               // 5        o       0       // J2
  O_J3,               // 6        o       0       // J3
  O_WDT_DIS,          // 7        o       0       // 1: WDT Disable(bootloader 등등)
  DEBUG_TX,           // 8        m       6       // Debug(RS-232) TX
  DEBUG_RX,           // 9        m       6       // Debug(RS-232) RS
  I_DI1,              // 10       i       0       // DI1
  I_DI2,              // 11       i       0       // DI2
  I_KEY1,             // 12       i       0       // Key1
  I_KEY2,             // 13       i       0       // Key2
  I_KEY3,             // 14       i       0       // Key3
  I_KEY4,             // 15       i       0       // Key4
  P16,                // 16       o       0       // NC
  O_LD_RUN,           // 17       o       0       // LED Run
  O_LD_ALM,           // 18       o       0       // LED Alarm
  P19,                // 19       o       0       // NC
  O_LD_ERR,           // 20       o       0       // LED Error
  O_LD_PWR,           // 21       o       0       // LED Power
  P22,                // 22       o       0       // NC
  I_MON_N5V,          // 23       i       0       // MON -5V
  I_MON_N15V,         // 24       i       0       // MON -15V
  I_MON_P15V,         // 25       i       0       // MON +15V
  P26,                // 26       o       0       // NC
  P27,                // 27       o       0       // NC
  nEM1CS4,            // 28       m       ?       // nEM1CS4   W5300
  I_ETH_INT,          // 29       i       0       // ETH_INT
  P30,                // 30       o       0       // NC
  nEM1WE,             // 31       m       2       // nEM1WE   WR
  P32,                // 32       o       0       // NC
  O_ADC_CONV,         // 33       o       0       // ADC Convst
  nEM1CS2,            // 34       m       2       // nEM1CS2  MPRAM
  nEM1CS3,            // 35       m       2       // nEM1CS3  ADC
  I_ADC_BUSY,         // 36       i       0       // ADC Busy
  nEM1OE,             // 37       m       2       // nEM1OE   RD
  EM1A0,              // 38       m       2       // EM1A0
  EM1A1,              // 39       m       2       // EM1A1
  EM1A2,              // 40       m       2       // EM1A2
  EM1A3,              // 41       m       2       // EM1A3
  O_LD_GRE,           // 42       o       ?       // LED Green
  O_LD_RED,           // 43       o       ?       // LED Red
  EM1A4,              // 44       m       2       // EM1A4
  EM1A5,              // 45       m       2       // EM1A5
  EM1A6,              // 46       m       2       // EM1A6
  EM1A7,              // 47       m       2       // EM1A7
  EM1A8,              // 48       m       2       // EM1A8
  EM1A9,              // 49       m       2       // EM1A9
  EM1A10,             // 50       m       2       // EM1A10
  EM1A11,             // 51       m       2       // EM1A11
  EM1A12,             // 52       m       2       // EM1A12
  O_TP20,             // 53       o       0       // TP20
  O_TP17,             // 54       o       0       // TP17
  O_TP16,             // 55       o       0       // TP16
  O_TP15,             // 56       o       0       // TP15
  P57,                // 57       o       0       // NC
  P58,                // 58       o       0       // NC
  P59,                // 59       o       0       // NC
  P60,                // 60       o       0       // NC
  P61,                // 61       o       0       // NC
  O_RTC_CE,           // 62       o       0       // RTC CE
  O_RTC_SCK,          // 63       o       0       // RTC SCK
  IO_RTC_IO,          // 64       io      0       // RTC IO
  P65,                // 65       o       0       // NC
  O_nETH_RST,         // 66       o       0       // nETH Reset
  O_ADC_RST,          // 67       o       0       // ADC Reset
  P68,                // 68       o       0       // NC
  EM1D15,             // 69       m       2       // EM1D15
  EM1D14,             // 70       m       2       // EM1D14
  EM1D13,             // 71       m       2       // EM1D13
  EM1D12,             // 72       m       2       // EM1D12
  EM1D11,             // 73       m       2       // EM1D11
  EM1D10,             // 74       m       2       // EM1D10
  EM1D9,              // 75       m       2       // EM1D9
  EM1D8,              // 76       m       2       // EM1D8
  EM1D7,              // 77       m       2       // EM1D7
  EM1D6,              // 78       m       2       // EM1D6
  EM1D5,              // 79       m       2       // EM1D5
  EM1D4,              // 80       m       2       // EM1D4
  EM1D3,              // 81       m       2       // EM1D3
  EM1D2,              // 82       m       2       // EM1D2
  EM1D1,              // 83       m       2       // EM1D1
  BOOT0,              // 84       m       2       // BOOT0(GPIO84)
  EM1D0,              // 85       m       2       // EM1D0
  EM1A13,             // 86       m       2       // EM1A13
  EM1A14,             // 87       m       2       // EM1A14
  EM1A15,             // 88       m       2       // EM1A15
  EM1A16,             // 89       m       2       // EM1A16
  EM1A17,             // 90       m       2       // EM1A17
  EM1A18,             // 91       m       2       // EM1A18
  EM1A19,             // 92       m       2       // EM1A19
  I_MON_P24V,         // 93       i       0       // MON +24V
  O_WDT_TRIG,         // 94       o       0       // WDT Trig
  P95,                // 95~98    x       x       // not pin
  P99 = 99,           // 99       o       0       // NC
  eNC100,             // 100~132  x       x       // not pin
  P133 = 133    //, // 133      x       x       // 설정하지 마시요.
};

// Input
#define nLINK_LED           GpioDataRegs.GPADAT.bit.GPIO1       // 1        i       0       // nLinkLED
#define nTX_LED             GpioDataRegs.GPADAT.bit.GPIO2       // 2        i       0       // nTxLED
#define DI1                 GpioDataRegs.GPADAT.bit.GPIO10      // 10       i       0       // DI1
#define DI2                 GpioDataRegs.GPADAT.bit.GPIO11      // 11       i       0       // DI2
#define KEY1                GpioDataRegs.GPADAT.bit.GPIO12      // 12       i       0       // Key1
#define KEY2                GpioDataRegs.GPADAT.bit.GPIO13      // 13       i       0       // Key2
#define KEY3                GpioDataRegs.GPADAT.bit.GPIO14      // 14       i       0       // Key3
#define KEY4                GpioDataRegs.GPADAT.bit.GPIO15      // 15       i       0       // Key4
#define MON_N5V             GpioDataRegs.GPADAT.bit.GPIO23      // 23       i       0       // MON -5V
#define MON_N15V            GpioDataRegs.GPADAT.bit.GPIO24      // 24       i       0       // MON -15V
#define MON_P15V            GpioDataRegs.GPADAT.bit.GPIO25      // 25       i       0       // MON +15V
#define ETH_INT             GpioDataRegs.GPADAT.bit.GPIO29      // 29       i       0       // ETH_INT
#define ADC_BUSY            GpioDataRegs.GPBDAT.bit.GPIO36      // 36       i       0       // ADC Busy
#define RTC_IO              GpioDataRegs.GPCDAT.bit.GPIO64      // 64       io      0       // RTC IO
#define MON_P24V            GpioDataRegs.GPCDAT.bit.GPIO93      // 93       i       0       // MON +24V

// Output
#define J0_HI               GpioDataRegs.GPADAT.bit.GPIO3 = 1   // 3        o       0       // J0
#define J0_LO               GpioDataRegs.GPADAT.bit.GPIO3 = 0
#define J0_T                GpioDataRegs.GPATOGGLE.bit.GPIO3 = 1;
#define J1_HI               GpioDataRegs.GPADAT.bit.GPIO4 = 1   // 4        o       0       // J1
#define J1_LO               GpioDataRegs.GPADAT.bit.GPIO4 = 0
#define J1_T                GpioDataRegs.GPATOGGLE.bit.GPIO4 = 1;
#define J2_HI               GpioDataRegs.GPADAT.bit.GPIO5 = 1   // 5        o       0       // J2
#define J2_LO               GpioDataRegs.GPADAT.bit.GPIO5 = 0
#define J2_T                GpioDataRegs.GPATOGGLE.bit.GPIO5 = 1;
#define J3_HI               GpioDataRegs.GPADAT.bit.GPIO6 = 1   // 6        o       0       // J3
#define J3_LO               GpioDataRegs.GPADAT.bit.GPIO6 = 0
#define J3_T                GpioDataRegs.GPATOGGLE.bit.GPIO6 = 1;
#define WDT_DIS_HI          GpioDataRegs.GPADAT.bit.GPIO7 = 1   // 7        o       0       // 1: WDT Disable(bootloader 등등)
#define WDT_DIS_LO          GpioDataRegs.GPADAT.bit.GPIO7 = 0
#define WDT_DIS_T           GpioDataRegs.GPATOGGLE.bit.GPIO7 = 1;
#define LD_ERR_HI           GpioDataRegs.GPADAT.bit.GPIO17 = 1  // 17       o       0       // LED Power
#define LD_ERR_LO           GpioDataRegs.GPADAT.bit.GPIO17 = 0
#define LD_ERR_T            GpioDataRegs.GPATOGGLE.bit.GPIO17 = 1;
#define LD_ALM_HI           GpioDataRegs.GPADAT.bit.GPIO18 = 1  // 18       o       0       // LED Error
#define LD_ALM_LO           GpioDataRegs.GPADAT.bit.GPIO18 = 0
#define LD_ALM_T            GpioDataRegs.GPATOGGLE.bit.GPIO18 = 1;
#define LD_RUN_HI           GpioDataRegs.GPADAT.bit.GPIO20 = 1  // 20       o       0       // LED Alarm
#define LD_RUN_LO           GpioDataRegs.GPADAT.bit.GPIO20 = 0
#define LD_RUN_T            GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1;
#define LD_PWR_HI           GpioDataRegs.GPADAT.bit.GPIO21 = 1  // 21       o       0       // LED Run
#define LD_PWR_LO           GpioDataRegs.GPADAT.bit.GPIO21 = 0
#define LD_PWR_T            GpioDataRegs.GPATOGGLE.bit.GPIO21 = 1;
#define ADC_CONV_HI         GpioDataRegs.GPBDAT.bit.GPIO33 = 1  // 33       o       0       // ADC Convst
#define ADC_CONV_LO         GpioDataRegs.GPBDAT.bit.GPIO33 = 0
#define ADC_CONV_T          GpioDataRegs.GPBTOGGLE.bit.GPIO33 = 1;
#define LD_GRE_HI           GpioDataRegs.GPBDAT.bit.GPIO42 = 1  // 42       o       ?       // LED Green
#define LD_GRE_LO           GpioDataRegs.GPBDAT.bit.GPIO42 = 0
#define LD_GRE_T            GpioDataRegs.GPBTOGGLE.bit.GPIO42 = 1;
#define LD_RED_HI           GpioDataRegs.GPBDAT.bit.GPIO43 = 1  // 43       o       ?       // LED Red
#define LD_RED_LO           GpioDataRegs.GPBDAT.bit.GPIO43 = 0
#define LD_RED_T            GpioDataRegs.GPBTOGGLE.bit.GPIO43 = 1;
#define TP20_HI             GpioDataRegs.GPBDAT.bit.GPIO53 = 1  // 53       o       0       // TP20
#define TP20_LO             GpioDataRegs.GPBDAT.bit.GPIO53 = 0
#define TP20_T              GpioDataRegs.GPBTOGGLE.bit.GPIO53 = 1;
#define TP17_HI             GpioDataRegs.GPBDAT.bit.GPIO54 = 1  // 54       o       0       // TP17
#define TP17_LO             GpioDataRegs.GPBDAT.bit.GPIO54 = 0
#define TP17_T              GpioDataRegs.GPBTOGGLE.bit.GPIO54 = 1;
#define TP16_HI             GpioDataRegs.GPBDAT.bit.GPIO55 = 1  // 55       o       0       // TP16
#define TP16_LO             GpioDataRegs.GPBDAT.bit.GPIO55 = 0
#define TP16_T              GpioDataRegs.GPBTOGGLE.bit.GPIO55 = 1;
#define TP15_HI             GpioDataRegs.GPBDAT.bit.GPIO56 = 1  // 56       o       0       // TP15
#define TP15_LO             GpioDataRegs.GPBDAT.bit.GPIO56 = 0
#define TP15_T              GpioDataRegs.GPBTOGGLE.bit.GPIO56 = 1;
#define RTC_CE_HI           GpioDataRegs.GPBDAT.bit.GPIO62 = 1  // 62       o       0       // RTC CE
#define RTC_CE_LO           GpioDataRegs.GPBDAT.bit.GPIO62 = 0
#define RTC_CE_T            GpioDataRegs.GPBTOGGLE.bit.GPIO62 = 1;
#define RTC_SCK_HI          GpioDataRegs.GPBDAT.bit.GPIO63 = 1  // 63       o       0       // RTC SCK
#define RTC_SCK_LO          GpioDataRegs.GPBDAT.bit.GPIO63 = 0
#define RTC_SCK_T           GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
#define RTC_IO_HI           GpioDataRegs.GPCDAT.bit.GPIO64 = 1  // 64       o       0       // RTC IO
#define RTC_IO_LO           GpioDataRegs.GPCDAT.bit.GPIO64 = 0
#define RTC_IO_T            GpioDataRegs.GPCTOGGLE.bit.GPIO64 = 1;
#define nETH_RST_HI         GpioDataRegs.GPCDAT.bit.GPIO66 = 1  // 66       o       0       // nETH Reset
#define nETH_RST_LO         GpioDataRegs.GPCDAT.bit.GPIO66 = 0
#define nETH_RST_T          GpioDataRegs.GPCTOGGLE.bit.GPIO66 = 1;
#define ADC_RST_HI          GpioDataRegs.GPCDAT.bit.GPIO67 = 1  // 67       o       0       // ADC Reset
#define ADC_RST_LO          GpioDataRegs.GPCDAT.bit.GPIO67 = 0
#define ADC_RST_T           GpioDataRegs.GPCTOGGLE.bit.GPIO67 = 1;
#define WDT_TRIG_HI         GpioDataRegs.GPCDAT.bit.GPIO94 = 1  // 94       o       0       // WDT Trig
#define WDT_TRIG_LO         GpioDataRegs.GPCDAT.bit.GPIO94 = 0
#define WDT_TRIG_T          GpioDataRegs.GPCTOGGLE.bit.GPIO94 = 1;



enum
{
    eON_DELAY_100MS     = BIT0,
    eON_DELAY_200MS     = BIT1,
    eON_DELAY_300MS     = BIT2,
    eON_DELAY_400MS     = BIT3,
    eON_DELAY_500MS     = BIT4,
    eON_DELAY_600MS     = BIT5,
    eON_DELAY_700MS     = BIT6,
    eON_DELAY_800MS     = BIT7,
    eON_DELAY_900MS     = BIT8,
    eON_DELAY_1000MS    = BIT9,
    eON_DELAY_1100MS    = BIT10,
    eON_DELAY_1200MS    = BIT11,
    eON_DELAY_1300MS    = BIT12,
    eON_DELAY_1400MS    = BIT13,
    eON_DELAY_1500MS    = BIT14,
    eON_DELAY_1600MS    = BIT15,
    eON_DELAY_1700MS    = BIT16,
    eON_DELAY_1800MS    = BIT17,
    eON_DELAY_1900MS    = BIT18,
    eON_DELAY_2000MS    = BIT19,
    eON_DELAY_2100MS    = BIT20,
    eON_DELAY_2200MS    = BIT21,
    eON_DELAY_2300MS    = BIT22,
    eON_DELAY_2400MS    = BIT23,
    eON_DELAY_2500MS    = BIT24,
    eON_DELAY_2600MS    = BIT25,
    eON_DELAY_2700MS    = BIT26,
    eON_DELAY_2800MS    = BIT27,
    eON_DELAY_2900MS    = BIT28,
    eON_DELAY_3000MS    = BIT29,
    eON_DELAY_3100MS    = BIT30,
    eON_DELAY_3200MS    = BIT31,
};
enum
{
    eON_DELAY_1S        = BIT0,
    eON_DELAY_2S        = BIT1,
    eON_DELAY_3S        = BIT2,
    eON_DELAY_4S        = BIT3,
    eON_DELAY_5S        = BIT4,
    eON_DELAY_6S        = BIT5,
    eON_DELAY_7S        = BIT6,
    eON_DELAY_8S        = BIT7,
    eON_DELAY_9S        = BIT8,
    eON_DELAY_10S       = BIT9,
    eON_DELAY_11S       = BIT10,
    eON_DELAY_12S       = BIT11,
    eON_DELAY_13S       = BIT12,
    eON_DELAY_14S       = BIT13,
    eON_DELAY_15S       = BIT14,
    eON_DELAY_16S       = BIT15,
};







typedef struct
{
// 0x00100000 ~ 0x0010CFFF(0x0000CFFF) 까지 설정값
  UINT16    wStartH;        // NC
  UINT16    wStartH_1;
  UINT16    wStartL;
  UINT16    wStartL_1;
  UINT16    wSerialH;       // Memory Map 정렬
  UINT16    wSerialH_1;
  UINT16    wSerialL;
  UINT16    wSerialL_1;
  UINT16    wMagic;         // Magic Code
  UINT16    wMagic_1;
  UINT16    wClear;         // Clear Code
  UINT16    wClear_1;
  UINT16    wPcb;           // PCB No
  UINT16    wPcb_1;
  UINT16    wVer;           // Version No
  UINT16    wVer_1;
  UINT16    wYYYY;          // Version YYYY
  UINT16    wYYYY_1;
  UINT16    wMMDD;          // Version MMDD
  UINT16    wMMDD_1;
  UINT16    wN010;
  UINT16    wN010_1;
  UINT16    wN011;
  UINT16    wN011_1;
  UINT16    wEv;            // Event Point No (-1: No Event, 0~99: 100개의 Event)
  UINT16    wEv_1;
  UINT16    wFaNum;
  UINT16    wFaNum_1;
  UINT16    wFaMb;          // Fault Modbus Point No (-1: No Fault, 0~25: 26개의 Fault 중 앞 20개만 사용, 6개는 버퍼)
  UINT16    wFaMb_1;
  UINT16    wFaEnd;         // Fault 저장 목표
  UINT16    wFaEnd_1;
  UINT16    wPass;
  UINT16    wPass_1;
  UINT16    wPassXCs;
  UINT16    wPassXCs_1;
  UINT16    wId;
  UINT16    wId_1;
  UINT16    wBps;
  UINT16    wBps_1;
  UINT16    wN020;
  UINT16    wN020_1;
  UINT16    wN021;
  UINT16    wN021_1;
  UINT16    wN022;
  UINT16    wN022_1;
  UINT16    wN023;
  UINT16    wN023_1;
  UINT16    wN024;
  UINT16    wN024_1;
  UINT16    wN025;
  UINT16    wN025_1;
  UINT16    wCommXCs;
  UINT16    wCommXCs_1;
  UINT16    wN027;
  UINT16    wN027_1;
  UINT16    ilUtc;                  // 28
  UINT16    ilUtc_1;
  UINT16    ilUtcLo;                // 29
  UINT16    ilUtcLo_1;
  UINT16    lUtcMs;                 // 30
  UINT16    lUtcMs_1;
  UINT16    lUtcMsLo;               // 31
  UINT16    lUtcMsLo_1;

  UINT16    wModel[8*2];            // 32
/*
  UINT16    wModel0001;             // 32
  UINT16    wModel0001_1;
  UINT16    wModel0203;
  UINT16    wModel0203_1;
  UINT16    wModel0405;
  UINT16    wModel0405_1;
  UINT16    wModel0607;
  UINT16    wModel0607_1;
  UINT16    wModel0809;
  UINT16    wModel0809_1;
  UINT16    wModel1011;
  UINT16    wModel1011_1;
  UINT16    wModel1213;
  UINT16    wModel1213_1;
  UINT16    wModel1415;
  UINT16    wModel1415_1;
*/

  UINT16    wSerial[16*2];          // 40
/*
  UINT16    wSerial0001;            // 40
  UINT16    wSerial0001_1;
  UINT16    wSerial0203;
  UINT16    wSerial0203_1;
  UINT16    wSerial0405;
  UINT16    wSerial0405_1;
  UINT16    wSerial0607;
  UINT16    wSerial0607_1;
  UINT16    wSerial0809;
  UINT16    wSerial0809_1;
  UINT16    wSerial1011;
  UINT16    wSerial1011_1;
  UINT16    wSerial1213;
  UINT16    wSerial1213_1;
  UINT16    wSerial1415;
  UINT16    wSerial1415_1;
  UINT16    wSerial1617;
  UINT16    wSerial1617_1;
  UINT16    wSerial1819;
  UINT16    wSerial1819_1;
  UINT16    wSerial2021;
  UINT16    wSerial2021_1;
  UINT16    wSerial2223;
  UINT16    wSerial2223_1;
  UINT16    wSerial2425;
  UINT16    wSerial2425_1;
  UINT16    wSerial2627;
  UINT16    wSerial2627_1;
  UINT16    wSerial2829;
  UINT16    wSerial2829_1;
  UINT16    wSerial3031;
  UINT16    wSerial3031_1;
*/

  UINT16    wIpAddr[2*2];         // 192.168.10.100  // 56
  UINT16    wSubMask[2*2];        // 255.255.255.0
  UINT16    wDefGate[2*2];        // 192.168.10.1
  UINT16    wPortNum;             // 
  UINT16    wPortNum_1;           // 
  UINT16    wLocIpAddr[2*2];      // 192.168.10.100
/*
  UINT16    wIpAddrH;             // 192.168  // 56
  UINT16    wIpAddrH_1;           // 
  UINT16    wIpAddrL;             // 10.100
  UINT16    wIpAddrL_1;           // 
  UINT16    wSubMaskH;            // 255.255
  UINT16    wSubMaskH_1;          // 
  UINT16    wSubMaskL;            // 255.0
  UINT16    wSubMaskL_1;          // 
  UINT16    wDefGateH;            // 192.168
  UINT16    wDefGateH_1;          // 
  UINT16    wDefGateL;            // 10.1
  UINT16    wDefGateL_1;          // 
  UINT16    wPortNum;             // 
  UINT16    wPortNum_1;           // 
  UINT16    wLocIpAddrH;          // 192.168
  UINT16    wLocIpAddrH_1;        // 
  UINT16    wLocIpAddrL;          // 10.100
  UINT16    wLocIpAddrL_1;        // 
*/
  UINT16    wN65;                 // 65
  UINT16    wN65_1;               //
  UINT16    wN66;                 // 66
  UINT16    wN66_1;               //
  UINT16    wN67;                 // 67
  UINT16    wN67_1;               //
  UINT16    wN68;                 // 68
  UINT16    wN68_1;               //
  UINT16    wN69;                 // 69
  UINT16    wN69_1;               //
  UINT16    wN70;                 // 70
  UINT16    wN70_1;               //
  UINT16    wEthXCs;              // 71
  UINT16    wEthXCs_1;            //

  UINT16    wTrig;                // TrigTime(Trigger 전 파형 저장 시간) (msec)  // 72
  UINT16    wTrig_1;              // 
  UINT16    wTrigXCs;             // 73
  UINT16    wTrigXCs_1;           //

  UINT16    wDebo;                // Di Debounce Time (msec)  // 74
  UINT16    wDebo_1;              // 
  UINT16    wDeboXCs;             // 75
  UINT16    wDeboXCs_1;           //

  UINT16    wNo100ms;             // 76 
  UINT16    wNo100ms_1;           //    
  UINT16    wNo500ms;             // 77 
  UINT16    wNo500ms_1;           //    
  UINT16    wNoXCs;               // 78 
  UINT16    wNoXCs_1;             //    

// DC 차단기 Trip 전류 
  UINT16    wTrip[3*2];           // 79, 80, 81
  UINT16    wTripXCs;             // 82 
  UINT16    wTripXCs_1;           //    
  UINT16    wChat;                // 83 
  UINT16    wChat_1;              //    
/*
  UINT16    wN79;                 // 79 
  UINT16    wN79_1;               //    
  UINT16    wN80;                 // 80 
  UINT16    wN80_1;               //    
  UINT16    wN81;                 // 81 
  UINT16    wN81_1;               //    
  UINT16    wN82;                 // 82 
  UINT16    wN82_1;               //    
  UINT16    wN83;                 // 83 
  UINT16    wN83_1;               //    
*/

  UINT16    wN84;                 // 84 
  UINT16    wN84_1;               //    
  UINT16    wN85;                 // 85 
  UINT16    wN85_1;               //    
  UINT16    wN86;                 // 86 
  UINT16    wN86_1;               //    
  UINT16    wN87;                 // 87 
  UINT16    wN87_1;               //    
  UINT16    wN88;                 // 88 
  UINT16    wN88_1;               //    
  UINT16    wN89;                 // 89 
  UINT16    wN89_1;               //    
  UINT16    wN90;                 // 90 
  UINT16    wN90_1;               //    
  UINT16    wN91;                 // 91 
  UINT16    wN91_1;               //    
  UINT16    wN92;                 // 92 
  UINT16    wN92_1;               //    
  UINT16    wN93;                 // 93 
  UINT16    wN93_1;               //    
  UINT16    wN94;                 // 94 
  UINT16    wN94_1;               //    
  UINT16    wN95;                 // 95 
  UINT16    wN95_1;               //    
/*
  UINT16    wCh0ZeR;              // 96
  UINT16    wCh0ZeR_1;            //    
  UINT16    wCh1ZeR;              // 97
  UINT16    wCh1ZeR_1;            //    
  UINT16    wCh2ZeR;              // 98 
  UINT16    wCh2ZeR_1;            //    
  UINT16    wCh3ZeR;              // 99 
  UINT16    wCh3ZeR_1;            //    
  UINT16    wCh4ZeR;              // 100
  UINT16    wCh4ZeR_1;            //    
  UINT16    wCh5ZeR;              // 101
  UINT16    wCh5ZeR_1;            //    
  UINT16    wCh6ZeR;              // 102
  UINT16    wCh6ZeR_1;            //    
  UINT16    wCh7ZeR;              // 103
  UINT16    wCh7ZeR_1;            //    
*/
  UINT16    wZeR[8*2];            // 96 ~ 103
  UINT16    wZeRDcXCs;            // 104
  UINT16    wZeRDcXCs_1;          //    
  UINT16    wZeRAcXCs;            // 105
  UINT16    wZeRAcXCs_1;          //    

/*
  UINT16    wCo0SpR;              // 106
  UINT16    wCo0SpR_1;            //    
  UINT16    wCh1SpR;              // 107
  UINT16    wCh1SpR_1;            //    
  UINT16    wCh2SpR;              // 108
  UINT16    wCh2SpR_1;            //    
  UINT16    wCh3SpR;              // 109
  UINT16    wCh3SpR_1;            //    
  UINT16    wCh4SpR;              // 110
  UINT16    wCh4SpR_1;            //    
  UINT16    wCh5SpR;              // 111
  UINT16    wCh5SpR_1;            //    
  UINT16    wCh6SpR;              // 112
  UINT16    wCh6SpR_1;            //    
  UINT16    wCh7SpR;              // 113
  UINT16    wCh7SpR_1;            //    
*/
  UINT16    wSpR[8*2];            // 106 ~ 113
  UINT16    wSpRDcXCs;            // 114
  UINT16    wSpRDcXCs_1;          //    
  UINT16    wSpRAcXCs;            // 115
  UINT16    wSpRAcXCs_1;          //    

  UINT16    wN116;                // 116
  UINT16    wN116_1;              //    
  UINT16    wN117;                // 117
  UINT16    wN117_1;              //    
  UINT16    wN118;                // 118
  UINT16    wN118_1;              //    
  UINT16    wN119;                // 119
  UINT16    wN119_1;              //    
  UINT16    wN120;                // 120
  UINT16    wN120_1;              //    
  UINT16    wN121;                // 121
  UINT16    wN121_1;              //    
  UINT16    wN122;                // 122
  UINT16    wN122_1;              //    
  UINT16    wN123;                // 123
  UINT16    wN123_1;              //    
  UINT16    wN124;                // 124
  UINT16    wN124_1;              //    
  UINT16    wN125;                // 125
  UINT16    wN125_1;              //    
  UINT16    wN126;                // 126
  UINT16    wN126_1;              //    
  UINT16    wN127;                // 127
  UINT16    wN127_1;              //    
                                        
/*
  UINT16    fCh0Zero_H;           // 128
  UINT16    fCh0Zero_H1;          //    
  UINT16    fCh0Zero_L;           // 129
  UINT16    fCh0Zero_L1;          //    
  UINT16    fCh1Zero_H;           // 130
  UINT16    fCh1Zero_H1;          //    
  UINT16    fCh1Zero_L;           // 131
  UINT16    fCh1Zero_L1;          //    
  UINT16    fCh2Zero_H;           // 132
  UINT16    fCh2Zero_H1;          //    
  UINT16    fCh2Zero_L;           // 133
  UINT16    fCh2Zero_L1;          //    
  UINT16    fCh3Zero_H;           // 134
  UINT16    fCh3Zero_H1;          //    
  UINT16    fCh3Zero_L;           // 135
  UINT16    fCh3Zero_L1;          //    
  UINT16    fCh4Zero_H;           // 136
  UINT16    fCh4Zero_H1;          //    
  UINT16    fCh4Zero_L;           // 137
  UINT16    fCh4Zero_L1;          //    
  UINT16    fCh5Zero_H;           // 138
  UINT16    fCh5Zero_H1;          //    
  UINT16    fCh5Zero_L;           // 139
  UINT16    fCh5Zero_L1;          //    
  UINT16    fCh6Zero_H;           // 140
  UINT16    fCh6Zero_H1;          //    
  UINT16    fCh6Zero_L;           // 141
  UINT16    fCh6Zero_L1;          //    
  UINT16    fCh7Zero_H;           // 142
  UINT16    fCh7Zero_H1;          //    
  UINT16    fCh7Zero_L;           // 143
  UINT16    fCh7Zero_L1;          //    
*/
  UINT16    fZe[8*2*2];           // 128 ~ 143
  UINT16    wZeDcXCs;             // 144
  UINT16    wZeDcXCs_1;           //    
  UINT16    wZeAcXCs;             // 145
  UINT16    wZeAcXCs_1;           //    
                                        
/*
  UINT16    fCh0Span_H;           // 146
  UINT16    fCh0Span_H1;          //       
  UINT16    fCh0Span_L;           // 147
  UINT16    fCh0Span_L1;          //    
  UINT16    fCh1Span_H;           // 148
  UINT16    fCh1Span_H1;          //    
  UINT16    fCh1Span_L;           // 149
  UINT16    fCh1Span_L1;          //    
  UINT16    fCh2Span_H;           // 150
  UINT16    fCh2Span_H1;          //    
  UINT16    fCh2Span_L;           // 151
  UINT16    fCh2Span_L1;          //    
  UINT16    fCh3Span_H;           // 152
  UINT16    fCh3Span_H1;          //    
  UINT16    fCh3Span_L;           // 153
  UINT16    fCh3Span_L1;          //    
  UINT16    fCh4Span_H;           // 154
  UINT16    fCh4Span_H1;          //    
  UINT16    fCh4Span_L;           // 155
  UINT16    fCh4Span_L1;          //    
  UINT16    fCh5Span_H;           // 156
  UINT16    fCh5Span_H1;          //    
  UINT16    fCh5Span_L;           // 157
  UINT16    fCh5Span_L1;          //    
  UINT16    fCh6Span_H;           // 158
  UINT16    fCh6Span_H1;          //    
  UINT16    fCh6Span_L;           // 159
  UINT16    fCh6Span_L1;          //    
  UINT16    fCh7Span_H;           // 160
  UINT16    fCh7Span_H1;          //    
  UINT16    fCh7Span_L;           // 161
  UINT16    fCh7Span_L1;          //
*/
  UINT16    fSp[8*2*2];           // 146 ~161
  UINT16    wSpDcXCs;             // 162
  UINT16    wSpDcXCs_1;           //
  UINT16    wSpAcXCs;             // 163
  UINT16    wSpAcXCs_1;           //

/*
  UINT16    fCh0Phase_H;          // 164
  UINT16    fCh0Phase_H1;         //       
  UINT16    fCh0Phase_L;          // 165
  UINT16    fCh0Phase_L1;         //    
  UINT16    fCh1Phase_H;          // 166
  UINT16    fCh1Phase_H1;         //     
  UINT16    fCh1Phase_L;          // 167
  UINT16    fCh1Phase_L1;         //    
  UINT16    fCh2Phase_H;          // 168
  UINT16    fCh2Phase_H1;         //    
  UINT16    fCh2Phase_L;          // 169
  UINT16    fCh2Phase_L1;         //    
  UINT16    fCh3Phase_H;          // 160
  UINT16    fCh3Phase_H1;         //    
  UINT16    fCh3Phase_L;          // 171
  UINT16    fCh3Phase_L1;         //    
  UINT16    fCh4Phase_H;          // 172
  UINT16    fCh4Phase_H1;         //    
  UINT16    fCh4Phase_L;          // 173
  UINT16    fCh4Phase_L1;         //    
  UINT16    fCh5Phase_H;          // 174
  UINT16    fCh5Phase_H1;         //    
  UINT16    fCh5Phase_L;          // 175
  UINT16    fCh5Phase_L1;         //    
  UINT16    fCh6Phase_H;          // 176
  UINT16    fCh6Phase_H1;         //    
  UINT16    fCh6Phase_L;          // 177
  UINT16    fCh6Phase_L1;         //    
  UINT16    fCh7Phase_H;          // 178
  UINT16    fCh7Phase_H1;         //   
  UINT16    fCh7Phase_L;          // 179
  UINT16    fCh7Phase_L1;         //
*/
  UINT16    fPh[8*2*2];           // 164 ~ 179
  UINT16    wN180;                // 180
  UINT16    wN180_1;              //    
  UINT16    wPhXCs;               // 181
  UINT16    wPhXCs_1;             //

/*
  UINT16    fCh0Ratio_H;          // 182
  UINT16    fCh0Ratio_H1;         //       
  UINT16    fCh0Ratio_L;          // 183
  UINT16    fCh0Ratio_L1;         //    
  UINT16    fCh1Ratio_H;          // 184
  UINT16    fCh1Ratio_H1;         //     
  UINT16    fCh1Ratio_L;          // 185
  UINT16    fCh1Ratio_L1;         //  
  UINT16    fCh2Ratio_H;          // 186
  UINT16    fCh2Ratio_H1;         //  
  UINT16    fCh2Ratio_L;          // 187
  UINT16    fCh2Ratio_L1;         //  
  UINT16    fCh3Ratio_H;          // 188
  UINT16    fCh3Ratio_H1;         //  
  UINT16    fCh3Ratio_L;          // 189
  UINT16    fCh3Ratio_L1;         //  
  UINT16    fCh4Ratio_H;          // 190
  UINT16    fCh4Ratio_H1;         //    
  UINT16    fCh4Ratio_L;          // 191
  UINT16    fCh4Ratio_L1;         //  
  UINT16    fCh5Ratio_H;          // 192
  UINT16    fCh5Ratio_H1;         //  
  UINT16    fCh5Ratio_L;          // 193
  UINT16    fCh5Ratio_L1;         //  
  UINT16    fCh6Ratio_H;          // 194
  UINT16    fCh6Ratio_H1;         //  
  UINT16    fCh6Ratio_L;          // 195
  UINT16    fCh6Ratio_L1;         //  
  UINT16    fCh7Ratio_H;          // 196
  UINT16    fCh7Ratio_H1;         //  
  UINT16    fCh7Ratio_L;          // 197
  UINT16    fCh7Ratio_L1;         //
*/
  UINT16    fRatio[8*2*2];        // 182 ~ 197
  UINT16    wDcRatioXCs;          // 198
  UINT16    wDcRatioXCs_1;        //
  UINT16    wAcRatioXCs;          // 199
  UINT16    wAcRatioXCs_1;        //

/*
  UINT16    wMac0_;               // 200
  UINT16    wMac0_1;              //       
  UINT16    wMac2_;               // 202
  UINT16    wMac2_1;              //       
  UINT16    wMac4_;               // 204
  UINT16    wMac4_1;              //       
*/
  UINT16    wMac[3*2];            // 200
  UINT16    wMacXCs;              // 206
  UINT16    wMacXCs_1;            //

} MRAM_DATA;
extern MRAM_DATA *pMram;

#define eFAULT_EMPTY        65535
#define eEVENT_EMPTY        65535
enum
{
  eEV_EMPTY,
  eEV_ERASE,
  eEV_PWR_ON,
  eEV_PWR_OFF,
  eEV_N5V_FA,
  eEV_N5V_CL,
  eEV_N15V_FA,
  eEV_N15V_CL,
  eEV_P15V_FA,
  eEV_P15V_CL,
  eEV_P24V_FA,
  eEV_P24V_CL,
  eEV_SV_FA,
  eEV_SV_CL,
  eEV_ADC_FA,
  eEV_ADC_CL,
  eEV_ADC1_FA,
  eEV_ADC1_CL,
  eEV_ADC2_FA,
  eEV_ADC2_CL,
  eEV_ADC3_FA,
  eEV_ADC3_CL,
  eEV_ADC4_FA,
  eEV_ADC4_CL,
  eEV_ADC5_FA,
  eEV_ADC5_CL,
  eEV_ADC6_FA,
  eEV_ADC6_CL,
  eEV_ADC7_FA,
  eEV_ADC7_CL,
  eEV_ADC8_FA,
  eEV_ADC8_CL,
};
enum
{
  eEV_NO,
  eEV_NO_1,
  eEV_TYPE,
  eEV_TYPE_1,
  eEV_UTC_H,
  eEV_UTC_H_1,
  eEV_UTC_L,
  eEV_UTC_L_1,
  eEV_UTCMS_H,
  eEV_UTCMS_H_1,
  eEV_UTCMS_L,
  eEV_UTCMS_L_1,
};
typedef struct
{
  UINT16      wNo;                    // No(0~99)
  UINT16      wNo_1;                  //
  UINT16      wType;                  // 전원 이상, ADC 이상, 
  UINT16      wType_1;                //
  UINT16      ilUtcH;                 // UTC+9
  UINT16      ilUtcH_1;
  UINT16      ilUtcL;
  UINT16      ilUtcL_1;
  UINT16      lUtcMsH;                // msec
  UINT16      lUtcMsH_1;
  UINT16      lUtcMsL;
  UINT16      lUtcMsL_1;
} EVENT_NO;
#define eEVENT_MAX      100           // Event 최대 저장 개수
//#define eEVENT_MAX      10           // Test Event 최대 저장 개수
typedef struct
{
// 0x0010D000 ~ 0x0010DFFF(0x00000FFF) 까지 Event 내역
  EVENT_NO    No[eEVENT_MAX];
} EVENT_DATA;
extern EVENT_DATA *pEvent;

typedef struct
{
  UINT16      wNo;                    // No(0~255)
  UINT16      wType;                  // type(Trip: 0x55, Close: 0xAA)
  UINT32      lTime;                  // Time (UTC+9)
  UINT32      lms;                    // msec
  float       fConectDutyA;           // Contect Duty A
  float       fConectDutyB;           // Contect Duty B
  float       fConectDutyC;           // Contect Duty C
  float       fTripCoil1PC;           // Trip Coil 1 Peak Current
  float       fTripCoil1CF;           // Trip Coil 1 Current Flow
  float       fTripCoil2PC;           // Trip Coil 2 Peak Current
  float       fTripCoil2CF;           // Trip Coil 2 Current Flow
  float       fCloseCoilPC;           // Close Coil Peak Current
  float       fCloseCoilCF;           // Close Coil Current Flow
  float       fAContectRunTime;       // A접점 동작 시간
  float       fBContectRunTime;       // B접점 동작 시간
  float       fACloseTripTime;        // A상 차단/투입 시간
  float       fBCloseTripTime;        // B상 차단/투입 시간
  float       fCCloseTripTime;        // C상 차단/투입 시간
} FAULT_BUF;
typedef struct
{
  FAULT_BUF   BUF[6];                  // 버퍼 6개
} FAULT_REG;
extern FAULT_REG sFault;
enum
{
  eFA_EMPTY,
  eFA_TRIP1,
  eFA_TRIP2,
  eFA_CLOSE,
};
enum
{
  eFA_NO,
  eFA_NO_1,
  eFA_TYPE,
  eFA_TYPE_1,
  eFA_UTC_H,
  eFA_UTC_H_1,
  eFA_UTC_L,
  eFA_UTC_L_1,
  eFA_UTCMS_H,
  eFA_UTCMS_H_1,
  eFA_UTCMS_L,
  eFA_UTCMS_L_1,
  eFA_CONTDA_H,
  eFA_CONTDA_H_1,
  eFA_CONTDA_L,
  eFA_CONTDA_L_1,
  eFA_CONTDB_H,
  eFA_CONTDB_H_1,
  eFA_CONTDB_L,
  eFA_CONTDB_L_1,
  eFA_CONTDC_H,
  eFA_CONTDC_H_1,
  eFA_CONTDC_L,
  eFA_CONTDC_L_1,
  eFA_TC1PC_H,
  eFA_TC1PC_H_1,
  eFA_TC1PC_L,
  eFA_TC1PC_L_1,
  eFA_TC1CF_H,
  eFA_TC1CF_H_1,
  eFA_TC1CF_L,
  eFA_TC1CF_L_1,
  eFA_TC2PC_H,
  eFA_TC2PC_H_1,
  eFA_TC2PC_L,
  eFA_TC2PC_L_1,
  eFA_TC2CF_H,
  eFA_TC2CF_H_1,
  eFA_TC2CF_L,
  eFA_TC2CF_L_1,
  eFA_CC_PC_H,
  eFA_CC_PC_H_1,
  eFA_CC_PC_L,
  eFA_CC_PC_L_1,
  eFA_CC_CF_H,
  eFA_CC_CF_H_1,
  eFA_CC_CF_L,
  eFA_CC_CF_L_1,
  eFA_CC_A_H,
  eFA_CC_A_H_1,
  eFA_CC_A_L,
  eFA_CC_A_L_1,
  eFA_TC_B_H,
  eFA_TC_B_H_1,
  eFA_TC_B_L,
  eFA_TC_B_L_1,
  eFA_TC_CC_AH,
  eFA_TC_CC_AH_1,
  eFA_TC_CC_AL,
  eFA_TC_CC_AL_1,
  eFA_TC_CC_BH,
  eFA_TC_CC_BH_1,
  eFA_TC_CC_BL,
  eFA_TC_CC_BL_1,
  eFA_TC_CC_CH,
  eFA_TC_CC_CH_1,
  eFA_TC_CC_CL,
  eFA_TC_CC_CL_1,
};
typedef struct
{
  UINT16      wNo;                    // (UINT16) No(0~255) // 20개 인대 왜 256개를 프리카운터로 돌리는지?
  UINT16      wNo_1;                  //
  UINT16      wType;                  // (UINT16) type(Trip: 0x55, Close: 0xAA)
  UINT16      wType_1;                //
  UINT16      ilUtcH;                 // (INT32) Time Hi (UTC+9)
  UINT16      ilUtcH_1;
  UINT16      ilUtcL;
  UINT16      ilUtcL_1;
  UINT16      lUtcMsH;                // (UINT32) msec Hi
  UINT16      lUtcMsH_1;
  UINT16      lUtcMsL;
  UINT16      lUtcMsL_1;
  UINT16      fContDAH;               // (float) Contect Duty A Hi
  UINT16      fContDAH_1;
  UINT16      fContDAL;
  UINT16      fContDAL_1;
  UINT16      fContDBH;               // (float) Contect Duty B Hi
  UINT16      fContDBH_1;
  UINT16      fContDBL;
  UINT16      fContDBL_1;
  UINT16      fContDCH;               // (float) Contect Duty C Hi
  UINT16      fContDCH_1;
  UINT16      fContDCL;
  UINT16      fContDCL_1;
  UINT16      fTC1PCH;                // (float) Trip Coil 1 Peak Current Hi
  UINT16      fTC1PCH_1;
  UINT16      fTC1PCL;
  UINT16      fTC1PCL_1;
  UINT16      fTC1CFH;                // (float) Trip Coil 1 Current Flow Hi
  UINT16      fTC1CFH_1;
  UINT16      fTC1CFL;
  UINT16      fTC1CFL_1;
  UINT16      fTC2PCH;                // (float) Trip Coil 2 Peak Current Hi
  UINT16      fTC2PCH_1;
  UINT16      fTC2PCL;
  UINT16      fTC2PCL_1;
  UINT16      fTC2CFH;                // (float) Trip Coil 2 Current Flow Hi
  UINT16      fTC2CFH_1;
  UINT16      fTC2CFL;
  UINT16      fTC2CFL_1;
  UINT16      fCC_PCH;                // (float) Close Coil Peak Current Hi
  UINT16      fCC_PCH_1;
  UINT16      fCC_PCL;
  UINT16      fCC_PCL_1;
  UINT16      fCC_CFH;                // (float) Close Coil Current Flow Hi
  UINT16      fCC_CFH_1;
  UINT16      fCC_CFL;
  UINT16      fCC_CFL_1;
  UINT16      fCC_AH;                 // (float) A접점 동작 시간 Hi
  UINT16      fCC_AH_1;
  UINT16      fCC_AL;
  UINT16      fCC_AL_1;
  UINT16      fTC_BH;                 // (float) B접점 동작 시간 Hi
  UINT16      fTC_BH_1;
  UINT16      fTC_BL;
  UINT16      fTC_BL_1;
  UINT16      fTC_CC_AH;              // (float) A상 차단/투입 시간 Hi
  UINT16      fTC_CC_AH_1;
  UINT16      fTC_CC_AL; 
  UINT16      fTC_CC_AL_1; 
  UINT16      fTC_CC_BH;              // (float) B상 차단/투입 시간 Hi
  UINT16      fTC_CC_BH_1;
  UINT16      fTC_CC_BL;
  UINT16      fTC_CC_BL_1;
  UINT16      fTC_CC_CH;              // (float) C상 차단/투입 시간 Hi
  UINT16      fTC_CC_CH_1;
  UINT16      fTC_CC_CL;
  UINT16      fTC_CC_CL_1;
  UINT16      wN34;                   // NC
  UINT16      wN34_1;                 //
  UINT16      wN35;                   // NC
  UINT16      wN35_1;                 //
  UINT16      wN36;                   // NC
  UINT16      wN36_1;                 //
  UINT16      wN37;                   // NC
  UINT16      wN37_1;                 //
  UINT16      wN38;                   // NC
  UINT16      wN38_1;                 //
  UINT16      wN39;                   // NC
  UINT16      wN39_1;                 //
  UINT16      wN40;                   // NC
  UINT16      wN40_1;                 //
  UINT16      wN41;                   // NC
  UINT16      wN41_1;                 //
  UINT16      wN42;                   // NC
  UINT16      wN42_1;                 //
  UINT16      wN43;                   // NC
  UINT16      wN43_1;                 //
  UINT16      wN44;                   // NC
  UINT16      wN44_1;                 //
  UINT16      wN45;                   // NC
  UINT16      wN45_1;                 //
  UINT16      wN46;                   // NC
  UINT16      wN46_1;                 //
  UINT16      wN47;                   // NC
  UINT16      wN47_1;                 //
} FAULT_NO;
#define eFAULT_MAX      26            // Fault 최대 저장 개수 // 26개로 되어 있으나 20개 임 / 6개는 동시 저장 버퍼
typedef struct
{
// 0x0010E000 ~ 0x0010FFFF(0x00001FFF) 까지 Fault 내역
  FAULT_NO        No[eFAULT_MAX];
} FAULT_DATA;
extern FAULT_DATA *pFault;

#define eWAVE_NUM       2304
#define eWAVE_MAX       ( eWAVE_NUM *2 )
typedef struct
{
  INT16     iwTripCoil1[eWAVE_NUM *2];      // Trip Coil1 전류
  INT16     iwTripCoil2[eWAVE_NUM *2];      // Trip Coil2 전류
  INT16     iwCloseCoil[eWAVE_NUM *2];      // Close Coil 전류
  INT16	    iwVolt[eWAVE_NUM *2];           // 전압 rms 
  INT16	    iwCurr[3][eWAVE_NUM *2];        // 전류 A, B, C rms 
  UINT16	  wContact[eWAVE_NUM];            // DIO byte를 word에 나눠서 저장해야 되
} WAVE_NO;
typedef struct
{
// 0x00110000 ~ 0x001EBFFF(0x000DBFFF) 까지 Fault Wave 파형
  WAVE_NO         No[eFAULT_MAX];
} WAVE_DATA;
extern WAVE_DATA *pWave;

// *2를 Wave보다 더한 이유는 18주기 *2 파형을 가지고 있기 위하여
typedef struct
{
  INT16     iwTripCoil1[eWAVE_MAX *2];   // Trip Coil1 전류
  INT16     iwTripCoil2[eWAVE_MAX *2];   // Trip Coil2 전류
  INT16     iwCloseCoil[eWAVE_MAX *2];   // Close Coil 전류
  INT16	    iwVolt[eWAVE_MAX *2];        // 전압 rms 
  INT16	    iwCurr[3][eWAVE_MAX *2];     // 전류 A, B, C rms 
  UINT16	  wContact[eWAVE_MAX];         // DIO byte를 word에 나눠서 저장해야 되
} RAW_NO;
typedef struct
{
// 0x001EC000 ~ 0x001FFFFF(0x00013FFF) 까지 Fault Wave 파형
  RAW_NO    No;
} RAW_DATA;
extern RAW_DATA *pRaw;


typedef struct
{
  INT16   iwAdcCs0;         // 0x00300000
} ADC_DATA;
extern ADC_DATA *pAdc;

typedef struct
{
  UINT16  wMR;              // 0x00380000
  UINT16  wN0001;           // 0x00380001
  UINT16  wN0010;           // 0x00380002
  UINT16  wN0011;           // 0x00380003
  UINT16  wIR;              // 0x00380004
  UINT16  wN0021;           // 0x00380005
  UINT16  wN0030;           // 0x00380006
  UINT16  wN0031;           // 0x00380007
  UINT16  wIMR;             // 0x00380008
  UINT16  wN0041;           // 9
  UINT16  wN0050;           // A
  UINT16  wN0051;           // B
  UINT16  wR006;            // C
  UINT16  wN0061;           // D
  UINT16  wN0070;           // E
  UINT16  wN0071;           // F
  UINT16  wSHAR;            // 10
  UINT16  wN0081;           // 11
  UINT16  wN0090;           // 12
  UINT16  wN0091;           // 13
  UINT16  wSHAR2;           // 14
  UINT16  wN00A1;           // 15
  UINT16  wN00B0;           // 16
  UINT16  wN00B1;           // 17
  UINT16  wSHAR4;           // 18
  UINT16  wN00C1;           // 19
  UINT16  wN00D0;           // 1A
  UINT16  wN00D1;           // 1B
  UINT16  wR00E;            // 1C
  UINT16  wN00E1;           // 1D
  UINT16  wN00F0;           // 1E
  UINT16  wN00F1;           // 1F
  UINT16  wGAR;             // 20
  UINT16  wN0100;           // 21
  UINT16  wN0110;           // 22
  UINT16  wN0111;           // 23
  UINT16  wGAR2;            // 24
  UINT16  wN0121;           // 25
  UINT16  wN0130;           // 26
  UINT16  wN0131;           // 27
  UINT16  wSUBR;            // 28
  UINT16  wN0141;           // 29
  UINT16  wN0150;           // 2A
  UINT16  wN0151;           // 2B
  UINT16  wSUBR2;           // 2C
  UINT16  wN0161;           // 2D
  UINT16  wN0170;           // 2E
  UINT16  wN0171;           // 2F
  UINT16  wSIPR;            // 30
  UINT16  wN0181;           // 31
  UINT16  wN0190;           // 32
  UINT16  wN0191;           // 33
  UINT16  wSIPR2;           // 34
  UINT16  wN01A1;           // 35
  UINT16  wN01B0;           // 36
  UINT16  wN01B1;           // 37
  UINT16  wRTR;             // 38
  UINT16  wN01C1;           // 39
  UINT16  wN01D0;           // 3A
  UINT16  wN01D1;           // 3B
  UINT16  wRCR;             // 3C
  UINT16  wN01E1;           // 3D
  UINT16  wN01F0;           // 3E
  UINT16  wN01F1;           // 3F
  UINT16  wTMS01R;          // 40
  UINT16  wN0201;           // 41
  UINT16  wN0210;           // 42
  UINT16  wN0211;           // 43
  UINT16  wTMS23R;          // 44
  UINT16  wN0221;           // 45
  UINT16  wN0230;           // 46
  UINT16  wN0231;           // 47
  UINT16  wTMS45R;          // 48
  UINT16  wN0241;           // 49
  UINT16  wN0250;           // 4A
  UINT16  wN0251;           // 4B
  UINT16  wTMS67R;          // 4C
  UINT16  wN0261;           // 4D
  UINT16  wN0270;           // 4E
  UINT16  wN0271;           // 4F
  UINT16  wRMS01R;          // 50
  UINT16  wN0281;           // 51
  UINT16  wN0290;           // 52
  UINT16  wN0291;           // 53
  UINT16  wRMS23R;          // 54
  UINT16  wN02A1;           // 55
  UINT16  wN02B0;           // 56
  UINT16  wN02B1;           // 57
  UINT16  wRMS45R;          // 58
  UINT16  wN02C1;           // 59
  UINT16  wN02D0;           // 5A
  UINT16  wN02D1;           // 5B
  UINT16  wRMS67R;          // 5C
  UINT16  wN02E1;           // 5D
  UINT16  wN02F0;           // 5E
  UINT16  wN02F1;           // 5F
  UINT16  wMTYPER;          // 60
  UINT16  wN0301;           // 61
  UINT16  wN0310;           // 62
  UINT16  wN0311;           // 63
  UINT16  wPATR;            // 64
  UINT16  wN0321;           // 65
  UINT16  wN0330;           // 66
  UINT16  wN0331;           // 67
  UINT16  wR0340;           // 68
  UINT16  wN0341;           // 69
  UINT16  wN0350;           // 6A
  UINT16  wN0351;           // 6B
  UINT16  wPTIMER;          // 6C
  UINT16  wN0361;           // 6D
  UINT16  wN0370;           // 6E
  UINT16  wN0371;           // 6F
  UINT16  wPMAGICR;         // 70
  UINT16  wN0381;           // 71
  UINT16  wN0390;           // 72
  UINT16  wN0391;           // 73
  UINT16  wR03A0;           // 74
  UINT16  wN03A1;           // 75
  UINT16  wN03B0;           // 76
  UINT16  wN03B1;           // 77
  UINT16  wPSIDR;           // 78
  UINT16  wN03C1;           // 79
  UINT16  wN03D0;           // 7A
  UINT16  wN03D1;           // 7B
  UINT16  wR03E0;           // 7C
  UINT16  wN03E1;           // 7D
  UINT16  wN03F0;           // 7E
  UINT16  wN03F1;           // 7F
  UINT16  wPDHAR;           // 80
  UINT16  wN0401;           // 81
  UINT16  wN0410;           // 82
  UINT16  wN0411;           // 83
  UINT16  wPDHAR2;          // 84
  UINT16  wN0421;           // 85
  UINT16  wN0430;           // 86
  UINT16  wN0431;           // 87
  UINT16  wPDHAR4;          // 88
  UINT16  wN0441;           // 89
  UINT16  wN0450;           // 8A
  UINT16  wN0451;           // 8B
  UINT16  wR046;            // 8C
  UINT16  wN0461;           // 8D
  UINT16  wN0470;           // 8E
  UINT16  wN0471;           // 8F
  UINT16  wUIPR;            // 90
  UINT16  wN0481;           // 91
  UINT16  wN0490;           // 92
  UINT16  wN0491;           // 93
  UINT16  wUIPR2;           // 94
  UINT16  wN04A1;           // 95
  UINT16  wN04B0;           // 96
  UINT16  wN04B1;           // 97
  UINT16  wUPORTR;          // 98
  UINT16  wN04C1;           // 99
  UINT16  wN04D0;           // 9A
  UINT16  wN04D1;           // 9B
  UINT16  wFMTUR;           // 9C
  UINT16  wN04E1;           // 9D
  UINT16  wN04F0;           // 9E
  UINT16  wN04F1;           // 9F
  UINT16  wR050;            // A0
  UINT16  wN0501;           // A1
  UINT16  wN0510;           // A2
  UINT16  wN0511;           // A3
  UINT16  wR052;            // A4
  UINT16  wN0521;           // A5
  UINT16  wN0530;           // A6
  UINT16  wN0531;           // A7
  UINT16  wR054;            // A8
  UINT16  wN0541;           // A9
  UINT16  wN0550;           // AA
  UINT16  wN0551;           // AB
  UINT16  wR056;            // AC
  UINT16  wN0561;           // AD
  UINT16  wN0570;           // AE
  UINT16  wN0571;           // AF
  UINT16  wR058;            // B0
  UINT16  wN0581;           // B1
  UINT16  wN0590;           // B2
  UINT16  wN0591;           // B3
  UINT16  wR05A;            // B4
  UINT16  wN05A1;           // B5
  UINT16  wN05B0;           // B6
  UINT16  wN05B1;           // B7
  UINT16  wR05C;            // B8
  UINT16  wN05C1;           // B9
  UINT16  wN05D0;           // BA
  UINT16  wN05D1;           // BB
  UINT16  wR05E;            // BC
  UINT16  wN05E1;           // BD
  UINT16  wN05F0;           // BE
  UINT16  wN05F1;           // BF
  UINT16  wP0_BRDYR;        // C0
  UINT16  wN0601;           // C1
  UINT16  wN0610;           // C2
  UINT16  wN0611;           // C3
  UINT16  wP0_BDPTHR;       // C4
  UINT16  wN0621;           // C5
  UINT16  wN0630;           // C6
  UINT16  wN0631;           // C7
  UINT16  wP1_BRDYR;        // C8
  UINT16  wN0641;           // C9
  UINT16  wN0650;           // CA
  UINT16  wN0651;           // CB
  UINT16  wP1_BDPTHR;       // CC
  UINT16  wN0661;           // CD
  UINT16  wN0670;           // CE
  UINT16  wN0671;           // CF
  UINT16  wP2_BRDYR;        // D0
  UINT16  wN0681;           // D1
  UINT16  wN0690;           // D2
  UINT16  wN0691;           // D3
  UINT16  wP2_BDPTHR;       // D4
  UINT16  wN06A1;           // D5
  UINT16  wN06B0;           // D6
  UINT16  wN06B1;           // D7
  UINT16  wP3_BRDYR;        // D8
  UINT16  wN06C1;           // D9
  UINT16  wN06D0;           // DA
  UINT16  wN06D1;           // DB
  UINT16  wP4_BDPTHR;       // DC
  UINT16  wN06E1;           // DD
  UINT16  wN06F0;           // DE
  UINT16  wN06F1;           // DF
  UINT16  wN0700;           // E0
  UINT16  wN0701;           // E1
  UINT16  wN0710;           // E2
  UINT16  wN0711;           // E3
  UINT16  wN0720;           // E4
  UINT16  wN0721;           // E5
  UINT16  wN0730;           // E6
  UINT16  wN0731;           // E7
  UINT16  wN0740;           // E8
  UINT16  wN0741;           // E9
  UINT16  wN0750;           // EA
  UINT16  wN0751;           // EB
  UINT16  wN0760;           // EC
  UINT16  wN0761;           // ED
  UINT16  wN0770;           // EE
  UINT16  wN0771;           // EF
  UINT16  wN0780;           // F0
  UINT16  wN0781;           // F1
  UINT16  wN0790;           // F2
  UINT16  wN0791;           // F3
  UINT16  wN07A0;           // F4
  UINT16  wN07A1;           // F5
  UINT16  wN07B0;           // F6
  UINT16  wN07B1;           // F7
  UINT16  wN07C0;           // F8
  UINT16  wN07C1;           // F9
  UINT16  wN07D0;           // FA
  UINT16  wN07D1;           // FB
  UINT16  wN07E0;           // FC
  UINT16  wN07E1;           // FD
  UINT16  wN07F0;           // FE
  UINT16  wN07F1;           // FF
  UINT16  wN0800;           // 100
  UINT16  wN0801;           // 101
  UINT16  wN0810;           // 102
  UINT16  wN0811;           // 103
  UINT16  wN0820;           // 104
  UINT16  wN0821;           // 105
  UINT16  wN0830;           // 106
  UINT16  wN0831;           // 107
  UINT16  wN0840;           // 108
  UINT16  wN0841;           // 109
  UINT16  wN0850;           // 10A
  UINT16  wN0851;           // 10B
  UINT16  wN0860;           // 10C
  UINT16  wN0861;           // 10D
  UINT16  wN0870;           // 10E
  UINT16  wN0871;           // 10F
  UINT16  wN0880;           // 110
  UINT16  wN0881;           // 111
  UINT16  wN0890;           // 112
  UINT16  wN0891;           // 113
  UINT16  wN08A0;           // 114
  UINT16  wN08A1;           // 115
  UINT16  wN08B0;           // 116
  UINT16  wN08B1;           // 117
  UINT16  wN08C0;           // 118
  UINT16  wN08C1;           // 119
  UINT16  wN08D0;           // 11A
  UINT16  wN08D1;           // 11B
  UINT16  wN08E0;           // 11C
  UINT16  wN08E1;           // 11D
  UINT16  wN08F0;           // 11E
  UINT16  wN08F1;           // 11F
  UINT16  wN0900;           // 120
  UINT16  wN0901;           // 121
  UINT16  wN0910;           // 122
  UINT16  wN0911;           // 123
  UINT16  wN0920;           // 124
  UINT16  wN0921;           // 125
  UINT16  wN0930;           // 126
  UINT16  wN0931;           // 127
  UINT16  wN0940;           // 128
  UINT16  wN0941;           // 129
  UINT16  wN0950;           // 12A
  UINT16  wN0951;           // 12B
  UINT16  wN0960;           // 12C
  UINT16  wN0961;           // 12D
  UINT16  wN0970;           // 12E
  UINT16  wN0971;           // 12F
  UINT16  wN0980;           // 130
  UINT16  wN0981;           // 131
  UINT16  wN0990;           // 132
  UINT16  wN0991;           // 133
  UINT16  wN09A0;           // 134
  UINT16  wN09A1;           // 135
  UINT16  wN09B0;           // 136
  UINT16  wN09B1;           // 137
  UINT16  wN09C0;           // 138
  UINT16  wN09C1;           // 139
  UINT16  wN09D0;           // 13A
  UINT16  wN09D1;           // 13B
  UINT16  wN09E0;           // 13C
  UINT16  wN09E1;           // 13D
  UINT16  wN09F0;           // 13E
  UINT16  wN09F1;           // 13F
  UINT16  wN0A00;           // 140
  UINT16  wN0A01;           // 141
  UINT16  wN0A10;           // 142
  UINT16  wN0A11;           // 143
  UINT16  wN0A20;           // 144
  UINT16  wN0A21;           // 145
  UINT16  wN0A30;           // 146
  UINT16  wN0A31;           // 147
  UINT16  wN0A40;           // 148
  UINT16  wN0A41;           // 149
  UINT16  wN0A50;           // 14A
  UINT16  wN0A51;           // 14B
  UINT16  wN0A60;           // 14C
  UINT16  wN0A61;           // 14D
  UINT16  wN0A70;           // 14E
  UINT16  wN0A71;           // 14F
  UINT16  wN0A80;           // 150
  UINT16  wN0A81;           // 151
  UINT16  wN0A90;           // 152
  UINT16  wN0A91;           // 153
  UINT16  wN0AA0;           // 154
  UINT16  wN0AA1;           // 155
  UINT16  wN0AB0;           // 156
  UINT16  wN0AB1;           // 157
  UINT16  wN0AC0;           // 158
  UINT16  wN0AC1;           // 159
  UINT16  wN0AD0;           // 15A
  UINT16  wN0AD1;           // 15B
  UINT16  wN0AE0;           // 15C
  UINT16  wN0AE1;           // 15D
  UINT16  wN0AF0;           // 15E
  UINT16  wN0AF1;           // 15F
  UINT16  wN0B00;           // 160
  UINT16  wN0B01;           // 161
  UINT16  wN0B10;           // 162
  UINT16  wN0B11;           // 163
  UINT16  wN0B20;           // 164
  UINT16  wN0B21;           // 165
  UINT16  wN0B30;           // 166
  UINT16  wN0B31;           // 167
  UINT16  wN0B40;           // 168
  UINT16  wN0B41;           // 169
  UINT16  wN0B50;           // 16A
  UINT16  wN0B51;           // 16B
  UINT16  wN0B60;           // 16C
  UINT16  wN0B61;           // 16D
  UINT16  wN0B70;           // 16E
  UINT16  wN0B71;           // 16F
  UINT16  wN0B80;           // 170
  UINT16  wN0B81;           // 171
  UINT16  wN0B90;           // 172
  UINT16  wN0B91;           // 173
  UINT16  wN0BA0;           // 174
  UINT16  wN0BA1;           // 175
  UINT16  wN0BB0;           // 176
  UINT16  wN0BB1;           // 177
  UINT16  wN0BC0;           // 178
  UINT16  wN0BC1;           // 179
  UINT16  wN0BD0;           // 17A
  UINT16  wN0BD1;           // 17B
  UINT16  wN0BE0;           // 17C
  UINT16  wN0BE1;           // 17D
  UINT16  wN0BF0;           // 17E
  UINT16  wN0BF1;           // 17F
  UINT16  wN0C00;           // 180
  UINT16  wN0C01;           // 181
  UINT16  wN0C10;           // 182
  UINT16  wN0C11;           // 183
  UINT16  wN0C20;           // 184
  UINT16  wN0C21;           // 185
  UINT16  wN0C30;           // 186
  UINT16  wN0C31;           // 187
  UINT16  wN0C40;           // 188
  UINT16  wN0C41;           // 189
  UINT16  wN0C50;           // 18A
  UINT16  wN0C51;           // 18B
  UINT16  wN0C60;           // 18C
  UINT16  wN0C61;           // 18D
  UINT16  wN0C70;           // 18E
  UINT16  wN0C71;           // 18F
  UINT16  wN0C80;           // 190
  UINT16  wN0C81;           // 191
  UINT16  wN0C90;           // 192
  UINT16  wN0C91;           // 193
  UINT16  wN0CA0;           // 194
  UINT16  wN0CA1;           // 195
  UINT16  wN0CB0;           // 196
  UINT16  wN0CB1;           // 197
  UINT16  wN0CC0;           // 198
  UINT16  wN0CC1;           // 199
  UINT16  wN0CD0;           // 19A
  UINT16  wN0CD1;           // 19B
  UINT16  wN0CE0;           // 19C
  UINT16  wN0CE1;           // 19D
  UINT16  wN0CF0;           // 19E
  UINT16  wN0CF1;           // 19F
  UINT16  wN0D00;           // 1A0
  UINT16  wN0D01;           // 1A1
  UINT16  wN0D10;           // 1A2
  UINT16  wN0D11;           // 1A3
  UINT16  wN0D20;           // 1A4
  UINT16  wN0D21;           // 1A5
  UINT16  wN0D30;           // 1A6
  UINT16  wN0D31;           // 1A7
  UINT16  wN0D40;           // 1A8
  UINT16  wN0D41;           // 1A9
  UINT16  wN0D50;           // 1AA
  UINT16  wN0D51;           // 1AB
  UINT16  wN0D60;           // 1AC
  UINT16  wN0D61;           // 1AD
  UINT16  wN0D70;           // 1AE
  UINT16  wN0D71;           // 1AF
  UINT16  wN0D80;           // 1B0
  UINT16  wN0D81;           // 1B1
  UINT16  wN0D90;           // 1B2
  UINT16  wN0D91;           // 1B3
  UINT16  wN0DA0;           // 1B4
  UINT16  wN0DA1;           // 1B5
  UINT16  wN0DB0;           // 1B6
  UINT16  wN0DB1;           // 1B7
  UINT16  wN0DC0;           // 1B8
  UINT16  wN0DC1;           // 1B9
  UINT16  wN0DD0;           // 1BA
  UINT16  wN0DD1;           // 1BB
  UINT16  wN0DE0;           // 1BC
  UINT16  wN0DE1;           // 1BD
  UINT16  wN0DF0;           // 1BE
  UINT16  wN0DF1;           // 1BF
  UINT16  wN0E00;           // 1C0
  UINT16  wN0E01;           // 1C1
  UINT16  wN0E10;           // 1C2
  UINT16  wN0E11;           // 1C3
  UINT16  wN0E20;           // 1C4
  UINT16  wN0E21;           // 1C5
  UINT16  wN0E30;           // 1C6
  UINT16  wN0E31;           // 1C7
  UINT16  wN0E40;           // 1C8
  UINT16  wN0E41;           // 1C9
  UINT16  wN0E50;           // 1CA
  UINT16  wN0E51;           // 1CB
  UINT16  wN0E60;           // 1CC
  UINT16  wN0E61;           // 1CD
  UINT16  wN0E70;           // 1CE
  UINT16  wN0E71;           // 1CF
  UINT16  wN0E80;           // 1D0
  UINT16  wN0E81;           // 1D1
  UINT16  wN0E90;           // 1D2
  UINT16  wN0E91;           // 1D3
  UINT16  wN0EA0;           // 1D4
  UINT16  wN0EA1;           // 1D5
  UINT16  wN0EB0;           // 1D6
  UINT16  wN0EB1;           // 1D7
  UINT16  wN0EC0;           // 1D8
  UINT16  wN0EC1;           // 1D9
  UINT16  wN0ED0;           // 1DA
  UINT16  wN0ED1;           // 1DB
  UINT16  wN0EE0;           // 1DC
  UINT16  wN0EE1;           // 1DD
  UINT16  wN0EF0;           // 1DE
  UINT16  wN0EF1;           // 1DF
  UINT16  wN0F00;           // 1E0
  UINT16  wN0F01;           // 1E1
  UINT16  wN0F10;           // 1E2
  UINT16  wN0F11;           // 1E3
  UINT16  wN0F20;           // 1E4
  UINT16  wN0F21;           // 1E5
  UINT16  wN0F30;           // 1E6
  UINT16  wN0F31;           // 1E7
  UINT16  wN0F40;           // 1E8
  UINT16  wN0F41;           // 1E9
  UINT16  wN0F50;           // 1EA
  UINT16  wN0F51;           // 1EB
  UINT16  wN0F60;           // 1EC
  UINT16  wN0F61;           // 1ED
  UINT16  wN0F70;           // 1EE
  UINT16  wN0F71;           // 1EF
  UINT16  wN0F80;           // 1F0
  UINT16  wN0F81;           // 1F1
  UINT16  wN0F90;           // 1F2
  UINT16  wN0F91;           // 1F3
  UINT16  wN0FA0;           // 1F4
  UINT16  wN0FA1;           // 1F5
  UINT16  wN0FB0;           // 1F6
  UINT16  wN0FB1;           // 1F7
  UINT16  wN0FC0;           // 1F8
  UINT16  wN0FC1;           // 1F9
  UINT16  wN0FD0;           // 1FA
  UINT16  wN0FD1;           // 1FB
  UINT16  wIDR;             // 1FC
  UINT16  wN0FE1;           // 1FD
  UINT16  wN0FF0;           // 1FE
  UINT16  wN0FF1;           // 1FF


} W5300_DATA;
extern W5300_DATA *pW5300;


#define eIN_CHANGE      10
typedef struct _INPUT_CNT
{
  UINT16        wInput;
  UINT16        w1Hi;
  UINT16        w1Lo;
  UINT16        w2Hi;
  UINT16        w2Lo;
} INPUT_CNT;
typedef struct _INPUT_REG
{
  INPUT_CNT     Cnt;
  UINT16        wInput;
} INPUT_REG;
extern INPUT_REG sIn;


/*
typedef struct _ERROR_REG
{
  UINT16  wReset;           // MCU Reset 회수
  UINT16  wSyncCs;          // Sync Cs
  UINT16  wSyncCount;       // Sync Count
  UINT16  wSyncCode;        // Sync Code 0x02
  UINT16  wSyncTime;        // Sync Time

} ERROR_REG;
extern ERROR_REG sError;
extern ERROR_REG sETemp;

typedef struct _FAULT_REG
{
//  BOOL    bReset;           // MCU Reset 회수
  BOOL    bSyncCs;          // Sync Cs          3회 이상
  BOOL    bSyncCount;       // Sync Count
  BOOL    bSyncCode;        // Sync Code 0x02
  BOOL    bSyncTime;        // Sync Time
  BOOL    bSyncCsFix;       // Sync Cs          10회 이상
  BOOL    bSyncCountFix;    // Sync Count
  BOOL    bSyncCodeFix;     // Sync Code 0x02
  BOOL    bSyncTimeFix;     // Sync Time
  BOOL    bWdtFix;          // Wdt
} FAULT_REG;
extern FAULT_REG sFault;
*/

typedef struct _TEST_REG
{
  UINT16  wAdcNormalGain;   // Adc Normal Gain 110.00V 11.000A
  BOOL    bBoot;

  BOOL    bUtc2Rtc;
  BOOL    bRtc2Utc;

  UINT16  wPit;

  BOOL    b1Line;

// Modbus
  BOOL        bModbus;
  BOOL        bMod;

} TEST_REG;
extern TEST_REG sTest;

#endif /* __MAIN_H */
