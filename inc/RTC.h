/*
 * RTC.h
 *
 *  Created on: 2017-09-21
 *      Author: C-031
 */

#ifndef RTC_H_
#define RTC_H_

#include "stdint.h"

void Init_RTC(void);
void InitActualTime(void);

#define FORWARD	0
#define BACKWARD !FORWARD
static unsigned long volatile * const PtrILR = (unsigned long *) 0x40024000;
static unsigned long volatile * const PtrCCR = (unsigned long *) 0x40024008;
static unsigned long volatile * const PtrCIIR = (unsigned long *) 0x4002400C;
static unsigned long volatile * const PtrAMR = (unsigned long *) 0x40024010;
static unsigned long volatile * const PtrRTC_AUXEN = (unsigned long *) 0x40024058;
static unsigned long volatile * const PtrRTC_AUX = (unsigned long *) 0x4002405C;
static unsigned long volatile * const PtrCTIME0 = (unsigned long *) 0x40024014;
static unsigned long volatile * const PtrCTIME1 = (unsigned long *) 0x40024018;
static unsigned long volatile * const PtrCTIME2 = (unsigned long *) 0x4002401C;
static unsigned long volatile * const PtrSEC = (unsigned long *) 0x40024020;
static unsigned long volatile * const PtrMIN = (unsigned long *) 0x40024024;
static unsigned long volatile * const PtrHOUR = (unsigned long *) 0x40024028;
static unsigned long volatile * const PtrDOM = (unsigned long *) 0x4002402C;
static unsigned long volatile * const PtrDOW = (unsigned long *) 0x40024030;
static unsigned long volatile * const PtrDOY = (unsigned long *) 0x40024034;
static unsigned long volatile * const PtrMONTH = (unsigned long *) 0x40024038;
static unsigned long volatile * const PtrYEAR = (unsigned long *) 0x4002403C;
static unsigned long volatile * const PtrCALIBRATION = (unsigned long *) 0x40024040;
static unsigned long volatile * const PtrGPREG0 = (unsigned long *) 0x40024044;
static unsigned long volatile * const PtrGPREG1 = (unsigned long *) 0x40024048;
static unsigned long volatile * const PtrGPREG2 = (unsigned long *) 0x4002404C;
static unsigned long volatile * const PtrGPREG3 = (unsigned long *) 0x40024050;
static unsigned long volatile * const PtrGPREG4 = (unsigned long *) 0x40024054;
static unsigned long volatile * const PtrALSEC = (unsigned long *) 0x40024060;
static unsigned long volatile * const PtrALMIN = (unsigned long *) 0x40024064;
static unsigned long volatile * const PtrALHOUR = (unsigned long *) 0x40024068;
static unsigned long volatile * const PtrALDOM = (unsigned long *) 0x4002406C;
static unsigned long volatile * const PtrALDOW = (unsigned long *) 0x40024070;
static unsigned long volatile * const PtrALDOY = (unsigned long *) 0x40024074;
static unsigned long volatile * const PtrALMON = (unsigned long *) 0x40024078;
static unsigned long volatile * const PtrALYEAR = (unsigned long *) 0x4002407C;

#define RTC_ILR *PtrILR
#define RTC_CCR *PtrCCR
#define RTC_CIIR *PtrCIIR
#define RTC_AMR *PtrAMR
#define RTC_AUXEN *PtrAUXEN
#define RTC_AUX *PtrAUX
#define RTC_CTIME0 *PtrCTIME0
#define RTC_CTIME1 *PtrCTIME1
#define RTC_CTIME2 *PtrCTIME2
#define RTC_SEC 	*PtrSEC
#define RTC_MIN 	*PtrMIN
#define RTC_HOUR 	*PtrHOUR
#define RTC_DOM 	*PtrDOM
#define RTC_DOW 	*PtrDOW
#define RTC_DOY 	*PtrDOY
#define RTC_MONTH  	*PtrMONTH
#define RTC_YEAR 	*PtrYEAR
#define RTC_CALIBRATION *PtrCALIBRATION
#define RTC_GPREG0  *PtrGPREG0
#define RTC_GPREG1  *PtrGPREG1
#define RTC_GPREG2  *PtrGPREG2
#define RTC_GPREG3  *PtrGPREG3
#define RTC_GPREG4  *PtrGPREG4

#define RTC_ALSEC  	*PtrALSEC
#define RTC_ALMIN  	*PtrALMIN
#define RTC_ALHOUR  *PtrALHOUR
#define RTC_ALDOM  	*PtrALDOM
#define RTC_ALDOW  	*PtrALDOW
#define RTC_ALDOY  	*PtrALDOY
#define RTC_ALMONTH	*PtrALMON
#define RTC_ALYEAR  *PtrALYEAR


#endif /* RTC_H_ */
