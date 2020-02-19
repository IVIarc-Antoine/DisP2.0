/*
 * SPI.cpp
 *
 *  Created on: 23 nov. 2019
 *      Author: Marc-Antoine
 */


#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "GPIO.h"
#include "interrupt.h"
#include "SPI.h"
#include <stdint.h>




void Init_SPI(void)
{
	SB(8,PCONP);
	I2B(PCLKSEL0,16,1);//96MHz
	S0SPCR = 0x20;//8 bits par transfert, pas d'interrupts, MSB en premier, CPOL = 0, CPHA = 0
	S0SCPCCR = 10;// à partir du clk de 96MHz on divise par 10 pour obtenir 9,6MHz un peu plus bas que 11MHz, pour le FT812 lors de l'init, on change pour 8 apres l'init (12MHz)
	//S0SCPCCR = 0xF0; //à partir d'un clock de 12MHz, qu'on divise par 240(0xF0) on obtiens 50KHz, la freq recommandée par Michel pour le LCD

	/*I2B(PINSEL0,30,F3);//P0.15 SCK
	I2B(PINSEL1,0,F0);//P0.16 Slave Select Master (GPIO)
	I2B(PINSEL1,4,F3);//P0.18 MOSI*/
	/*Pas de MISO sur le LCD*/
	//I2B(PINMODE0,30,0);// pull up sur SCK car on est en mode 3 (CPOL =1 , CPHA = 1) => Défini par le LCD (pas obligatoire mais évite des problèmes)
	/*I2B(PINMODE1,0,0);// pull up sur Slave Select car active low (on ne veut pas activer par accident)
	I2B(PINMODE1,4,2);// MOSI set en float
	SB(16,FIO0DIR);//P0.16 en output (GPIO)*/
}
void SPI_Send(unsigned char* tx, int L, SPI_Target Dest)//tx = string(array) to send, L = nbr de paquet à envoyer, Dest = Destination, voir typedef dans .h
{
	int Timeout = SPI_TIMEOUT;

	CB(Dest,FIO0PIN);//Slave Select
	for(int i = 0;i < L;i++)
	{

		S0SPDR = tx[i];
		while(!(S0SPSR >> 7))//on attends le SPI transfer complete flag
		{
			if(!Timeout--)//si un problème de transmission, on sort
				return;
		}
	}
	SB(Dest,FIO0PIN);//Slave Select
	//while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)

	//LCD_Delay_Flag = 0;
}
uint8_t SPIReadWrite(uint8_t Data)
{
	uint8_t Read = 0;
	S0SPDR = Data;
	while(!TB(7,S0SPSR));
	Read = S0SPDR;

	return Read;
}

