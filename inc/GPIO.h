/*
 * GPIO.h
 *
 *  Created on: 12 oct. 2017
 *      Author: mauclair
 */

#ifndef GPIO_H_
#define GPIO_H_


#include "stdint.h"


/****************** FIODIR *********************************************/
/* GPIO 0 DIR */
static uint32_t volatile * const PtrFIO0DIR = (uint32_t *) 0x2009C000;
static uint8_t volatile * const PtrFIO0DIR0 = (uint8_t *) 0x2009C000;
static uint8_t volatile * const PtrFIO0DIR1 = (uint8_t *)  0x2009C001;
static uint8_t volatile * const PtrFIO0DIR2 = (uint8_t *)  0x2009C002;
static uint8_t volatile * const PtrFIO0DIR3 = (uint8_t *)  0x2009C003;
static uint16_t volatile * const PtrFIO0DIRL = (uint16_t *)  0x2009C000;
static uint16_t volatile * const PtrFIO0DIRU = (uint16_t *)  0x2009C002;
#define FIO0DIR *PtrFIO0DIR
#define FIO0DIR0 *PtrFIO0DIR0
#define FIO0DIR1 *PtrFIO0DIR1
#define FIO0DIR2 *PtrFIO0DIR2
#define FIO0DIR3 *PtrFIO0DIR3
#define FIO0DIRL *PtrFIO0DIRL
#define FIO0DIRU *PtrFIO0DIRU

/* GPIO 1 DIR */
static uint32_t volatile * const PtrFIO1DIR = (uint32_t *) 0x2009C020;
static uint8_t volatile * const PtrFIO1DIR0 = (uint8_t *) 0x2009C020;
static uint8_t volatile * const PtrFIO1DIR1 = (uint8_t *) 0x2009C021;
static uint8_t volatile * const PtrFIO1DIR2 = (uint8_t *) 0x2009C022;
static uint8_t volatile * const PtrFIO1DIR3 = (uint8_t *) 0x2009C023;
static uint16_t volatile * const PtrFIO1DIRL = (uint16_t *) 0x2009C020;
static uint16_t volatile * const PtrFIO1DIRU = (uint16_t *) 0x2009C022;
#define FIO1DIR *PtrFIO1DIR
#define FIO1DIR0 *PtrFIO1DIR0
#define FIO1DIR1 *PtrFIO1DIR1
#define FIO1DIR2 *PtrFIO1DIR2
#define FIO1DIR3 *PtrFIO1DIR3
#define FIO1DIRL *PtrFIO1DIRL
#define FIO1DIRU *PtrFIO1DIRU


/* GPIO 2 DIR */
static uint32_t volatile * const PtrFIO2DIR  = (uint32_t *) 0x2009C040;
static uint8_t volatile * const PtrFIO2DIR0 = (uint8_t *) 0x2009C040;
static uint8_t volatile * const PtrFIO2DIR1 = (uint8_t *)  0x2009C041;
static uint8_t volatile * const PtrFIO2DIR2 = (uint8_t *)  0x2009C042;
static uint8_t volatile * const PtrFIO2DIR3 = (uint8_t *)  0x2009C043;
static uint16_t volatile * const PtrFIO2DIRL = (uint16_t *) 0x2009C040;
static uint16_t volatile * const PtrFIO2DIRU = (uint16_t *) 0x2009C042;
#define FIO2DIR *PtrFIO2DIR
#define FIO2DIR0 *PtrFIO2DIR0
#define FIO2DIR1 *PtrFIO2DIR1
#define FIO2DIR2 *PtrFIO2DIR2
#define FIO2DIR3 *PtrFIO2DIR3
#define FIO2DIRL *PtrFIO2DIRL
#define FIO2DIRU *PtrFIO2DIRU

/* GPIO 3 DIR */
static uint32_t volatile * const PtrFIO3DIR  = (uint32_t *) 0x2009C060;
static uint8_t volatile * const PtrFIO3DIR0 = (uint8_t * ) 0x2009C060;
static uint8_t volatile * const PtrFIO3DIR1 = (uint8_t * ) 0x2009C061;
static uint8_t volatile * const PtrFIO3DIR2 = (uint8_t * ) 0x2009C062;
static uint8_t volatile * const PtrFIO3DIR3 = (uint8_t * ) 0x2009C063;
static uint16_t volatile * const PtrFIO3DIRL = (uint16_t *) 0x2009C060;
static uint16_t volatile * const PtrFIO3DIRU = (uint16_t *) 0x2009C062;
#define FIO3DIR  *PtrFIO3DIR
#define FIO3DIR0 *PtrFIO3DIR0
#define FIO3DIR1 *PtrFIO3DIR1
#define FIO3DIR2 *PtrFIO3DIR2
#define FIO3DIR3 *PtrFIO3DIR3
#define FIO3DIRL *PtrFIO3DIRL
#define FIO3DIRU *PtrFIO3DIRU

/* GPIO 4 DIR */
static uint32_t volatile * const PtrFIO4DIR = (uint32_t *) 0x2009C080;
static uint8_t volatile * const PtrFIO4DIR0 = (uint8_t *) 0x2009C080;
static uint8_t volatile * const PtrFIO4DIR1 = (uint8_t *) 0x2009C081;
static uint8_t volatile * const PtrFIO4DIR2 = (uint8_t *) 0x2009C082;
static uint8_t volatile * const PtrFIO4DIR3 = (uint8_t *) 0x2009C083;
static uint16_t volatile * const PtrFIO4DIRL = (uint16_t *) 0x2009C080;
static uint16_t volatile * const PtrFIO4DIRU = (uint16_t *) 0x2009C082;
#define FIO4DIR *PtrFIO4DIR
#define FIO4DIR0 *PtrFIO4DIR0
#define FIO4DIR1 *PtrFIO4DIR1
#define FIO4DIR2 *PtrFIO4DIR2
#define FIO4DIR3 *PtrFIO4DIR3
#define FIO4DIRL *PtrFIO4DIRL
#define FIO4DIRU *PtrFIO4DIRU
/****************** FIODIR END*********************************************/












/****************** FIOMASK *********************************************/
/* GPIO 0 MASK */
static uint32_t volatile * const PtrFIO0MASK = (uint32_t *) 0x2009C010;
static uint8_t volatile * const PtrFIO0MASK0 = (uint8_t *) 0x2009C010;
static uint8_t volatile * const PtrFIO0MASK1 = (uint8_t *)  0x2009C011;
static uint8_t volatile * const PtrFIO0MASK2 = (uint8_t *)  0x2009C012;
static uint8_t volatile * const PtrFIO0MASK3 = (uint8_t *)  0x2009C013;
static uint16_t volatile * const PtrFIO0MASKL = (uint16_t *)  0x2009C010;
static uint16_t volatile * const PtrFIO0MASKU = (uint16_t *)  0x2009C012;
#define FIO0MASK *PtrFIO0MASK
#define FIO0MASK0 *PtrFIO0MASK0
#define FIO0MASK1 *PtrFIO0MASK1
#define FIO0MASK2 *PtrFIO0MASK2
#define FIO0MASK3 *PtrFIO0MASK3
#define FIO0MASKL *PtrFIO0MASKL
#define FIO0MASKU *PtrFIO0MASKU

/* GPIO 1 MASK */
static uint32_t volatile * const PtrFIO1MASK = (uint32_t *) 0x2009C030;
static uint8_t volatile * const PtrFIO1MASK0 = (uint8_t *) 0x2009C030;
static uint8_t volatile * const PtrFIO1MASK1 = (uint8_t *) 0x2009C031;
static uint8_t volatile * const PtrFIO1MASK2 = (uint8_t *) 0x2009C032;
static uint8_t volatile * const PtrFIO1MASK3 = (uint8_t *) 0x2009C033;
static uint16_t volatile * const PtrFIO1MASKL = (uint16_t *) 0x2009C030;
static uint16_t volatile * const PtrFIO1MASKU = (uint16_t *) 0x2009C032;
#define FIO1MASK *PtrFIO1MASK
#define FIO1MASK0 *PtrFIO1MASK0
#define FIO1MASK1 *PtrFIO1MASK1
#define FIO1MASK2 *PtrFIO1MASK2
#define FIO1MASK3 *PtrFIO1MASK3
#define FIO1MASKL *PtrFIO1MASKL
#define FIO1MASKU *PtrFIO1MASKU


/* GPIO 2 MASK */
static uint32_t volatile * const PtrFIO2MASK  = (uint32_t *) 0x2009C050;
static uint8_t volatile * const PtrFIO2MASK0 = (uint8_t *) 0x2009C050;
static uint8_t volatile * const PtrFIO2MASK1 = (uint8_t *)  0x2009C051;
static uint8_t volatile * const PtrFIO2MASK2 = (uint8_t *)  0x2009C052;
static uint8_t volatile * const PtrFIO2MASK3 = (uint8_t *)  0x2009C053;
static uint16_t volatile * const PtrFIO2MASKL = (uint16_t *) 0x2009C050;
static uint16_t volatile * const PtrFIO2MASKU = (uint16_t *) 0x2009C052;
#define FIO2MASK *PtrFIO2MASK
#define FIO2MASK0 *PtrFIO2MASK0
#define FIO2MASK1 *PtrFIO2MASK1
#define FIO2MASK2 *PtrFIO2MASK2
#define FIO2MASK3 *PtrFIO2MASK3
#define FIO2MASKL *PtrFIO2MASKL
#define FIO2MASKU *PtrFIO2MASKU

/* GPIO 3 MASK */
static uint32_t volatile * const PtrFIO3MASK  = (uint32_t *) 0x2009C070;
static uint8_t volatile * const PtrFIO3MASK0 = (uint8_t * ) 0x2009C070;
static uint8_t volatile * const PtrFIO3MASK1 = (uint8_t * ) 0x2009C071;
static uint8_t volatile * const PtrFIO3MASK2 = (uint8_t * ) 0x2009C072;
static uint8_t volatile * const PtrFIO3MASK3 = (uint8_t * ) 0x2009C073;
static uint16_t volatile * const PtrFIO3MASKL = (uint16_t *) 0x2009C070;
static uint16_t volatile * const PtrFIO3MASKU = (uint16_t *) 0x2009C072;
#define FIO3MASK  *PtrFIO3MASK
#define FIO3MASK0 *PtrFIO3MASK0
#define FIO3MASK1 *PtrFIO3MASK1
#define FIO3MASK2 *PtrFIO3MASK2
#define FIO3MASK3 *PtrFIO3MASK3
#define FIO3MASKL *PtrFIO3MASKL
#define FIO3MASKU *PtrFIO3MASKU

/* GPIO 4 MASK */
static uint32_t volatile * const PtrFIO4MASK = (uint32_t *) 0x2009C090;
static uint8_t volatile * const PtrFIO4MASK0 = (uint8_t *) 0x2009C090;
static uint8_t volatile * const PtrFIO4MASK1 = (uint8_t *) 0x2009C091;
static uint8_t volatile * const PtrFIO4MASK2 = (uint8_t *) 0x2009C092;
static uint8_t volatile * const PtrFIO4MASK3 = (uint8_t *) 0x2009C093;
static uint16_t volatile * const PtrFIO4MASKL = (uint16_t *) 0x2009C090;
static uint16_t volatile * const PtrFIO4MASKU = (uint16_t *) 0x2009C092;
#define FIO4MASK *PtrFIO4MASK
#define FIO4MASK0 *PtrFIO4MASK0
#define FIO4MASK1 *PtrFIO4MASK1
#define FIO4MASK2 *PtrFIO4MASK2
#define FIO4MASK3 *PtrFIO4MASK3
#define FIO4MASKL *PtrFIO4MASKL
#define FIO4MASKU *PtrFIO4MASKU
/****************** FIOMASK END*********************************************/









/****************** FIOPIN *********************************************/
/* GPIO 0 PIN */
static uint32_t volatile * const PtrFIO0PIN = (uint32_t *) 0x2009C014;
static uint8_t volatile * const PtrFIO0PIN0 = (uint8_t *)  0x2009C014;
static uint8_t volatile * const PtrFIO0PIN1 = (uint8_t *)  0x2009C015;
static uint8_t volatile * const PtrFIO0PIN2 = (uint8_t *)  0x2009C016;
static uint8_t volatile * const PtrFIO0PIN3 = (uint8_t *)  0x2009C017;
static uint16_t volatile * const PtrFIO0PINL = (uint16_t *)  0x2009C014;
static uint16_t volatile * const PtrFIO0PINU = (uint16_t *)  0x2009C016;
#define FIO0PIN *PtrFIO0PIN
#define FIO0PIN0 *PtrFIO0PIN0
#define FIO0PIN1 *PtrFIO0PIN1
#define FIO0PIN2 *PtrFIO0PIN2
#define FIO0PIN3 *PtrFIO0PIN3
#define FIO0PINL *PtrFIO0PINL
#define FIO0PINU *PtrFIO0PINU

/* GPIO 1 PIN */
static uint32_t volatile * const PtrFIO1PIN = (uint32_t *) 0x2009C034;
static uint8_t volatile * const PtrFIO1PIN0 = (uint8_t *) 0x2009C034;
static uint8_t volatile * const PtrFIO1PIN1 = (uint8_t *) 0x2009C035;
static uint8_t volatile * const PtrFIO1PIN2 = (uint8_t *) 0x2009C036;
static uint8_t volatile * const PtrFIO1PIN3 = (uint8_t *) 0x2009C037;
static uint16_t volatile * const PtrFIO1PINL = (uint16_t *) 0x2009C034;
static uint16_t volatile * const PtrFIO1PINU = (uint16_t *) 0x2009C036;
#define FIO1PIN *PtrFIO1PIN
#define FIO1PIN0 *PtrFIO1PIN0
#define FIO1PIN1 *PtrFIO1PIN1
#define FIO1PIN2 *PtrFIO1PIN2
#define FIO1PIN3 *PtrFIO1PIN3
#define FIO1PINL *PtrFIO1PINL
#define FIO1PINU *PtrFIO1PINU


/* GPIO 2 PIN */
static uint32_t volatile * const PtrFIO2PIN  = (uint32_t *) 0x2009C054;
static uint8_t volatile * const PtrFIO2PIN0 = (uint8_t *) 0x2009C054;
static uint8_t volatile * const PtrFIO2PIN1 = (uint8_t *)  0x2009C055;
static uint8_t volatile * const PtrFIO2PIN2 = (uint8_t *)  0x2009C056;
static uint8_t volatile * const PtrFIO2PIN3 = (uint8_t *)  0x2009C057;
static uint16_t volatile * const PtrFIO2PINL = (uint16_t *) 0x2009C054;
static uint16_t volatile * const PtrFIO2PINU = (uint16_t *) 0x2009C056;
#define FIO2PIN *PtrFIO2PIN
#define FIO2PIN0 *PtrFIO2PIN0
#define FIO2PIN1 *PtrFIO2PIN1
#define FIO2PIN2 *PtrFIO2PIN2
#define FIO2PIN3 *PtrFIO2PIN3
#define FIO2PINL *PtrFIO2PINL
#define FIO2PINU *PtrFIO2PINU

/* GPIO 3 PIN */
static uint32_t volatile * const PtrFIO3PIN  = (uint32_t *) 0x2009C074;
static uint8_t volatile * const PtrFIO3PIN0 = (uint8_t * ) 0x2009C074;
static uint8_t volatile * const PtrFIO3PIN1 = (uint8_t * ) 0x2009C075;
static uint8_t volatile * const PtrFIO3PIN2 = (uint8_t * ) 0x2009C076;
static uint8_t volatile * const PtrFIO3PIN3 = (uint8_t * ) 0x2009C077;
static uint16_t volatile * const PtrFIO3PINL = (uint16_t *) 0x2009C074;
static uint16_t volatile * const PtrFIO3PINU = (uint16_t *) 0x2009C076;
#define FIO3PIN  *PtrFIO3PIN
#define FIO3PIN0 *PtrFIO3PIN0
#define FIO3PIN1 *PtrFIO3PIN1
#define FIO3PIN2 *PtrFIO3PIN2
#define FIO3PIN3 *PtrFIO3PIN3
#define FIO3PINL *PtrFIO3PINL
#define FIO3PINU *PtrFIO3PINU

/* GPIO 4 PIN */
static uint32_t volatile * const PtrFIO4PIN = (uint32_t *) 0x2009C094;
static uint8_t volatile * const PtrFIO4PIN0 = (uint8_t *) 0x2009C094;
static uint8_t volatile * const PtrFIO4PIN1 = (uint8_t *) 0x2009C095;
static uint8_t volatile * const PtrFIO4PIN2 = (uint8_t *) 0x2009C096;
static uint8_t volatile * const PtrFIO4PIN3 = (uint8_t *) 0x2009C097;
static uint16_t volatile * const PtrFIO4PINL = (uint16_t *) 0x2009C094;
static uint16_t volatile * const PtrFIO4PINU = (uint16_t *) 0x2009C096;
#define FIO4PIN *PtrFIO4PIN
#define FIO4PIN0 *PtrFIO4PIN0
#define FIO4PIN1 *PtrFIO4PIN1
#define FIO4PIN2 *PtrFIO4PIN2
#define FIO4PIN3 *PtrFIO4PIN3
#define FIO4PINL *PtrFIO4PINL
#define FIO4PINU *PtrFIO4PINU
/****************** FIOPIN END*********************************************/




/****************** FIOSET *********************************************/
/* GPIO 0 SET */
static uint32_t volatile * const PtrFIO0SET = (uint32_t *) 0x2009C018;
static uint8_t volatile * const PtrFIO0SET0 = (uint8_t *) 0x2009C018;
static uint8_t volatile * const PtrFIO0SET1 = (uint8_t *)  0x2009C019;
static uint8_t volatile * const PtrFIO0SET2 = (uint8_t *)  0x2009C01A;
static uint8_t volatile * const PtrFIO0SET3 = (uint8_t *)  0x2009C01B;
static uint16_t volatile * const PtrFIO0SETL = (uint16_t *)  0x2009C018;
static uint16_t volatile * const PtrFIO0SETU = (uint16_t *)  0x2009C01A;
#define FIO0SET *PtrFIO0SET
#define FIO0SET0 *PtrFIO0SET0
#define FIO0SET1 *PtrFIO0SET1
#define FIO0SET2 *PtrFIO0SET2
#define FIO0SET3 *PtrFIO0SET3
#define FIO0SETL *PtrFIO0SETL
#define FIO0SETU *PtrFIO0SETU

/* GPIO 1 SET */
static uint32_t volatile * const PtrFIO1SET = (uint32_t *) 0x2009C038;
static uint8_t volatile * const PtrFIO1SET0 = (uint8_t *) 0x2009C038;
static uint8_t volatile * const PtrFIO1SET1 = (uint8_t *) 0x2009C039;
static uint8_t volatile * const PtrFIO1SET2 = (uint8_t *) 0x2009C03A;
static uint8_t volatile * const PtrFIO1SET3 = (uint8_t *) 0x2009C03B;
static uint16_t volatile * const PtrFIO1SETL = (uint16_t *) 0x2009C038;
static uint16_t volatile * const PtrFIO1SETU = (uint16_t *) 0x2009C03B;
#define FIO1SET *PtrFIO1SET
#define FIO1SET0 *PtrFIO1SET0
#define FIO1SET1 *PtrFIO1SET1
#define FIO1SET2 *PtrFIO1SET2
#define FIO1SET3 *PtrFIO1SET3
#define FIO1SETL *PtrFIO1SETL
#define FIO1SETU *PtrFIO1SETU


/* GPIO 2 SET */
static uint32_t volatile * const PtrFIO2SET  = (uint32_t *) 0x2009C058;
static uint8_t volatile * const PtrFIO2SET0 = (uint8_t *) 0x2009C058;
static uint8_t volatile * const PtrFIO2SET1 = (uint8_t *)  0x2009C059;
static uint8_t volatile * const PtrFIO2SET2 = (uint8_t *)  0x2009C05A;
static uint8_t volatile * const PtrFIO2SET3 = (uint8_t *)  0x2009C05B;
static uint16_t volatile * const PtrFIO2SETL = (uint16_t *) 0x2009C058;
static uint16_t volatile * const PtrFIO2SETU = (uint16_t *) 0x2009C05A;
#define FIO2SET *PtrFIO2SET
#define FIO2SET0 *PtrFIO2SET0
#define FIO2SET1 *PtrFIO2SET1
#define FIO2SET2 *PtrFIO2SET2
#define FIO2SET3 *PtrFIO2SET3
#define FIO2SETL *PtrFIO2SETL
#define FIO2SETU *PtrFIO2SETU

/* GPIO 3 SET */
static uint32_t volatile * const PtrFIO3SET  = (uint32_t *) 0x2009C078;
static uint8_t volatile * const PtrFIO3SET0 = (uint8_t * ) 0x2009C078;
static uint8_t volatile * const PtrFIO3SET1 = (uint8_t * ) 0x2009C079;
static uint8_t volatile * const PtrFIO3SET2 = (uint8_t * ) 0x2009C07A;
static uint8_t volatile * const PtrFIO3SET3 = (uint8_t * ) 0x2009C07B;
static uint16_t volatile * const PtrFIO3SETL = (uint16_t *) 0x2009C078;
static uint16_t volatile * const PtrFIO3SETU = (uint16_t *) 0x2009C07A;
#define FIO3SET  *PtrFIO3SET
#define FIO3SET0 *PtrFIO3SET0
#define FIO3SET1 *PtrFIO3SET1
#define FIO3SET2 *PtrFIO3SET2
#define FIO3SET3 *PtrFIO3SET3
#define FIO3SETL *PtrFIO3SETL
#define FIO3SETU *PtrFIO3SETU

/* GPIO 4 SET */
static uint32_t volatile * const PtrFIO4SET = (uint32_t *) 0x2009C098;
static uint8_t volatile * const PtrFIO4SET0 = (uint8_t *) 0x2009C098;
static uint8_t volatile * const PtrFIO4SET1 = (uint8_t *) 0x2009C099;
static uint8_t volatile * const PtrFIO4SET2 = (uint8_t *) 0x2009C09A;
static uint8_t volatile * const PtrFIO4SET3 = (uint8_t *) 0x2009C09B;
static uint16_t volatile * const PtrFIO4SETL = (uint16_t *) 0x2009C098;
static uint16_t volatile * const PtrFIO4SETU = (uint16_t *) 0x2009C09A;
#define FIO4SET *PtrFIO4SET
#define FIO4SET0 *PtrFIO4SET0
#define FIO4SET1 *PtrFIO4SET1
#define FIO4SET2 *PtrFIO4SET2
#define FIO4SET3 *PtrFIO4SET3
#define FIO4SETL *PtrFIO4SETL
#define FIO4SETU *PtrFIO4SETU
/****************** FIOSET END*********************************************/













/****************** FIOCLR *********************************************/
/* GPIO 0 CLR */
static uint32_t volatile * const PtrFIO0CLR = (uint32_t *) 0x2009C01C;
static uint8_t volatile * const PtrFIO0CLR0 = (uint8_t *) 0x2009C01C;
static uint8_t volatile * const PtrFIO0CLR1 = (uint8_t *)  0x2009C01D;
static uint8_t volatile * const PtrFIO0CLR2 = (uint8_t *)  0x2009C01E;
static uint8_t volatile * const PtrFIO0CLR3 = (uint8_t *)  0x2009C01F;
static uint16_t volatile * const PtrFIO0CLRL = (uint16_t *)  0x2009C01C;
static uint16_t volatile * const PtrFIO0CLRU = (uint16_t *)  0x2009C01E;
#define FIO0CLR *PtrFIO0CLR
#define FIO0CLR0 *PtrFIO0CLR0
#define FIO0CLR1 *PtrFIO0CLR1
#define FIO0CLR2 *PtrFIO0CLR2
#define FIO0CLR3 *PtrFIO0CLR3
#define FIO0CLRL *PtrFIO0CLRL
#define FIO0CLRU *PtrFIO0CLRU

/* GPIO 1 CLR */
static uint32_t volatile * const PtrFIO1CLR = (uint32_t *) 0x2009C03C;
static uint8_t volatile * const PtrFIO1CLR0 = (uint8_t *) 0x2009C03C;
static uint8_t volatile * const PtrFIO1CLR1 = (uint8_t *) 0x2009C03D;
static uint8_t volatile * const PtrFIO1CLR2 = (uint8_t *) 0x2009C03E;
static uint8_t volatile * const PtrFIO1CLR3 = (uint8_t *) 0x2009C03F;
static uint16_t volatile * const PtrFIO1CLRL = (uint16_t *) 0x2009C03C;
static uint16_t volatile * const PtrFIO1CLRU = (uint16_t *) 0x2009C03E;
#define FIO1CLR *PtrFIO1CLR
#define FIO1CLR0 *PtrFIO1CLR0
#define FIO1CLR1 *PtrFIO1CLR1
#define FIO1CLR2 *PtrFIO1CLR2
#define FIO1CLR3 *PtrFIO1CLR3
#define FIO1CLRL *PtrFIO1CLRL
#define FIO1CLRU *PtrFIO1CLRU


/* GPIO 2 CLR */
static uint32_t volatile * const PtrFIO2CLR  = (uint32_t *) 0x2009C05C;
static uint8_t volatile * const PtrFIO2CLR0 = (uint8_t *) 0x2009C05C;
static uint8_t volatile * const PtrFIO2CLR1 = (uint8_t *)  0x2009C05D;
static uint8_t volatile * const PtrFIO2CLR2 = (uint8_t *)  0x2009C05E;
static uint8_t volatile * const PtrFIO2CLR3 = (uint8_t *)  0x2009C05F;
static uint16_t volatile * const PtrFIO2CLRL = (uint16_t *) 0x2009C05C;
static uint16_t volatile * const PtrFIO2CLRU = (uint16_t *) 0x2009C05E;
#define FIO2CLR *PtrFIO2CLR
#define FIO2CLR0 *PtrFIO2CLR0
#define FIO2CLR1 *PtrFIO2CLR1
#define FIO2CLR2 *PtrFIO2CLR2
#define FIO2CLR3 *PtrFIO2CLR3
#define FIO2CLRL *PtrFIO2CLRL
#define FIO2CLRU *PtrFIO2CLRU

/* GPIO 3 CLR */
static uint32_t volatile * const PtrFIO3CLR  = (uint32_t *) 0x2009C07C;
static uint8_t volatile * const PtrFIO3CLR0 = (uint8_t * ) 0x2009C07C;
static uint8_t volatile * const PtrFIO3CLR1 = (uint8_t * ) 0x2009C07D;
static uint8_t volatile * const PtrFIO3CLR2 = (uint8_t * ) 0x2009C07E;
static uint8_t volatile * const PtrFIO3CLR3 = (uint8_t * ) 0x2009C07B;
static uint16_t volatile * const PtrFIO3CLRL = (uint16_t *) 0x2009C07C;
static uint16_t volatile * const PtrFIO3CLRU = (uint16_t *) 0x2009C07E;
#define FIO3CLR  *PtrFIO3CLR
#define FIO3CLR0 *PtrFIO3CLR0
#define FIO3CLR1 *PtrFIO3CLR1
#define FIO3CLR2 *PtrFIO3CLR2
#define FIO3CLR3 *PtrFIO3CLR3
#define FIO3CLRL *PtrFIO3CLRL
#define FIO3CLRU *PtrFIO3CLRU

/* GPIO 4 CLR */
static uint32_t volatile * const PtrFIO4CLR = (uint32_t *) 0x2009C09C;
static uint8_t volatile * const PtrFIO4CLR0 = (uint8_t *) 0x2009C09C;
static uint8_t volatile * const PtrFIO4CLR1 = (uint8_t *) 0x2009C09D;
static uint8_t volatile * const PtrFIO4CLR2 = (uint8_t *) 0x2009C09F;
static uint8_t volatile * const PtrFIO4CLR3 = (uint8_t *) 0x2009C09B;
static uint16_t volatile * const PtrFIO4CLRL = (uint16_t *) 0x2009C09C;
static uint16_t volatile * const PtrFIO4CLRU = (uint16_t *) 0x2009C09E;
#define FIO4CLR *PtrFIO4CLR
#define FIO4CLR0 *PtrFIO4CLR0
#define FIO4CLR1 *PtrFIO4CLR1
#define FIO4CLR2 *PtrFIO4CLR2
#define FIO4CLR3 *PtrFIO4CLR3
#define FIO4CLRL *PtrFIO4CLRL
#define FIO4CLRU *PtrFIO4CLRU
/****************** FIOCLR END*********************************************/



/* GPIO Interrupt */
static uint32_t volatile * const PtrIOInt_Status = (uint32_t *) 0x40028080;
#define IOIntStatus *PtrIOInt_Status

/* Port 0 */
static uint32_t volatile * const PtrIO0IntEnR = (uint32_t *) 0x40028090;
static uint32_t volatile * const PtrIO0IntEnF = (uint32_t *) 0x40028094;
static uint32_t volatile * const PtrIO0IntStatR = (uint32_t *) 0x40028084;
static uint32_t volatile * const PtrIO0IntStatF = (uint32_t *) 0x40028088;
static uint32_t volatile * const PtrIO0IntClr = (uint32_t *) 0x4002808C;
#define IO0IntEnR *PtrIO0IntEnR
#define IO0IntEnF *PtrIO0IntEnF
#define IO0IntStatR *PtrIO0IntStatR
#define IO0IntStatF *PtrIO0IntStatF
#define IO0IntClr *PtrIO0IntClr

/* Port 2 */
static uint32_t volatile * const PtrIO2IntEnR = (uint32_t *) 0x400280B0;
static uint32_t volatile * const PtrIO2IntEnF = (uint32_t *) 0x400280B4;
static uint32_t volatile * const PtrIO2IntStatR = (uint32_t *) 0x400280A4;
static uint32_t volatile * const PtrIO2IntStatF = (uint32_t *) 0x400280A8;
static uint32_t volatile * const PtrIO2IntClr = (uint32_t *) 0x400280AC;
#define IO2IntEnR *PtrIO2IntEnR
#define IO2IntEnF *PtrIO2IntEnF
#define IO2IntStatR *PtrIO2IntStatR
#define IO2IntStatF *PtrIO2IntStatF
#define IO2IntClr *PtrIO2IntClr


#endif /* GPIO_H_ */
