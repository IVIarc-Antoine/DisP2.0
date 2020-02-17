/*
 * LCD.h
 *
 *  Created on: 23 nov. 2019
 *      Author: Marc-Antoine
 */

#ifndef LCD_H_
#define LCD_H_




void LCD_Init(void);
void Init_SSD1306(void);
void Init_SSD1306V2(void);
void Init_LCD1604(void);
void Init_ILI9341(void);
void ILI9341_WrCommand(unsigned char Command);
void ILI9341_WrData(unsigned char Data);
void LCD_Command(unsigned char* Data);
void LCD_Send(char x);
void LCD_WriteByte(unsigned char Octet);
void LCD_Load(unsigned char* data);
void LCD_CurPos(unsigned char pos);
void LCD_WriteStr(const unsigned char* Str);
void LCD_PrintDec(unsigned int NbrDec);
void LCD_Update(void);




#endif /* LCD_H_ */
