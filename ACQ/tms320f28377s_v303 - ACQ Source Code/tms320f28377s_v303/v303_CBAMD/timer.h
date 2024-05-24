/* ************************************ ************************************ *
 *
 * Project Name : CBAMD(sanion)
 * Programmer   : In Ho Kim (20220308)
 * File Name    : timer.h
 *
 * ************************************ ************************************ */


#define eBLOCK_OUTPUT       3       // 3ȸ �̻� ���ʹ� DO ��� ����
#define eBLOCK_MPRAM        10      // 10ȸ �̻� ���ʹ� H/W���� MPRAM ���� ���� & DO ��� Clear


#ifndef __TIMER_H
#define __TIMER_H

//#include "main.h"				// LeakCurrent Header

#define eTIME_SYNC_CAL          37
#define eTIME_MPRAM_SYNC_CAL    4

extern void Init_Timer( void );

extern void Freq_TimeSetting( void );



#endif /* __TIMER_H */ 
