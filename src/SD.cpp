/*
 * SD.cpp
 *
 *  Created on: 18 févr. 2020
 *      Author: Marc-Antoine
 */
#include "Macro.h"
#include <stdbool.h>
#include <stdint.h>
#include "SPI.h"
#include "GPIO.h"
#include "Timers.h"
#include "SD.h"



SDError Init_SD(void)
{
	uint8_t R1 = 0;
	uint32_t R3 = 0;
	uint32_t R7 = 0;
	//uint32_t Buffer = 0;
	uint8_t Resultat = 0;
	SDError Erreur;


	Sleep(1);

	SD_CShigh();

	SD_Write32(0xFFFFFFFF);
	SD_Write32(0xFFFFFFFF);
	SD_Write16(0xFFFF);//donnes plus de 74 coup de clock avec MOSI high

	SD_CSlow();

	SD_CommandFrame(CMD0,0x00,0x00);
	SD_NCR();

	R1 = SD_Read8();

	if(R1 != 0x01)//si la carte SD n'est pas en Idle State
	{
		SD_CShigh();
		Erreur = SD_ErrorIdentification(R1);
		return Erreur;
	}

	SD_CommandFrame(CMD8,0x1AA,0xE3);
	SD_NCR();

	R1 = SD_Read8();
	R7 = SD_Read32();

	if(R1 == 0x05)//Si la carte SD nous retourne IllegalCommand + IdleState, on passe à une autre étape
	{
		Resultat = SD_WaitFor(ACMD41,0x00,0x00,1000);
		if(Resultat)//Si on a bien eu 0x00
		{
			SD_CommandFrame(CMD16,0x200,0x00);
			SD_CShigh();
			return NoError;//on a une carte SD Ver.1
		}
		else
		{
			Resultat = SD_WaitFor(CMD1,0x00,0x00,1000);
			if(Resultat)//Si on a bien eu 0x00
			{
				SD_CommandFrame(CMD16,0x200,0x00);
				SD_CShigh();
				return NoError;//on a une carte SD MMC Ver.3
			}
			else
			{
				SD_CShigh();
				return CMD1Error;
			}
		}
	}
	if(R1)// si il y a un code d'erreur autre que IllegalCommand ou pas de réponse, on retourne le code d'erreur
	{
		SD_CShigh();
		Erreur = SD_ErrorIdentification(R1);
		return Erreur;
	}

	//Si R1 est 0x00 on continue

	if((R7 & 0x1FFF) != 0x1AA)//est-ce que les lower 12 bits de R7 != l'argument de CMD8 (Donc mismatch)
	{
		SD_CShigh();
		return CMD8Mismatch;
	}

	Resultat = SD_WaitFor(ACMD41,0x40000000,0x00,1000);
	if(Resultat)//Si on a bien eu 0x00
	{
		SD_CommandFrame(CMD58,0x00,0x00);
		R1 = SD_Read8();
		R3 = SD_Read32();

		if(((R3 >>30) & 0x1))
		{
			SD_CShigh();
			return NoError;//on a une carte SD Ver.2 avec des block address
		}

		SD_CommandFrame(CMD16,0x200,0x00);
		SD_CShigh();
		return NoError;//on a une carte SD MMC Ver.3

	}
	else
	{
		SD_CShigh();
		return CMD1Error;
	}



}
void SD_CSlow(void)
{
	CB(8,FIO0PIN);
}
void SD_CShigh(void)
{
	SB(8,FIO0PIN);
}
void SD_NCR(void)
{
	SD_Write8(0xFF);
}
void SD_CommandFrame(CMD_INDEX Index,uint32_t Argument,uint8_t CRC)
{

	if(Index > 60)//On deal avec un ACMD
	{
		SD_WrIndex(CMD55);
		SD_Write32(0x00);
		SD_Write8((uint8_t)((CRC << 1) | 1));
		SD_NCR();

		(uint8_t)Index = (uint8_t)Index - 60;
	}

	SD_WrIndex(Index);
	SD_Write32(Argument);
	SD_Write8((uint8_t)((CRC << 1) | 1));
	SD_NCR();

}
void SD_WrIndex(CMD_INDEX CMD)
{
	uint8_t Index = 0;

	Index = ((CMD & 0x3F) | 0x40);//Pour obtenir 01xxxxxx (x = CMD)

	SD_Write8(Index);
}
void SD_Write8(uint8_t Data8)
{
	uint8_t dummy = 0;

	dummy = SPIReadWrite(Data8);
}
void SD_Write16(uint16_t Data16)
{
	uint16_t dummy = 0;

	dummy = SPIReadWrite((uint8_t)Data16);

	dummy = SPIReadWrite((uint8_t)(Data16>>8));
}
void SD_Write32(uint32_t Data32)
{
	uint32_t dummy = 0;

	dummy = SPIReadWrite((uint8_t)Data32);

	dummy = SPIReadWrite((uint8_t)(Data32 >> 8));

	dummy = SPIReadWrite((uint8_t)(Data32 >> 16));

	dummy = SPIReadWrite((uint8_t)(Data32 >> 24));
}
uint8_t SD_Read8(void)
{
	uint8_t Read = 0x00;

	Read = SPIReadWrite(0x00);

	return Read;
}
uint16_t SD_Read16(void)
{
	uint16_t Read = 0;
	uint16_t Buffer = 0;

	Buffer = SPIReadWrite(0x00);
	Read = Read | Buffer;

	Buffer = SPIReadWrite(0x00);
	Buffer = Buffer << 8;
	Read = Read |Buffer;

	return Read;
}
uint32_t SD_Read32(void)
{
	uint32_t Read = 0;
	uint32_t Buffer = 0;

	Buffer = SPIReadWrite(0x00);
	Read = Read | Buffer;

	Buffer = SPIReadWrite(0x00);
	Buffer = Buffer << 8;
	Read = Read | Buffer;

	Buffer = SPIReadWrite(0x00);
	Buffer = Buffer << 16;
	Read = Read | Buffer;

	Buffer = SPIReadWrite(0x00);
	Buffer = Buffer << 24;
	Read = Read | Buffer;

	return Read;
}
SDError SD_ErrorIdentification(uint8_t Error)
{
	switch(Error)
	{
		case 0x00:
			return NoError;
		case 0x01:
			return InIdleState;
		case 0x02:
			return EraseReset;
		case 0x04:
			return IllegalCommand;
		case 0x08:
			return CommandCRCError;
		case 0x10:
			return EraseSequenceError;
		case 0x20:
			return AddressError;
		case 0x40:
			return ParameterError;
		default:
			return MultipleErrors;
	}

}
uint8_t SD_WaitFor(CMD_INDEX Index,uint32_t Argument,uint8_t ValAtt, uint32_t Miliseconds)
{
	uint8_t R1 = 0;
	uint16_t LoopNbr = 0;
	uint8_t Resultat = 0;

	if(Miliseconds > 100)
	{
		LoopNbr = Miliseconds/100;
		ST_TIMEOUT(1000);
		SB(0,STCTRL);
		for(uint16_t i = 0;i < LoopNbr; i++)//loop le nombre de fois nécessaire pour atteindre le multiplicateur de l'attente
		{
			while(!TB(16,STCTRL))
			{
				SD_CommandFrame(Index,Argument,0x00);
				SD_NCR();
				R1 = SD_Read8();
				if(R1 == ValAtt)
				{
					Resultat = 1;
					CB(0,STCTRL);
					return Resultat;

				}
			}
		}
	}
	SB(0,STCTRL);
	ST_TIMEOUT(10*Miliseconds);

	while(!TB(16,STCTRL))
	{
		SD_CommandFrame(Index,Argument,0x00);
		SD_NCR();
		R1 = SD_Read8();
		if(R1 == ValAtt)
		{
			Resultat = 1;
			break;
		}
	}
	CB(0,STCTRL);
	return Resultat;

}
