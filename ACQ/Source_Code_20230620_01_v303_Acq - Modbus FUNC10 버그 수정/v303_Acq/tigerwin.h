/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : tigerwin.h
 *
 * *************************************************************************/ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIGERWIN_H
#define __TIGERWIN_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


#define MRAM_CS2_BASE       0x00100000
#define MRAM_CS2_SIZE       0x0000CFFF      // A0-A19
#define EVENT_CS2_BASE      0x0010D000      //                    저장개수 Addr보상
#define EVENT_CS2_SIZE      0x00000FFF      // ( 8                 *100 ) *2 = 1600(0x640) / Max 32 *100 = 3200(0xC80)
#define FAULT_CS2_BASE      0x0010E000
#define FAULT_CS2_SIZE      0x00001FFF      // ( 48                *26 )  *2 = 2496(0x9C0) / Max 144 *26 = 3744(0xEA0)
#define WAVE_CS2_BASE       0x00110000
#define WAVE_CS2_SIZE       0x000DBFFF      // (((2304 *7) +1152)  *26 )  *2 = 898560(0xDB600)
#define RAW_CS2_BASE        0x001EC000
#define RAW_CS2_SIZE        0x00013FFF      // ((((2304 *7) +1152) *2 )   *2 = 69120(0x10E00)
#define ADC_CS3_BASE        0x00300000
#define ADC_CS3_SIZE        0x00000001      // 1
#define W5300_CS4_BASE      0x00380000
#define W5300_CS4_SIZE      0x000001FF      // A1~A9



typedef enum
{
  MEMORY_TYPE_MRAM,
  MEMORY_TYPE_EVENT,
  MEMORY_TYPE_FAULT,
  MEMORY_TYPE_WAVE,
  MEMORY_TYPE_RAW,
  MEMORY_TYPE_ADC,
  MEMORY_TYPE_W5300    //,
}
MEMORY_TYPE;

typedef struct
{
  UINT32  Start;
  UINT32  Size;
}
TABLE_ADDRESS_MAP;
extern const TABLE_ADDRESS_MAP	ADDRESS_MAP[];

extern char bTxData[32];
extern char bTxData2[32];



// 1. Modbus FUNC10 수신 및 송신 문제로 소스 수정
// 1.1. FUNC10 RX 명령을 받았을 때 UINT32(4byte)의 Data 전송시 규격이 잘못되어 수정함
// 1.1.1. 0x12345678 전송시 0x5678 0x1234가 전송 되고 있었음
// 1.2. FUNC10 TX 명령을 수신할 때 Data를 가져오지 못하는 문제가 있어 설정이 잘못되어 수정함
#define eYYYYMMDD         0x20230620
#define eVERSION          0x0103        // v1.03
// 1. w5300 H/W Reset로 Link 다시 되는 것 확인하였음 // 세니온에서 Test를 잘못 한것으로 판단 됨
// 2. Fault Data가 있을 때 1028 번지 0xFF00 으로 표시되고 있는데 0xFF01~ 표시 되게 함 // Fault Data가 몇개 있는지 표시
// 3. 1043번지 추가하여 0xFF00이 들어오면 Fault Erase 기능으로 사용 함
// 4. Reset 기능 활성화함 // Jumper WDT 연결해야 Reset 동작 됨
//#define eYYYYMMDD         0x20230522
//#define eVERSION          0x0102        // v1.02
// 1. w5300 H/W Reset 했는데 세니온에서 Test하는 장비에서 안됨
//#define eYYYYMMDD         0x20230518
// 20230502
//#define eYYYYMMDD         0x20230502
//#define eVERSION          0x0101        // v1.01
//#define eVERSION          0x0100
// 1. DC3(CC) 화면 계측 튐 버그 수정
//#define eYYYYMMDD         0x20221123
//#define eYYYYMMDD         0x20221115
//#define eYYYYMMDD         0x20220518

#define eMAGIC_CODE       0xA502
#define eCLEAR_CODE       0x0001

#define eSV_MAGIC_DEF     eMAGIC_CODE
#define eSV_CLEAR_DEF     eCLEAR_CODE
#define eSV_PCB_DEF       0x0100
#define eSV_VER_DEF       0x0100
#define eSV_YYYY_DEF      0x2022
#define eSV_MMDD_DEF      0x0516

#define eSV_IP_H_DEF      (UINT16)( (192 <<8) + 168 )
#define eSV_IP_L_DEF      (UINT16)( (10  <<8) + 100 )
#define eSV_SUB_H_DEF     (UINT16)( (255 <<8) + 255 )
#define eSV_SUB_L_DEF     (UINT16)( (255 <<8) + 0   )
#define eSV_GAT_H_DEF     (UINT16)( (192 <<8) + 168 )
#define eSV_GAT_L_DEF     (UINT16)( (10  <<8) + 1   )
#define eSV_PORT_DEF      100
#define eSV_LOC_H_DEF     (UINT16)( (192 <<8) + 168 )
#define eSV_LOC_L_DEF     (UINT16)( (10  <<8) + 100 )
#define eSV_ETH_MIN       0
#define eSV_ETH_MAX       255
#define eSV_POT_MIN       0
#define eSV_POT_MAX       65535

#define eSV_TRIG_MIN      10
#define eSV_TRIG_MAX      100
#define eSV_TRIG_DEF      20
#define eSV_DEBO_MIN      5
#define eSV_DEBO_MAX      100
#define eSV_DEBO_DEF      10

#define eSV_NO100MS_MIN   3
//#define eINT_100MS_NO   16
#define eSV_NO100MS_MAX   eINT_100MS_NO
#define eSV_NO100MS_DEF   8
#define eSV_NO500MS_MIN   3
//#define eINT_500MS_NO   16
#define eSV_NO500MS_MAX   eINT_500MS_NO
#define eSV_NO500MS_DEF   8


#define eSV_DCZER_MIN     0           // (/10) 0.0~1.0V
#define eSV_DCZER_MAX     10          // (/10) 0.0~1.0V
#define eSV_DCZER_DEF     0           // (/10) DC Zero 0V
#define eSV_DCSPR_MIN     1           // (/10) 0.1~6.0V
#define eSV_DCSPR_MAX     60          // (/10) 0.1~6.0V
#define eSV_DCSPR_DEF     40          // (/10) DC Span 4.0V / A로 입력되야 되지만 입력을 DC 20이상 인가해야 되는 문제로 전압을 인가하는 구조로 만듬

#define eSV_DCZE_DEF      0.0
#define eSV_DCSP_DEF      26438.0


#define eSV_ACVZER_MIN    0           // (/10) 0.0~10.0V
#define eSV_ACVZER_MAX    100         // (/10) 0.0~10.0V
#define eSV_ACVZER_DEF    0           // (/10) ACV Zero 0.0V
#define eSV_ACVSPR_MIN    100         // (/10) 10.0~200.0V
#define eSV_ACVSPR_MAX    2000        // (/10) 10.0~200.0V
#define eSV_ACVSPR_DEF    635         // (/10) ACV Span 63.5V
#define eSV_ACIZER_MIN    0           // (/10) 0.0~10.0A
#define eSV_ACIZER_MAX    100         // (/10) 0.0~10.0A
#define eSV_ACIZER_DEF    0           // (/10) ACI Zero 0A
#define eSV_ACISPR_MIN    10          // (/10) 1.0~20.0A
#define eSV_ACISPR_MAX    200         // (/10) 1.0~20.0A
#define eSV_ACISPR_DEF    50          // (/10) ACI Span 5.0A

#define eSV_ACVZE_DEF     0.7
#define eSV_ACVSP_DEF     8465.0
#define eSV_ACIZE_DEF     4.8
#define eSV_ACISP_DEF     1530.0

#define eSV_PH_DEF        0

#define eSV_PASS_MIN      0
#define eSV_PASS_MAX      9999
#define eSV_PASS_DEF      0
#define eSV_ID_MIN        1
#define eSV_ID_MAX        32
#define eSV_ID_DEF        1
enum
{
  eBPS_9600,
  eBPS_19200,
  eBPS_38400,
  eBPS_57600,
  eBPS_115200,
  eBPS_230400,
  eBPS_460800,
  eBPS_921600,
};
#define eSV_BPS_MIN           0
#define eSV_BPS_MAX           6
#define eSV_BPS_DEF           3       // 0: 9600, 1: 19200, 2: 57600, 3: 115200, 4: 230400, 5: 460800, 6: 921600
#define eSV_NOP_DEF           0x00
#define eSV_ACVRATIO_MIN      10.0    // 10.0~200V
#define eSV_ACVRATIO_MAX      200.0   // 10.0~200V
#define eSV_ACVRATIO_DEF      63.5    // 63.5V // ACV Ratio
#define eSV_ACIRATIO_MIN      1.0     // 1.0~20.0A
#define eSV_ACIRATIO_MAX      20.0    // 1.0~20.0A
#define eSV_ACIRATIO_DEF      5.0     // 5.0A // ACT Ratio
#define eSV_DCRATIO_MIN       1.0     // 1.0~40.0A
#define eSV_DCRATIO_MAX       40.0    // 1.0~40.0A
#define eSV_DCRATIO_DEF       25.0    // 25.0A // DC Ratio
#define eSV_TRIP_MIN          1       // 0.1~5.0A
#define eSV_TRIP_MAX          50      // 0.1~5.0A
#define eSV_TRIP_DEF          5       // 5 = 0.5A // 
#define eSV_CHAT_MIN          1       // 1msec
#define eSV_CHAT_MAX          50      // 50msec
#define eSV_CHAT_DEF          5       // 5msec

#define eSV_TIM_YY_MIN        0       // YY
#define eSV_TIM_YY_MAX        99
#define eSV_TIM_YY_DEF        22
#define eSV_TIM_MM_MIN        1       // MM
#define eSV_TIM_MM_MAX        12
#define eSV_TIM_MM_DEF        11
#define eSV_TIM_DD_MIN        1       // DD
#define eSV_TIM_DD_MAX        31
#define eSV_TIM_DD_DEF        8
#define eSV_TIM_hh_MIN        0       // hh
#define eSV_TIM_hh_MAX        23
#define eSV_TIM_hh_DEF        11
#define eSV_TIM_mm_MIN        0       // mm
#define eSV_TIM_mm_MAX        59
#define eSV_TIM_mm_DEF        22
#define eSV_TIM_ss_MIN        0       // ss // msec는 비교에 사용 되지 않으므로.. *1000를 하지 않음 // *1000 (msec)
#define eSV_TIM_ss_MAX        59
#define eSV_TIM_ss_DEF        0

enum    // sSet.wStatus
{
  eO_FAULT_BLOCKING   = BIT0,
  eO_FAULT_WDT        = BIT1,
  eO_FAULT_OUT_ENABLE = BIT2,
  eO_FAULT_24V        = BIT3,
  eO_FAULT_OUTPUT     = BIT4,
  eO_FAULT_INPUT      = BIT5,
  eO_FAULT_SYNC       = BIT6,
  eO_FAULT_125V       = BIT7,
  eO_FAULT_LINK       = BIT8,
  eO_FAULT_P12V       = BIT9,
  eO_FAULT_N12V       = BIT10,
  eO_FAULT_ADC        = BIT11     //,
};
enum
{
  eFAULT_BLOCKING = ( 1 *4 ),
  eFAULT_WATCHDOG = ( 1 *4 ),
  eFAULT_OUT_ENABLE = ( 1 *4 ),
  eFAULT_P12V = ( 1 *4 ),
  eFAULT_N12V = ( 1 *4 )   //,
};
#define eTEST_CLEAR_DELAY      100
#define eERROR_CLEAR_DELAY     100
enum    // sIn.wInput / sSta.lError
{
  eST_B_IN_DI1      = BIT0,     // sIn.wInput Only
  eST_B_IN_DI2      = BIT1,     // sIn.wInput Only
//  eST_B_ERR_ADC     = BIT3,     // sSta.lError Only   // ADC 전체 Error 판단 할 수 없음
  eST_B_IN_N5V      = BIT4,
  eST_B_IN_N15V     = BIT5,
  eST_B_IN_P15V     = BIT6,
  eST_B_IN_P24V     = BIT7,
  eST_B_ERR_ADCH0   = BIT8,     // sSta.lError Only
  eST_B_ERR_ADCH1   = BIT9,     // sSta.lError Only
  eST_B_ERR_ADCH2   = BIT10,    // sSta.lError Only
  eST_B_ERR_ADCH3   = BIT11,    // sSta.lError Only
  eST_B_ERR_ADCH4   = BIT12,    // sSta.lError Only
  eST_B_ERR_ADCH5   = BIT13,    // sSta.lError Only
  eST_B_ERR_ADCH6   = BIT14,    // sSta.lError Only
  eST_B_ERR_ADCH7   = BIT15,    // sSta.lError Only
  eST_B_ERR_SV      = BIT16,    // sSta.lError Only
};
typedef struct
{
  BOOL            bMainLoop;          // Main Loop On Bit
  UINT32          lPowerOnDelay;      // Power On Delay Bit
  UINT16          wPowerOnDelaySec;   // Power On Delay sec Bit

  BOOL            bPowerStart;        // Power Event 저장 되었으며 다른 Event 저장 됨

  UINT16          wTc1;             // Fault Trip 진입 불가 Status / 전류가 설정치의 10% 미만으로 떨어지면 지워짐
  UINT16          wTc2;             // Fault Trip 진입 불가 Status / 전류가 설정치의 10% 미만으로 떨어지면 지워짐
  UINT16          wCc;              // Fault Close 진입 불가 Status / 전류가 설정치의 10% 미만으로 떨어지면 지워짐

  UINT32          lError;
  UINT16          wSvErr;

  INT32           ilUtc;
} STATUS_REG;
extern STATUS_REG sSta;
extern STATUS_REG sStaTemp;

typedef struct
{
  UINT16  wMain;
  UINT8   bSync;

} STEP_REG;
extern STEP_REG sStep;

#define eAI_MAX             12
/*
#define eWDT_CHANGE         ( 1 )       // 256usec
#define eSYNC_FAIL          10      // MPRAM 10이상 통신 안되면
#define eOUT_MAX            15
#define eIN_MAX             24
#define eTEST_CLEAR         10
#define eERROR_CLEAR        10
*/
typedef struct
{
  UINT16          wMain;
  UINT16          w1msec;
  UINT8           b64sample;        // 60Hz 260usec, 50Hz 313usec
  UINT8           b16sample;        // 60Hz 1042usec, 50Hz 1250usec
  UINT8           bFreq1sec;        // 60Hz 960회를 1000으로 만듬(24회에 +1), 50Hz 800회를 1000으로 만듬(4회에 +1)
  UINT8           bBoot0_1Sec;
  UINT8           bBoot1_0Sec;

  UINT16          bAdcRead;         // AD Conv -> Adc Read / 순서 Count

  UINT16          wEv;              // Event Point No
  UINT16          wFa;              // Fault Point No
  UINT16          wFaEnd;           // Fault Point No 최종
  UINT16          wFaMb;            // Fault Modbus No
  UINT16          wFaNum;           // Fault No 0~255 FreeCount

  UINT16          wTc1;             // Debounce Count
  UINT16          wTc2;             // Debounce Count
  UINT16          wCc;              // Debounce Count

  UINT32          lSocketOff;       // wSocketOff 60sec(60 *4)
} COUNT_REG;
extern COUNT_REG sCnt;


typedef struct
{
  UINT8   bYY;    // 년
  UINT8   bMM;    // 월
  UINT8   bDD;    // 일
  UINT8   bhh;    // 시
  UINT8   bmm;    // 분
  UINT8   bss;    // 초
  UINT8   bwe;    // 주
  UINT16  wms;    // msec
} TIME_REG;


enum    // sSet.wZeroR, wSpanR, fZero, fSpan
{
  eSET_TEMP,
  eSET_TRIP_COIL1,
  eSET_TRIP_COIL2,
  eSET_CLOSE_COIL,
  eSET_V,
  eSET_IA,
  eSET_IB,
  eSET_IC,
};
#define eSAMPLE_NO          128       // 128 sample Data
#define eDFT_SAMPLE_NO      16        // Dft 연산 개수 16ea
#define ePASS_LV1           2020      // LEVEL1
enum
{
  eST_LV_OFF,
  eST_LV1,
  eST_LV2,
  eST_LV3,
};
typedef struct
{
  UINT16                wMagic;
  UINT16                wClear;
  UINT16                wPcb;
  UINT16                wVer;
  UINT16                wYYYY;
  UINT16                wMMDD;

  UINT16                wPass;

// Comm
  UINT16                wId;
  UINT16                wBps;
  UINT16                wN20;
  UINT16                wN21;
  UINT16                wN22;
  UINT16                wN23;
  UINT16                wN24;
  UINT16                wN25;

  UINT16                wNo100ms;
  UINT16                wNo500ms;

  float                 fRatio[eADC_MAX];   // DC 차단기 전압 -> 전류 비율, AC 전압 비율

  UINT16                wZeR[eADC_MAX];
  UINT16                wSpR[eADC_MAX];
  float                 fZe[eADC_MAX];
  float                 fSp[eADC_MAX];
  float                 fPh[eADC_MAX];

  UINT16                wMac[3];

  UINT16                wPassXCs;           // Password
  UINT16                wCommXCs;           // Communication
  UINT16                wNoXCs;             // wNo100ms ~ wNo500ms
  UINT16                wDcRatioXCs;        // DC 차단기 전류 -> 전압 비율
  UINT16                wAcRatioXCs;        // AC 전압 -> 전압 비율
  UINT16                wZeRDcXCs;          // ZeR DC
  UINT16                wSpRDcXCs;          // SpR AC
  UINT16                wZeRAcXCs;          // ZeR DC
  UINT16                wSpRAcXCs;          // SpR AC
  UINT16                wZeDcXCs;           // Ze DC
  UINT16                wSpDcXCs;           // Sp DC
  UINT16                wZeAcXCs;           // Ze AC
  UINT16                wSpAcXCs;           // Sp AC
  UINT16                wPhXCs;             // Ph
  UINT16                wMacXCs;            // wMac

  BOOL                  bFreq50Hz;          // 0:60Hz 1:50Hz    / pMram 에서 가져 와야 되는데 현재 초기화 안되어 있어 가져 오지 않고 있음
  UINT16                wFreqTime;          // 200000000 / ( 60*64*2);     // 1/60/64/2 / DIV2
  UINT16                w1secCount;         // 60Hz:3840, 50Hz:3200
  UINT16                w1usecCount;        // Timer0 1usec Count No
  UINT16                wSyncTimeSave;

  UINT16                wChat;              // DC Trip/Close Coil 체터링 시간 / 설정이 있지는 않지만 추가 함

  TIME_REG              Time;

} SETTING_REG;
extern SETTING_REG sSet;
extern SETTING_REG sSetTemp;


typedef struct
{
  UINT16                wRun;
  UINT16                w100ms;
  UINT16                w500ms;

} INT_COUNT;
enum
{
  eV,
  eIA,
  eIB,
  eIC,
};
enum    // sInt.fReal
{
  eINT_TEMP,            // 온도
  eINT_TC1,             // Trip Coil1 DC Code
  eINT_TC2,             // Trip Coil2 DC Code
  eINT_CC,              // Close Coil DC Code
  eINT_V_BIAS,          // V Bias
  eINT_IA_BIAS,         // IA Bias
  eINT_IB_BIAS,         // IB Bias
  eINT_IC_BIAS,         // IC Bias
/*
  eINT_RAW_V,           // V  Raw rms     / Gain 연산 안된 Data
  eINT_RAW_IA,          // IA Raw rms     / Gain 연산 안된 Data
  eINT_RAW_IB,          // IB Raw rms     / Gain 연산 안된 Data
  eINT_RAW_IC,          // IC Raw rms     / Gain 연산 안된 Data
  eINT_RAW_VP,          // V  RAW Phase   / VA 표준화 되기 전
  eINT_RAW_IAP,         // IA RAW Phase   / VA 표준화 되기 전
  eINT_RAW_IBP,         // IB RAW Phase   / VA 표준화 되기 전
  eINT_RAW_ICP,         // IC RAW Phase   / VA 표준화 되기 전
*/
  eINT_V,               // V rms
  eINT_IA,              // IA rms
  eINT_IB,              // IB rms
  eINT_IC,              // IC rms
  eINT_VP,              // V Phase
  eINT_IAP,             // IA Phase
  eINT_IBP,             // IB Phase
  eINT_ICP,             // IC Phase
  eINT_MAX,
};
#define eINT_100MS_NO   16
#define eINT_500MS_NO   16
typedef struct
{
  INT_COUNT             Cnt;

  float                 fReal[eINT_MAX];
  float                 f100ms[eINT_MAX][eINT_100MS_NO];
  float                 f100Real[eINT_MAX];
  float                 f500ms[eINT_MAX][eINT_500MS_NO];
  float                 f500Real[eINT_MAX];

} INT_REG;
extern INT_REG  sInt;

enum
{
  eINT_SV_PASS,
  eINT_SV_ID,
  eINT_SV_ETH,
  eINT_SV_TRIG,
  eINT_SV_DEBO,
  eINT_SV_TRIP,
  eINT_SV_INT,
  eINT_SV_DCRATIO,
  eINT_SV_ACRATIO,
  eINT_SV_DCZER,
  eINT_SV_DCSPR,
  eINT_SV_ACZER,
  eINT_SV_ACSPR,
  eINT_SV_DCZE,
  eINT_SV_DCSP,
  eINT_SV_ACZE,
  eINT_SV_ACSP,
  eINT_SV_ACPH,
  eINT_SV_MAX,
};

enum      // sRms sRmsSet
{
  eCAL_DSP_V,
  eCAL_DSP_VP,
  eCAL_DSP_IA,
  eCAL_DSP_IAP,
  eCAL_DSP_IB,
  eCAL_DSP_IBP,
  eCAL_DSP_IC,
  eCAL_DSP_ICP,
  eCAL_DSP_TC1,
  eCAL_DSP_TC2,
  eCAL_DSP_CC,
  eCAL_DSP_TEMP,
  eCAL_DSP_MAX,
};
typedef struct
{
  float                 fMin;
  float                 fMax;
  UINT16                *pwZeR;
  UINT16                *pwSpR;
  float                 *pfZe;
  float                 *pfSp;
  float                 *pfCode;
  float                 *pfRms;

} RMS_REG;
extern RMS_REG  sRms;
extern RMS_REG  sRmsSet[];


typedef struct
{
// 일반
  UINT16                wModel[8];
  UINT16                wSerial[16];
  UINT16                wVersion;

  UINT16                wDi;

  UINT16                wAlarm;
  UINT16                wError;
  UINT16                wFault;

  UINT16                wIpAddr[2];
  UINT16                wSubMask[2];
  UINT16                wDefGate[2];
  UINT16                wPortNum;
  UINT16                wLocIpAddr[2];

  UINT32                lUtc;

  UINT16                wTrig;          // 1040
  UINT16                wDebo;          // 1041

  UINT16                wReset;         // 1042
  UINT16                wFaErase;       // 1043
// <- 여기까지가 Modbus Memory Map 1043
  UINT16                wTrip[3];

  INT32                 ilUtc;

// 계측
  float                 fValue[eCAL_DSP_MAX];


  UINT32                lYYYYMMDD;

  float                 fVValue[eADC_MAX];   // IA, IB, IC 전압계측

  UINT16                wEthXCs;      // wIpAddress[0] ~ LocalIpAddr[1]
  UINT16                wTrigXCs;     // TrigTime
  UINT16                wDeboXCs;     // wDebounce
  UINT16                wTripXCs;     // DC 차단디 Trip 전류


  float                 fRealVal[eCAL_DSP_MAX];   // Real Value
  float                 fRealVVal[eADC_MAX];      // Real Value DC Current Voltge

  UINT16                wLv;

  TIME_REG              Time;
  UINT32                lUtcMs;

//  UINT16                wFault;


} DISPLAY_REG;
extern DISPLAY_REG sDsp;
extern DISPLAY_REG sDspTemp;



typedef struct _ETHER_STEP
{
  UINT8       bRx;
  UINT8       bTx;
//  UINT8       bRun;
  UINT8       bTxStart;       // Tx 시작 준비

  UINT8       bType;
  UINT8       bView;
//  UINT8       bInput;
//  UINT8       bOutput;
  UINT8       bAdc;

  UINT8       bDebugView;

//  UINT8       bTypeRet;
  UINT16                wRun;

} ETHER_STEP;
typedef struct _ETHER_COUNT
{
  UINT8   bTxStart;       // Master 일 때 송신 시간 Count
  UINT8   bRx;
  UINT8   bRxEnd;
  UINT8   bRxErr;
  UINT8   bTx;            // Tx 전송 진행
  UINT8   bTxEnd;         // Tx 전송 개수
  UINT8   bTxOff;         // Tx 전송 완료 후 PTT Off 카운트
//  UINT16  wLoss;
  UINT8   bRxData;

  UINT16  wTxTest;        // Test Mode에서 PC 통신 포트 이상 유무 검사용

  UINT16  wTerminal;

// Modbus
  UINT16    wRx;
  UINT16    wRxEnd;
  UINT16    wRxErr;
  UINT16    wSciErr;

} ETHER_COUNT;
#define eETH_MAX_BUF_SIZE		512
typedef struct _ETHER_REG
{
//  ETHER_STATUS Sta;
  ETHER_STEP   Stp;
  ETHER_COUNT  Cnt;

  UINT8       bRxData[eETH_MAX_BUF_SIZE];
  UINT8       bRxDataTemp[eETH_MAX_BUF_SIZE];
  UINT8       bTxData[eETH_MAX_BUF_SIZE];
  UINT8       bTxDataTemp[eETH_MAX_BUF_SIZE];
  UINT8       bRxCs;
  UINT8       bRxCsTemp;
  UINT8       bRxVersion;
  UINT8       bByteCount;

  UINT16      wLen;

//  union W2B   RxCrcTemp;
//  union W2B   RxCrc;
//  char        bCmd;
//  char        bCmdData[eTERMINAL_DATA];
//  UINT8       bCmdCount;

//  char        bCmdTp;

//  char        bCmdTy;           // dcZero, dcSpan, acZero, acSpan
//  char        bCmdSub;          // Range, Exit
//  char        bCmdNum;

// Modbus
//  BOOL        bModbus;

  UINT16      wCrc;

} ETHER_REG;
extern ETHER_REG     sEth;




/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void GPIO_Setup( UINT16 pin, UINT16 cpu, UINT16 peripheral, UINT16 output, UINT16 flags );

extern void DATA_OUT( UINT8 i_bOCS, UINT8 i_bData );
extern UINT8 DATA_IN( UINT8 i_bICS );

extern void Init_Gpio( void );
extern void Init_MemoryPointer( void );
extern void Init_RebootVariable( void );
extern void Init_BootVariable( void );
extern void Init_SettingRegister( void );
extern void Init_Register( void );
extern void Init_StartRegister( void );
extern void Init_Interrupt( void );

//extern char  *HEX2BIN( UINT8 i_bCount, UINT32 i_lHex );
extern void HEX2BIN( char *s, UINT8 i_bCount, UINT32 i_lHex );
extern UINT16 BIN2HEX( char *s );

extern void Boot_Make( void );

extern void Conv_CODE2RMS( RMS_REG sRms );
extern void Conv_VOLT2CURR( UINT16 i_wNo, float *i_pfSource, float *i_pfTarget );

extern void main_loop( void );
extern UINT8 Debug_View( void );


extern void EventWr( UINT16 i_wEvent );
extern char* List_Evt( UINT16 i_wType );
extern void EventRd( void );
extern char* List_Fat( UINT16 i_wType );
extern void FaultRd( void );
extern void FaultWr( UINT16 i_wNo );


#endif  /*__TIGERWIN_H*/

