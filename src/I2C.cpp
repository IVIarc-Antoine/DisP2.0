/*
 * I2C.cpp
 *
 *  Created on: 12 déc. 2019
 *      Author: Marc-Antoine
 */

//#include <array>
#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "interrupt.h"
#include "I2C.h"
#include "Timers.h"

using namespace std;

extern int StatutI2C;
bool I2CBegin = 0;
bool FlagACK = 0;

extern struct Interrupt{
	bool STT;
	bool LCD;
	bool RTC;
	bool InitDone;
	bool I2C;
	bool I2CRead;
}Flag;

struct Master{
	unsigned char SlaveOwnAdr;//adresse du slave
	unsigned char* TxBuffer;//pointeur vers le message à envoyer
	int TxLen;//taille du message à envoyer
	unsigned char* RxBuffer;//pointeur vers le message à envoyer
	int RxLen;//taille du message à envoyer
}I2CMaster;

unsigned char TxBuffer[8] = {0x00,0xAF};
unsigned char RxBuffer[8] = {0};

void Init_I2C(void)
{
	SB(19,PCONP);//I2C1 Power On
	I2B(PCLKSEL1,6,1);//CCLK, pour l'instant, on va peut-être changer
	I2C1SCHL = 246;//car 96MHz on va rouler à 390Khz pour etre dans le range de 333-407 KHz pour le ssd1306
	I2C1SCLL = 246;//car 50%
	I2C1CONSET = 0x40;//I2CEnable

}
void I2C_Start(void)
{
	I2CBegin = 1;
	I2C1CONSET = 0x20;//Start flag (STA)
}
void I2C_SendCommand(unsigned char Command)
{
	while(!Flag.STT);
	Flag.STT = 0;
	I2CMaster.SlaveOwnAdr = SSD1306Adr;
	I2C_Start();
	TxBuffer[0] = 0x00;
	TxBuffer[1] = Command;
	I2CMaster.TxLen = 2;
}
void I2C_SendDoubleCommand(unsigned char Command1,unsigned char Command2)
{
	while(!Flag.STT);
	Flag.STT = 0;
	I2CMaster.SlaveOwnAdr = SSD1306Adr;
	I2C_Start();
	TxBuffer[0] = 0x80;
	TxBuffer[1] = Command1;
	TxBuffer[2] = Command2;
	I2CMaster.TxLen = 3;

}
void I2C_LCDCommand(unsigned char Command)
{
	while(!Flag.STT);
	Flag.STT = 0;
	I2CMaster.SlaveOwnAdr = LCDAdr;
	I2C_Start();
	TxBuffer[0] = Command;
	I2CMaster.TxLen = 1;

}
unsigned char I2C_ReadData(void)
{
	while(!Flag.STT);
	Flag.STT = 0;
	Flag.I2CRead = 1;
	I2C_Start();
	I2CMaster.RxLen = 1;
	return RxBuffer[0];
	Flag.I2CRead = 0;

}
void I2C_AdrLookup(void)
{
	unsigned char ValidAddress[20] = {0};
	static unsigned char ValidAddressCpt = 0;

	for(int i = 0;i<0x7E;i++)
	{
		while(!Flag.STT);
		Flag.STT = 0;
		I2CMaster.SlaveOwnAdr = i;
		I2C_Start();
		TxBuffer[0] = 0xAA;
		I2CMaster.TxLen = 1;

		if(FlagACK)
		{
			ValidAddress[ValidAddressCpt] = i-1;
			ValidAddressCpt++;
			FlagACK = 0;
		}
	}

}
void I2C_SendData(unsigned char* Data, uint8_t SlaveAdr)
{
	uint8_t LastI2CSTAT = 0;

	I2CMaster.SlaveOwnAdr = SlaveAdr;//slave adr + wirte va s'envoyer dans i2c_stat_handler()
	I2CMaster.TxLen = (sizeof(Data));
	I2C_Start();

	uint32_t timeOut = STRELOAD;

	ST_TIMEOUT(20000);
	SB(0,STCTRL);

	while(!TB(4,I2C1CONSET) || (!TB(16,STCTRL)))//Test pour voir si le STOP flag à été envoyé ou si le délais est terminé
	{
		if(I2C1STAT != LastI2CSTAT)
		{
			LastI2CSTAT = I2C1STAT;
			I2C_Stat_Handler(I2C1STAT);
		}
	}
	CB(0,STCTRL);
	STCURR = 0;
	STRELOAD = timeOut;

}
void I2C_Stat_Handler(int I2CSTAT)
{
	static int TxCpt = 0;
	static int RxCpt = 0;

	switch(I2CSTAT)
	{
	case 0x00://Bus error
		I2C1CONSET = 0x14;//set STO + AA
		I2C1CONCLRL = 0x8;// clear SI
		break;
	case 0x08://START has been transmitted
		I2C1CONCLRL = 0x20;// clear STA
	case 0x10://A repeated START has been transmitted
		if(Flag.I2CRead)
			I2C1DAT = (I2CMaster.SlaveOwnAdr << 1) + 1; //slave adr + read
		else
			I2C1DAT = I2CMaster.SlaveOwnAdr << 1; //slave adr + write
		//I2C1CONSET = 0x04;// Set AA
		I2C1CONCLRL = 0x08;// clear SI
		//I2C1CONCLRL = 0x10;// clear STO
		//Set up Master Transmit mode data buffer. (tableau tx buffer)
		TxCpt = 0;
		break;
	case 0x18://Previous state was 0x08 or 0x10, slave + Write has been transmitted,
			  //ACK has been received, the first data byte will be transmitted
		FlagACK = 1;
		I2C1DAT = TxBuffer[TxCpt]; //control byte for single command 0x00;
		I2C1CONSET = 0x04;// Set AA
		I2C1CONCLRL = 0x08;// clear SI
		//I2C1CONCLRL = 0x10;// clear STO
		I2C1CONCLRL = 0x20;// clear STA
		TxCpt++;
		break;
	case 0x20://slave + Write has been transmitted, NACK has been received,
		      //a STOP condition will be transmitted
		I2C1CONSET = 0x14;//Set STO + AA;
		I2C1CONCLRL = 0x08;// clear SI
		I2C1CONCLRL = 0x20;// clear STA
		break;
	case 0x28://Data has been transmitted, ACK has been received. If the transmitted data was the last
		      //data byte then transmit a STOP condition, otherwise transmit the next data byte.
		if(TxCpt < I2CMaster.TxLen)
		{
			I2C1DAT = TxBuffer[TxCpt];//0xAF set display on
			I2C1CONSET = 0x04;// Set AA
			I2C1CONCLRL = 0x08;// clear SI
			//I2C1CONCLRL = 0x10;// clear STO
			I2C1CONCLRL = 0x20;// clear STA

			TxCpt++;
			break;
		}
		else
		{
			I2C1CONSET = 0x14;// set STO + AA
			I2C1CONCLRL = 0x20;// clear STA
			I2C1CONCLRL = 0x08;// clear SI
			break;
		}
	case 0x30://Data has been transmitted, NOT ACK received. A STOP condition will be transmitted.
		I2C1CONSET = 0x14;//Set STO + AA
		I2C1CONCLRL = 0x08;// clear SI
		I2C1CONCLRL = 0x20;// clear STA
		break;
	case 0x38://Arbitration has been lost during Slave Address + Write or data. The bus has been
			  //released and not addressed Slave mode is entered. A new START condition will be
			  //transmitted when the bus is free again.
		I2C1CONSET = 0x24;//Set STA + AA
		I2C1CONCLRL = 0x08;// clear SI
		//I2C1CONCLRL = 0x10;// clear STO
		break;
	case 0x40://Previous state was State 08 or State 10. Slave Address + Read has been transmitted,
			  //ACK has been received. Data will be received and ACK returned.
		I2C1CONSET = 0x04;// Set AA
		I2C1CONCLRL = 0x08;// clear SI
		//I2C1CONCLRL = 0x10;// clear STO
		I2C1CONCLRL = 0x20;// clear STA
		break;

	case 0x48://Slave Address + Read has been transmitted, NOT ACK has been received. A STOP
			  //condition will be transmitted.
		I2C1CONSET = 0x14;//Set STO + AA
		I2C1CONCLRL = 0x08;// clear SI
		I2C1CONCLRL = 0x20;// clear STA
		break;
	case 0x50://Data has been received, ACK has been returned. Data will be read from I2DAT. Additional
			  //data will be received. If this is the last data byte then NOT ACK will be returned, otherwise
			  //ACK will be returned.
		RxBuffer[RxCpt] = I2C1DAT;
		if(RxCpt < I2CMaster.RxLen)
		{
			I2C1CONSET = 0x04;// Set AA
			I2C1CONCLRL = 0x08;// clear SI
			//I2C1CONCLRL = 0x10;// clear STO
			I2C1CONCLRL = 0x20;// clear STA
			RxCpt++;
			break;
		}
		else
		{
			I2C1CONCLRL = 0x0C;//clear SI + AA
			//I2C1CONCLRL = 0x10;// clear STO
			I2C1CONCLRL = 0x20;// clear STA
			break;
		}
	case 0x58://Data has been received, NOT ACK has been returned. Data will be read from I2DAT. A
			  //STOP condition will be transmitted.
		RxBuffer[RxCpt] = I2C1DAT;
		I2C1CONSET = 0x14;//Set STO + AA
		I2C1CONCLRL = 0x08;// clear SI
		I2C1CONCLRL = 0x20;// clear STA
		break;


	}








}

