/*
 * CAN.cpp
 *
 *  Created on: 13 févr. 2020
 *      Author: Marc-Antoine
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>//pour le sprintf()
#include <string.h>
//#include <cstring>
#include "board.h"
#include <cr_section_macros.h>
#include "PinsFunctions.h"
#include "GPIO.h"
#include "Clock.h"
#include "Macro.h"
#include "Timers.h"
#include "SPI.h"
#include "LCD.h"
#include "interrupt.h"
#include "RTC.h"
#include "I2C.h"
#include "DisP.h"


void Init_CAN(void)
{
	SB(13,PCONP);
	I2B(PCLKSEL0,26,1); //PCLK_CAN1 = CCLK
	I2B(PCLKSEL0,28,1); //PCLK_CAN2 = CCLK
	I2B(PCLKSEL0,30,1); //PCLK_ACF = CCLK



}
