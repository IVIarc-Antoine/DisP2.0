/*
 * Interrupt.h
 *
 *  Created on: 2018-10-09
 *      Author: C-031
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "stdint.h"

/*enum BOOLEAN {
	true,
	false
}bool;

typedef enum BOOLEAN bool;*/




void Init_Interrupts(void);

static uint32_t volatile * const PtrISER0 = (uint32_t *) 0xE000E100;
static uint32_t volatile * const PtrISER1 = (uint32_t *) 0xE000E104;
static uint32_t volatile * const PtrICER0 = (uint32_t *) 0xE000E180;
static uint32_t volatile * const PtrICER1 = (uint32_t *) 0xE000E184;
static uint32_t volatile * const PtrISPR0 = (uint32_t *) 0xE000E200;
static uint32_t volatile * const PtrISPR1 = (uint32_t *) 0xE000E204;
static uint32_t volatile * const PtrICPR0 = (uint32_t *) 0xE000E280;
static uint32_t volatile * const PtrICPR1 = (uint32_t *) 0xE000E284;
static uint32_t volatile * const PtrIABR0 = (uint32_t *) 0xE000E300;
static uint32_t volatile * const PtrIABR1 = (uint32_t *) 0xE000E304;
static uint32_t volatile * const PtrIPR0 = (uint32_t *) 0xE000E400;
static uint32_t volatile * const PtrIPR1 = (uint32_t *) 0xE000E404;
static uint32_t volatile * const PtrIPR2 = (uint32_t *) 0xE000E408;
static uint32_t volatile * const PtrIPR3 = (uint32_t *) 0xE000E40C;
static uint32_t volatile * const PtrIPR4 = (uint32_t *) 0xE000E410;
static uint32_t volatile * const PtrIPR5 = (uint32_t *) 0xE000E414;
static uint32_t volatile * const PtrIPR6 = (uint32_t *) 0xE000E418;
static uint32_t volatile * const PtrIPR7 = (uint32_t *) 0xE000E41C;
static uint32_t volatile * const PtrIPR8 = (uint32_t *) 0xE000E420;
static uint32_t volatile * const PtrSTIR = (uint32_t *) 0xE000EF00;
#define ISER0 *PtrISER0
#define ISER1 *PtrISER1
#define ICER0 *PtrICER0
#define ICER1 *PtrICER1
#define ISPR0 *PtrISPR0
#define ISPR1 *PtrISPR1
#define ICPR0 *PtrICPR0
#define ICPR1 *PtrICPR1
#define IABR0 *PtrIABR0
#define IABR1 *PtrIABR1
#define IPR0 *PtrIPR0
#define IPR1 *PtrIPR1
#define IPR2 *PtrIPR2
#define IPR3 *PtrIPR3
#define IPR4 *PtrIPR4
#define IPR5 *PtrIPR5
#define IPR6 *PtrIPR6
#define IPR7 *PtrIPR7
#define IPR8 *PtrIPR8
#define STIR *PtrSTIR


/* Eternal interrupt */
static uint32_t volatile * const PtrEXTINT = (uint32_t *) 0x400FC140;
static uint32_t volatile * const PtrEXTMODE = (uint32_t *) 0x400FC148;
static uint32_t volatile * const PtrEXTPOLAR = (uint32_t *) 0x400FC14C;
#define EXTINT *PtrEXTINT
#define EXTMODE *PtrEXTMODE
#define EXTPOLAR *PtrEXTPOLAR

#endif /* INTERRUPT_H_ */
