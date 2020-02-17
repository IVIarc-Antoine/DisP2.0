/*
 * Timers.h
 *
 *  Created on: 12 oct. 2017
 *      Author: mauclair
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "stdint.h"

void Sleep(uint32_t ms);
void ST_TIMEOUT(uint32_t tMicroSeconds);
void Init_RIT(void);
void Init_TMR0(void);
void Init_ST(void);



/* Registres du module Timer 0 */
static uint32_t volatile * const PtrT0IR = (uint32_t *) 0x40004000;
static uint32_t volatile * const PtrT0TCR = (uint32_t *) 0x40004004;
static uint32_t volatile * const PtrT0TC = (uint32_t *) 0x40094008;
static uint32_t volatile * const PtrT0PR = (uint32_t *) 0x4000400C;
static uint32_t volatile * const PtrT0PC = (uint32_t *) 0x40004010;
static uint32_t volatile * const PtrT0MCR = (uint32_t *) 0x40004014;
static uint32_t volatile * const PtrT0MR0 = (uint32_t *) 0x40004018;
static uint32_t volatile * const PtrT0MR1 = (uint32_t *) 0x4000401C;
static uint32_t volatile * const PtrT0MR2 = (uint32_t *) 0x40004020;
static uint32_t volatile * const PtrT0MR3 = (uint32_t *) 0x40004024;
static uint32_t volatile * const PtrT0CCR = (uint32_t *) 0x40004028;
static uint32_t volatile * const PtrT0CR0 = (uint32_t *) 0x4000402C;
static uint32_t volatile * const PtrT0CR1 = (uint32_t *) 0x40004030;
static uint32_t volatile * const PtrT0EMR = (uint32_t *) 0x4000403C;
static uint32_t volatile * const PtrT0CTCR = (uint32_t *) 0x40004070;
#define T0IR *PtrT0IR
#define T0TCR *PtrT0TCR
#define T0TC *PtrT0TC
#define T0PR *PtrT0PR
#define T0PC *PtrT0PC
#define T0MCR *PtrT0MCR
#define T0MR0 *PtrT0MR0
#define T0MR1 *PtrT0MR1
#define T0MR2 *PtrT0MR2
#define T0MR3 *PtrT0MR3
#define T0CCR *PtrT0CCR
#define T0CR0 *PtrT0CR0
#define T0CR1 *PtrT0CR1
#define T0EMR *PtrT0EMR
#define T0CTCR *PtrT0CTCR



/* Registres du module Timer 1 */
static uint32_t volatile * const PtrT1IR = (uint32_t *) 0x40008000;
static uint32_t volatile * const PtrT1TCR = (uint32_t *) 0x40008004;
static uint32_t volatile * const PtrT1TC = (uint32_t *) 0x40008008;
static uint32_t volatile * const PtrT1PR = (uint32_t *) 0x4000800C;
static uint32_t volatile * const PtrT1PC = (uint32_t *) 0x40008010;
static uint32_t volatile * const PtrT1MCR = (uint32_t *) 0x40008014;
static uint32_t volatile * const PtrT1MR0 = (uint32_t *) 0x40008018;
static uint32_t volatile * const PtrT1MR1 = (uint32_t *) 0x4000801C;
static uint32_t volatile * const PtrT1MR2 = (uint32_t *) 0x40008020;
static uint32_t volatile * const PtrT1MR3 = (uint32_t *) 0x40008024;
static uint32_t volatile * const PtrT1CCR = (uint32_t *) 0x40008028;
static uint32_t volatile * const PtrT1CR0 = (uint32_t *) 0x4000802C;
static uint32_t volatile * const PtrT1CR1 = (uint32_t *) 0x40008030;
static uint32_t volatile * const PtrT1EMR = (uint32_t *) 0x4000803C;
static uint32_t volatile * const PtrT1CTCR = (uint32_t *) 0x40008070;
#define T1IR *PtrT1IR
#define T1TCR *PtrT1TCR
#define T1TC *PtrT1TC
#define T1PR *PtrT1PR
#define T1PC *PtrT1PC
#define T1MCR *PtrT1MCR
#define T1MR0 *PtrT1MR0
#define T1MR1 *PtrT1MR1
#define T1MR2 *PtrT1MR2
#define T1MR3 *PtrT1MR3
#define T1CCR *PtrT1CCR
#define T1CR0 *PtrT1CR0
#define T1CR1 *PtrT1CR1
#define T1EMR *PtrT1EMR
#define T1CTCR *PtrT1CTCR




/* Registres du module Timer 2 */
static uint32_t volatile * const PtrT2IR = (uint32_t *) 0x40090000;
static uint32_t volatile * const PtrT2TCR = (uint32_t *) 0x40090004;
static uint32_t volatile * const PtrT2TC = (uint32_t *) 0x40090008;
static uint32_t volatile * const PtrT2PR = (uint32_t *) 0x4009000C;
static uint32_t volatile * const PtrT2PC = (uint32_t *) 0x40090010;
static uint32_t volatile * const PtrT2MCR = (uint32_t *) 0x40090014;
static uint32_t volatile * const PtrT2MR0 = (uint32_t *) 0x40090018;
static uint32_t volatile * const PtrT2MR1 = (uint32_t *) 0x4009001C;
static uint32_t volatile * const PtrT2MR2 = (uint32_t *) 0x40090020;
static uint32_t volatile * const PtrT2MR3 = (uint32_t *) 0x40090024;
static uint32_t volatile * const PtrT2CCR = (uint32_t *) 0x40090028;
static uint32_t volatile * const PtrT2CR0 = (uint32_t *) 0x4009002C;
static uint32_t volatile * const PtrT2CR1 = (uint32_t *) 0x40090030;
static uint32_t volatile * const PtrT2EMR = (uint32_t *) 0x4009003C;
static uint32_t volatile * const PtrT2CTCR = (uint32_t *) 0x40090070;
#define T2IR *PtrT2IR
#define T2TCR *PtrT2TCR
#define T2TC *PtrT2TC
#define T2PR *PtrT2PR
#define T2PC *PtrT2PC
#define T2MCR *PtrT2MCR
#define T2MR0 *PtrT2MR0
#define T2MR1 *PtrT2MR1
#define T2MR2 *PtrT2MR2
#define T2MR3 *PtrT2MR3
#define T2CCR *PtrT2CCR
#define T2CR0 *PtrT2CR0
#define T2CR1 *PtrT2CR1
#define T2EMR *PtrT2EMR
#define T2CTCR *PtrT2CTCR

/* Registres du module Timer 3 */
static uint32_t volatile * const PtrT3IR = (uint32_t *) 0x40094000;
static uint32_t volatile * const PtrT3TCR = (uint32_t *) 0x40094004;
static uint32_t volatile * const PtrT3TC = (uint32_t *) 0x40094008;
static uint32_t volatile * const PtrT3PR = (uint32_t *) 0x4009400C;
static uint32_t volatile * const PtrT3PC = (uint32_t *) 0x40094010;
static uint32_t volatile * const PtrT3MCR = (uint32_t *) 0x40094014;
static uint32_t volatile * const PtrT3MR0 = (uint32_t *) 0x40094018;
static uint32_t volatile * const PtrT3MR1 = (uint32_t *) 0x4009401C;
static uint32_t volatile * const PtrT3MR2 = (uint32_t *) 0x40094020;
static uint32_t volatile * const PtrT3MR3 = (uint32_t *) 0x40094024;
static uint32_t volatile * const PtrT3CCR = (uint32_t *) 0x40094028;
static uint32_t volatile * const PtrT3CR0 = (uint32_t *) 0x4009402C;
static uint32_t volatile * const PtrT3CR1 = (uint32_t *) 0x40094030;
static uint32_t volatile * const PtrT3EMR = (uint32_t *) 0x4009403C;
static uint32_t volatile * const PtrT3CTCR = (uint32_t *) 0x40094070;
#define T3IR *PtrT3IR
#define T3TCR *PtrT3TCR
#define T3TC *PtrT3TC
#define T3PR *PtrT3PR
#define T3PC *PtrT3PC
#define T3MCR *PtrT3MCR
#define T3MR0 *PtrT3MR0
#define T3MR1 *PtrT3MR1
#define T3MR2 *PtrT3MR2
#define T3MR3 *PtrT3MR3
#define T3CCR *PtrT3CCR
#define T3CR0 *PtrT3CR0
#define T3CR1 *PtrT3CR1
#define T3EMR *PtrT3EMR
#define T3CTCR *PtrT3CTCR


/* Registres du module Repetitve Timer RIT */
static unsigned long volatile * const PtrRI_TIMER_COMPVAL = (unsigned long *) 0x400B0000;
static unsigned long volatile * const PtrRI_TIMER_MASK = (unsigned long *) 0x400B0004;
static unsigned long volatile * const PtrRI_TIMER_CTRL = (unsigned long *) 0x400B0008;
static unsigned long volatile * const PtrRI_TIMER_COUNT = (unsigned long *) 0x400B000C;
#define RI_TIMER_COMPVAL *PtrRI_TIMER_COMPVAL
#define RI_TIMER_MASK *PtrRI_TIMER_MASK
#define RI_TIMER_CTRL *PtrRI_TIMER_CTRL
#define RI_TIMER_COUNT *PtrRI_TIMER_COUNT

/* Registres du module System Tick Timer ST*/
static unsigned long volatile * const PtrSTCTRL = (unsigned long *) 0xE000E010;
static unsigned long volatile * const PtrSTRELOAD = (unsigned long *) 0xE000E014;
static unsigned long volatile * const PtrSTCURR = (unsigned long *) 0xE000E018;
static unsigned long volatile * const PtrSTCALIB = (unsigned long *) 0xE000E01C;
#define STCTRL *PtrSTCTRL
#define STRELOAD *PtrSTRELOAD
#define STCURR *PtrSTCURR
#define STCALIB *PtrSTCALIB



#endif /* TIMERS_H_ */
