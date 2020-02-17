/*
 * interrupt.cpp

 *
 *  Created on: 6 sept. 2019
 *      Author: Marc-Antoine
 */
//extern "C"
//{
#include <stdbool.h>
#include <stdio.h>//pour le sprintf()
#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "interrupt.h"
#include "Timers.h"
#include "GPIO.h"
//#include "PWM.h"
//#include "UART.h"
//#include "ConsoleInOut.h"
//#include "InputRedirect.h"
#include "LCD.h"
//#include "ADC_DAC.h"
#include "RTC.h"
#include "I2C.h"

volatile static int i = 0 ;
volatile static int j = 0 ;
volatile static int AffHex = 0 ;
volatile static int AffDec = 0 ;
volatile static int k = 0 ;

char buffer[8];//taille du tableau de 8 parce que 8 afficheurs (pour le sprintf())
//volatile static int Nom[8] = {0X16,0X0A,0X1B,0X0C,0x30,0x30,0x30,0x30};
volatile static int Hex[16] = {0X0,0X1,0X2,0X3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF};
//volatile static int Hex[16] = {0xF,0xE,0xD,0xC,0xB,0xA,0x9,0x8,0x7,0x6,0x5,0x4,0X3,0X2,0X1,0X0};
volatile static unsigned int T0 = 0 ;
volatile static unsigned int T1 = 0 ;
volatile static unsigned int T2 = 0 ;
volatile static unsigned int T = 0 ;
volatile static unsigned int OldT = 1 ;//pour que OldT != T sur la première interruption
volatile static unsigned int Ton = 0 ;
volatile static unsigned int OldTon = 1 ;//pour que OldTon != Ton sur la première interruption
volatile static unsigned int Freq = 0 ;
//volatile static unsigned int RPM = 0 ;
volatile static unsigned int AFreq = 0 ;
volatile static unsigned int Duty = 0 ;
volatile static unsigned int CapNumber = 0 ;
char Touche = 0;
volatile static char Reception = 0;
volatile static unsigned int FlagMoteur = 0;
volatile static unsigned int CapItemFlag = 0;
unsigned char TouchesRecues[4];
int cpt = 0;

unsigned int BitBucket;


extern bool I2CBegin;

struct Interrupt{
	bool STT;
	bool LCD;
	bool RTC;
	bool InitDone;
	bool I2C;
}Flag;

struct Disp{
	char Moteur;
	char TempSen;
	char IRcap;
	char GazInj;
	char Conv;
}Affiche;

struct General{
	struct M{
		unsigned int RPM;
		unsigned int Duty;
		unsigned int Freq;
	}Moteur;
	struct T{
		unsigned int Celcius;
		unsigned int Faren;
		bool Unit;
	}Temp;
	struct G{
		unsigned int Inj;
	}Gaz;
	struct A{
		unsigned char Current;
		bool Decimale;
	}Affichage;
	struct C{
		int Compte1;
		int Compte2;
		int itemL1;
		int itemL2;
	}Convoyeur;
}Data;

int StatutI2C;

char GPIOIntCnt = 0;

char Keypad = 0;

extern char LCD_Delay_Flag;

bool Delay_Flag;



void Init_Interrupts(void)
{
	//SB(29,ISER0);	//Permet l'interruption du RIT
					//SB(29,ICER0); pour désactiver l'interruption(C au lieu de S)

	//SB(1,ISER0);	//pour activer l'interruption du timer 0


	//SB(8,ISER0);	//pour activer l'interrupt du UART3


	//SB(21,ISER0);	//pour les GPIO interrupts(External Interrupts 3 enable)


	//SB(1,STCTRL);	//pour le ST Timer


	//SB(22,ISER0);	//Pour le ADC


	//SB(17,ISER0);	//Pour le RTC


	//SB(11,ISER0);	//Pour le I2C1


}



void RIT_IRQHandler(void)
{

	/*****Le RIT nous donnes 1ms de délais*****/

	SetBit(0,RI_TIMER_CTRL);	//Tue le bit d'interruption

	LCD_Delay_Flag = 1;
	Delay_Flag = 1;

	/* Utiliser le sprintf pour l'affichage
	 *
	 * le sprintf store la donnée dans un tableau (fait à l'avance) au lieu de l'imprimer.
	 *
	 * On peut storer la donnée sous nimporte quel base (ex %d, %x, etc.)donc pas besoin de modulo pour passer de hexa/bin à décimale
	 *
	 * Donc pour décomposer la variable RPM dans un tableau on fait comme ça:
	 *
	 * #include <stdio.h>
	 *
	 * char buffer[8];//taille du tableau de 8 parce que 8 afficheurs
	 *
	 * sprintf(buffer,"RPM %d",RPM);//sprintf retourne le nombre de caractères total mais je ne l'utilise pas ici
	 *
	 * FIO2PINL=(FIO2PINL & 0xF8C0) | (k<<8) | buffer[j];
	 *
	 * if(k == 0)		//à quelle position on affiche la lettre (display 0 à display 7)
	 * 		k = 7;
	 * else
	 *		k--;
	 *
	 * if(j == 7)
	 * 		j = 0;
	 * else
	 * 		j++;
	 *
	 * */

}
/*void UART3_IRQHandler(void)
{

	Reception = ConsoleInOctet();//pour filtrer les caractères entrants
	Touche = Reception;
	//ConsoleOutOctet(Touche);

}*/
void SysTick_Handler(void)
{
	Flag.STT = 1;

}
/*void ADC_IRQHandler(void)
{


	//CB(4,AD0INTEN);
	CB(16,AD0CR);
	//if(Flag.ADCStart = 1)
	//{
		if(Affiche.TempSen == 0)
		{
			Data.Temp.Celcius = 8205-(((AD0DR0>>4) & 0xFFF)*2);//806µV de résolution, formule originale: Temp = 82 - 24.863*V // V = ResADC * 806µV : les 2 formules simplifiés donne : Temp = 82 - (ResADC/50)
																// * 100 pour avoir les décimales : 8200 - ((ResADC * 100)/50) donc 8205(vrai chiffre) - (ResADC*2)
			//Data.Temp.Faren = ((Data.Temp.Faren *9)/5)+3200;//donnes les Farenheit *100 pour les décimales
			BitBucket = AD0DR1;

		}
		else
		{
			Data.Temp.Celcius = 8205-(((AD0DR1>>4) & 0xFFF)*2);
			BitBucket = AD0DR0;
		}

		if(Affiche.GazInj == 0)
		{
			Data.Gaz.Inj = ((((AD0DR2>>4) & 0xFFF)*4)/5);//donne la tension en milivolt, environ
			BitBucket = AD0DR4;
		}
		else
		{
			Data.Gaz.Inj = ((((AD0DR4>>4) & 0xFFF)*4)/5);
			BitBucket = AD0DR2;
		}


		Data.Temp.Faren = ((Data.Temp.Celcius *9)/5)+3200;//donnes les Farenheit *100 pour les décimales

		//Flag.ADCStart = 0;
	//}


}*/
/*void CAN_IRQHandler(void)
{
#if FULL_CAN_AF_USED
	uint16_t i = 0, FullCANEntryNum = 0;
#endif
	uint32_t IntStatus;
	CAN_MSG_T RcvMsgBuf;
	IntStatus = Chip_CAN_GetIntStatus(LPC_CAN);

	PrintCANErrorInfo(IntStatus);
*/
	/* New Message came */
	/*if (IntStatus & CAN_ICR_RI) {
		Chip_CAN_Receive(LPC_CAN, &RcvMsgBuf);
		DEBUGOUT("Message Received!!!\r\n");
		PrintCANMsg(&RcvMsgBuf);

		if (RcvMsgBuf.Type & CAN_REMOTE_MSG) {
			ReplyRemoteMessage(&RcvMsgBuf);
		}
		else {
			ReplyNormalMessage(&RcvMsgBuf);
		}

	}
#if FULL_CAN_AF_USED
	FullCANEntryNum = Chip_CAN_GetEntriesNum(LPC_CANAF, LPC_CANAF_RAM, CANAF_RAM_FULLCAN_SEC);
	if (FullCANEntryNum > 64) {
		FullCANEntryNum = 64;
	}
	for (i = 0; i < FullCANEntryNum; i++)
		if (Chip_CAN_GetFullCANIntStatus(LPC_CANAF, i)) {
			uint8_t SCC;
			Chip_CAN_FullCANReceive(LPC_CANAF, LPC_CANAF_RAM, i, &RcvMsgBuf, &SCC);
			if (SCC == CAN_CTRL_NO) {
				DEBUGOUT("FullCAN Message Received!!!\r\n");
				PrintCANMsg(&RcvMsgBuf);
				if (RcvMsgBuf.Type & CAN_REMOTE_MSG) {
					ReplyRemoteMessage(&RcvMsgBuf);
				}
				else {
					ReplyNormalMessage(&RcvMsgBuf);
				}
			}
		}

#endif /*FULL_CAN_AF_USED*//*
}*/

void RTC_IRQHandler (void)
{
	Flag.RTC = 1;
	//SB(16,AD0CR);//on fait un burst de conversion toutes les secondes
	//Flag.ADCStart = 1;
	SB(1,RTC_ILR);

	//ToggleBit(19,FIO0PIN);//P0.19 (test)
	//ToggleBit(20,FIO0PIN);//P0.20 (test)

	//ToggleBit(27,FIO0PIN);//P0.27 (test)
	//ToggleBit(28,FIO0PIN);//P0.28 (test)

}
void I2C1_IRQHandler(void)
{

	if(I2CBegin)
		I2C_Stat_Handler(I2C1STAT);//fonction à faire
	else
		I2C1CONCLRL = 0x8;// clear SI

}

//}
