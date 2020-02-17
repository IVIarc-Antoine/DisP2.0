/*
 * PinsFunctions.h
 *
 *  Created on: 12 oct. 2017
 *      Author: mauclair
 */

#ifndef PINSFUNCTIONS_H_
#define PINSFUNCTIONS_H_

#include "stdint.h"

/* PIN function on GPIO */
static uint32_t volatile * const PtrPINSEL0= (uint32_t *) 0x4002C000;
static uint32_t volatile * const PtrPINSEL1= (uint32_t *) 0x4002C004;
static uint32_t volatile * const PtrPINSEL2= (uint32_t *) 0x4002C008;
static uint32_t volatile * const PtrPINSEL3= (uint32_t *) 0x4002C00C;
static uint32_t volatile * const PtrPINSEL4= (uint32_t *) 0x4002C010;
static uint32_t volatile * const PtrPINSEL7= (uint32_t *) 0x4002C01C;
static uint32_t volatile * const PtrPINSEL9= (uint32_t *) 0x4002C024;
static uint32_t volatile * const PtrPINSEL10= (uint32_t *) 0x4002C028;
#define PINSEL0 *PtrPINSEL0
#define PINSEL1 *PtrPINSEL1
#define PINSEL2 *PtrPINSEL2
#define PINSEL3 *PtrPINSEL3
#define PINSEL4 *PtrPINSEL4
#define PINSEL7 *PtrPINSEL7
#define PINSEL9 *PtrPINSEL9
#define PINSEL10 *PtrPINSEL10


static uint32_t volatile * const PtrPINMODE0= (uint32_t *) 0x4002C040;
static uint32_t volatile * const PtrPINMODE1= (uint32_t *) 0x4002C044;
static uint32_t volatile * const PtrPINMODE2= (uint32_t *) 0x4002C048;
static uint32_t volatile * const PtrPINMODE3= (uint32_t *) 0x4002C04C;
static uint32_t volatile * const PtrPINMODE4= (uint32_t *) 0x4002C050;
static uint32_t volatile * const PtrPINMODE7= (uint32_t *) 0x4002C05C;
static uint32_t volatile * const PtrPINMODE9= (uint32_t *) 0x4002C064;
#define PINMODE0 *PtrPINMODE0
#define PINMODE1 *PtrPINMODE1
#define PINMODE2 *PtrPINMODE2
#define PINMODE3 *PtrPINMODE3
#define PINMODE4 *PtrPINMODE4
#define PINMODE7 *PtrPINMODE7
#define PINMODE9 *PtrPINMODE9


static uint32_t volatile * const PtrPINMODE_OD0= (uint32_t *) 0x4002C068;
static uint32_t volatile * const PtrPINMODE_OD1= (uint32_t *) 0x4002C06C;
static uint32_t volatile * const PtrPINMODE_OD2= (uint32_t *) 0x4002C070;
static uint32_t volatile * const PtrPINMODE_OD3= (uint32_t *) 0x4002C074;
static uint32_t volatile * const PtrPINMODE_OD4= (uint32_t *) 0x4002C078;
#define PINMODE_OD0 *PtrPINMODE_OD0
#define PINMODE_OD1 *PtrPINMODE_OD1
#define PINMODE_OD2 *PtrPINMODE_OD2
#define PINMODE_OD3 *PtrPINMODE_OD3
#define PINMODE_OD4 *PtrPINMODE_OD4

static uint32_t volatile * const PtrI2CPADCFG= (uint32_t *) 0x4002C07C;
#define I2CPADCFG *PtrI2CPADCFG


#endif /* PINSFUNCTIONS_H_ */
