/*
 * Timers.cpp
 *
 *  Created on: 6 sept. 2019
 *      Author: Marc-Antoine
 */

#include <stdbool.h>
#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "interrupt.h"
#include "Timers.h"
#include "GPIO.h"

extern bool Delay_Flag;

void Sleep(uint32_t ms)
{
	uint32_t timeOut = STRELOAD;


	for(uint16_t i = 0;i<(ms/174);i++)
	{
		ST_TIMEOUT(174*1000);
		//STCURR = 0;
		SB(0,STCTRL);

		for(unsigned int i = 0;i<(ms/174);i++)
		{
			while(!(TB(16,STCTRL)));
			//STCURR = 0;
		}
		CB(0,STCTRL);
		//STCURR = 0;
		STRELOAD = timeOut;
	}

	ST_TIMEOUT((ms%174)*1000);
	SB(0,STCTRL);
	//STCURR = 0;
	for(unsigned int i = 0;i<(ms%174);i++)
	{
		while(!(TB(16,STCTRL)));
		//STCURR = 0;
	}
	CB(0,STCTRL);
	//STCURR = 0;
	STRELOAD = timeOut;


}
void ST_TIMEOUT(uint32_t tMicroSeconds)
{
	STRELOAD = (96 * tMicroSeconds);
}
void Init_RIT(void)
{




	SetBit(16,PCONP);
	I2B(PCLKSEL1, 26,0);          //24MHz à la sortie du MUX
	RI_TIMER_COMPVAL = 15000;	  //1ms de délais
	RI_TIMER_CTRL = 0x0A;		  //Activer le RIT + RAZ du timer counter



}

void Init_TMR0(void)
{



	SB(1,PCONP);
	I2B(PCLKSEL0,2,0);	//24 MHz
	//I2B(CTCR,0,1);	//Mode compteur, trigger sur rising edge
	//I2B(CTCR,2,0);	//input sur p1.26 (CAP0)

	T0CCR = 0x15;		//on initialise seulement le rising edge du CR0 au début
	//SB(0,T0CCR);	//pour trigger un interrupt en event sur CAP0
	//SB(4,T0CCR);	//pour trigger un interrupt en event sur CAP1
	T0IR = 0x3F;
	T0TCR = 0x1;





}
void Init_ST(void)
{
	STCTRL = 0x5;//check si probleme avec st timer, il était à 0x5 avant (julien l'avait à 0x7)(0x5 = sans interrupt, 0x7 = avec interrupt) => interrupt set dans Init_Interrupts()
	STRELOAD = 96000;//setté à 1ms (174ms c'est le plus long qu'on peut faire, sinon on déborde du registre de 24 bits)
}
