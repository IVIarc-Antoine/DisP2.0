/*
 * LCD.cpp
 *
 *  Created on: 23 nov. 2019
 *      Author: Marc-Antoine
 */

//#include <windows.h>
#include <stdbool.h>
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


/*idée pour les délais*/

/* Utiliser le STCTRL >> 16 du ST timer qui est setté à 300ms
 * c'est beaucoup plus long que nécéssaire mais il est déja implémenté
 * de plus des interruptions pourront se produire pendant le délais
 *
 * essayer de desendre le délais du st timer à 100ms
 */

/*implémenter un timer qui n'est pas utilisé pour avoir le 100µs de délais */


/*Utiliser le RIT Timer qui est setté à 2ms*/


unsigned char tx_packet[80] = {0};//max 80 blocs de 8 bits (il faut s'arrêter en quelque part)

unsigned char Turn_On_Display[3] = {0xFE,0x41};
unsigned char Turn_Off_Display[3] = {0xFE,0x42};
unsigned char HomeCursor[3] = {0xFE,0x46};
unsigned char Underline_On[3] = {0xFE,0x47};
unsigned char Underline_Off[3] = {0xFE,0x48};
unsigned char Cursor_Left[3] = {0xFE,0x49};
unsigned char Cursor_Right[3] = {0xFE,0x4A};
unsigned char Blinking_On[3] = {0xFE,0x4B};
unsigned char Blinking_Off[3] = {0xFE,0x4C};
unsigned char BackSpace[3] = {0xFE,0x4E};
unsigned char ClearScreen[3] = {0xFE,0x51};
unsigned char Shift_Left[3] = {0xFE,0x55};
unsigned char Shift_Right[3] = {0xFE,0x56};

char LCD_Delay_Flag;

extern float DutyOutput;

extern struct Disp{
	char Moteur;
	char TempSen;
	char IRcap;
	char GazInj;
	char Conv;
}Affiche;

extern struct General{
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
extern struct Interrupt{
	bool STT;
	bool LCD;
	bool RTC;
	bool InitDone;
}Flag;

void LCD_Init(void)
{
	/*LCD_Load(ClearScreen);
	LCD_Send(sizeof(ClearScreen));

	LCD_Load(HomeCursor);
	LCD_Send(sizeof(HomeCursor));*/

	//while(!(STCTRL >> 16));//délais de 300ms avant de faire l'init

	LCD_Command(ClearScreen);

	LCD_CurPos(0x0);
	LCD_WriteStr((unsigned char*)"Veuillez entrer le  ");
	LCD_CurPos(0x40);
	LCD_WriteStr((unsigned char*)"nombre d'items sur  ");
	LCD_CurPos(0x14);
	LCD_WriteStr((unsigned char*)"les lignes puis     ");
	LCD_CurPos(0x54);
	LCD_WriteStr((unsigned char*)"appuyez sur <ENTER> ");

	//while(!(STCTRL >> 16));

	//LCD_Command(HomeCursor);
	/*LCD_CurPos(0x0);
	LCD_WriteStr((unsigned char*)"M :    RPM");*/

	/*LCD_CurPos(0xC);
	LCD_WriteStr((unsigned char*)"Duty:");*/

	/*LCD_CurPos(0x40);
	LCD_WriteStr((unsigned char*)"T :  .  C");*/

	/*LCD_CurPos(0x4C);
	LCD_WriteStr((unsigned char*)"Heure:");*/

	/*LCD_CurPos(0x14);
	LCD_WriteStr((unsigned char*)"F :    Hz");*/

	/*LCD_CurPos(0x1E);
	LCD_WriteStr((unsigned char*)"[  :  :  ]");*/

	/*LCD_CurPos(0x54);
	LCD_WriteStr((unsigned char*)"C :   /");*/

	/*LCD_CurPos(0x5F);
	LCD_WriteStr((unsigned char*)"Gaz");*/

}
void Init_SSD1306(void)
{
	/*Fundamental Commands*/
	I2C_SendCommand(0xAE);//Screen off
	I2C_SendDoubleCommand(0x81,0x7F);//set contrast control + contrast level
	I2C_SendCommand(0xA6);//Set normal display
	/*Scrolling Commands*/
	I2C_SendCommand(0x2F);//Deactivate scrolling
	/*Addressing Commands*/
	I2C_SendCommand(0x22);//Set memory mode to page(0x20+0x02)
	/*Hardware Configuration Commands*/
	I2C_SendCommand(0xA1);//Set segment re-map
	I2C_SendDoubleCommand(0xA8,0x3F);//Set multiplex ratio + Vertical Size - 1
	I2C_SendCommand(0xC0);//Set COM output scan direction
	I2C_SendDoubleCommand(0xD3,0x00);//Set Display Offset
	I2C_SendDoubleCommand(0xDA,0x12);//Set COM pins hardware configuration + Alternate com config & disable com left/right
	/*Timing and Driving Settings*/
	I2C_SendDoubleCommand(0xD5,0x80);//Set display oscillator frequency + Default value
	I2C_SendDoubleCommand(0xD9,0x22);//Set pre-changed period + Default value
	I2C_SendDoubleCommand(0xDB,0x20);//Set VCOMH Deselected level + Default value
	/*Charge pump regulator*/
	I2C_SendCommand(0x8D);//Set charge pump
	I2C_SendCommand(0x14);//VCC generated by internal DC/DC circuit
	/*Turn the screen back on...*/
	I2C_SendCommand(0xA4);//Set entire display on
	I2C_SendCommand(0xAF);//Set display on
}
void Init_SSD1306V2(void)
{
	I2C_SendDoubleCommand(0xA8,0x3F);//Set MUX Ratio
	I2C_SendDoubleCommand(0xD3,0x00);//Set Display Offset
	I2C_SendCommand(0x40);//Set Display Start Line
	I2C_SendCommand(0xA0);//Set Segment re-map (0 is mapped to SEG0)
	I2C_SendCommand(0xC0);//Set COM Output Scan Direction (normal mode)
	I2C_SendDoubleCommand(0xDA,0x02);//Set COM Pins hardware configuration (sequential COM pin config + Disable COM Left/Right remap)
	I2C_SendDoubleCommand(0x81,0x7F);//Set Contrast Control
	I2C_SendCommand(0xA4);//Disable Entire Display On
	I2C_SendCommand(0xA6);//Set Normal Display
	I2C_SendDoubleCommand(0xD5,0x80);//Set Osc Frequency (reset value (8/1))
	I2C_SendDoubleCommand(0x8D,0x14);//Enable charge pump regulator
	I2C_SendCommand(0xAF);//Display On


}
void SSD1306_WrData(unsigned char Data)
{

}
void Init_LCD1604(void)
{
	unsigned char InstrSet[12] = {0x30,0x30,0x30,0x20,0x20,0x00,0x00,0x80,0x00,0x10,0x00,0x20};



	for(int i = 0;i<12;i++)
	{

		if((i == 6) || (i == 8) || (i == 10) || (i == 12))
			I2C_LCDCommand(InstrSet[i]);
		else
		{
			while(!Flag.STT);//on skip le busy flag check en le remplacant par un délais
			Flag.STT = 0;
			I2C_LCDCommand(InstrSet[i]);
		}

	}
}
void Init_ILI9341(void)
{
	ILI9341_WrCommand(0xEF);               // ??? NOT FOUND IN DATASHEET ???
	ILI9341_WrData(0x03);
	ILI9341_WrData(0x80);
	ILI9341_WrData(0x02);

	ILI9341_WrCommand(0xCF);               // Power control B (CFh) page 196
	ILI9341_WrData(0x00);
	ILI9341_WrData(0XC1);
	ILI9341_WrData(0X30);

	ILI9341_WrCommand(0xED);               // Power on sequence control (EDh) page 200
	ILI9341_WrData(0x64);
	ILI9341_WrData(0x03);
	ILI9341_WrData(0X12);
	ILI9341_WrData(0X81);

	ILI9341_WrCommand(0xE8);              // Driver timing control A (E8h) page 197
	ILI9341_WrData(0x85);
	ILI9341_WrData(0x00);
	ILI9341_WrData(0x78);

	ILI9341_WrCommand(0xCB);               // Power control A (CBh) page 195
	ILI9341_WrData(0x39);
	ILI9341_WrData(0x2C);
	ILI9341_WrData(0x00);
	ILI9341_WrData(0x34);
	ILI9341_WrData(0x02);

	ILI9341_WrCommand(0xF7);              // Pump ratio control (F7h) page 202
	ILI9341_WrData(0x20);

	ILI9341_WrCommand(0xEA);              // Driver timing control B (EAh) page 199
	ILI9341_WrData(0x00);
	ILI9341_WrData(0x00);

	ILI9341_WrCommand(0xC0);       // Power Control 1 (C0h) page 178
	ILI9341_WrData(0x23);

	ILI9341_WrCommand(0xC1);       // Power Control 2 (C1h) page 179
	ILI9341_WrData(0x10);

	ILI9341_WrCommand(0xC5);       // VCOM Control 1 (C5h) page 180
	ILI9341_WrData(0x3e);
	ILI9341_WrData(0x28);

	ILI9341_WrCommand(0xC7);       // VCOM control 2 (C7h) page 182
	ILI9341_WrData(0x86);

	ILI9341_WrCommand(0x0B);       // Read Display MADCTL (0Bh) page 95
	ILI9341_WrData(0x48);

	ILI9341_WrCommand(0x3A);       // COLMOD: Pixel Format Set (3Ah) page 134
	ILI9341_WrData(0x55);

	ILI9341_WrCommand(0xB1);       // Frame Rate Control (In Normal Mode/Full Colors) (B1h) page 155
	ILI9341_WrData(0x00);
	ILI9341_WrData(0x18);

	ILI9341_WrCommand(0xB6);       // Display Function Control (B6h page 164
	ILI9341_WrData(0x08);
	ILI9341_WrData(0x82);
	ILI9341_WrData(0x27);

	ILI9341_WrCommand(0xF2);               // Enable 3Gamma (F2h) page 201
	ILI9341_WrData(0x00);

	ILI9341_WrCommand(0x26);      // Gamma Set (26h) page 107
	ILI9341_WrData(0x01);

	ILI9341_WrCommand(0xE0);      // Positive Gamma Correction (E0h) page 188
	ILI9341_WrData(0x0F);
	ILI9341_WrData(0x31);
	ILI9341_WrData(0x2B);
	ILI9341_WrData(0x0C);
	ILI9341_WrData(0x0E);
	ILI9341_WrData(0x08);
	ILI9341_WrData(0x4E);
	ILI9341_WrData(0xF1);
	ILI9341_WrData(0x37);
	ILI9341_WrData(0x07);
	ILI9341_WrData(0x10);
	ILI9341_WrData(0x03);
	ILI9341_WrData(0x0E);
	ILI9341_WrData(0x09);
	ILI9341_WrData(0x00);

	ILI9341_WrCommand(0xE1);      // Negative Gamma Correction (E1h) page 189
	ILI9341_WrData(0x00);
	ILI9341_WrData(0x0E);
	ILI9341_WrData(0x14);
	ILI9341_WrData(0x03);
	ILI9341_WrData(0x11);
	ILI9341_WrData(0x07);
	ILI9341_WrData(0x31);
	ILI9341_WrData(0xC1);
	ILI9341_WrData(0x48);
	ILI9341_WrData(0x08);
	ILI9341_WrData(0x0F);
	ILI9341_WrData(0x0C);
	ILI9341_WrData(0x31);
	ILI9341_WrData(0x36);
	ILI9341_WrData(0x0F);
}
void ILI9341_WrCommand(unsigned char Command)
{
	int Timeout = SPI_TIMEOUT;

	CB(LCDILI9341,FIO0PIN);//Slave Select
	CB(LCDILI93410DC,FIO0PIN);//Data/Command : set at Command

	S0SPDR = Command;

	while(!(S0SPSR >> 7))//on attends le SPI transfer complete flag
	{
		if(!Timeout--)//si un problème de transmission, on sort
			return;
	}

	SB(LCDILI9341,FIO0PIN);//Slave Select


}
void ILI9341_WrData(unsigned char Data)
{
	int Timeout = SPI_TIMEOUT;

	CB(LCDILI9341,FIO0PIN);//Slave Select
	SB(LCDILI93410DC,FIO0PIN);//Data/Command : set at Data

	S0SPDR = Data;

	while(!(S0SPSR >> 7))//on attends le SPI transfer complete flag
	{
		if(!Timeout--)//si un problème de transmission, on sort
			return;
	}

	SB(LCDILI9341,FIO0PIN);//Slave Select

}
void LCD_Command(unsigned char* Data)
{
	for(int i = 0;*Data != '\0';Data++)
	{
		tx_packet[i] = *Data;
		i++;
	}

	CB(LCD2004,FIO0PIN);//Slave Select

	for(int i = 0;tx_packet[i];i++)//tant qu'on a pas de \0 dans tx_packet[i]
	{
		S0SPDR = tx_packet[i];
		while(!(S0SPSR >> 7));//on attends le SPI transfer complete flag
	}
	SB(LCD2004,FIO0PIN);//Slave Select
	while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)
	//while(!(STCTRL >> 16));
	LCD_Delay_Flag = 0;

}
void LCD_Send(char x)// x = nbr de paquet à envoyer
{
	CB(LCD2004,FIO0PIN);//Slave Select
	for(int i = 0;i < x;i++)
	{
		S0SPDR = tx_packet[i];
		while(!(S0SPSR >> 7));//on attends le SPI transfer complete flag
	}
	SB(LCD2004,FIO0PIN);//Slave Select
	while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)

	LCD_Delay_Flag = 0;
}
void LCD_Load(unsigned char* data)
{
	for(int i = 0;*data != '\0';data++)
	{
		tx_packet[i] = *data;
		i++;
	}

}
void LCD_WriteByte(unsigned char Octet)
{
	CB(LCD2004,FIO0PIN);//Slave Select
	S0SPDR = Octet;
	while(!(S0SPSR >> 7));//on attends le SPI transfer complete flag
	SB(LCD2004,FIO0PIN);//Slave Select
	while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)

	LCD_Delay_Flag = 0;
}
void LCD_WriteStr(const unsigned char* Str)
{
	while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)
	LCD_Delay_Flag = 0;
	CB(LCD2004,FIO0PIN);//Slave Select
	for(;*Str != '\0';Str++)
	{
		S0SPDR = *Str;
		while(!(S0SPSR >> 7));//on attends le SPI transfer complete flag
		while(!LCD_Delay_Flag);//on attends un cycle de RIT Timer (2ms)
		LCD_Delay_Flag = 0;
	}
	SB(LCD2004,FIO0PIN);//Slave Select

}
void LCD_CurPos(unsigned char pos)
{
	unsigned char Position[3] = {0xFE,0x45,0};

	Position[2] = pos;

	memcpy(tx_packet,Position,3);

	/*for(int i = 0;i<3;i++)
	{
		tx_packet[i] = Position[i];
	}*/

	LCD_Send(3);
}
void LCD_PrintDec(unsigned int NbrDec)// à vérifier, peut-être problème ici
{
	if(NbrDec > 9999)
	{
		LCD_WriteByte(((NbrDec/10000)%10) + 48);
		//Exit10k = 1;
	}
	if(NbrDec > 999)
	{
		LCD_WriteByte(((NbrDec/1000)%10) + 48);
		//Exit1k = 1;
	}
	if(NbrDec > 99)
	{
		LCD_WriteByte(((NbrDec/100)%10) + 48);
		//ExitC = 1;
	}
	if(NbrDec > 9)
	{
		LCD_WriteByte(((NbrDec/10)%10) + 48);
		//ExitD = 1;
	}

	LCD_WriteByte((NbrDec % 10) + 48);

}
void LCD_Update(void)
{

	LCD_CurPos(0x00);
	if(Affiche.Moteur)//moteur 2
	{
		LCD_WriteStr((unsigned char*)"M2:");
	}
	else//moteur 1
	{
		LCD_WriteStr((unsigned char*)"M1:");
	}

	LCD_CurPos(0x03);
	LCD_PrintDec(Data.Moteur.RPM);

	if(Data.Moteur.RPM < 1000)
		LCD_WriteByte(' ');
	if(Data.Moteur.RPM < 100)
			LCD_WriteByte(' ');
	if(Data.Moteur.RPM < 10)
			LCD_WriteByte(' ');

	LCD_WriteStr((unsigned char*)"RPM  Duty:");

	//LCD_CurPos(0x11);
	LCD_PrintDec(Data.Moteur.Duty/100);

	if(Data.Moteur.Duty < 1000)//Duty < 10%
		LCD_WriteByte(' ');
	if(Data.Moteur.Duty < 100)
			LCD_WriteByte(' ');

	LCD_WriteByte('%');


	/*Affichage de la fréquence*/

	LCD_CurPos(0x14);
	if(Affiche.Moteur)//moteur 2
	{
		LCD_WriteStr((unsigned char*)"F2:");
	}
	else//moteur 1
	{
		LCD_WriteStr((unsigned char*)"F1:");
	}



	if(Data.Moteur.Freq < 1000)
		LCD_WriteByte(' ');
	if(Data.Moteur.Freq < 100)
		LCD_WriteByte(' ');
	if(Data.Moteur.Freq < 10)
		LCD_WriteByte(' ');

	LCD_PrintDec(Data.Moteur.Freq);

	//LCD_CurPos(0x1B);
	LCD_WriteStr((unsigned char*)"Hz ");



	LCD_CurPos(0x54);
	if(Affiche.Conv)//conv 2
	{
		LCD_WriteStr((unsigned char*)"C2:");
		if(Data.Convoyeur.Compte2 < 1000)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.Compte2 < 100)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.Compte2 < 10)
			LCD_WriteByte(' ');
		LCD_PrintDec(Data.Convoyeur.Compte2);
		LCD_WriteByte('/');//pour mettre un backslash, il faut mettre '//'
		LCD_PrintDec(Data.Convoyeur.itemL2);
		if(Data.Convoyeur.itemL2 < 1000)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.itemL2 < 100)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.itemL2 < 10)
			LCD_WriteByte(' ');
	}
	else//conv 1
	{
		LCD_WriteStr((unsigned char*)"C1:");
		if(Data.Convoyeur.Compte1 < 1000)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.Compte1 < 100)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.Compte1 < 10)
			LCD_WriteByte(' ');
		LCD_PrintDec(Data.Convoyeur.Compte1);
		LCD_WriteByte('/');//pour mettre un backslash, il faut mettre '//'
		LCD_PrintDec(Data.Convoyeur.itemL1);
		if(Data.Convoyeur.itemL1 < 1000)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.itemL1 < 100)
			LCD_WriteByte(' ');
		if(Data.Convoyeur.itemL1 < 10)
			LCD_WriteByte(' ');
	}
	LCD_WriteByte(' ');



	if(Flag.RTC)
	{
		/*Affichage de la température*/

		LCD_CurPos(0x40);
		if(Affiche.TempSen)//Temperature 2
		{
			LCD_WriteStr((unsigned char*)"T2:");
		}
		else//Temperature 1
		{
			LCD_WriteStr((unsigned char*)"T1:");
		}


		if(Data.Temp.Unit)
		{
			if(Data.Temp.Faren < 1000)//Temp < 10C
				LCD_WriteByte(' ');

			LCD_PrintDec(Data.Temp.Faren/100);
			LCD_WriteByte('.');

			if(Data.Temp.Faren %100 < 10)//si la décimale est en dessous de .10
				LCD_WriteByte('0');
			LCD_PrintDec(Data.Temp.Faren%100);
			LCD_WriteByte(0xDF);//le signe deg (*)
			LCD_WriteStr((unsigned char*)"F ");
		}
		else
		{
			if(Data.Temp.Celcius < 1000)//Temp < 10C
				LCD_WriteByte(' ');

			LCD_PrintDec(Data.Temp.Celcius/100);
			LCD_WriteByte('.');

			if(Data.Temp.Celcius %100 < 10)//si la décimale est en dessous de .10
				LCD_WriteByte('0');
			LCD_PrintDec(Data.Temp.Celcius%100);
			LCD_WriteByte(0xDF);//le signe deg (*)
			LCD_WriteStr((unsigned char*)"C ");
		}



		/*En tête de l,affichage de l'heure*/

		LCD_CurPos(0x4B);
		LCD_WriteStr((unsigned char*)" Heure:");




		/*Affichage de l'heure*/

		LCD_CurPos(0x1E);
		LCD_WriteByte('[');
		if(RTC_HOUR < 10)
			LCD_WriteByte('0');
		LCD_PrintDec(RTC_HOUR);
		LCD_WriteByte(':');
		if(RTC_MIN < 10)
			LCD_WriteByte('0');
		LCD_PrintDec(RTC_MIN);
		LCD_WriteByte(':');
		if(RTC_SEC < 10)
			LCD_WriteByte('0');
		LCD_PrintDec(RTC_SEC);
		LCD_WriteByte(']');


		/*Gaz Injection*/

		LCD_CurPos(0x61);
		if(Affiche.GazInj)//Gaz 2
		{
			LCD_WriteStr((unsigned char*)"G2:");
		}
		else//Gaz 1
		{
			LCD_WriteStr((unsigned char*)"G1:");
		}

		LCD_PrintDec(Data.Gaz.Inj);




		Flag.RTC = 0;
	}

	Flag.LCD = 1;


}


