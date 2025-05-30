/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name	  : modbus.c
 *
 * *************************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include "F28x_Project.h"       // Device Headerfile and Examples Include File
#include "string.h"             //
#include "stdio.h"              //
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "tigerwin.h"
#include "sci.h"
#include "modbus.h"
#include "rtc.h"
#include "emif.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
MODBUS_REG    sMb;

/* Private function prototypes -----------------------------------------------*/
void Modbus_Data( void );
BOOL Modbus_WaveRd( void );
void Init_Modbus( void );
void Modbus_Func( ETHER_REG *pEth );
void Modbus_CommError( ETHER_REG *pEth, UINT8 bErrorCode );
//UINT16 Modbus_Address( UINT8 i_bStep );
BOOL Modbus_Addr( ETHER_REG *pEth, MODBUS_REG *pMb );
void Modbus_RxMake( ETHER_REG *pEth );
//void Modbus_RxMake( void );
UINT16 Modbus_Crc( UINT8 *i_pbData, UINT16 i_wLen );
UINT16 Rx_ErrorCount( UINT8 i_bBps, UINT16 i_wLen );

/* Private user code ---------------------------------------------------------*/


void Modbus_Data( void )
{
  UINT16  i;

//20220607 Alarm 과 Error 동작 시켜야 됨
  if( Modbus_WaveRd( ) )
  {
    if( ++sCnt.wFaMb >= ( eFAULT_MAX *2 ) )
      sCnt.wFaMb = eFAULT_MAX;
    for( i=0; i<17; i++ )
      sFat.wMb[i] = 0;
  }
  if( sCnt.wFaMb != sCnt.wFaEnd && sCnt.wFa == sCnt.wFaEnd )
  {
UINT16  i_wFa = 0;
    if( sCnt.wFaEnd > sCnt.wFaMb )  i_wFa = sCnt.wFaEnd - sCnt.wFaMb;
    else                            i_wFa = ( eFAULT_MAX + sCnt.wFaEnd ) - sCnt.wFaMb;
    sDsp.wFault = 0xFF00 | i_wFa;
  }
  else
    sDsp.wFault = 0x0000;
}
BOOL Modbus_WaveRd( void )
{
  UINT16  i, i_wNum = 0;

  for( i=0; i<16; i++ )
  {
    if( sFat.wMb[i] == 0xFFFF )
      i_wNum++;
  }
  if( i_wNum == 16 )
  {
    if( sFat.wMb[i] == 0x3FFF )
      return 1;
  }
  return 0;
}

enum
{
  eMB_PIT_F03_SET,
  eMB_PIT_F03_MEAS,
  eMB_PIT_F03_LIST,
  eMB_PIT_F03_WAVE,
  eMB_PIT_F06_SET0,
  eMB_PIT_F06_SET1,
  eMB_PIT_F10_SET,
  eMB_PIT_MAX,
};
void Init_Modbus( void )
{
  sMb.bId           = sSet.wId;
  sMb.wNo           = eMB_PIT_MAX;
  sMb.Pit[eMB_PIT_F03_SET ].pwPit = (UINT16 *)&sDsp.wModel;                 // Setting
  sMb.Pit[eMB_PIT_F03_SET ].wSta  = 1000;
  sMb.Pit[eMB_PIT_F03_SET ].wEnd  = 1043;
//  sMb.Pit[eMB_PIT_F03_SET ].wEnd  = 1042;
  sMb.Pit[eMB_PIT_F03_MEAS].pwPit = (UINT16 *)&sDsp.fValue;                 // 측정
  sMb.Pit[eMB_PIT_F03_MEAS].wSta  = 1100;
  sMb.Pit[eMB_PIT_F03_MEAS].wEnd  = 1123;
  sMb.Pit[eMB_PIT_F03_LIST].pwPit = (UINT16 *)&pFault->No[0].wNo;           // Fault List / 항상 바뀜
  sMb.Pit[eMB_PIT_F03_LIST].wSta  = 1200;
  sMb.Pit[eMB_PIT_F03_LIST].wEnd  = 1233;
  sMb.Pit[eMB_PIT_F03_WAVE].pwPit = (UINT16 *)&pWave->No[0].iwTripCoil1;    // Fault Wave / 항상 바뀜
  sMb.Pit[eMB_PIT_F03_WAVE].wSta  = 1300;
  sMb.Pit[eMB_PIT_F03_WAVE].wEnd  = 18579;
  sMb.Pit[eMB_PIT_F06_SET0].pwPit = (UINT16 *)&sDsp.wIpAddr;                // Setting IpAddress ~ LocIpAddr
  sMb.Pit[eMB_PIT_F06_SET0].wSta  = 1029;
  sMb.Pit[eMB_PIT_F06_SET0].wEnd  = 1037;
// 1038~1039(ilUtc)가 32bit라 F06으로 쓰면 안됨 시간이라 문제가 될 수 있음
  sMb.Pit[eMB_PIT_F06_SET1].pwPit = (UINT16 *)&sDsp.wTrig;                  // Setting wTrig ~ FaErase
  sMb.Pit[eMB_PIT_F06_SET1].wSta  = 1040;
  sMb.Pit[eMB_PIT_F06_SET1].wEnd  = 1043;
//  sMb.Pit[eMB_PIT_F06_SET1].wEnd  = 1042;
  sMb.Pit[eMB_PIT_F10_SET].pwPit  = (UINT16 *)&sDsp.wIpAddr;                // Setting IpAddress ~ Di Debounce Time
  sMb.Pit[eMB_PIT_F10_SET].wSta   = 1029;
  sMb.Pit[eMB_PIT_F10_SET].wEnd   = 1041;
}


enum
{
  eMB_NO,       // 8ea Data
  eMB_F03,
  eMB_F04,
  eMB_F06,
  eMB_F10,      // Func 0x10 8ea + Byte Len
};
enum
{
  eMB_ILL_FUNC    = 1,      // 1
  eMB_ILL_ADDR,             // 2
  eMB_ILL_VAL,              // 3
};
enum
{
// 참고 : http://comfilewiki.co.kr/ko/doku.php?id=tcpport:funtion_code%EB%B3%84_data_%EA%B5%AC%EC%A1%B0_%EB%B0%8F_%EB%94%94%EB%B0%94%EC%9D%B4%EC%8A%A4_%EC%A0%9C%EC%96%B4:index
// 참고 : https://search.naver.com/p/crd/rd?m=1&px=297&py=596&sx=297&sy=212&p=hN0nzlprvxsssOESjVVssssstHZ-333792&q=modbus+function+1&ie=utf8&rev=1&ssc=tab.nx.all&f=nexearch&w=nexearch&s=0PtFNgkMKb7cZ2oTCgt0wQ%3D%3D&time=1640828883799&a=web_gen*D.link&r=1&i=a00000fa_be4c45728443552eaef456c4&u=https%3A%2F%2Fwww.modbus.org%2Fdocs%2FPI_MBUS_300.pdf&cr=2
// Coil과 Input은 bit제어는 같으나 Write에서 지원 안됨
//                                                    / U8;U8;U16  ;U16  ;U16                     -> U8;U8;U8  ;U16  ;CRC
// Coil Port 0000(16)부터 8bit Read (16~24bit)        / ID;FN;START;LEN  ;CRC                     -> ID;FN;BYTE;DATA ;CRC
  eMB_FUNC01    = 0x01,     // Read Coil              / FF;01;00;00;00;08;A5;5A                   -> 01;01;01  ;00   ;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U16                     -> U8;U8;U8  ;U16  ;CRC
// Input Port 0000부터 16bit Read (0~15bit)           / ID;FN;START;LEN  ;CRC                     -> ID;FN;BYTE;DATA ;CRC
  eMB_FUNC02    = 0x02,     // Read Input             / FF;02;00;00;00;10;A5;5A                   -> 01;02;02  ;00;00;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U16                     -> U8;U8;U8  ;U16  ;U16  ;CRC
// Register 번지0000부터 2word Read                   / ID;FN;START;LEN  ;CRC                     -> ID;FN;BYTE;AI0  ;AI1  ;CRC
  eMB_FUNC03    = 0x03,     // Read Register          / FF;03;00;00;00;02;A5;5A                   -> 01;03;04  ;00;00;00;00;A5;5A
  eMB_FUNC04    = 0x04,     // Read Register          / FF;04;00;00;00;02;A5;5A                   -> 01;04;04  ;00;00;00;00;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U16                     -> U8;U8;U16  ;U16  ;U16
// Coil Port 0000(16) On(FF00)(Off:0000) (16~24번지)  / ID;FN;START;DATA ;CRC                     -> ID;FN;START;DATA ;CRC
  eMB_FUNC05    = 0x05,     // Write Signal Coil      / FF;05;00;00;FF;00;A5;5A                   -> FF;01;00;00;FF;00;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U16                     -> U8;U8;U16  ;U16  ;U16
// Register 0004번지 0x1234 Write                     / ID;FN;START;DATA ;CRC                     -> ID;FN;START;DATA ;CRC
  eMB_FUNC06    = 0x06,     // Write Signal Register  / FF;06;00;04;12;34;A5;5A                   -> FF;06;00;04;12;34;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U8  ;U16  ;U16          -> U8;U8;U16  ;U16  ;U16
// Output Port 7,4,3,2,0(0x9D) On                     / ID;FN;START;LEN  ;BYTE;DATA ;CRC          -> ID;FN;START;LEN  ;CRC
  eMB_FUNC0F    = 0x0F,     // Write Multi Coils      / FF;0F;00;10;00;08;01  ;9D   ;A5;5A        -> FF;06;00;10;00;08;A5;5A
//                                                    / U8;U8;U16  ;U16  ;U8  ;U16  ;U16  ;U16    -> U8;U8;U16  ;U16  ;U16
// Register 0004~0005번지 20(0x14), 60(0x3C) Write    / ID;FN;START;LEN  ;BYTE;DATA ;DATA ;CRC    -> ID;FN;START;LEN  ;CRC
  eMB_FUNC10    = 0x10,     // Write Multi Register   / FF;10;00;04;00;02;04  ;00;14;00;3C;A5;5A  -> FF;06;00;04;00;02;A5;5A
};

#define eMB_RX_1MIN_INIT    (60*1000)   // 1분 마다 수신 버퍼 변경이 없으면 초기화
void Modbus_RxMake( ETHER_REG *pEth )
{
  UINT8   i_bData;
//  UINT8   i_bBank = pEth->Cnt.bRxBank ^ 0x01;
//  UINT16  i = 0, j = 0;
//  UINT16  i_wLen;
//  UINT16  *i_pwData;
//  UINT8   *i_pbRxData;

// 여기에 bps별 초기화 Count 만들어야 됨
#if(0)
// 20220615  Modbus_Make 함수 만들어 일정 시간 동안 수신이 없으면 버퍼 번지 초기화 시켜야 됨
#if(1)
// 이 구조를 썻으면 졸겠는데 Len이 계속 바뀌는게 아니라 다 수신 되면 바뀌는 구조라 이 구조를 사용 할 수 없음
  i_wLen = LL_DMA_GetDataLength( DMA1, LL_DMA_CHANNEL_3 );
  if( LL_DMA_GetDataLength( DMA1, LL_DMA_CHANNEL_2 ) != 0 || pEth->wLenOld != i_wLen )
  {
    pEth->Cnt.wRxErr = Rx_ErrorCount( eBPS_19200, i_wLen );
    pEth->Cnt.wUartErr = 0;
  }
  pEth->wLenOld = i_wLen;

  if( --pEth->Cnt.wRxErr == 0 )    // 여기에 DMA RX Count 변화가 없으면 --동작 시킴
  {
    pEth->Cnt.wRxErr = eMB_RX_1MIN_INIT;

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    pEth->Stp.bRxDma = eMB_NO;
    pEth->bRxData[0][0] = 0;
    pEth->bRxData[0][1] = 0;
    pEth->bRxData[1][0] = 0;
    pEth->bRxData[1][1] = 0;
    LL_DMA_SetMemoryAddress( DMA1, LL_DMA_CHANNEL_3, (uint32_t)&pEth->bRxData[pEth->Cnt.bRxBank][0] );
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, 8);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    pEth->Cnt.wRx = pEth->Cnt.wRxEnd = 0;
  }
#endif
  if( sStatus.wPowerOnDelaySec & eON_DELAY_7S )
  {
    if( ++pEth->Cnt.wUartErr >= eUART_FAIL )
    {
      pEth->Cnt.wUartErr = eUART_FAIL;
      sError.wStatus |= eERR_B_UART;
    }
    else
      sError.wStatus &= ~eERR_B_UART;
  }
#endif

  for( ; pEth->Cnt.bRx != pEth->Cnt.bRxEnd; )
  {
    i_bData = pEth->bRxData[pEth->Cnt.bRxEnd++];
    pEth->Cnt.bRxEnd %= eSCI_BUFFER;

// Modbus Start
    switch( pEth->Stp.bRx )
    {
    case eMB_RX_TR_ID_HI:
      sMb.Cnt.wRxData = 0;
    case eMB_RX_TR_ID_LO:
    case eMB_RX_PO_ID_HI:
    case eMB_RX_PO_ID_LO:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
    break;
    case eMB_RX_LEN_HI:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
      sMb.wRxLen = i_bData;
    break;
    case eMB_RX_LEN_LO:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
      sMb.wRxLen = (UINT16)i_bData << 8;
    break;
    case eMB_RX_ID:
//      sMb.Cnt.wRxData = 0;
      if( sMb.bId != i_bData && i_bData != 0xFF )
        pEth->Stp.bRx = eMB_RX_END -1;    // Fail
      else
        sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
    break;
    case eMB_RX_FN:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
      if( eMB_FUNC03 == i_bData || eMB_FUNC04 == i_bData )
        pEth->Stp.bRx = eMB_RX_RD_S_ADD_HI -1;
      else if( eMB_FUNC06 == i_bData )
        pEth->Stp.bRx = eMB_RX_WR_ADD_HI -1;
      else if( eMB_FUNC10 == i_bData )
        pEth->Stp.bRx = eMB_RX_MWR_S_ADD_HI -1;
      else
        pEth->Stp.bRx = eMB_RX_END -1;    // Fail
    break;
// Read ADD HI LO, No HI 
    case eMB_RX_RD_NO_LO:
      pEth->Stp.bRx = eMB_RX_CRC_HI -1;
    case eMB_RX_RD_S_ADD_HI:
    case eMB_RX_RD_S_ADD_LO:
    case eMB_RX_RD_NO_HI:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
    break;
// Write ADD HI LO, No HI
    case eMB_RX_WR_DATA_LO:
      pEth->Stp.bRx = eMB_RX_CRC_HI -1;
    case eMB_RX_WR_ADD_HI:
    case eMB_RX_WR_ADD_LO:
    case eMB_RX_WR_DATA_HI:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
    break;
// Multi Write ADD HI LO, Woed Count, Byte Count
    case eMB_RX_MWR_BYTE_CNT:
      sMb.Cnt.wLen = (UINT16)i_bData;
    case eMB_RX_MWR_S_ADD_HI:
    case eMB_RX_MWR_S_ADD_LO:
    case eMB_RX_MWR_WORD_CNT_HI:
    case eMB_RX_MWR_WORD_CNT_LO:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
    break;
    case eMB_RX_MWR_VALUE:
      sMb.bRxData[sMb.Cnt.wRxData++] = i_bData;
      if( sMb.Cnt.wRxData >= ( sMb.Cnt.wLen + 13 ) )
        pEth->Stp.bRx = eMB_RX_CRC_HI -1;
      else
        pEth->Stp.bRx = eMB_RX_MWR_VALUE -1;
    break;
    case eMB_RX_CRC_HI:
      pEth->wCrc = (UINT16)( i_bData << 8 );
    break;
    case eMB_RX_CRC_LO:
      pEth->wCrc |= (UINT16)( i_bData );
      if( sMb.bRxData[0] == sMb.bId )
      {
        if( pEth->wCrc == Modbus_Crc( (UINT8 *)sMb.bRxData, sMb.Cnt.wRxData ) || pEth->wCrc == 0xA55A )
        {
          sCnt.lSocketOff = 0;
  #if(1)
          switch( sMb.bRxData[1] )
          {
          case eMB_FUNC03:
          case eMB_FUNC04:
          case eMB_FUNC06:
          case eMB_FUNC10:
            if( Modbus_Addr( pEth, &sMb ) )
              NOP;
//              Modbus_Func( pEth );
            else
              Modbus_CommError( pEth, eMB_ILL_ADDR );
          break;											
          default:
            Modbus_CommError( pEth, eMB_ILL_FUNC );
          break;
          }
  #endif
        }
        else
        {
          Modbus_CommError( pEth, eMB_ILL_VAL );
        }
      }
    default:
      pEth->Stp.bRx = eMB_RX_END;
    break;
    }

// Ethernet modbus는 통신 구조가 달라 앞에 6개 byte 내용이 있음 // "00 01" "00 00" "00 06" // "00 01": 그대로 전송, "00 00": 고정, "00 06": len
    if( pEth->Stp.bRx == eMB_RX_CRC_HI -1 )
    {
//      sMb.Cnt.wRxData 와 sMb.wRxLen 개수 검증하는 단계가 있어야 됨
      if( sMb.bRxData[6] == sMb.bId )
      {
        switch( sMb.bRxData[7] )
        {
        case eMB_FUNC03:
        case eMB_FUNC04:
        case eMB_FUNC06:
        case eMB_FUNC10:
          sCnt.lSocketOff = 0;
          if( Modbus_Addr( pEth, &sMb ) )
            NOP;
//              Modbus_Func( pEth );
          else
            Modbus_CommError( pEth, eMB_ILL_ADDR );
        break;											
        default:
          Modbus_CommError( pEth, eMB_ILL_FUNC );
        break;
        }
      }
      pEth->Stp.bRx = eMB_RX_END;
    }


    pEth->Stp.bRx++;
//    pEth->Cnt.wRx++;

// 여기에 Main 주기 부하를 줄이기 위해서는 256이 최대로 동작 하지 않게 분배하는 개수를 만들어야 될 수도 있음

    if( pEth->Stp.bRx >= eMB_RX_END )
    {
      pEth->Cnt.wRx = pEth->Cnt.wRxEnd;
      pEth->Stp.bRx = 0;
    }
  }
}


void Modbus_CommError( ETHER_REG *pEth, UINT8 bErrorCode )
//void Modbus_CommError( ETHER_REG *pEth, UINT8 bErrorCode )
{
  UINT16  i=0;
//  UINT16  i_wCrc;
//  comstep = mcomstep;

  pEth->bTxData[i++] = sMb.bRxData[0];
  pEth->bTxData[i++] = sMb.bRxData[1];
  pEth->bTxData[i++] = sMb.bRxData[2];
  pEth->bTxData[i++] = sMb.bRxData[3];
  i += 2;
//  pEth->bTxData[i++] = 0;
//  pEth->bTxData[i++] = 3;

  pEth->bTxData[i++] = sMb.bRxData[6];
  pEth->bTxData[i++] = sMb.bRxData[7] | 0x80;
  pEth->bTxData[i++] = bErrorCode;

//  i_wCrc = Modbus_Crc( (UINT8 *)&pEth->bTxData[0], 3 );

//  pEth->bTxData[i++] = (UINT8)( i_wCrc >> 8 );
//  pEth->bTxData[i++] = (UINT8)( i_wCrc );

  pEth->Cnt.bTxEnd = i;
  i -= 6;
  pEth->bTxData[4] = ( i >> 8 ) & 0xFF;         // 
  pEth->bTxData[5] = i & 0xFF;         // 
//  SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
//  SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int

}

BOOL Modbus_Addr( ETHER_REG *pEth, MODBUS_REG *pMb )
{
  UINT16  i =0, j =0;
  UINT16  i_wSta, i_wLen, i_wEnd, i_wFu;
  UINT16  i_wCnt;
//  UINT16  i_wCrc, i_wCnt;
  UINT16  i_wNum, i_wPit, i_wNo;
  BOOL    i_bSta = 0;
  UINT16  *i_pwData;
  UINT16  *i_pwUtc;

  if( pMb->bRxData[7] == eMB_FUNC03 || pMb->bRxData[7] == eMB_FUNC04 )
  {
    i_wSta = ( (UINT16)pMb->bRxData[8 ] << 8 ) | ( pMb->bRxData[9] );
    i_wLen = ( (UINT16)pMb->bRxData[10] << 8 ) | ( pMb->bRxData[11] );
    i_wEnd = i_wSta + i_wLen -1;
    for( i=0; i<(pMb->wNo); i++ )
    {
      i_wFu = i;
      if( i_wSta >= pMb->Pit[i_wFu].wSta && i_wEnd <= pMb->Pit[i_wFu].wEnd )
      {
        i_pwUtc = (UINT16 *)&sDsp.lUtc;
        *i_pwUtc = (UINT16)( sDsp.ilUtc >> 16 ) & 0xFFFF;
        i_pwUtc += 1;
        *i_pwUtc = (UINT16)( sDsp.ilUtc & 0xFFFF );

        if( i_wFu == 2 || i_wFu == 3 )
        {
          if( sCnt.wFaMb == eFAULT_EMPTY )  return 0;                 // 저장된 Fault가 없으면
          if( sCnt.wFaMb == sCnt.wFaEnd )   i_wCnt = sCnt.wFaMb -1;   // 전송할 Data가 없는데 달라고 하면 바로전 Fault를 전송 함
          else                              i_wCnt = sCnt.wFaMb;
          i_wCnt %= eFAULT_MAX;
          sMb.Pit[eMB_PIT_F03_LIST].pwPit = (UINT16 *)&pFault->No[i_wCnt].wNo;           // Fault List / 항상 바뀜
          sMb.Pit[eMB_PIT_F03_WAVE].pwPit = (UINT16 *)&pWave->No[i_wCnt].iwTripCoil1;    // Fault Wave / 항상 바뀜
          if( i_wFu == 3 )
          {
            if( i_wLen < 64 )               return 0;                 // 최소 전송 Word보다 작으면 번지 불량
            if( i_wLen %64 != 0 )           return 0;                 // Len은 64, 128, 192, ... 으로 전송 해야 됨
            i_wPit = ( i_wSta -1300 ) /64;
            i_wNum = i_wLen /64;
            i_wNo  = i_wPit / 16;
            for( i=0; i<i_wNum; i++ )
              sFat.wMb[i_wNo] |= ( BIT0 << i_wPit );
          }
        }
        i_pwData  = pMb->Pit[i_wFu].pwPit;
        if( i_wFu < 2 )   i_wSta = ( i_wSta - pMb->Pit[i_wFu].wSta );
        else              i_wSta = ( i_wSta - pMb->Pit[i_wFu].wSta ) *2;
        i_pwData += i_wSta;
        i = 0;
        pEth->bTxData[i++] = pMb->bRxData[0];         // 
        pEth->bTxData[i++] = pMb->bRxData[1];         // 
        pEth->bTxData[i++] = pMb->bRxData[2];         // 
        pEth->bTxData[i++] = pMb->bRxData[3];         // 
        i += 2;
//        pEth->bTxData[i++] = pMb->bRxData[4];         // 
//        pEth->bTxData[i++] = pMb->bRxData[5];         // 
        pEth->bTxData[i++] = pMb->bRxData[6];         // ID
        pEth->bTxData[i++] = pMb->bRxData[7];         // FN
        pEth->bTxData[i++] = i_wLen *2;               // 전송 Data Byte
        if( i_wFu >= 2 )  i_wLen *= 2;
        for( j=0; j<i_wLen; )
        {
          pEth->bTxData[i++] = ( i_pwData[j] >> 8 ) & 0x00FF;             //
          pEth->bTxData[i++] = ( i_pwData[j] >> 0 ) & 0x00FF;             //
          if( i_wFu < 2 )   j++;
          else              j += 2;
        }

//        i_wCrc = Modbus_Crc( (UINT8 *)&pEth->bTxData[0], i );
//        pEth->bTxData[i++] = (UINT8)( i_wCrc >> 8 );
//        pEth->bTxData[i++] = (UINT8)( i_wCrc );

        pEth->Cnt.bTxEnd = i;
//
        i -= 6;
        pEth->bTxData[4] = ( i >> 8 ) & 0xFF;         // 
        pEth->bTxData[5] = i & 0xFF;         // 
//        SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
//        SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int

        pEth->Cnt.wRxErr = Rx_ErrorCount( eBPS_115200, 8 );
        pEth->Cnt.wSciErr = 0;

        return 1;
      }
    }
  }
  else if( pMb->bRxData[7] == eMB_FUNC06 )
  {
    i_wSta = ( (UINT16)pMb->bRxData[8] << 8 ) | ( pMb->bRxData[9] );
    i_bSta = 0;
    if( i_wSta >= pMb->Pit[eMB_PIT_F06_SET0].wSta && i_wSta <= pMb->Pit[eMB_PIT_F06_SET0].wEnd )
    {
      i_pwData  = pMb->Pit[eMB_PIT_F06_SET0].pwPit;
      i_pwData += ( i_wSta - pMb->Pit[eMB_PIT_F06_SET0].wSta );
      i_pwData[0]  = ( (UINT16)pMb->bRxData[10] << 8 ) & 0xFF00;
      i_pwData[0] |= ( (UINT16)pMb->bRxData[11] << 0 ) & 0x00FF;
      Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,        9,    (UINT16 *)&sDsp.wIpAddr,    (UINT16 *)&pMram->wEthXCs,      (UINT16 *)&sDsp.wEthXCs     );
      i_bSta = 1;
    }
    else if( i_wSta >= pMb->Pit[eMB_PIT_F06_SET1].wSta && i_wSta <= pMb->Pit[eMB_PIT_F06_SET1].wEnd )
    {
      i_pwData  = pMb->Pit[eMB_PIT_F06_SET1].pwPit;
      i_pwData += ( i_wSta - pMb->Pit[eMB_PIT_F06_SET1].wSta );
      i_pwData[0]  = ( (UINT16)pMb->bRxData[10] << 8 ) & 0xFF00;
      i_pwData[0] |= ( (UINT16)pMb->bRxData[11] << 0 ) & 0x00FF;
      i_bSta = 1;
    }
    if( i_bSta )
    {
      pEth->bTxData[i++] = pMb->bRxData[0];         // 
      pEth->bTxData[i++] = pMb->bRxData[1];         // 
      pEth->bTxData[i++] = pMb->bRxData[2];         // 
      pEth->bTxData[i++] = pMb->bRxData[3];         // 
      i += 2;
//      pEth->bTxData[i++] = pMb->bRxData[4];         // 
//      pEth->bTxData[i++] = pMb->bRxData[5];         // 

      pEth->bTxData[i++] = pMb->bRxData[6];         // ID
      pEth->bTxData[i++] = pMb->bRxData[7];         // FN
      pEth->bTxData[i++] = i_wLen *2;               // 전송 Data Byte
      pEth->bTxData[i++] = ( i_pwData[0] >> 8 ) & 0x00FF;             //
      pEth->bTxData[i++] = ( i_pwData[0] >> 0 ) & 0x00FF;             //

//      i_wCrc = Modbus_Crc( (UINT8 *)&pEth->bTxData[0], i );
//      pEth->bTxData[i++] = (UINT8)( i_wCrc >> 8 );
//      pEth->bTxData[i++] = (UINT8)( i_wCrc );

      pEth->Cnt.bTxEnd = i;
      i -= 6;
      pEth->bTxData[4] = ( i >> 8 ) & 0xFF;         // 
      pEth->bTxData[5] = i & 0xFF;         // 
//      SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
//      SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int

      pEth->Cnt.wRxErr = Rx_ErrorCount( eBPS_115200, 8 );
      pEth->Cnt.wSciErr = 0;

           if( i_wSta == 1040 )   Conv_MramWrXCs( (UINT16 *)&pMram->wTrig,          1,    (UINT16 *)&sDsp.wTrig,      (UINT16 *)&pMram->wTrigXCs,     (UINT16 *)&sDsp.wTrigXCs    );
      else if( i_wSta == 1041 )   Conv_MramWrXCs( (UINT16 *)&pMram->wDebo,          1,    (UINT16 *)&sDsp.wDebo,      (UINT16 *)&pMram->wDeboXCs,     (UINT16 *)&sDsp.wDeboXCs    );
      else if( i_wSta == 1042 )   sDbg.Stp.bType = eST_DBG_RESET;     // Reset 작업해야 됨
      else if( i_wSta == 1043 )
      {
        pMram->wFaNum = pMram->wFaMb = pMram->wFaEnd = sCnt.wFaNum = sCnt.wFaMb = sCnt.wFa = sCnt.wFaEnd = eFAULT_EMPTY;
        i_pwData[0] = 0;
      }
      return 1;
    }
  }
  else if( pMb->bRxData[7] == eMB_FUNC10 )
  {
    i_wSta = ( (UINT16)pMb->bRxData[8 ] << 8 ) | ( pMb->bRxData[9 ] );
    i_wLen = ( (UINT16)pMb->bRxData[10] << 8 ) | ( pMb->bRxData[11] );
    i_wEnd = i_wSta + i_wLen -1;
    if( i_wSta >= pMb->Pit[eMB_PIT_F10_SET].wSta && i_wEnd <= pMb->Pit[eMB_PIT_F10_SET].wEnd )
    {
      i_pwData  = pMb->Pit[eMB_PIT_F10_SET].pwPit;
      i_wSta -= pMb->Pit[eMB_PIT_F10_SET].wSta;
      i_pwData += i_wSta;
      i_wEnd -= pMb->Pit[eMB_PIT_F10_SET].wSta;
      i = 13;
//      i = 7;
      for( j=0; j<i_wLen; j++ )
      {
        i_pwData[j]  = ( (UINT16)pMb->bRxData[i++] << 8 ) & 0xFF00;
        i_pwData[j] |= ( (UINT16)pMb->bRxData[i++] << 0 ) & 0x00FF;
      }
      switch( i_wEnd )
      {
      default:
      case 13:    break;      // 1042, 1043
      case 12:                // 1041
        Conv_MramWrXCs( (UINT16 *)&pMram->wDebo,          1,    (UINT16 *)&sDsp.wDebo,      (UINT16 *)&pMram->wDeboXCs,     (UINT16 *)&sDsp.wDeboXCs    );
        if( i_wSta == 12 ) break;
      case 11:                // 1040
        Conv_MramWrXCs( (UINT16 *)&pMram->wTrig,          1,    (UINT16 *)&sDsp.wTrig,      (UINT16 *)&pMram->wTrigXCs,     (UINT16 *)&sDsp.wTrigXCs    );
        if( i_wSta == 11 ) break;
      case 10:                // 1039
      case 9:                 // 1038
        sRtc.bTimeWrite = 1;
        i_pwUtc = (UINT16 *)&sDsp.ilUtc;
        *i_pwUtc = ( sDsp.lUtc >> 16 ) & 0xFFFF;
        i_pwUtc += 1;
        *i_pwUtc = sDsp.lUtc & 0xFFFF;
        Utc2Rtc( 9, &sSet.Time, &sDsp.ilUtc );
        if( i_wSta == 9  ) break;
      case 8:                 // 1037
      case 7:                 // 1036
      case 6:                 // 1035
      case 5:                 // 1034
      case 4:                 // 1033
      case 3:                 // 1032
      case 2:                 // 1031
      case 1:                 // 1030
      case 0:                 // 1029
        Conv_MramWrXCs( (UINT16 *)&pMram->wIpAddr,        9,    (UINT16 *)&sDsp.wIpAddr,    (UINT16 *)&pMram->wEthXCs,      (UINT16 *)&sDsp.wEthXCs     );
      break;
      }
      i = 0;
      pEth->bTxData[i++] = pMb->bRxData[0];         // 
      pEth->bTxData[i++] = pMb->bRxData[1];         // 
      pEth->bTxData[i++] = pMb->bRxData[2];         // 
      pEth->bTxData[i++] = pMb->bRxData[3];         // 
      i += 2;
//      pEth->bTxData[i++] = pMb->bRxData[4];         // 
//      pEth->bTxData[i++] = pMb->bRxData[5];         // 

      pEth->bTxData[i++] = pMb->bRxData[6];         // ID
      pEth->bTxData[i++] = pMb->bRxData[7];         // FN
      pEth->bTxData[i++] = pMb->bRxData[8];         // Sta
      pEth->bTxData[i++] = pMb->bRxData[9];         // Sta
      pEth->bTxData[i++] = pMb->bRxData[10];         // Len
      pEth->bTxData[i++] = pMb->bRxData[11];         // Len

//      i_wCrc = Modbus_Crc( (UINT8 *)&pEth->bTxData[0], i );
//      pEth->bTxData[i++] = (UINT8)( i_wCrc >> 8 );
//      pEth->bTxData[i++] = (UINT8)( i_wCrc );

      pEth->Cnt.bTxEnd = i;
      i -= 6;
      pEth->bTxData[4] = ( i >> 8 ) & 0xFF;         // 
      pEth->bTxData[5] = i & 0xFF;         // 
//      SciaRegs.SCIFFTX.bit.SCIFFENA = 1;
//      SciaRegs.SCICTL2.bit.TXINTENA = 1;      // TX Int

      pEth->Cnt.wRxErr = Rx_ErrorCount( eBPS_115200, 8 );
      pEth->Cnt.wSciErr = 0;

      return 1;
    }
  }
  return 0;
}


#if(1)
static const uint16_t wCRCTable[] = {                             // <<== 2022.02.05 추가 (죄송합니다.~ㅠㅠ)
  0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241, 0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
  0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40, 0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
  0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40, 0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
  0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641, 0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
  0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240, 0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
  0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41, 0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
  0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41, 0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
  0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640, 0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
  0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240, 0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
  0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41, 0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
  0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41, 0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
  0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640, 0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
  0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241, 0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
  0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40, 0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
  0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40, 0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
  0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641, 0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};
UINT16 Modbus_Crc( UINT8 *i_pbData, UINT16 i_wLen )
{
  UINT8   bTemp;
  UINT16  wCRCWord = 0xFFFF;

  while( i_wLen-- )
  {
    bTemp = ( *i_pbData++ ^ wCRCWord ) & 0x00FF;
    wCRCWord >>= 8;
    wCRCWord ^= wCRCTable[bTemp];
  }
  return wCRCWord;
}
#else
const UINT8 i_bCrc16Hi[256] =
{
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
/* CRC16 Table Low byte */

const UINT8 i_bCrc16Lo[256] =
{
  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2,
  0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
  0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
  0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
  0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
  0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
  0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
  0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
  0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
  0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
  0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE,
  0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
  0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,
  0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
  0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
  0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62,
  0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
  0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE,
  0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
  0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
  0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
  0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76,
  0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
  0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
  0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
  0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
  0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
  0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A,
  0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86,
  0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};
/* CRC16 Table High byte */
UINT16 Modbus_Crc( UINT8 *i_pbData, UINT16 i_wLen )
{
  UINT8   i_bCrcHi; /* high byte of CRC initialized */
  UINT8   i_bCrcLo; /* low byte of CRC initialized */
  UINT16  i_wIndex; /* will index into CRC16 lookup table */

  i_bCrcHi = 0xFF; /* high byte of CRC16 initialized */
  i_bCrcLo = 0xFF; /* low byte of CRC16 initialized */
  while( i_wLen-- )
  {
    i_wIndex = i_bCrcHi ^ *i_pbData++; /* calculate the CRC16 */
    i_bCrcHi = i_bCrcLo ^ i_bCrc16Hi[i_wIndex];
    i_bCrcLo = i_bCrc16Lo[i_wIndex];
  }

//  *i_pbData++ = i_bCrcHi;
//  *i_pbData++ = i_bCrcLo;
  return ( (UINT16)i_bCrcHi << 8 | i_bCrcLo );
}
#endif




UINT16 Rx_ErrorCount( UINT8 i_bBps, UINT16 i_wLen )
{
#if(0)
// 메인주기를 생각하면 계산적으로 최소 2가 되야 되므로 그냥 2로 고정 시킴
  return  10;   // 9600bps 1byte가 1msec 이므로 메인주기 1msec라고 가정하면 PC 반응성을 참고하여 10회 이후에 초기화 하면 될 것으로 판단 됨
#else
  UINT16  i_wNo;
  UINT32  i_lBps;

  switch( i_bBps )
  {
  case eBPS_9600:     i_lBps = 9600;    break;
  case eBPS_19200:    i_lBps = 19200;   break;
  case eBPS_38400:    i_lBps = 38400;   break;
  case eBPS_57600:    i_lBps = 57600;   break;
  case eBPS_115200:   i_lBps = 115200;  break;
  case eBPS_230400:   i_lBps = 230400;  break;
  case eBPS_460800:   i_lBps = 460800;  break;
  case eBPS_921600:   i_lBps = 921600;  break;
  }

  if( i_wLen == 0 )
  {
  i_wNo = ( 10 *4 );
  }
  else
  {
  i_wNo = (UINT16)( ( ( (UINT32)( 4000000000 )/i_lBps ) * i_wLen ) / 100000 );
  i_wNo += ( 3 *4 );
  }
//  if( i_wNo <= 2 )    i_wNo = 2;

  return i_wNo;
#endif
}



/******************************* TIGERWIN END OF FILE *******************************/
