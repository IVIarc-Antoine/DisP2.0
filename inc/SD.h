/*
 * SD.h
 *
 *  Created on: 18 févr. 2020
 *      Author: Marc-Antoine
 */

#ifndef SD_H_
#define SD_H_

typedef enum {
	CMD0,
	CMD1,
	CMD2,
	CMD3,
	CMD4,
	CMD5,
	CMD7 = 7,
	CMD8,
	CMD9,
	CMD10,
	CMD11,
	CMD12,
	CMD13,
	CMD15 = 15,
	CMD16,
	CMD17,
	CMD18,
	CMD19,
	CMD20,
	CMD23 = 23,
	CMD24,
	CMD25,
	CMD27 = 27,
	CMD28,
	CMD29,
	CMD30,
	CMD32 = 32,
	CMD33,
	CMD38 = 38,
	CMD40 = 40,
	CMD42 = 42,
	CMD52 = 52,
	CMD53,
	CMD54,
	CMD55,
	CMD56,
	CMD57,
	CMD58,
	CMDOffset = 60,
	ACMD6 = 66,//les ACMD sont décalés de 60 pour pouvoir les différencier des CMD
	ACMD13 = 73,
	ACMD22 = 82,
	ACMD23,
	ACMD41 = 101,
	ACMD42,
	ACMD51 = 111,
}CMD_INDEX;

typedef enum {
	NoError,
	CMD0Error,
	CMD8Mismatch,
	CMD1Error,
	NoResponse,
	ParameterError,
	AddressError,
	EraseSequenceError,
	CommandCRCError,
	IllegalCommand,
	EraseReset,
	InIdleState,
	MultipleErrors
}SDError;

SDError Init_SD(void);
void SD_CSlow(void);
void SD_CShigh(void);
void SD_NCR(void);
void SD_CommandFrame(CMD_INDEX Index,uint32_t Argument,uint8_t CRC);
void SD_WrIndex(CMD_INDEX CMD);
void SD_Write8(uint8_t Data8);
void SD_Write16(uint16_t Data16);
void SD_Write32(uint32_t Data32);
uint8_t SD_Read8(void);
uint16_t SD_Read16(void);
uint32_t SD_Read32(void);
SDError SD_ErrorIdentification(uint8_t Error);
uint8_t SD_WaitFor(CMD_INDEX Index,uint32_t Argument,uint8_t ValAtt, uint32_t Miliseconds);


#endif /* SD_H_ */
