/******************************************************************************************************
 **                     Copyright(C) 2014 SANION Co. Ltd.                    **
 **                  --------------------------------------                  **
 **                              WWW.SANION.COM                              **
 ******************************************************************************************************
    PROJECT     : UR-IED
 ******************************************************************************************************
    FILE NAME   : UR_SDK.h
    AUTHOR      : sootoo23
    DATE        : 2016.05.31
    REVISION    : V1.00
    DESCRIPTION : UR SDK HEADER (lib sdk, app shared header)
 ******************************************************************************************************
    HISTORY     :
        2016-05-31 sootoo23 - Create
 ******************************************************************************************************/
	 
	 
#ifndef URSDK_H_
#define URSDK_H_
	 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include <pthread.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
		 
#ifdef __cplusplus
	  extern "C" {
#endif

/************************************************************************/
/* Thread Value		                                                    */
/************************************************************************/
//extern pthread_mutex_t dsUTCTimeMutex;


#define CommVersion "1.0"
#define LUVersion "1.0"
/******************************************************************************
								Common Define
******************************************************************************/
// MPU Set Flag
#define DATA_REQUESTED_BY_MPU			0x00A5  // MPU?μ ?°μ΄?°λ? ?μ²­
#define DATA_SET_BY_MPU					0x00E7  // MPU?μ ?°μ΄?°λ? κ°±μ ??
#define DATA_READ_BY_MPU				0x00C3  // MPU?μ ?°μ΄?°λ? ?½μ
#define ERROR_IN_DATA_SET_BY_MPU		0x0081  // ?°μ΄?°λ? ?€λ₯
#define DATA_BEING_WRITTEN_BY_MPU		0x0049  // MPU?μ ?°μ΄?°λ? ?°λμ€?

// DSP Set Flag
#define DATA_REQUESTED_BY_DSP			0x007E  // DSP?μ ?°μ΄?°λ? ?μ²­
#define DATA_SET_BY_DSP 				0x005A  // DSP?μ ?°μ΄?°λ? κ°±μ ??
#define DATA_READ_BY_DSP				0x0018  // DSP?μ ?°μ΄?°λ? ?½μ
#define ERROR_IN_DATA_SET_BY_DSP		0x003C  // ?°μ΄???€λ₯
#define DATA_BEING_WRITTEN_BY_DSP		0x001F  // DSP?μ ?°μ΄?°λ? ?°λμ€?

// 61850-> MPU&DSP DATA
#define DATA_READ_BY_61850				0x00FD
#define DATA_BEING_READ_BY_61850		0x0060
#define DATA_SET_BY_61850				(DATA_SET_BY_MPU+1)  		///< STB?μ ?°μ΄?°λ? κ°±μ ??
#define DATA_REQUESTED_BY_61850			(DATA_REQUESTED_BY_MPU+1)  	///< STB?μ ?°μ΄?°λ? ?μ²­
#define ERROR_IN_DATA_SET_BY_61850		(ERROR_IN_DATA_SET_BY_MPU+1)///< ?°μ΄?°λ? ?€λ₯

/******************************************************************************
								DSP Define
******************************************************************************/
// Event Type
#define DEBUGEVN_TYPE_START		((U32)0x0)
#define ALMEVN_TYPE_START		((U32)0x100)
#define MOEVN_TYPE_START		((U32)0x200)
#define IOEVN_TYPE_START		((U32)0x300)
#define CTLEVN_TYPE_START		((U32)0x400)
#define COMMEVN_TYPE_START		((U32)0x500)
#define LOGICEVN_TYPE_START		((U32)0x600)
#define FAULTEVN_TYPE_START		((U32)0x700)
#define CFGEVN_TYPE_START		((U32)0x800)
#define CFGEVN_TYPE_END			((U32)0xF00)

typedef enum
{
	DEBUGEVT_START = DEBUGEVN_TYPE_START,
	DEBUGEVT_DO_CTRL,
	DEBUGEVT_LED_CTRL,
	
	ALMEVT_START = ALMEVN_TYPE_START,
	ALMEVT_FAULT_OCCURRED,					// λ³΄νΈμμ κ³ μ₯λ°μ
	ALMEVT_PICKUP_OCCURRED,					// Pickup λ°μ
	ALMEVT_IED_LOCK_OCCURRED,				// IED λμ μ κΈμμ λ°μ
	ALMEVT_IED_LOCK_RELEASED,				// IED λμ μ κΈμμ ν΄μ 
	ALMEVT_IED_UNLOCK_OCCURRED,				// IED λμ λ―Έ μ κΈμμ λ°μ
	ALMEVT_IED_UNLOCK_RELEASED,				// IED λμ λ―Έ μ κΈμμ ν΄μ 
	ALMEVT_END	= MOEVN_TYPE_START -1,
	MOEVT_START = MOEVN_TYPE_START,
	MOEVT_ADC_FAILED_OCCURRED,				// κ³μΈ‘ νλ‘μ΄μ λ°μ
	MOEVT_ADC_FAILED_RELEASED,				// κ³μΈ‘ νλ‘μ΄μ ν΄μ 
	MOEVT_ADC2_5V_FAILED_OCCURRED,			// ADC 2.5 V μ΄μ λ°μ
	MOEVT_ADC2_5V_FAILED_RELEASED,			// ADC 2.5 V μ΄μ ν΄μ 
	MOEVT_ADCV_FAILED_OCCURRED,				// ADC 5 V μ΄μ λ°μ
	MOEVT_ADCV_FAILED_RELEASED,				// ADC 5 V μ΄μ ν΄μ 
	MOEVT_ADC_FACTOR_ERR_OCCURRED,			// ADC Factor μ΄μ λ°μ
	MOEVT_ADC_FACTOR_ERR_RELEASED,			// ADC Factor μ΄μ ν΄μ 
	MOEVT_LOGIC_SOLVER_ERR_OCCURRED = 0x221,// Logic Solver μ΄μ λ°μ
	MOEVT_LOGIC_SOLVER_ERR_RELEASED,		// Logic Solver μ΄μ ν΄μ 
	MOEVT_LOGIC_DATA_ERR_OCCURRED,			// Logic Data μ΄μ λ°μ
	MOEVT_LOGIC_DATA_ERR_RELEASED,			// Logic Data μ΄μ ν΄μ 
	MOEVT_TEXT_EVT_OCCURRED,				// κ°μ νμ€νΈ μ΄λ²€νΈ λ°μ
	MOEVT_CORE_FAILED_OCCURRED = 0x240,		// Processor μ΄μ λ°μ
	MOEVT_CORE_FAILED_RELEASED,				// Processor μ΄μ ν΄μ 
	MOEVT_MEMIF_FAILED_OCCURRED,			// Mem IF μ΄μ λ°μ
	MOEVT_MEMIF_FAILED_RELEASED,			// MEM IF μ΄μ ν΄μ 
	MOEVT_TASK_FAILED_OCCURRED,				// Task μ΄μ λ°μ
	MOEVT_TASK_FAILED_RELEASED,				// Task μ΄μ ν΄μ 
	MOEVT_SETTING_RANGE_FAILED_OCCURRED,	// μ€μ μΉ λ²μ  μ΄μ λ°μ
	MOEVT_SETTING_RANGE_FAILED_RELEASED,	// μ€μ μΉ λ²μ  μ΄μ ν΄μ 
	MOEVT_SETTING_CRC_FAILED_OCCURRED,		// μ€μ μΉ CRC  μ΄μ λ°μ
	MOEVT_SETTING_CRC_FAILED_RELEASED,		// μ€μ μΉ CRC  μ΄μ ν΄μ 
	MOEVT_EVENT_CRC_FAILED_OCCURRED,		// μ΄λ²€νΈ CRC  μ΄μ λ°μ
	MOEVT_COMTRADE_CRC_FAILED_OCCURRED,		// Comtrade CRC μ΄μ λ°μ
	MOEVT_INIT_SETTING_RANGE_FAILED_OCCURRED,// μ΄κΈ° μ€μ μΉ  λ²μ μ΄μ λ°μ
	MOEVT_INIT_SETTING_RANGE_FAILED_RELEASED,// μ΄κΈ° μ€μ μΉ  λ²μ μ΄μ ν΄μ 
	MOEVT_DSP_CORE_REBOOT,					// DSP core reboot
	MOEVT_IOBD_FAULT_OCCURRED = 0x260,		//IO λ³΄λ μ΄μ λ°μ
	MOEVT_IOBD_FAULT_RELEASED,				//IO λ³΄λ μ΄μ ν΄μ 
	MOEVT_IED_POWER_DOWN,					// IED Power off
	MOEVT_IED_POWER_UP,						// IED Power on
	MOEVT_IOBD_UPDATE_RET,					// IO λ³΄λ μλ°μ΄νΈ
	MOEVT_CAN_ID_CHANGE,					// IO CAN ID λ³κ²½
	MOEVT_IOBD_CFG_FAILED_OCCURRED,			// IO λ³΄λ μ€μ κ° μ΄μ λ°μ
	MOEVT_IOBD_CFG_FAILED_RELEASED,			// IO λ³΄λ μ€μ κ° μ΄μ ν΄μ 
	MOEVT_IOBD_REBOOT,						// IO λ³΄λ μ¬λΆν
	MOEVT_IOBO_POWER_RANGE_ERR_OCCURRED,	// μΈλΆμ μ μ΄μ λ°μ
	MOEVT_IOBO_POWER_RANGE_ERR_RELEASED,	// μΈλΆμ μ μ΄μ ν΄μ 
	MOEVT_IOBD_DIPU_I2C_ERR_OCCURRED,		// DIPU λ³΄λ μΈλΆμ μ I2c μ΄μ λ°μ
	MOEVT_IOBD_DIPU_I2C_ERR_RELEASED,		// DIPU λ³΄λ μΈλΆμ μ I2c μ΄μ ν΄μ 
	MOEVT_IOBD_UPDATE_SUCCESS,				// IO λ³΄λ μλ°μ΄νΈ μ±κ³΅
	MOEVT_IOBD_UPDATE_FAIL,					// IO λ³΄λ μλ°μ΄νΈ μ€ν¨
	MOEVT_IOBD_UPDATE_NOT_RUN,				// IO λ³΄λ μλ°μ΄νΈ μ€ν¨
	MOEVT_DI_LOCK_OCCURRED = 0x270,			// DI ν¬νΈ Lock μν λ°μ
	MOEVT_DI_LOCK_RELEASED,					// DI ν¬νΈ Lock μν ν΄μ 
	MOEVT_DO_SEL_FAIL_OCCURRED,				// DO Select Feedback μ΄μ λ°μ 
	MOEVT_DO_SEL_FAIL_RELEASED,				// DO Select Feedback μ΄μ ν΄μ  
	MOEVT_DO_OPER_FAIL_OCCURRED,			// DO Output Feedback μ΄μ λ°μ 
	MOEVT_DO_OPER_FAIL_RELEASED,			// DO Output Feedback μ΄μ ν΄μ  
	MOEVT_DO_TCS_FAIL_OCCURRED,				// TCS Feedback μ΄μ λ°μ
	MOEVT_DO_TCS_FAIL_RELEASED,				// TCS Feedback μ΄μ ν΄μ 
	MOEVT_DO_CONTACT_ERROR_OCCURRED,		// IO DO μ μ  μ΄μ λ°μ
	MOEVT_DO_CONTACT_ERROR_RELEASED,		// IO DO μ μ  μ΄μ ν΄μ 
	MOEVT_DO_CIRCUIT_ERROR_OCCURRED,		// IO DO νλ‘ μ΄μ λ°μ
	MOEVT_DO_CIRCUIT_ERROR_RELEASED,		// IO DO νλ‘ μ΄μ ν΄μ 
	MOEVT_IOBD_TRIPCOIL_ERROR_OCCURRED,		// IO λ³΄λ Trip Coil μ΄μ λ°μ
	MOEVT_IOBD_TRIPCOIL_ERROR_RELEASED,		// IO λ³΄λ Trip Coil μ΄μ ν΄μ 
	MOEVT_ADC_INTERRUPT_ERROR_OCCURRED,
	MOEVT_ADC_INTERRUPT_ERROR_RELEASED,
	MOEVT_END	= IOEVN_TYPE_START -1,
	IOEVT_START = IOEVN_TYPE_START,
	STS_IOEVT_DI_OCCURRED,
	STS_IOEVT_DI_RELEASED,
	//STS_IOEVT_DO_OCCURRED,
	//STS_IOEVT_DO_RELEASED
	IOEVT_END	= CTLEVN_TYPE_START -1,
	CTRLEVT_START = CTLEVN_TYPE_START,
	CTRLEVT_TEXT_EVT_OCCRRED,
	CTRLEVT_WIREDXUR_FAIL_EVT_OCCURED,
	CTRLEVT_LCD_FAIL_EVT_OCCURED,
	CTRLEVT_IEC61850_FAIL_EVT_OCCURED,
	CTRLEVT_END	= COMMEVN_TYPE_START -1,
	COMMEVT_START = COMMEVN_TYPE_START,
	COMMEVT_CAN_FAILED_OCCURRED,			// CAN ν΅μ  μ΄μ λ°μ
	COMMEVT_CAN_FAILED_RELEASED,			// CAN ν΅μ  μ΄μ ν΄μ 
	COMMEVT_PCIE_FAILED_OCCURRED,			// PCIE ν΅μ  μ΄μ λ°μ
	COMMEVT_PCIE_FAILED_RELEASED,			// PCIE ν΅μ  μ΄μ ν΄μ 
	COMMEVT_ADCSPI_FAILED_OCCURRED,			// ADCSPI ν΅μ  μ΄μ λ°μ
	COMMEVT_ADCSPI_FAILED_RELEASED,			// ADCSPI ν΅μ  μ΄μ ν΄μ 
	COMMEVT_WIREDXUR_CONNECT,				// Wired-XUR μ μ
	COMMEVT_WIREDXUR_DISCONNECT,			// Wired-XUR λ¨μ 
	COMMEVT_61850_ASSOCIATION_FAILED_OCCURRED,	// 61850 ν΅μ  Association μ΄μ λ°μ
	COMMEVT_61850_ASSOCIATION_SUCCESS,		// 61850 ν΅μ  Association μ΄μ ν΄μ 
	COMMEVT_61850_RELEASE_FAILED_OCCURRED, 	// 61850 ν΅μ  Release μ΄μ λ°μ
	COMMEVT_61850_RELEASE_SUCCESS,			// 61850 ν΅μ  Release μ΄μ ν΄μ 
	COMMEVT_61850_ABORT_FAILED_OCCURRED,	// 61850 ν΅μ  Abort μ΄μ λ°μ
	COMMEVT_61850_ABORT_SUCCESS,			// 61850 ν΅μ  Abort μ΄μ ν΄μ  
	COMMEVT_BOARD_RESPONSE_FAILED_OCCURRED,	// IO λ³΄λ λ―Έμλ΅ λ°μ
	COMMEVT_BOARD_RESPONSE_FAILED_RELEASED,	// IO λ³΄λ λ―Έμλ΅ ν΄μ 
	COMMEVT_END	= FAULTEVN_TYPE_START -1,
	PROTEVT_START = FAULTEVN_TYPE_START,
	PROTEVT_FAULT_OCCURRED,					// κ³ μ₯ λ°μ
	PROTEVT_FAULT_RELEASED,					// κ³ μ₯ ν΄μ 
	PROTEVT_END	= CFGEVN_TYPE_START -1,
	CFGEVT_START = CFGEVN_TYPE_START,
	CFGEVT_GENERAL_SETTING,
	CFGEVT_NETWORK_SETTING,
	CFGEVT_FUNCTIONKEY_SETTING,
	CFGEVT_MAINMEASURE_SETTING,
	CFGEVT_PASSWORD_SETTING,
	CFGEVT_DI_INPUT_SETTING,
	CFGEVT_DO_OUTPUT_SETTING,
	CFGEVT_CT_INPUT_SETTING,
	CFGEVT_PT_INPUT_SETTING,
	CFGEVT_TD_RTD_INPUT_SETTING,
	CFGEVT_LED_OUTPUT_SETTING,
	CFGEVT_LED_COLOR_SETTING,
	CFGEVT_LED_TYPE_SETTING,
	CFGEVT_DI_DEBOUNCE_SETTING,
	CFGEVT_DO_DURATION_TIME_SETTING,
	CFGEVT_DO_TYPE_SETTING,
	CFGEVT_TCS_USE_SETTING,
	CFGEVT_TCS_TIME_SETTING,
	CFGEVT_TRS_TIME_SETTING,
	CFGEVT_US_EQ_SETTING,
	CFGEVT_US_PORT_SETTING_GROUP1,
	CFGEVT_US_PORT_SETTING_GROUP2,
	CFGEVT_US_PORT_SETTING_GROUP3,
	CFGEVT_US_PORT_SETTING_GROUP4,
	CFGEVT_FAULT_RECORD_SETTING,
	CFGEVT_US_ACTIVE_GROUP_SETTING,
	CFGEVT_HARMONICS_SETTING,
	CFGEVT_POWER_CALCULATION_SETTING,
	CFGEVT_USER_MEASURE_SETTING,
	CFGEVT_RTD_ALARM_SETTING,
	CFGEVT_TD_ALARM_SETTING,
	CFGEVT_SLD_DOWN,
	CFGEVT_DI_NAME_DOWN,
	CFGEVT_DO_NAME_DOWN,
	CFGEVT_AI_NAME_DOWN,
	CFGEVT_AO_NAME_DOWN,
	CFGEVT_US_NAME_DOWN,
	CFGEVT_US_STRINGLIST_DOWN,
	CFGEVT_US_PROT_INFO_DOWN,
	CFGEVT_US_EQUIP_INFO_DWON,
	CFGEVT_LOGIC_INFO_DOWN,
	CFGEVT_LOGIC_POSTION_INFO_DOWN,
	CFGEVT_DIDO_LED_ATTRIBUTE_DWON,
	CFGEVT_DEVICE_NAME_SETTING,
	CFGEVT_OTHER_EQUIP_INFO_DOWN,
	CFGEVT_OTHER_EQUIP_CTRL_VALUE_DOWN,
	CFGEVT_GOCB_USE_SETTING,
	CFGEVT_GOCB_TESTMODE_SETTING,
	CFGEVT_SETTING_VLAUE_CONSOLE_CHANGE
}EVT_TYPE;
#define MAX_SIZE_OF_DATA_LIST_TO_CU 200

/******************************************************************************
								IO Define
******************************************************************************/
#define MAX_DI_CHANNEL      6
#define MAX_DO_CHANNEL      3


/******************************************************************************
						PDDAU definition : added by symoon
******************************************************************************/

// enumeration for PD information
enum {
	// 0
	ENUM_PD_DEVICE_TYPE,
	ENUM_PD_PD_ALARM,
	ENUM_PD_EVENT_LEVEL_STATE,
	ENUM_PD_OP_COUNT,
	ENUM_PD_TYPE_0,
	// 5
	ENUM_PD_TYPE_1,
	ENUM_PD_TYPE_2,
	ENUM_PD_TYPE_3,
	ENUM_PD_TYPE_4,
	ENUM_PD_TYPE_5,
	// 10
	ENUM_PD_TYPE_6,
	ENUM_PD_TYPE_7,
	ENUM_PD_TYPE_8,
	ENUM_PD_TYPE_9,
	ENUM_PD_TYPE_10,
	// 15
	ENUM_PD_TYPE_11,
	ENUM_PD_MODEVCOMF,
	ENUM_PD_MODEVFLT,
	ENUM_PD_TRENDTRANSF,
	ENUM_PD_EVTTRANSF,
	// 20
	ENUM_PD_RTTRANSF,
	ENUM_PD_ACOUSTIC_PD,
	ENUM_PD_MAX_APPARENT_PD_MAG,
	ENUM_PD_MAX_APPARENT_PD_ANG,
	ENUM_PD_AVG_DISCHARGE_I,
	// 25
	ENUM_PD_UHF_PD,
	ENUM_PD_1ST_HARMONIC_RELATION,
	ENUM_PD_2ND_HARMONIC_RELATION,
	ENUM_PD_MAX_PD_MAG_CNT,
	ENUM_PD_MAX_PD_ANG_CNT,
	// 30
	NUM_KIND_PD_STATUS
};

enum {
	// 0
	ENUM_PD_EVENT_AMP_THRESHOLD1,
	ENUM_PD_EVENT_PPS_THRESHOLD1,
	ENUM_PD_EVENT_AMP_THRESHOLD2,
	ENUM_PD_EVENT_PPS_THRESHOLD2,
	ENUM_PD_PULSE_LVL_THRESHOLD,
	// 5
	ENUM_PD_ATTENUATION_SETTING,
	ENUM_PD_PHASE_SHIFT,
	ENUM_PD_CENTER_HZ,
	ENUM_PD_BANDWIDTH,
	ENUM_PD_DEVICE_VOLTAGE,
	// 10
	ENUM_PD_RSOPCNT,
	// 11
	NUM_KIND_PD_SETTING
};

#define SIZE_OF_PD_DATA_LIST_TO_CU						60																// Number of buffer unit in the queue
#define SIZE_OF_PD_DATA_UNIT							((NUM_KIND_PD_STATUS*2)+NUM_KIND_PD_SETTING+1)					// 2 means data, quality 
#define SIZE_OF_PD_DATA_UNIT_IN_BYTES					(SIZE_OF_PD_DATA_UNIT*4)										// 4 means sizeof(U32)
#define TOTAL_SIZE_OF_PD_DATA_LIST_TO_CU				(SIZE_OF_PD_DATA_UNIT_IN_BYTES*SIZE_OF_PD_DATA_LIST_TO_CU)
#define TOTAL_SIZE_OF_PD_DATA_LIST_TO_CU_IN_BYTES		(TOTAL_SIZE_OF_PD_DATA_LIST_TO_CU*4)							// 4 means sizeof(U32)

/******************************************************************************************************
 Time Sync Manager Func
******************************************************************************************************/
typedef enum
{
	TMSYNC_NTP,
	TMSYNC_IRIGB,
}TIMESYNC_TYPE;
	
typedef struct {
    U32	u32TmSyncInterval;	// Time Sync Interval (sec)
   	S32	s32TmUtcOffset;		// UTC Offset (μ+λΆ)
   	S32 s32TimeSyncMode;
} dsTimeSyncInfo;

int TSM_Initialize(void);
void TSM_GetOsTimeStr(char *TimeStr);
void TSM_SetDate(int year, int month, int day);
void TSM_SetTime(int hour, int min, int sec);
int TSM_GetUTCOffsetVal(void);

/******************************************************************************************************
 System Setting Module Func
******************************************************************************************************/
typedef struct {
    U32	m_u32IPAddr;	///< v4IP
    U32	m_u32Subnet;	///< Subnet mask
    U32	m_u32Gateway;	///< gateway
} dsNetworkInfo;

typedef struct{
	S32	s32UTCOffsetHour;
	S32 s32UTDOffsetMinute;	
	U32 				u32AppMode;					// Application Mode setting (0:Basic, x10:DIO Test, x11:Meas Test)
	dsTimeSyncInfo	    dsTimeSyncInfo;
	dsNetworkInfo		dsNetWorkCfg[3];			// 0:MPU, 1:STB 1port			// 0.0.0.0 ~ 255.255.255.255
}dsDeviceInfo;

/******************************************************************************
						DAU definition : added by symoon
******************************************************************************/


// enumeration for DGA information
enum {
	// 0
	ENUM_DGA_INSULATION_ALARM,
	ENUM_DGA_H2_ALARM,
	ENUM_DGA_N2_ALARM,
	ENUM_DGA_O2_ALARM,
	ENUM_DGA_C2H2_ALARM,
	// 5
	ENUM_DGA_CH4_ALARM,
	ENUM_DGA_C2H6_ALARM,
	ENUM_DGA_C2H4_ALARM,
	ENUM_DGA_CO_ALARM,
	ENUM_DGA_CO2_ALARM,
	// 10
	ENUM_DGA_H2O_ALARM,
	ENUM_DGA_C3H8_ALARM,
	ENUM_DGA_MODEVCOMF,
	ENUM_DGA_MODEVFLT,
	ENUM_DGA_DGA_ALARM,
	// 15
	ENUM_DGA_TEMPERATURE,
	ENUM_DGA_LEVEL,
	ENUM_DGA_PRESSURE,
	ENUM_DGA_H2O_PPM,
	ENUM_DGA_H2_PPM,
	// 20
	ENUM_DGA_N2_PPM,
	ENUM_DGA_CO_PPM,
	ENUM_DGA_CO2_PPM,
	ENUM_DGA_CH4_PPM,
	ENUM_DGA_C2H2_PPM,
	// 25
	ENUM_DGA_C2H4_PPM,
	ENUM_DGA_C2H6_PPM,
	ENUM_DGA_O2_PPM,
	ENUM_DGA_C3H8_PPM,
	// 29
	NUM_KIND_DGA_STATUS
};

enum {
	// 0
	ENUM_DGA_H2_SETTING,
	ENUM_DGA_N2_SETTING,
	ENUM_DGA_O2_SETTING,
	ENUM_DGA_C2H2_SETTING,
	ENUM_DGA_CH4_SETTING,
	// 5
	ENUM_DGA_C2H6_SETTING,
	ENUM_DGA_C2H4_SETTING,
	ENUM_DGA_CO_SETTING,
	ENUM_DGA_CO2_SETTING,
	ENUM_DGA_H2O_SETTING,
	// 10
	ENUM_DGA_C3H8_SETTING,
	// 11
	NUM_KIND_DGA_SETTING
};

#define SIZE_OF_DGA_DATA_LIST_TO_CU						24																// Number of buffer unit in the queue
#define SIZE_OF_DGA_DATA_UNIT							((NUM_KIND_DGA_STATUS*2)+NUM_KIND_DGA_SETTING+1)				// 2 means data, quality 
#define SIZE_OF_DGA_DATA_UNIT_IN_BYTES					(SIZE_OF_DGA_DATA_UNIT*4)										// 4 means sizeof(U32)
#define TOTAL_SIZE_OF_DGA_DATA_LIST_TO_CU				(SIZE_OF_DGA_DATA_UNIT_IN_BYTES*SIZE_OF_DGA_DATA_LIST_TO_CU)
#define TOTAL_SIZE_OF_DGA_DATA_LIST_TO_CU_IN_BYTES		(TOTAL_SIZE_OF_DGA_DATA_LIST_TO_CU*4)							// 4 means sizeof(U32)


// enumeration for OLTC driving motor information
enum {
	// 0
	ENUM_OLTC_OIL_FILTER,
	ENUM_OLTC_MOTOR_DRIVE_BLOCK,
	ENUM_OLTC_VAC_CEL_ALARM,
	ENUM_OLTC_OIL_FILTER_TRIP,
	ENUM_OLTC_MOTOR_DRIVE_I_ALARM,
	// 5
	ENUM_OLTC_MOTOR_DRIVE_I_WARNING,
	ENUM_OLTC_TORQUE_ALARM,
	ENUM_OLTC_TORQUE_WARNING,
	ENUM_OLTC_OP_DURATION_ALARM,
	ENUM_OLTC_OP_DURATION_WARNING,
	// 10
	ENUM_OLTC_OP_COUNT_ALARM,
	ENUM_OLTC_OP_COUNT_WARNING,
	ENUM_OLTC_ABRASION_ALARM,
	ENUM_OLTC_ABRASION_WARNING,
	ENUM_OLTC_OIL_TEMPERATURE_DIFF_ALARM,
	// 15
	ENUM_OLTC_OIL_FILTER_COUNT,
	ENUM_OLTC_OIL_FILTER_COUNT_ALARM,
	ENUM_OLTC_OIL_FILTER_COUNT_WARNING,
	ENUM_OLTC_EVTTRANSF,
	ENUM_OLTC_RSOPCNT,
	// 20
	ENUM_OLTC_MODEVCOMF,
	ENUM_OLTC_MODEVFLT,
	ENUM_OLTC_ALARM,
	ENUM_OLTC_TORQUE,
	ENUM_OLTC_MOTOR_DRIVE_I,
	// 25
	ENUM_OLTC_ABRASION_LEVEL,
	ENUM_OLTC_OP_DURATION,
	ENUM_OLTC_OIL_TEMPERATURE_DIFF,
	ENUM_OLTC_OUTSIDE_TEMPERATURE,
	ENUM_OLTC_MOTOR_DRIVE_I_PHASE_A,
	// 30
	ENUM_OLTC_MOTOR_DRIVE_I_PHASE_B,
	ENUM_OLTC_MOTOR_DRIVE_I_PHASE_C,
	ENUM_OLTC_OIL_FILTER_TEMPERATURE,
	ENUM_OLTC_OIL_FILTER_PRESSURE,
	ENUM_OLTC_OIL_FILTER_MOISTURE,
	// 35
	NUM_KIND_OLTC_STATUS
};

enum {
	// 0
	ENUM_OLTC_MOTOR_DRIVE_I_ALARM_LEVEL,
	ENUM_OLTC_MOTOR_DRIVE_I_WARNING_LEVEL,
	ENUM_OLTC_TORQUE_ALARM_LEVEL,
	ENUM_OLTC_TORQUE_WARNING_LEVEL,
	ENUM_OLTC_OP_DURATION_ALARM_LEVEL,
	// 5
	ENUM_OLTC_OP_DURATION_WARNING_LEVEL,
	// 6
	NUM_KIND_OLTC_SETTING
};

#define SIZE_OF_OLTC_DATA_LIST_TO_CU					100																// Number of buffer unit in the queue
#define SIZE_OF_OLTC_DATA_UNIT							((NUM_KIND_OLTC_STATUS*2)+NUM_KIND_OLTC_SETTING+1)				// 2 means data, quality
#define SIZE_OF_OLTC_DATA_UNIT_IN_BYTES					(SIZE_OF_OLTC_DATA_UNIT*4)										// 4 means sizeof(U32)
#define TOTAL_SIZE_OF_OLTC_DATA_LIST_TO_CU				(SIZE_OF_OLTC_DATA_UNIT_IN_BYTES*SIZE_OF_OLTC_DATA_LIST_TO_CU)
#define TOTAL_SIZE_OF_OLTC_DATA_LIST_TO_CU_IN_BYTES		(TOTAL_SIZE_OF_OLTC_DATA_LIST_TO_CU*4)							// 4 means sizeof(U32)


// enumeration for bushing leakage current information
enum {
	// 0
	ENUM_BSH_BSH_ALARM,
	ENUM_BSH_RTTRANSF,
	ENUM_BSH_MODEVCOMF,
	ENUM_BSH_MODEVFLT,
	ENUM_BSH_REACTANCE,
	// 5
	ENUM_BSH_ABSREACTANCE,
	ENUM_BSH_LOSSFACTOR,
	ENUM_BSH_VOLTAGE,
	ENUM_BSH_DISPLACEMENT_I,
	ENUM_BSH_LEAKAGE_I,
	// 10
	ENUM_BSH_LEAKAGE_I_ANG,
	ENUM_BSH_VOLTAGE_ANG,
	ENUM_BSH_POWER_FACTOR,
	ENUM_BSH_UNBALANCE_I,
	ENUM_BSH_UNBALANCE_I_ANG,
	// 15
	NUM_KIND_BSH_STATUS
};

enum {
	// 0
	ENUM_BSH_REACTANCE_SETTING,
	ENUM_BSH_POWERFACTOR_SETTING,
	ENUM_BSH_VOLTAGE_SETTING,
	// 3
	NUM_KIND_BSH_SETTING
};

#define SIZE_OF_BSH_DATA_LIST_TO_CU						100																// Number of buffer unit in the queue
#define SIZE_OF_BSH_DATA_UNIT							((NUM_KIND_BSH_STATUS*2)+NUM_KIND_BSH_SETTING+1)				// 2 means data, quality
#define SIZE_OF_BSH_DATA_UNIT_IN_BYTES					(SIZE_OF_BSH_DATA_UNIT*4)										// 4 means sizeof(U32)
#define TOTAL_SIZE_OF_BSH_DATA_LIST_TO_CU				(SIZE_OF_BSH_DATA_UNIT_IN_BYTES*SIZE_OF_BSH_DATA_LIST_TO_CU)
#define TOTAL_SIZE_OF_BSH_DATA_LIST_TO_CU_IN_BYTES		(TOTAL_SIZE_OF_BSH_DATA_LIST_TO_CU*4)							// 4 means sizeof(U32)


// enumeration for ACQ information
enum {
	// 0
	ENUM_ACQ_CLOSE_OPERATION,
	ENUM_ACQ_ABRASION_ALARM,
	ENUM_ACQ_ABRASION_WARNING,
	ENUM_ACQ_OP_TIME_ALARM,
	ENUM_ACQ_COIL_ALARM,
	// 5
	ENUM_ACQ_OP_CNT_ALARM,
	ENUM_ACQ_OP_CNT_WARNING,
	ENUM_ACQ_OP_TIME_WARNING,
	ENUM_ACQ_OP_TIME_SETTING_VALUE,
	ENUM_ACQ_EVTTRANSF,
	// 10
	ENUM_ACQ_RSOPCNT,
	ENUM_ACQ_MODEVCOMF,
	ENUM_ACQ_MODEVFLT,
	ENUM_ACQ_CB_ALARM,
	ENUM_ACQ_ACCUMULATED_ABRASION,
	// 15
	ENUM_ACQ_SWITCHING_I,
	ENUM_ACQ_RECENT_ABRASION,
	ENUM_ACQ_OPEN_AUX_SWITCH_TIME,
	ENUM_ACQ_CLOSE_AUX_SWITCH_TIME,
	ENUM_ACQ_OPEN_REACTION_TIME,
	// 20
	ENUM_ACQ_CLOSE_REACTION_TIME,
	ENUM_ACQ_OPEN_OP_SPEED,
	ENUM_ACQ_CLOSE_OP_SPEED,
	ENUM_ACQ_OPEN_OP_DURATION,
	ENUM_ACQ_CLOSE_OP_DURATION,
	// 25
	ENUM_ACQ_RELAY_CONTACT,
	ENUM_ACQ_OPEN_RELAY_OVERCONTACT,
	ENUM_ACQ_CLOSE_RELAY_OVERCONTACT,
	ENUM_ACQ_COIL_I,
	ENUM_ACQ_TEMPERATURE,
	// 30
	ENUM_ACQ_COIL_V,
	ENUM_ACQ_RECENT_CLOSE_COIL_I,
	ENUM_ACQ_RECENT_OPEN_COIL_I,
	ENUM_ACQ_BUS_IA,
	ENUM_ACQ_BUS_IB,
	// 35
	ENUM_ACQ_BUS_IC,
	// 36
	NUM_KIND_ACQ_STATUS
};

enum {
	// 0
	ENUM_ACQ_ABRASION_ALARM_LEVEL,
	ENUM_ACQ_ABRASION_WARNING_LEVEL,
	ENUM_ACQ_OP_ALARM_TIME_SETTING,
	ENUM_ACQ_OP_WARNING_TIME_SETTING,
	ENUM_ACQ_OP_ALARM_NUMBER_SETTING,
	// 5
	ENUM_ACQ_OP_WARNING_NUMBER_SETTING,
	// 6
	NUM_KIND_ACQ_SETTING
};

#define SIZE_OF_ACQ_DATA_LIST_TO_CU						100																// Number of buffer unit in the queue
#define SIZE_OF_ACQ_DATA_UNIT							((NUM_KIND_ACQ_STATUS*2)+NUM_KIND_ACQ_SETTING+1)				// 2 means data, quality
#define SIZE_OF_ACQ_DATA_UNIT_IN_BYTES					(SIZE_OF_ACQ_DATA_UNIT*4)										// 4 means sizeof(U32)
#define TOTAL_SIZE_OF_ACQ_DATA_LIST_TO_CU				(SIZE_OF_ACQ_DATA_UNIT_IN_BYTES*SIZE_OF_ACQ_DATA_LIST_TO_CU)
#define TOTAL_SIZE_OF_ACQ_DATA_LIST_TO_CU_IN_BYTES		(TOTAL_SIZE_OF_ACQ_DATA_LIST_TO_CU*4)							// 4 means sizeof(U32)


/******************************************************************************
						Data structure definition
******************************************************************************/

typedef struct {
	U32* m_pData;
} dsDataUnitToCU;

typedef struct arm_mms_utc_time_tag
  {
	U32 secs;		/* Number of seconds since January 1, 1970		*/
	U32 fraction;	/* Fraction of a second 						*/
	U32 qflags; 	/* Quality flags, 8 least-significant bits only */
	U32 usecs;
	U32  m_u32Flag; 	   // Update Flag  
  } ARM_MMS_UTC_TIME;
typedef struct
  {
  U32 secs;       /* Number of seconds since January 1, 1970      */
  U32 fraction;   /* Fraction of a second                         */
  U32 qflags;     /* Quality flags, 8 least-significant bits only */
  } MMS_UTC_TIME2;

typedef struct{
	U16 channel;
	U8  m_u8EventType;
	U32 m_u32EventTime;
	U32 m_u32EventTimeMsec;
	U16 m_u16TripCoil1Current[2304];
	U16 m_u16TripCoil2Current[2304];
	U16 m_u16CloseCoilCurrent[2304];
	U16 m_u16PhaseACurrent[2304];
	U16 m_u16PhaseBCurrent[2304];
	U16 m_u16PhaseCCurrent[2304];
	U8  m_u8Contacts[2304];
	U32 m_u32Handshake;
	U32 m_u32SData;
} CBDAUdat;

typedef struct {
	U32 m_u32WriteIndex;
	U32 m_u32ReadIndex;
	U32 m_u32ListSize;
	U32 m_u32Totallen;
	dsDataUnitToCU m_dsDataList[MAX_SIZE_OF_DATA_LIST_TO_CU];
	MMS_UTC_TIME2 m_timelist[MAX_SIZE_OF_DATA_LIST_TO_CU];
} dsTotalDataToCU;


/******************************************************************************
						Variables declaration
******************************************************************************/

// for PDs
dsTotalDataToCU*	pd1data;
dsTotalDataToCU*	pd2data;
dsTotalDataToCU*	pd3data;
dsTotalDataToCU*	pd4data;
dsTotalDataToCU*	pd5data;
dsTotalDataToCU*	pd6data;
dsTotalDataToCU*	pd7data;
dsTotalDataToCU*	pd8data;
dsTotalDataToCU*	pd9data;
dsTotalDataToCU*	pd10data;
dsTotalDataToCU*	pd11data;
dsTotalDataToCU*	pd12data;
dsTotalDataToCU*	pd13data;
dsTotalDataToCU*	pd14data;
dsTotalDataToCU*	pd15data;
dsTotalDataToCU*	pd16data;
dsTotalDataToCU*	pd17data;
dsTotalDataToCU*	pd18data;
dsTotalDataToCU*	pd19data;
dsTotalDataToCU*	pd20data;
dsTotalDataToCU*	pd21data;
dsTotalDataToCU*	pd22data;
dsTotalDataToCU*	pd23data;
dsTotalDataToCU*	pd24data;

// for DGAs
dsTotalDataToCU*	dga1data;
dsTotalDataToCU*	dga2data;
dsTotalDataToCU*	dga3data;
dsTotalDataToCU*	dga4data;
dsTotalDataToCU*	dga5data;
dsTotalDataToCU*	dga6data;

// for OLTCs
dsTotalDataToCU*	oltc1data;
dsTotalDataToCU*	oltc2data;
dsTotalDataToCU*	oltc3data;

// for Bushings
dsTotalDataToCU*	bsh1data;
dsTotalDataToCU*	bsh2data;

// for ACQs
dsTotalDataToCU*	acq1data;
dsTotalDataToCU*	acq2data;
dsTotalDataToCU*	acq3data;
dsTotalDataToCU*	acq4data;
dsTotalDataToCU*	acq5data;
dsTotalDataToCU*	acq6data;
dsTotalDataToCU*	acq7data;
dsTotalDataToCU*	acq8data;
dsTotalDataToCU*	acq9data;


/******************************************************************************
								61850 Define
******************************************************************************/
#define DEFS_DB_PHY_DO_HALFWORD_MAX_NO	5  /* Physical DO 66 */
#define DEFS_DB_PHY_DO_WORD_MAX_NO		4
#define DEFS_DB_PHY_DI_MAX_NO			10

typedef struct{
   U8 u8ctltype;  // 1 : SPC , 2 : DPC
   U8 u8dido;	// 1 : DI, 2 : DO
   U16 u16idx;
}dsControlBitInfo;

typedef struct {
   dsControlBitInfo 	 stControl_bitmap;
   dsControlBitInfo 	 stStatus_bitmap;
   dsControlBitInfo 	 stInterlock_bitmap;
} dsRawControlTbl;



typedef struct{
	U16  m_u16ActiveGrp;
	U32  m_u32Flag; 	   // Update Flag  
} dsSetActvGrp;

typedef struct dsLogicPhyDIMem
{
	U16 wPhyDI[DEFS_DB_PHY_DI_MAX_NO];
	ARM_MMS_UTC_TIME dsArmDestUTC;
} dsLogicPhyDIMem;

typedef struct{
	U16 			 u16TestDO[DEFS_DB_PHY_DO_HALFWORD_MAX_NO]; 
	U32 			 u32TestDO[DEFS_DB_PHY_DO_WORD_MAX_NO];
	U32 			 u32PrevTestDO[DEFS_DB_PHY_DO_WORD_MAX_NO];
} dsTestDO;

typedef struct{
   short u16numofdevice;
   dsSetActvGrp dsActGrp;	
   dsRawControlTbl control_tlb[256];
   ARM_MMS_UTC_TIME dsArmDestUTC;
   dsLogicPhyDIMem dsPhyDIMem;	 
   dsDeviceInfo    dsDeviceInfo;
	//GooseCtrlBlk
   U8				m_u8GoosePubEnable[20]; 		// GOOSE PUB Enable/disable ?λ³΄
   U8				m_u8GoosePubTestEnable[20]; 	// GOOSE PUB TEST Flag ?λ³΄	
   U8				u8simulation;
   U8				u8testmod;
   dsTestDO 		dsTestDO;   
	pthread_mutex_t mutex; // Mutex embedded within the structure
}ds61850SharedMemory;

int Get_61850PortStsValue(int ArrayIdx);
int Get_is61850Flag(void);

/// 2021.06.28 κΈ°μ‘΄ SUR5000 61850Lib ?¬ν¨?μ¬ μ»΄ν???λ €κ³?μΆκ???λΆλΆ?//
/// LocalUnit κ°λ° ??61850 μ½λμͺ?λ³κ²½νλ©΄μ ?κ±°?΄μΌ??                 ///
typedef struct {
	U32 	m_u32AppMode;				// Application Mode setting (0:Basic, x10:DIO Test, x11:Meas Test)
	U32		m_u32LiveTickCnt[4];        // Tick Count Live κ°μ (0:MPU, 1:DSP1, 2:IPU1, 3:STB)
}dsCoreSharedMemory;

typedef struct{
	U32 	u32UpdateFlag[4];   //0:DI, 1:DO, 2:AI, 3:AO
}dsLogicMem;

typedef struct {
	U32		m_u32WaveQSize; //WaveQ Size Check
} dsWaveQ;

typedef struct {
	U64    	m_EvtTmsec;					// Event Time (timeval sec)
	U64    	m_EvtTmusec;				// Event Time (timeval usec)
	U64    	m_u64EvtVal;	  			// ?΄λ²€???΄μ©(bitκ° ?¬νΈ ?λ²?΄λ€.)
	U32     m_u32EvtNum;				// ?΄λ²€??μ’λ₯
	U32 	m_u32EvtType;
	U32		m_u32EvtData1;				// ?΄λ²€??Data??μ’λ₯ (bitdata, data, ip, etc...)
	U32		m_u32EvtData2;				// ?΄λ²€??Gate??Trigger λ²νΈ
	F32		m_f32EvtAnValue[64];		// κ³ μ₯ ?΄λ²€?Έμ κ³μΈ‘ κ°??λ³΄.
	U8		u8EvtNumContent[64];
	U8		u8EvtValContent[64];
	U8		u8EvtData1Content[64];		// ?€μ  ?΄λ²€???΄μ  κ°??΄μ©
	U8		u8EvtData2Content[64];		// ?€μ  ?΄λ²€??λ³κ²?κ°??΄μ©	
} dsEvtFrmDspIfc;


extern ds61850SharedMemory g_ds61850SharedMem;
extern volatile dsCoreSharedMemory* g_pCoreSharedMem; 
extern volatile dsLogicMem* g_ptLogicMemory;
extern volatile dsWaveQ* g_ptWaveBuffer; 
extern volatile ds61850SharedMemory	*g_pSTBSharedMem;

int LGS_ChangeActiveGroup(U8* u8DataSrc);
void ERM_EvtQueue_Insert(dsEvtFrmDspIfc dsEvtData);
//////////////////////////////////////////////////////////////
typedef struct {
	U32 Func;
	U32 length;
	U32 data[1000];
} statusdata;
	

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* URSDK_H_ */
  

