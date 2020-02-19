/*
 * SPI.h
 *
 *  Created on: 23 nov. 2019
 *      Author: Marc-Antoine
 */

#ifndef SPI_H_
#define SPI_H_


#define SPI_TIMEOUT       10000

typedef enum{
	LCD2004 = 6,//P0.6
	LCDILI9341,	//P0.7
	SDCard,		//P0.8
	LCDILI93410DC //P0.9
}SPI_Target;

/*struct{
	char Red 	: 6;
	char Green 	: 6;
	char Blue	: 6;
}Color;*/

void Init_SPI(void);
void SPI_Send(unsigned char* tx, int L, SPI_Target Dest);
uint8_t SPIReadWrite(uint8_t Data);




static unsigned long volatile * const PtrSPI0_SPCR = (unsigned long *) 0x40020000;
static unsigned long volatile * const PtrSPI0_SPSR = (unsigned long *) 0x40020004;
static unsigned long volatile * const PtrSPI0_SPDR = (unsigned long *) 0x40020008;
static unsigned long volatile * const PtrSPI0_SCPCCR = (unsigned long *) 0x4002000C;
static unsigned long volatile * const PtrSPI0_SPINT = (unsigned long *) 0x4002001C;


#define S0SPCR *PtrSPI0_SPCR
#define S0SPSR *PtrSPI0_SPSR
#define S0SPDR *PtrSPI0_SPDR
#define S0SCPCCR *PtrSPI0_SCPCCR
#define S0SPINT *PtrSPI0_SPINT


#endif /* SPI_H_ */
