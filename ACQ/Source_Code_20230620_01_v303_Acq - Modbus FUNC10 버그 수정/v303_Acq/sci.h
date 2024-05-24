/* ************************************ ************************************ *
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : sci.h
 *
 * ************************************ ************************************ */

#ifndef __SCI_H
#define __SCI_H

#include "main.h"
#include "tigerwin.h"



#define CPU_FREQ            200E6
//#define LSPCLK_FREQ  CPU_FREQ/32
#define LSPCLK_FREQ          CPU_FREQ/16      // LOSPCP 1일때 반으로 줄임
#define SCI_PRD_1200        (Uint16)(LSPCLK_FREQ/1200)-1
#define SCI_PRD_2400        (Uint16)(LSPCLK_FREQ/2400)-1
#define SCI_PRD_4800        (Uint16)(LSPCLK_FREQ/4800)-1
#define SCI_PRD_9600        (Uint16)(LSPCLK_FREQ/9600)-1
#define SCI_PRD_14400       (Uint16)(LSPCLK_FREQ/14400)-1
#define SCI_PRD_19200       (Uint16)(LSPCLK_FREQ/19200)-1
#define SCI_PRD_38400       (Uint16)(LSPCLK_FREQ/38400)-1
#define SCI_PRD_57600       (Uint16)(LSPCLK_FREQ/57600)-1
#define SCI_PRD_76800       (Uint16)(LSPCLK_FREQ/76800)-1
#define SCI_PRD_115200      (Uint16)(LSPCLK_FREQ/115200)-1
#define SCI_PRD_230400      (Uint16)(LSPCLK_FREQ/230400)-1
#define SCI_PRD_460800      (Uint16)(LSPCLK_FREQ/460800)-1
#define SCI_PRD_921600      (Uint16)(LSPCLK_FREQ/921600)-1


enum
{
  eMFC_STX = ':',       // 0x3A
  eMFC_ETX = '\r',      // 0x0D

  eCOMM_STX = 0x02,
  eCOMM_L = 'L',        // Lcd
  eCOMM_S = 'S',        // Shuttle
  eCOMM_ETX = 0x03,
  eCOMM_ENT = '\r',    // 수신 신호는 Ent 신호임
  eCOMM_ENT_ = '\n',    //

  eCOMM_SYNC= 0xA5,
};

#define PTT_DELAY           NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;  // 15ea 90nsec Delay // 14ea로도 동작하나 하나 더 줌


typedef struct _SCI_STEP
{
  UINT8   bRx;
  UINT8   bTx;
//  UINT8   bRun;
  UINT8   bTxStart;       // Tx 시작 준비
} SCI_STEP;

#define eCOMM_LOSS              200
//#define eSCI_START_SYNC         50  // 50msec마다 전송
typedef struct _SCI_COUNT
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
} SCI_COUNT;

#define eSCI_BUFFER     64
typedef struct _SCI_REG
{
  SCI_STEP    Stp;
  SCI_COUNT   Cnt;
  char        bRxData[eSCI_BUFFER];
  char        bRxDataTemp[eSCI_BUFFER];
  char        bTxData[eSCI_BUFFER];
  char        bTxDataTemp[eSCI_BUFFER];
  UINT8       bRxCs;
  UINT8       bRxCsTemp;
  UINT8       bRxVersion;
  UINT8       bByteCount;

//  union W2B   RxCrcTemp;
//  union W2B   RxCrc;

} SCI_REG;
extern SCI_REG     sScib;


typedef struct _DEBUG_STATUS
{
  UINT8       bDebug;
//  UINT8       bCard;      // 디버그 선택된 Card
  UINT8       bAllCal;    // All Cal.
  UINT8       bView;

} DEBUG_STATUS;

enum    // sDbg.Step.bRx
{
  eMB_RX_TR_ID_HI,
  eMB_RX_TR_ID_LO,
  eMB_RX_PO_ID_HI,
  eMB_RX_PO_ID_LO,
  eMB_RX_LEN_HI,
  eMB_RX_LEN_LO,

  eMB_RX_ID,
  eMB_RX_FN,
  eMB_RX_RD_S_ADD_HI,
  eMB_RX_RD_S_ADD_LO,
  eMB_RX_RD_NO_HI,
  eMB_RX_RD_NO_LO,
  eMB_RX_WR_ADD_HI,
  eMB_RX_WR_ADD_LO,
  eMB_RX_WR_DATA_HI,
  eMB_RX_WR_DATA_LO,
  eMB_RX_MWR_S_ADD_HI,
  eMB_RX_MWR_S_ADD_LO,
  eMB_RX_MWR_WORD_CNT_HI,
  eMB_RX_MWR_WORD_CNT_LO,
  eMB_RX_MWR_BYTE_CNT,
  eMB_RX_MWR_VALUE,
  eMB_RX_CRC_HI,
  eMB_RX_CRC_LO,
  eMB_RX_END,
  eMB_RX_END_FIX,
};
enum        // sDebug.bDebugView
{
  eDEBUG_VIEW_NORMAL,
  eDEBUG_VIEW_ERROR_ING,
  eDEBUG_VIEW_ERROR_FIX,
  eDEBUG_VIEW_MAX     //,
};
typedef struct _DEBUG_STEP
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

} DEBUG_STEP;

typedef struct _DEBUG_COUNT
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

//  UINT8   bDi;
//  UINT8   bDiData;
//  UINT8   bDo;
//  UINT8   bDoData;

  UINT16  wTerminal;

// Modbus
  UINT16    wRx;
  UINT16    wRxEnd;
  UINT16    wRxErr;
  UINT16    wSciErr;

} DEBUG_COUNT;

//#define eSCID_BUFFER    256
#define eTERMINAL_DATA  40

enum
{
// sDbg.Stp.bType, pSci.Stp.bType
  eST_DBG_NORMAL,       // 0에서 이동하면 안됨

  eST_DBG_LOGO,
  eST_DBG_VIEW,
  eST_DBG_CLEAR,
  eST_DBG_RESET,
  eST_DBG_HELP,
  eST_DBG_EXIT,
  eST_DBG_BACK,

  eST_DBG_PASSWORD,
  eST_DBG_SETTING,
  eST_DBG_DEBUG,

  eST_DBG_ETHER,        // 10
  eST_DBG_LIST,
  eST_DBG_SYS,
  eST_DBG_ETC,
  eST_DBG_FACT,

// Ethernet
  eST_DBG_IP,
  eST_DBG_SUB,
  eST_DBG_DEF,
  eST_DBG_PORT,
  eST_DBG_LOC,
  eST_DBG_MAC,

// System
  eST_DBG_DEBOUNCE,     // 20
  eST_DBG_TRIPNUM,      //
  eST_DBG_TRIPCURR,     //
  eST_DBG_RATIO,        //
// Setting/Sys/Rstio
  eST_DBG_RATIO1,       //
  eST_DBG_RATIO2,       //
  eST_DBG_RATIO3,       //
  eST_DBG_RATIO4,       //
  eST_DBG_RATIO5,       //
  eST_DBG_RATIO6,       //
  eST_DBG_RATIO7,       //

// List
  eST_DBG_EVENT,        //
  eST_DBG_FAULT,        //

// Etc
  eST_DBG_TIME,
  eST_DBG_NEWPASS,
  eST_DBG_RE_ENTPASS,
  eST_DBG_MODEL,
  eST_DBG_SERIAL,
  eST_DBG_100MS,        // 30
  eST_DBG_500MS,

// Sys/Ratio
//  eST_DBG_DC_RATIO,      //

// List/Event
  eST_DBG_E_LIST,
  eST_DBG_E_ERASE,
// List/Fault
  eST_DBG_F_LIST,
  eST_DBG_F_ERASE,

// List/Fault
  eST_DBG_NO,

// Etc/Time
  eST_DBG_YEAR,         // YEAR
  eST_DBG_MON,          // MON
  eST_DBG_DAY,          // DAY
  eST_DBG_HOUR,         // 40 / HOUR
  eST_DBG_MIN,          // MIN
  eST_DBG_SEC,          // SEC

// Calibration
  eST_DBG_ACCALI,
  eST_DBG_DCCALI,

  eST_DBG_DCALL,
  eST_DBG_DC1,
  eST_DBG_DC2,
  eST_DBG_DC3,
  eST_DBG_DC_RATIO,

  eST_DBG_ACALL,
  eST_DBG_AC1,
  eST_DBG_AC2,
  eST_DBG_AC3,
  eST_DBG_AC4,
  eST_DBG_PH,
  eST_DBG_AC_RATIO,

  eST_DBG_DCALL_ZERO,
  eST_DBG_DC1_ZERO,
  eST_DBG_DC2_ZERO,
  eST_DBG_DC3_ZERO,
  eST_DBG_DCALL_SPAN,
  eST_DBG_DC1_SPAN,
  eST_DBG_DC2_SPAN,
  eST_DBG_DC3_SPAN,

  eST_DBG_ACALL_ZERO,
  eST_DBG_AC1_ZERO,
  eST_DBG_AC2_ZERO,
  eST_DBG_AC3_ZERO,
  eST_DBG_AC4_ZERO,
  eST_DBG_ACALL_SPAN,
  eST_DBG_AC1_SPAN,
  eST_DBG_AC2_SPAN,
  eST_DBG_AC3_SPAN,
  eST_DBG_AC4_SPAN,

  eST_DBG_DCALLRZERO,      // 50
  eST_DBG_DCALLRSPAN,
  eST_DBG_DC1RZERO,      // 50
  eST_DBG_DC1RSPAN,
  eST_DBG_DC2RZERO,      // 50
  eST_DBG_DC2RSPAN,
  eST_DBG_DC3RZERO,      // 50
  eST_DBG_DC3RSPAN,

  eST_DBG_ACVRZERO,
  eST_DBG_ACVRSPAN,
  eST_DBG_ACIRZERO,
  eST_DBG_ACIRSPAN,
  eST_DBG_AC1RZERO,
  eST_DBG_AC1RSPAN,
  eST_DBG_AC2RZERO,
  eST_DBG_AC2RSPAN,
  eST_DBG_AC3RZERO,
  eST_DBG_AC3RSPAN,
  eST_DBG_AC4RZERO,
  eST_DBG_AC4RSPAN,

//  eST_DBG_DCRATIO,      //
// Dccali/dcRatio
  eST_DBG_DCRATIO,      //
  eST_DBG_DCRATIO1,
  eST_DBG_DCRATIO2,
  eST_DBG_DCRATIO3,
  eST_DBG_ACVRATIO,
  eST_DBG_ACIRATIO,
  eST_DBG_ACRATIO1,
  eST_DBG_ACRATIO2,
  eST_DBG_ACRATIO3,
  eST_DBG_ACRATIO4,

  eST_DBG_NUMBER,       // 60
  eST_DBG_CHAR,


// sDbg.bCmd, pSci->bCmd
  eK_LOGO               = 'L',    // Ver & Logo
  eK_VIEW               = 'V',    // Setting View
  eK_CLEAR              = 'C',    // Clear
  eK_RESET              = 'R',    // Reset
  eK_HELP               = '?',    // Help
  eK_SAVE               = 'S',    // Save
  eK_EXIT               = 'X',    // eXit
  eK_BACK               = 'B',    // Back
  eK_PASS               = 'P',    // Password
  eK_SETTING            = 'S',    // Setting
  eK_DEBUG              = 'D',    // Debug

//  eK_NUMBER
//  eK_CHAR

// Setting
  eK_ETHER              = 'E',    // Ethernet
  eK_LIST               = 'L',    // List
  eK_SYS                = 'S',    // System
  eK_ETC                = 'T',    // eTc
  eK_FACT               = 'F',    // Factory

// Ethernet
  eK_IP                 = 'I',    // Ip address
  eK_SUB                = 'S',    // Subnet mask
  eK_DEF                = 'D',    // Default gateway
  eK_PORT               = 'P',    // Port number
  eK_LOC                = 'L',    // Local unit ip address
  eK_MAC                = 'M',    // MAC

// List
  eK_EVENT              = 'E',    // Event List
  eK_FAULT              = 'F',    // Fault List
// Event
  eK_E_LIST             = 'L',
  eK_E_ERASE            = 'E',
// Fault
  eK_F_LIST             = 'L',
  eK_F_ERASE            = 'E',
  eK_NO                 = 'N',    // No (1~26)
  eK_NUM1               = '1',    // TC1
  eK_NUM2               = '2',    // TC2
  eK_NUM3               = '3',    // CC
  eK_NUM4               = '4',    // V
  eK_NUM5               = '5',    // IA
  eK_NUM6               = '6',    // IB
  eK_NUM7               = '7',    // IC
  eK_NUM8               = '8',    // Contect

// System
  eK_DEBOUNCE           = 'D',    // Debounce
  eK_TRIPNUM            = 'N',    // trip Number
  eK_TRIPCURR           = 'T',    // Trip current
  eK_RATIO              = 'R',    // Ratio
// Sys/Ratio
  eK_RATIO1             = '1',    // Ratio1
  eK_RATIO2             = '2',    // Ratio2
  eK_RATIO3             = '3',    // Ratio3
  eK_RATIO4             = '4',    // Ratio4
  eK_RATIO5             = '5',    // Ratio5
  eK_RATIO6             = '6',    // Ratio6
  eK_RATIO7             = '7',    // Ratio7

// Etc
//  eK_PASS               = 'P',    // Password
  eK_TIME               = 'T',    // Time
  eK_MODEL              = 'M',    // Model
  eK_SERIAL             = 'S',    // Serial
  eK_100MS              = '1',    // 100ms
  eK_500MS              = '5',    // 500ms

// Etc/Time
  eK_YEAR               = 'Y',    // Year
  eK_MON                = 'M',    // Mon
  eK_DAY                = 'D',    // Day
  eK_HOUR               = 'O',    // hOur
  eK_MIN                = 'I',    // min
  eK_SEC                = 'S',    // Sec

// AC Calibration
  eK_ACCALI             = 'A',    // Ac calibration
// Accali
  eK_ACALL              = 'A',    // ac All
  eK_AC1                = '1',    // ac1(V)
  eK_AC2                = '2',    // ac2(IA)
  eK_AC3                = '3',    // ac3(IB)
  eK_AC4                = '4',    // ac4(IC)
  eK_ACRATIO            = 'R',    // acRatio
// Accali/acAll, Accali/ac1, Accali/ac2, Accali/ac3, Accali/ac4
  eK_ACALLVR            = 'V',    // ac all v Range
  eK_ACALLR             = 'R',    // ac all i Range
  eK_AC1R               = 'R',    // ac1(V) Range
  eK_AC2R               = 'R',    // ac2(IA) Range
  eK_AC3R               = 'R',    // ac3(IB) Range
  eK_AC4R               = 'R',    // ac4(IC) Range
// Acali/acRatio
  eK_AC_RATIO           = 'R',    // acRatio
  eK_ACVRATIO           = 'V',    // acVratio
  eK_ACIRATIO           = 'R',    // aciRatio
  eK_ACRATIO1           = '1',    // acratio1
  eK_ACRATIO2           = '2',    // acratio2
  eK_ACRATIO3           = '3',    // acratio3
  eK_ACRATIO4           = '4',    // acratio1

// DC Calibration
  eK_DCCALI             = 'D',    // Dc calibration
// Dccali
  eK_DCALL              = 'A',    // dc All
  eK_DC1                = '1',    // dc1 (TC1)
  eK_DC2                = '2',    // dc2 (TC2)
  eK_DC3                = '3',    // dc3 (CC)
  eK_DCRATIO            = 'R',    // dc Ratio
// Dccali/dcAll, Dccali/dc1, Dccali/dc2, Dccali/dc3
  eK_DCALLR             = 'R',    // dc All Range
  eK_DC1R               = 'R',    // dc1(TC1) Range
  eK_DC2R               = 'R',    // dc2(TC2) Range
  eK_DC3R               = 'R',    // dc3(CC) Range
// Dccali/dcRatio
  eK_DC_RATIO           = 'R',    // dcRatio
  eK_DCRATIO1           = '1',    // dcratio1
  eK_DCRATIO2           = '2',    // dcratio2
  eK_DCRATIO3           = '3',    // dcratio3

  eK_ZERO               = 'Z',    // Zero
  eK_SPAN               = 'S',    // Span
  eK_PH                 = 'P',    // Phase
  eK_VRANGE             = 'V',    // Voltage Range
  eK_RANGE              = 'R',    // Range


  eK_SPACE              = ' ',    // space
  eK_BS                 = 0x08,   // BackSpace
  eK_ENT                = '\r',   // Enter
  eK_BACKSLASH          = 0x5C,   // Backslash
  eK_SLASH              = '/',    // Slash
  eK_ESC                = 0x1B,   // ESC
};
enum
{
  eVIEW_LINE1,
  eVIEW_LINE2,
  eVIEW_LINE3,
  eVIEW_LINE4,
  eVIEW_LINE5,
  eVIEW_LINE6,
  eVIEW_LINE7,
  eVIEW_LINE8,
  eVIEW_LINE9,
  eVIEW_LINE10,
  eVIEW_LINE11,
  eVIEW_LINE12,
  eVIEW_LINE13,
  eVIEW_LINE14,
  eVIEW_LINE15,
  eVIEW_LINE16,
};
typedef struct _DEBUG_REG
{
  DEBUG_STATUS Sta;
  DEBUG_STEP   Stp;
  DEBUG_COUNT  Cnt;

  char        bRxData[eSCI_BUFFER];
  char        bRxDataTemp[eSCI_BUFFER];
  char        bTxData[eSCI_BUFFER*4];
  char        bTxDataTemp[eSCI_BUFFER];
  UINT8       bRxCs;
  UINT8       bRxCsTemp;
  UINT8       bRxVersion;
  UINT8       bByteCount;

  UINT16      wLen;

//  union W2B   RxCrcTemp;
//  union W2B   RxCrc;
  char        bCmd;
  char        bCmdData[eTERMINAL_DATA];
  UINT8       bCmdCount;

  char        bCmdTp;

  char        bCmdTy;           // dcZero, dcSpan, acZero, acSpan
  char        bCmdSub;          // Range, Exit
  char        bCmdNum;

  UINT16      wCrc;

} DEBUG_REG;
extern DEBUG_REG     sDbg;


enum
{
  eST_LINE_RUN,
  eST_LINE_LINE1,
  eST_LINE_TIME,
  eST_LINE_LINE2,
  eST_LINE_INFO,
  eST_LINE_LINE3,
  eST_LINE_VALUE,
  eST_LINE_PHASE,
  eST_LINE_LINE_DBG,
  eST_LINE_ZEROR,
  eST_LINE_SPANR,
  eST_LINE_LINE4,
  eST_LINE_ZERO,
  eST_LINE_SPAN,
  eST_LINE_PH,
  eST_LINE_RATIO,
  eST_LINE_LINE_END,
  eST_LINE_END = 99,
  eST_LINE_WAIT,
  eST_LINE_STA,
  eST_LINE_HELP_STA,
  eST_LINE_HELP,
};



#define eMAIN_TIME_CHECK        20          // 0.3333usec


#if(1)
enum    // sKey.bMode
{
  eKEY_MD_UINT8,
  eKEY_MD_INT8,
  eKEY_MD_UINT16,
  eKEY_MD_INT16,
  eKEY_MD_UINT32,
  eKEY_MD_INT32,
  eKEY_MD_FLOAT,
  eKEY_MD_UINT16_B,
  eKEY_MD_TIME,
  eKEY_MD_UINT16_IP,
  eKEY_MD_UINT16_MAC,
};
enum    // sKey.ibDot, sKey.ibDotP
{
  eKEY_DOT_0_00001  = -6,
  eKEY_DOT_0_0001,
  eKEY_DOT_0_001,
  eKEY_DOT_0_01,
  eKEY_DOT_0_1,
  eKEY_DOT_1_0,
  eKEY_DOT_1,               // 0
  eKEY_DOT_10,
  eKEY_DOT_100,
  eKEY_DOT_1000,
  eKEY_DOT_10000,
  eKEY_DOT_100000,
};
typedef struct _KEY_REG
{
  UINT8           bPageBack;      // Page Back 월래 Page로 이동
  UINT8           bPageGo;        // Page Go 원하는 Page로 이동
  UINT8           bNo;            // 255.255.255.255 -> 4
  INT8            ibDotP;         // Dot 현재 위치
  UINT16          wMul;           // 곱하기
  UINT8           bMode;          // Value Data 종류
  UINT8           *pbKey;         // 저장 위치
  INT8            *pibKey;        // 저장 위치
  UINT16          *pwKey;         // 저장 위치
  INT16           *piwKey;        // 저장 위치
  UINT32          *plKey;         // 저장 위치
  INT32           *pilKey;        // 저장 위치
  float           *pfKey;         // 저장 위치
  float           fKey;           // Value값
  float           fMin;           // Min값
  float           fMax;           // Max값
  float           fValue[6];

} KEY_REG;
extern KEY_REG     sKey;

#endif



typedef struct
{
  UINT16                wNo;
  UINT16                wType;
  INT32                 ilUtc;
  UINT32                lUtcMs;

  UINT16                wEv;
  UINT8                 bNo;
  TIME_REG              Time;

} EVT_REG;
extern EVT_REG  sEvt;

enum
{
  eFA_TC1_DI2,
  eFA_TC1_IA,
  eFA_TC1_IB,
  eFA_TC1_IC,
  eFA_TC2_DI2,
  eFA_TC2_IA,
  eFA_TC2_IB,
  eFA_TC2_IC,
  eFA_CC_DI1,
  eFA_CC_IA,
  eFA_CC_IB,
  eFA_CC_IC,

  eFA_B_TC1_DI2   = ( BIT0 << eFA_TC1_DI2 ),
  eFA_B_TC1_IA    = ( BIT0 << eFA_TC1_IA ),
  eFA_B_TC1_IB    = ( BIT0 << eFA_TC1_IB ),
  eFA_B_TC1_IC    = ( BIT0 << eFA_TC1_IC ),
  eFA_B_TC2_DI2   = ( BIT0 << eFA_TC2_DI2 ),
  eFA_B_TC2_IA    = ( BIT0 << eFA_TC2_IA ),
  eFA_B_TC2_IB    = ( BIT0 << eFA_TC2_IB ),
  eFA_B_TC2_IC    = ( BIT0 << eFA_TC2_IC ),
  eFA_B_CC_DI1    = ( BIT0 << eFA_CC_DI1 ),
  eFA_B_CC_IA     = ( BIT0 << eFA_CC_IA ),
  eFA_B_CC_IB     = ( BIT0 << eFA_CC_IB ),
  eFA_B_CC_IC     = ( BIT0 << eFA_CC_IC ),
};
typedef struct
{
  UINT16                wNo;
  UINT16                wType;
  INT32                 ilUtc;
  UINT32                lUtcMs;
  float                 fContDA;
  float                 fContDB;
  float                 fContDC;
  float                 fTc1Pc;
  float                 fTc1Cf;
  float                 fTc2Pc;
  float                 fTc2Cf;
  float                 fCc_Pc;
  float                 fCc_Cf;
  float                 fCc_A;
  float                 fTc_B;
  float                 fTc_Cc_A;
  float                 fTc_Cc_B;
  float                 fTc_Cc_C;

  UINT16                wTrig;        // Raw 저장 Point
  UINT16                wFa;
  UINT16                bType;        //
  UINT16                bNo;          // 저장 개수 Count    // 300msec 저장 이므로 2304개(*2) 저장
  UINT16                wEnd;         // Count 동작 정지 비트
  TIME_REG              Time;

} FATRD_REG;
extern FATRD_REG  sFatRd;

typedef struct
{
  FATRD_REG             No[26];

  UINT16                wList;
  UINT16                wNo;
  UINT16                wPit;

  UINT16                wMb[17];       // Modbus 64word 단위 전송되면 1이 되는 bit 270(16word + 14)개

} FAT_REG;
extern FAT_REG  sFat;



//---------------------------------------------------------------------------
// SCI 번지




// SCI 번지
//---------------------------------------------------------------------------



extern void Init_Sci( void );

//extern void Sci_Hmi_Make( DEBUG_REG *pSci );

extern void Sci_Make( void );

extern UINT16 BCD2DEC( UINT16 i_wBcd );
extern UINT16 DEC2BCD( UINT16 i_wDec );

#endif /* __SCI_H */ 
