/*
 * I2C.h
 *
 *  Created on: 2017-09-28
 *      Author: C-031
 */

#ifndef I2C_H_
#define I2C_H_

#include "stdint.h"

void Init_I2C(void);
void I2C_Start(void);
void I2C_SendCommand(unsigned char Command);
void I2C_SendDoubleCommand(unsigned char Command1,unsigned char Command2);
void I2C_LCDCommand(unsigned char Command);
unsigned char I2C_ReadData(void);
void I2C_AdrLookup(void);
void I2C_Send(unsigned char* Data);
void I2C_Stat_Handler(int I2CSTAT);




#define SSD1306Adr 0x3C	//write adr 0x78
#define LCDAdr 0x27		//write adr 0x4E
#define EEPROMAdr 0x50	//write adr 0xA0

static unsigned long volatile * const PtrI2C0CONSET = (unsigned long *) 0x4001C000;
static unsigned long volatile * const PtrI2C0STAT = (unsigned long *) 0x4001C004;
static unsigned long volatile * const PtrI2C0DAT = (unsigned long *) 0x4001C008;
static unsigned long volatile * const PtrI2C0ADR0 = (unsigned long *) 0x4001C00C;
static unsigned long volatile * const PtrI2C0SCHL = (unsigned long *) 0x4001C010;
static unsigned long volatile * const PtrI2C0SCLL = (unsigned long *) 0x4001C014;
static unsigned long volatile * const PtrI2C0CONCLRL = (unsigned long *) 0x4001C018;
static unsigned long volatile * const PtrI2C0MMCTRL = (unsigned long *) 0x4001C01C;
static unsigned long volatile * const PtrI2C0ADR1 = (unsigned long *) 0x4001C020;
static unsigned long volatile * const PtrI2C0ADR2 = (unsigned long *) 0x4001C024;
static unsigned long volatile * const PtrI2C0ADR3 = (unsigned long *) 0x4001C028;
static unsigned long volatile * const PtrI2C0DATA_BUFFER = (unsigned long *) 0x4001C02C;
static unsigned long volatile * const PtrI2C0MASK0 = (unsigned long *) 0x4001C030;
static unsigned long volatile * const PtrI2C0MASK1 = (unsigned long *) 0x4001C034;
static unsigned long volatile * const PtrI2C0MASK2 = (unsigned long *) 0x4001C038;
static unsigned long volatile * const PtrI2C0MASK3 = (unsigned long *) 0x4001C03C;
#define I2C0CONSET *PtrI2C0CONSET
#define I2C0STAT *PtrI2C0STAT
#define I2C0DAT	*PtrI2C0DAT
#define I2C0SCHL *PtrI2C0SCHL
#define I2C0SCLL *PtrI2C0SCLL
#define I2C0CONCLRL	*PtrI2C0CONCLRL
#define I2C0MMCTRL *PtrI2C0MMCTRL
#define I2C0ADR0 *PtrI2C0ADR0
#define I2C0ADR1 *PtrI2C0ADR1
#define I2C0ADR2 *PtrI2C0ADR2
#define I2C0ADR3 *PtrI2C0ADR3
#define I2C0DATA_BUFFER *PtrI2C0DATA_BUFFER
#define I2C0MASK0 *PtrI2C0MASK0
#define I2C0MASK1 *PtrI2C0MASK1
#define I2C0MASK2 *PtrI2C0MASK2
#define I2C0MASK3 *PtrI2C0MASK3

static unsigned long volatile * const PtrI2C1CONSET = (unsigned long *) 0x4005C000;
static unsigned long volatile * const PtrI2C1STAT = (unsigned long *) 0x4005C004;
static unsigned long volatile * const PtrI2C1DAT = (unsigned long *) 0x4005C008;
static unsigned long volatile * const PtrI2C1ADR0 = (unsigned long *) 0x4005C00C;
static unsigned long volatile * const PtrI2C1SCHL = (unsigned long *) 0x4005C010;
static unsigned long volatile * const PtrI2C1SCLL = (unsigned long *) 0x4005C014;
static unsigned long volatile * const PtrI2C1CONCLRL = (unsigned long *) 0x4005C018;
static unsigned long volatile * const PtrI2C1MMCTRL = (unsigned long *) 0x4005C01C;
static unsigned long volatile * const PtrI2C1ADR1 = (unsigned long *) 0x4005C020;
static unsigned long volatile * const PtrI2C1ADR2 = (unsigned long *) 0x4005C024;
static unsigned long volatile * const PtrI2C1ADR3 = (unsigned long *) 0x4005C028;
static unsigned long volatile * const PtrI2C1DATA_BUFFER = (unsigned long *) 0x4005C02C;
static unsigned long volatile * const PtrI2C1MASK0 = (unsigned long *) 0x4005C030;
static unsigned long volatile * const PtrI2C1MASK1 = (unsigned long *) 0x4005C034;
static unsigned long volatile * const PtrI2C1MASK2 = (unsigned long *) 0x4005C038;
static unsigned long volatile * const PtrI2C1MASK3 = (unsigned long *) 0x4005C03C;
#define I2C1CONSET *PtrI2C1CONSET
#define I2C1STAT *PtrI2C1STAT
#define I2C1DAT	*PtrI2C1DAT
#define I2C1SCHL *PtrI2C1SCHL
#define I2C1SCLL *PtrI2C1SCLL
#define I2C1CONCLRL	*PtrI2C1CONCLRL
#define I2C1MMCTRL *PtrI2C1MMCTRL
#define I2C1ADR0 *PtrI2C1ADR0
#define I2C1ADR1 *PtrI2C1ADR1
#define I2C1ADR2 *PtrI2C1ADR2
#define I2C1ADR3 *PtrI2C1ADR3
#define I2C1DATA_BUFFER *PtrI2C1DATA_BUFFER
#define I2C1MASK0 *PtrI2C1MASK0
#define I2C1MASK1 *PtrI2C1MASK1
#define I2C1MASK2 *PtrI2C1MASK2
#define I2C1MASK3 *PtrI2C1MASK3



static unsigned long volatile * const PtrI2C2CONSET = (unsigned long *) 0x400A0000;
static unsigned long volatile * const PtrI2C2STAT = (unsigned long *) 0x400A0004;
static unsigned long volatile * const PtrI2C2DAT = (unsigned long *) 0x400A0008;
static unsigned long volatile * const PtrI2C2ADR0 = (unsigned long *) 0x400A000C;
static unsigned long volatile * const PtrI2C2SCHL = (unsigned long *) 0x400A0010;
static unsigned long volatile * const PtrI2C2SCLL = (unsigned long *) 0x400A0014;
static unsigned long volatile * const PtrI2C2CONCLRL = (unsigned long *) 0x400A0018;
static unsigned long volatile * const PtrI2C2MMCTRL = (unsigned long *) 0x400A001C;
static unsigned long volatile * const PtrI2C2ADR1 = (unsigned long *) 0x400A0020;
static unsigned long volatile * const PtrI2C2ADR2 = (unsigned long *) 0x400A0024;
static unsigned long volatile * const PtrI2C2ADR3 = (unsigned long *) 0x400A0028;
static unsigned long volatile * const PtrI2C2DATA_BUFFER = (unsigned long *) 0x400A002C;
static unsigned long volatile * const PtrI2C2MASK0 = (unsigned long *) 0x400A0030;
static unsigned long volatile * const PtrI2C2MASK1 = (unsigned long *) 0x400A0034;
static unsigned long volatile * const PtrI2C2MASK2 = (unsigned long *) 0x400A0038;
static unsigned long volatile * const PtrI2C2MASK3 = (unsigned long *) 0x400A003C;
#define I2C2CONSET *PtrI2C2CONSET
#define I2C2STAT *PtrI2C2STAT
#define I2C2DAT	*PtrI2C2DAT
#define I2C2SCHL *PtrI2C2SCHL
#define I2C2SCLL *PtrI2C2SCLL
#define I2C2CONCLRL	*PtrI2C2CONCLRL
#define I2C2MMCTRL *PtrI2C2MMCTRL
#define I2C2ADR0 *PtrI2C2ADR0
#define I2C2ADR1 *PtrI2C2ADR1
#define I2C2ADR2 *PtrI2C2ADR2
#define I2C2ADR3 *PtrI2C2ADR3
#define I2C2DATA_BUFFER *PtrI2C2DATA_BUFFER
#define I2C2MASK0 *PtrI2C2MASK0
#define I2C2MASK1 *PtrI2C2MASK1
#define I2C2MASK2 *PtrI2C2MASK2
#define I2C2MASK3 *PtrI2C2MASK3



#endif /* I2C_H_ */
