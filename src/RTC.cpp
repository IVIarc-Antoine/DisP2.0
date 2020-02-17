/*
 * RTC.cpp
 *
 *  Created on: 8 déc. 2019
 *      Author: Marc-Antoine
 */

#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "interrupt.h"
#include "RTC.h"


void Init_RTC(void)
{
	SB(9,PCONP);
	InitActualTime();
	RTC_AMR = 0xE8;
	RTC_CIIR = 0x1;
	RTC_CCR = 0x11;
}
void InitActualTime(void)
{
	RTC_DOW = 1;
	RTC_HOUR = 16;
	RTC_MIN = 7;
	RTC_SEC = 40;

	RTC_YEAR = 2019;
	RTC_MONTH = 12;
	RTC_DOM = 8;
	RTC_DOY = 342;
}
