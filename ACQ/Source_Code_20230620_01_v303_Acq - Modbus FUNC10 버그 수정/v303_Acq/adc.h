/* *************************************************************************
 *
 * Project Name	: CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : adc.h
 *
 * *************************************************************************/ 

#ifndef __ADC_H
#define __ADC_H


#define eADC_READ_3         0         // ADC 한번에 3번 읽을 때.





#define eADC_SAMPLE         128

#define eADC_MAX            8

#define eADC_LOWDATA_MAX    65536     // 20초*60Hz*32Sample
#define eADC_LOWDATA_SIZE   8
#define eIO_LOWDATA_SIZE    2


#define eADC_SAME_READ      3         // 동일 Ch 3회 읽음
#define eADC_READ_TIME      6         // Sync 동작 후 Adc Read 시간   // eADC_READ_3 0 일때 사용
// OS 작업은 안하는 것이 맞다고 판단 됨 // 해보니 +한 값이 나오는 것으로 판단 됨
//#define eADC_READ_TIME      30        // 3회 연속 읽고 1sample에 3회 읽을 때
#define eADC_READ_COUNT     1         // 0: AD Conv -> 1: AD Read

#define eADC_CONV_OVER      100



#define eSQRT2      1.414213562
#define e2SQRT2     2.828427125       // 2*eSQRT2
#define e1dSQRT2    0.707106781       // 1/eSQRT2
#define ePI         3.141592654
#define e180dPI     57.29577951       // 180/ePI
#define ePId180     0.017453293       // ePI/180


#if(0)
//sSetting.wCtrlFlag
enum
{
  eCAL_ZERO_CAL       = BIT0,
  eCAL_SPAN_CAL       = BIT1,
  eCAL_AI_SAVE        = BIT2,
  eCAL_CT_CAL         = BIT4,
  eCAL_PT_CAL         = BIT5,
  eCAL_SAVE           = BIT6,
  eCAL_AI_TYPE_SAVE   = BIT8,
  eCAL_TYPE_SAVE      = BIT9,
  eCAL_FREQ_SEL_SAVE  = BIT10,
  eCAL_BIAS           = BIT11,        // eCAL_CT_CAL, eCAL_PT_CAL 2개중 한대를 On 하고 아 Bit가 들어오면 저장 됨
  eCAL_ANGLE          = BIT12,        // 위상 보상
  eCAL_NOP13          = BIT13,
  eCAL_FLOAT          = BIT14,        // Low Data float형으로 전송(0: wMainLow(low), wMainPhase(High), 1: 기존방식)
  eCAL_TEST           = BIT15,
};
enum
{
  eADC_CS2 = 16,                      // 0x00300010
  eADC_CS1 = 8,                       // 0x00300008
  eADC_CS0 = eADC_CS1+eADC_CS2,       // 0x00300018
//  eADC_NO_MAX = 3     //,
};
//#define eADC_NO_MAX             1
#endif

typedef struct
{
  UINT8           bTrip;
} ADC_STATUS;
typedef struct
{
  UINT8           bRaw;
  UINT8           bSta;
  UINT16          wRaw;
  UINT16          wTrip;
} ADC_COUNT;
typedef struct
{
  ADC_STATUS      Sta;
  ADC_COUNT       Cnt;

#if(0)  // 20220518 0: 128개를 적분 bias에 사용 / MRAM에 저장 되는 2주기 Data를 이용하여 Bias를 연산하므로 속도는 느린 반면 RAM 차지가 적음
  INT16           iwRawData[eADC_SAMPLE];   // Temp. ADC 128 Sample Raw Data
#else   // 내부 RAM을 이용하여 저장하는 방식으로 RAM을 많이 차지 하지만 속도는 빠름
  INT16           iwRawData[eADC_MAX][eADC_SAMPLE];   // ADC 128 Sample Raw Data
#endif
  INT32           ilBiasData[eADC_MAX];               // ADC 128 sample Bias 합
  UINT8           bSta[2];        // Status

  float           fLowData[eADC_MAX][eADC_SAMPLE];
  float           fLowDataOld[eADC_MAX][eADC_SAMPLE];
  UINT8           bPosition;
  UINT8           bPositionOld;

  float           fImagSum[eADC_MAX];
  float           fRealSum[eADC_MAX];

//  BOOL            bTestDft;                   // DFT Test

} ADC_REG;
extern ADC_REG      sAdc;


extern void Adc_DataFix( void );

extern void Adc_Read( void );
extern void Adc_Make( void );

extern void ADC_Test( void );

#endif /* __ADC_H */
