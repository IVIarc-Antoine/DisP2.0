/*
 * DisP.cpp
 *
 *  Created on: 21 janv. 2020
 *      Author: Marc-Antoine
 */

//Ébauche de code pour écran newhaven 7"
//L'adresse de base du Graphics Engine est :0x302000
//Les offset vont être à partir de cette adresse là

//les fonctions vont utiliser des defines pour le RegOffset et mettre la valeur à l'adresse offsetée

#include <stdbool.h>
#include <stdint.h>
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
#include "DisP.h"

extern bool Delay_Flag;
unsigned int GPIO_DAT;
unsigned int GPIO_DIR;

unsigned int cmdBufferRd;				// Used to navigate command ring buffer
unsigned int cmdBufferWr = 0x0000;		// Used to navigate command ring buffer
unsigned int cmdOffset = 0x0000;		// Used to navigate command rung buffer //Pour se situer dnas la mémoire, décalage en Octets de RAM_DL (0x300000)

void DisP_Init(void)
{
	unsigned long buffer;

	/*Reset sequence*/

	CB(6,FIO0PIN);//Set PowerDown à LOW
	Sleep(20);
	SB(6,FIO0PIN);//Set Powerdown à HIGH
	Sleep(20);
	/*Ajuster la vitesse du SPI à 11MHz Maximum*/

	host_command(CLKEXT,0);
	host_command(ACTIVE,0);

	Sleep(500);

	/*Vérifier/attendre que le FT812 est prêt*/

	while(rd8(REG_ID) != 0x7C);

	while(rd8(REG_CPURESET) != 0x00);

	/*Chip identification code*/	// pour tester seulement, pas nécessaire pour l'init

	buffer = rd8(0xC0003);
	buffer = rd8(0xC0002);
	buffer = rd8(0xC0001);
	buffer = rd8(0xC0000);

	/*configurer les GPIO et le PWM*/

	memwr8(REG_PWM_DUTY,0);

	GPIO_DAT = rd16(REG_GPIOX);
	memwr16(REG_GPIOX,GPIO_DAT|0x8000);

	GPIO_DIR = rd16(REG_GPIOX_DIR);
	memwr16(REG_GPIOX_DIR,GPIO_DIR|0x8000);

	/* Configure display registers */

	memwr16(REG_HCYCLE,928);
	memwr16(REG_HOFFSET,88);
	memwr16(REG_HSYNC0,0);
	memwr16(REG_HSYNC1,48);
	memwr16(REG_VCYCLE,525);
	memwr16(REG_VOFFSET,32);
	memwr16(REG_VSYNC0,0);
	memwr16(REG_VSYNC1,3);
	memwr8(REG_SWIZZLE,0);
	memwr8(REG_PCLK_POL,1);
	memwr8(REG_CSPREAD,1);
	memwr8(REG_DITHER,1);
	memwr16(REG_HSIZE,800);
	memwr16(REG_VSIZE,480);

	/* write first display list */

	wr(RAM_DL);
	wr32(CLEAR_COLOR_RGB(0,0,0));
	wr32(CLEAR(1,1,1));
	wr32(DISPLAY());
	endwr();

	memwr8(REG_DLSWAP,DLSWAP_FRAME);//display list swap

	memwr8(REG_PCLK,2);//after this display is visible on the LCD

	/*Ramping up backlight*/

	Sleep(20);
	for(int PWM = 0;PWM <= 127;PWM++)
	{
		wr(REG_PWM_DUTY);
		wr8(PWM);
		endwr();
		Sleep(20);
	}

	/*On peut après ca augmenter la vitesse du SPI jusqu'à 30MHz*/
	//S0SCPCCR = 8;//SPI clk 12MHz (vitesse max, si besoin de plus, regarder pour switcher en SSP)

}
void DisP_Example(void)
{
	wr(RAM_DL);
	wr32(CLEAR(1, 1, 1)); // clear screen
	wr32(BEGIN(BITMAPS)); // start drawing bitmaps
	wr32(VERTEX2II(330, 110, 31, 'D')); // ascii F in font 31
	wr32(VERTEX2II(360, 110, 31, 'i')); // ascii T
	wr32(VERTEX2II(390, 110, 31, 's')); // ascii D
	wr32(VERTEX2II(420, 110, 31, 'P')); // ascii I
	wr32(END());
	wr32( COLOR_RGB(251, 20, 10)); // change colour to red
	wr32(POINT_SIZE(2500)); // set point size to 20 pixels in radius
	wr32(BEGIN(POINTS)); // start drawing points
	wr32(VERTEX2II(0, 250, 0, 0)); // red point
	wr32(END());
	wr32(COLOR_RGB(13, 122, 26)); // change colour to red
	wr32(POINT_SIZE(2500)); // set point size to 20 pixels in radius
	wr32(BEGIN(POINTS)); // start drawing points
	wr32(VERTEX2II(511, 250, 0, 0)); // red point
	wr32(END());
	wr32(DISPLAY()); // display the image
	endwr();
	memwr8(REG_DLSWAP,DLSWAP_FRAME);//Super important, mettre à la fin de chaque commande. le FT812 attends cette commande pour faire le render
									//cmd_swap(); pour le co-processeur, c'est la meme chose au final



	/*memwr32(RAM_DL + 0, CLEAR(1, 1, 1)); // clear screen
	memwr32(RAM_DL + 4, BEGIN(BITMAPS)); // start drawing bitmaps
	memwr32(RAM_DL + 8, VERTEX2II(330, 110, 31, 'D')); // ascii F in font 31
	memwr32(RAM_DL + 12, VERTEX2II(360, 110, 31, 'i')); // ascii T
	memwr32(RAM_DL + 16, VERTEX2II(390, 110, 31, 's')); // ascii D
	memwr32(RAM_DL + 20, VERTEX2II(420, 110, 31, 'P')); // ascii I
	memwr32(RAM_DL + 24, END());
	memwr32(RAM_DL + 28, COLOR_RGB(251, 20, 10)); // change colour to red
	memwr32(RAM_DL + 32, POINT_SIZE(2500)); // set point size to 20 pixels in radius
	memwr32(RAM_DL + 36, BEGIN(POINTS)); // start drawing points
	memwr32(RAM_DL + 40, VERTEX2II(0, 250, 0, 0)); // red point
	memwr32(RAM_DL + 44, END());
	memwr32(RAM_DL + 48, COLOR_RGB(13, 122, 26)); // change colour to red
	memwr32(RAM_DL + 52, POINT_SIZE(2500)); // set point size to 20 pixels in radius
	memwr32(RAM_DL + 56, BEGIN(POINTS)); // start drawing points
	memwr32(RAM_DL + 60, VERTEX2II(511, 250, 0, 0)); // red point
	memwr32(RAM_DL + 64, END());
	memwr32(RAM_DL + 68, DISPLAY()); // display the image
	memwr8(REG_DLSWAP,0x02);*/

}
void DisP_Test1(void)
{
	BeginCoProList();
	cmd_dlstart();

	cmd(CLEAR_COLOR_RGB(100, 100, 100));
	cmd(CLEAR(1, 1, 1));
	cmd_button(20,20,60,60,30,NO,"OK!");
	//cmd(END());
	cmd_button(20,120,140,60,30,NO,"DisP");
	//cmd(BEGIN(BITMAPS));
	cmd(COLOR_RGB(255, 255, 255));
	cmd_text(309, 328, 29, NO, "0");
	cmd_text(281, 275, 29, NO, "1");
	cmd_text(283, 219, 29, NO, "2");
	cmd_text(309, 165, 29, NO, "3");
	cmd_text(365, 133, 29, NO, "4");
	cmd_text(424, 135, 29, NO, "5");
	cmd_text(474, 162, 29, NO, "6");
	cmd_text(508, 217, 29, NO, "7");
	cmd_text(506, 275, 29, NO, "8");
	cmd_text(475, 328, 29, NO, "9");
	//cmd(END());
	//cmd(CLEAR(1, 1, 1));
	cmd(COLOR_RGB(255, 0, 0));
	cmd_gauge(400, 258, 198,OPT_NOBACK, 9, 10, 800, 9000);
	//cmd(END());
	cmd(END());

	cmd(DISPLAY());
	cmd_swap();
	EndCoProList();
	AwaitCoProEmpty();

}
void DisP_4Points(void)
{
	dl(CLEAR(1,1,1));
	dl(COLOR_RGB(128,0,0));
	dl(POINT_SIZE(5*16));
	dl(BEGIN(POINTS));
	dl(VERTEX2F(30*16,17*16));
	dl(COLOR_RGB(0,128,0));
	dl(POINT_SIZE(8*16));
	dl(VERTEX2F(90*16,17*16));
	dl(COLOR_RGB(0,0,128));
	dl(POINT_SIZE(10*16));
	dl(VERTEX2F(30*16,51*16));
	dl(COLOR_RGB(128,128,0));
	dl(POINT_SIZE(13*16));
	dl(VERTEX2F(90*16,51*16));
	dl(END());
	dl(DISPLAY()); // display the image
}
void DisP_FlashingDot(void)
{
	unsigned char color = 0;

	while(1)
	{
        if(color == 0x00)                                                       // Toggle colour variable
            color = 0xFF;
        else
            color = 0x00;
	}
}
void DisP_Template1(void)
{
	BeginCoProList();
	cmd_dlstart();

	dl(BITMAP_HANDLE(0));
	cmd_setbitmap(0, ARGB1555, 800, 480);
	dl(CLEAR(1, 1, 1));
	//cmd_loadimage(images_3BlackTachBlackBG,0);
	dl(BEGIN(BITMAPS));
	dl(VERTEX2II(0, 75, 0, 0));
	dl(END());
	dl(BEGIN(BITMAPS));
	dl(VERTEX2II(355, 20, 31, 'D'));
	dl(VERTEX2II(385, 30, 30, 'i'));
	dl(VERTEX2II(395, 30, 30, 's'));
	dl(VERTEX2II(415, 20, 31, 'P'));
	dl(END());
	dl(BEGIN(BITMAPS));
	dl(COLOR_RGB(255, 255, 255));
	cmd_text(309, 328, 29, NO, "0");
	cmd_text(281, 275, 29, NO, "1");
	cmd_text(283, 219, 29, NO, "2");
	cmd_text(309, 165, 29, NO, "3");
	cmd_text(365, 133, 29, NO, "4");
	cmd_text(424, 135, 29, NO, "5");
	cmd_text(474, 162, 29, NO, "6");
	cmd_text(508, 217, 29, NO, "7");
	cmd_text(506, 275, 29, NO, "8");
	cmd_text(475, 328, 29, NO, "9");
	dl(END());
	dl(COLOR_RGB(255, 0, 0));
	cmd_gauge(400, 258, 198, OPT_NOBACKOPT_NOTICKS, 9000, 9000, 800, 9000);
	dl(END());
	dl(COLOR_RGB(255, 0, 0));
	cmd_gauge(637, 204, 80, OPT_NOBACKOPT_NOTICKS, 130, 130, 60, 130);
	dl(END());
	dl(COLOR_RGB(255, 0, 0));
	cmd_gauge(691, 258, 80, OPT_NOBACKOPT_NOTICKS, 130, 130, 120, 130);
	dl(END());
	dl(COLOR_RGB(255, 0, 0));
	cmd_gauge(161, 259, 170, OPT_NOBACKOPT_NOTICKS, 300, 300, 0, 300);
	dl(END());
	dl(DISPLAY());
	cmd_swap();
	//dl(CLEAR(1,1,1));
	EndCoProList();
	AwaitCoProEmpty();
	//memwr8(REG_DLSWAP,DLSWAP_FRAME);//Super important, mettre à la fin de chaque commande. le FT812 attends cette commande pour faire le render
}
void Disp_RPM(uint16_t rpm)
{
	BeginCoProList();
	cmd_dlstart();

	cmd(CLEAR_COLOR_RGB(0, 0, 0));                                               // Specify color to clear screen to
	cmd(CLEAR(1,1,1));                                                           // Clear color, stencil, and tag buffer
	cmd(COLOR_RGB(255,255,255));                                                 // Specify colour of text
	cmd(BITMAP_HANDLE(5));                                                       // Tell FT81x the properties of the bitmap we will display. Handle set to 5
	cmd(BITMAP_SOURCE(0));
	cmd(BITMAP_LAYOUT(L4, 400, 480));                                        // 9 bits faible de 800 (divisé par 2 je sais pas pourquoi), 9 bits faible de 480
	cmd(BITMAP_SIZE(NEAREST, REPEAT, REPEAT, 288, 480));                        //9 bits faible de 800 9 bits faible de 480
	cmd(BITMAP_LAYOUT_H(0, 0));
	cmd(BITMAP_SIZE_H(1, 0));													//bits 10 et 11 de 800, bits 10 et 11 de 480
	cmd(BEGIN(BITMAPS));                                                         // Place the bitmap (handle 5) at (100,100)
	cmd(VERTEX2II(0,75,5,0));
	cmd(END());
	//cmd(CLEAR(1, 1, 1));
	cmd_button(20,20,120,60,30,NO,"RPM");
	cmd(COLOR_RGB(255, 255, 255));
	cmd_text(309, 328, 29, NO, "0");
	cmd_text(281, 275, 29, NO, "1");
	cmd_text(283, 219, 29, NO, "2");
	cmd_text(309, 165, 29, NO, "3");
	cmd_text(365, 133, 29, NO, "4");
	cmd_text(424, 135, 29, NO, "5");
	cmd_text(474, 162, 29, NO, "6");
	cmd_text(508, 217, 29, NO, "7");
	cmd_text(506, 275, 29, NO, "8");
	cmd_text(475, 328, 29, NO, "9");
	cmd(COLOR_RGB(255, 0, 0));
	cmd_gauge(400, 258, 198,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);
	cmd(END());

	cmd(DISPLAY());
	cmd_swap();
	EndCoProList();
	AwaitCoProEmpty();
}
void Disp_RPM2(uint16_t rpm)
{
	BeginCoProList();
	cmd_dlstart();

	cmd(CLEAR_COLOR_RGB(0, 0, 0));                                               // Specify color to clear screen to
	cmd(CLEAR(1,1,1));                                                           // Clear color, stencil, and tag buffer
	cmd(COLOR_RGB(255,255,255));                                                 // Specify colour of text
	cmd(BITMAP_HANDLE(5));                                                       // Tell FT81x the properties of the bitmap we will display. Handle set to 5
	cmd(BITMAP_SOURCE(0));
	cmd(BITMAP_LAYOUT(L4, 400, 480));                                        // 9 bits faible de 800 (divisé par 2 je sais pas pourquoi), 9 bits faible de 480
	cmd(BITMAP_SIZE(NEAREST, REPEAT, REPEAT, 288, 480));                        //9 bits faible de 800 9 bits faible de 480
	cmd(BITMAP_LAYOUT_H(0, 0));
	cmd(BITMAP_SIZE_H(1, 0));													//bits 10 et 11 de 800, bits 10 et 11 de 480
	cmd(BEGIN(BITMAPS));                                                         // Place the bitmap (handle 5) at (100,100)
	cmd(VERTEX2II(0,0,5,0));
	cmd(END());
	//cmd(CLEAR(1, 1, 1));
	//cmd_button(20,20,120,60,30,0,"RPM");
	cmd(COLOR_RGB(255, 255, 255));
	cmd_text(309, 290, 29, NO, "0");
	cmd_text(281, 237, 29, NO, "1");
	cmd_text(283, 181, 29, NO, "2");
	cmd_text(309, 127, 29, NO, "3");
	cmd_text(365, 95, 29, NO, "4");
	cmd_text(424, 97, 29, NO, "5");
	cmd_text(474, 124, 29, NO, "6");
	cmd_text(508, 179, 29, NO, "7");
	cmd_text(506, 237, 29, NO, "8");
	cmd_text(475, 290, 29, NO, "9");
	cmd(COLOR_RGB(255, 0, 0));
	cmd_gauge(400, 220, 200,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);
	cmd(COLOR_RGB(0, 0, 0));
	cmd_number(348,302,31,NO,rpm);
	if(rpm < 2200)
		rpm = 2200;
	if(rpm > 6800)
		rpm = 6800;
	cmd(COLOR_RGB(255, 0, 0));
	cmd_gauge(79, 403, 83,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);
	cmd_gauge(229, 403, 83,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);
	cmd_gauge(571, 403, 83,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);
	cmd_gauge(721, 403, 83,OPT_NOBACKOPT_NOTICKS, 9, 10, rpm, 9000);

	cmd(END());

	cmd(DISPLAY());
	cmd_swap();
	EndCoProList();
	AwaitCoProEmpty();
}
void DisP_Background(void)
{
	BeginCoProList();
	cmd_dlstart();


	//ConvertedBitmap();
	cmd(BITMAP_HANDLE(0));
	cmd_setbitmap(0, L4, 800, 480);
	cmd(CLEAR(1, 1, 1));
	cmd(BEGIN(BITMAPS));
	cmd(VERTEX2II(0, 100, 0, 0));
	cmd(END());

	cmd(DISPLAY());
	cmd_swap();
	EndCoProList();
	AwaitCoProEmpty();
}
void wr(unsigned long Register)
{
	CB(7,FIO0PIN);
	S0SPDR = (0x2 << 6)|(Register >> 16);	//voir DS_FT81x.pdf Page 16     Send high byte of address
	while(!(S0SPSR >> 7));					//on attends le SPI transfer complete flag
	S0SPDR = (Register >> 8) & 0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = Register & 0xFF;				//Send low byte of address
	while(!(S0SPSR >> 7));
}
void endwr(void)
{
	SB(7,FIO0PIN);
}
void rd(unsigned long Register)
{
	CB(7,FIO0PIN);
	S0SPDR = (Register >> 16);			//voir DS_FT81x.pdf Page 15   Send high byte of address
	while(!(S0SPSR >> 7));				//on attends le SPI transfer complete flag
	S0SPDR = (Register >> 8) & 0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = Register & 0xFF;			//Send low byte of address
	while(!(S0SPSR >> 7));
	S0SPDR = 0x00;						//dummy byte
	while(!(S0SPSR >> 7));
	S0SPDR = 0x00;						//dummy byte pour placer le data recu dans S0SPDR
	while(!(S0SPSR >> 7));
}
void wr8(unsigned char Value)
{
	S0SPDR = Value;
	while(!(S0SPSR >> 7));
}
void memwr8(unsigned long Register, unsigned long Value)
{
	wr(Register);
	wr8(Value);
	endwr();
}
unsigned char rd8(unsigned long Register)
{
	rd(Register);
	SB(7,FIO0PIN);
	return S0SPDR;					//retourne le byte recu sur MISO
}
void wr16(unsigned int Value)
{
	S0SPDR = Value & 0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = (Value >> 8)&0xFF;
	while(!(S0SPSR >> 7));
}
void memwr16(unsigned long Register,unsigned long Value)
{
	wr(Register);
	wr16(Value);
	endwr();
}
unsigned int rd16(unsigned long Register)
{
	unsigned int Value;

	rd(Register);
	Value = S0SPDR;						//on recoit le LSB en premier
	S0SPDR = 0x00;						//dummy byte pour placer le data recu dans S0SPDR
	while(!(S0SPSR >> 7));
	SB(7,FIO0PIN);
	return Value | ((S0SPDR<<8) & 0xFF00);			//On recoit le MSB en dernier
}
void wr32(unsigned long Value)
{
	S0SPDR = Value & 0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = (Value >> 8)&0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = (Value >> 16)&0xFF;
	while(!(S0SPSR >> 7));
	S0SPDR = (Value >> 24)&0xFF;
	while(!(S0SPSR >> 7));
}
void memwr32(unsigned long Register, unsigned long Value)
{
	wr(Register);
	wr32(Value);
	endwr();
}
unsigned long rd32(unsigned long Register)
{
	unsigned long Value;

	rd(Register);
	Value = S0SPDR;						//on recoit le LSB en premier
	S0SPDR = 0x00;						//dummy byte pour placer le data recu dans S0SPDR
	while(!(S0SPSR >> 7));
	Value |= (S0SPDR<<8);
	S0SPDR = 0x00;						//dummy byte pour placer le data recu dans S0SPDR
	while(!(S0SPSR >> 7));
	Value |= (S0SPDR<<16);
	S0SPDR = 0x00;						//dummy byte pour placer le data recu dans S0SPDR
	while(!(S0SPSR >> 7));
	SB(7,FIO0PIN);
	return Value | (S0SPDR<<24);		//On recoit le MSB en dernier
}
void cmd(unsigned long Value)		   // pour écrire au co-processeur
{
	wr32(Value);
	cmdOffset = IncCMDOffset(cmdOffset,4);
}
void host_command(unsigned char Command,unsigned char Parameter)
{
	CB(7,FIO0PIN);
	S0SPDR = Command;						//voir DS_FT81x.pdf Page 16
	while(!(S0SPSR >> 7));
	S0SPDR = Parameter;
	while(!(S0SPSR >> 7));
	S0SPDR = 0x00;
	while(!(S0SPSR >> 7));
	endwr();
}
void dl(unsigned long Value)		//Pour les commandes de display list
{
	wr32(Value);
	//cmdOffset = IncCMDOffset(cmdOffset,4);
}
void LoadImagePNG(void)
{
	uint16_t Reg_Cmd_Write_Offset = 0;
	uint16_t ParameterAddr = 0;
	uint32_t End_Address = 0;
	uint32_t Width = 0;
	uint32_t Height = 0;
	uint32_t StartAddress = 0;

    BeginCoProList();                                                   // Begin new co-processor list
    cmd_loadimage(StartAddress,NO);                                          // Load image command. Extract data to RAM_G + 0, options = 0
    EndCoProList();                                                     // Finish the co-processor list
    //WriteDataToCMD(smallback, sizeof(smallback));   // Send data immediately after the command (since we don't select MEDIAFIFO as source in Options))
    AwaitCoProEmpty();                                                  // Await completion of the Load Image. Image will now be in RAM_G

    // ###### Check parameters of decompressed image ########

    BeginCoProList();                                                   // Begin co-pro list
    cmd_getprops(0, 0, 0);                                                  // GetProps command with three dummy 32-bit values
    EndCoProList();                                                     // Finish the co-processor list
    AwaitCoProEmpty();                                                  // Await the command completion

    Reg_Cmd_Write_Offset = rd16(REG_CMD_WRITE);                        // Check current pointer value

    ParameterAddr = ((Reg_Cmd_Write_Offset - 12) & 4095);                       // Go back by 12 bytes to get end address parameter
    End_Address = rd32((RAM_CMD+ParameterAddr));

    ParameterAddr = ((Reg_Cmd_Write_Offset - 8) & 4095);                        // Go back by 8 bytes to get width parameter
    Width = rd32((RAM_CMD+ParameterAddr));

    ParameterAddr = ((Reg_Cmd_Write_Offset - 4) & 4095);                        // Go back by 4 bytes to get height parameter
    Height = rd32((RAM_CMD+ParameterAddr));

    // ######################################################

    BeginCoProList();                                                   // Begin new screen
    cmd_dlstart();                                                          // Tell co-processor to create new Display List
    cmd(CLEAR_COLOR_RGB(0, 0, 0));                                               // Specify color to clear screen to
    cmd(CLEAR(1,1,1));                                                           // Clear color, stencil, and tag buffer
    cmd(COLOR_RGB(255,255,255));                                                 // White colour will display image with original colours

    cmd(BITMAP_HANDLE(0));                                                       // Tell FT81x the properties of the bitmap we will display.
    cmd(BITMAP_SOURCE(StartAddress));
    cmd(BITMAP_LAYOUT(ARGB1555, Width*2, Height));                                 // FMT, STR, H
    cmd(BITMAP_SIZE(BILINEAR, BORDER, BORDER, Width, Height));                   // W, H
    cmd(BITMAP_LAYOUT_H((Width * 2) >> 10, Height >> 9));
    cmd(BITMAP_SIZE_H(Width >> 9, Width >> 9));

    cmd(BEGIN(BITMAPS));
    cmd(VERTEX2II(200,200,0,0));                                                 // Display image at (200,200)
    cmd(END());

    cmd(DISPLAY());                                                              // Tell EVE that this is end of list
    cmd_swap();                                                             // Swap buffers in EVE to make this list active
    EndCoProList();                                                     // Finish the co-processor list burst write
    AwaitCoProEmpty();                                                  // Wait until co-processor has consumed all commands

}
void ConvertedBitmap(void)
{
    // -----------------  Load image data  -------------------------------------

    //WriteDataRAMG(smallback, sizeof(smallback), 0);                         // Load the image of EVE from header file into RAM_G

    // -------------------  Create screen  -------------------------------------

    BeginCoProList();                                                   // Begin new screen
    cmd_dlstart();                                                          // Tell co-processor to create new Display List

    cmd(CLEAR_COLOR_RGB(255, 255, 255));                                         // Specify color to clear screen to
    cmd(CLEAR(1,1,1));                                                           // Clear color, stencil, and tag buffer

    cmd(BITMAP_HANDLE(0));                                                       // Bitmap handle 0

    //API_BITMAP_HANDLE(0);                                                     // Tell FT81x the properties of the bitmap we will display later
    //API_BITMAP_SOURCE(0);
    //API_BITMAP_LAYOUT(RGB565, 116, 75);
    //API_BITMAP_SIZE(NEAREST, BORDER, BORDER, 58, 75);
    cmd_setbitmap(0,RGB332,800,480);                                          // Equivalent to the four lines above

    cmd(COLOR_RGB(255, 255, 255));                                               // Set color to white so that bitmap is drawn in original color
    cmd(BEGIN(BITMAPS));                                                         // Begin drawing bitmaps
    cmd(VERTEX2F(0,0));                                                          // Place bitmap
    cmd(END());                                                                  // Finish drawing bitmaps

    cmd(DISPLAY());                                                              // Tell EVE that this is end of list
    cmd_swap();                                                             // Swap buffers in EVE to make this list active

    EndCoProList();                                                     // Finish the co-processor list burst write
    AwaitCoProEmpty();                                                  // Wait until co-processor has consumed all commands

    //APP_SnapShot2PPM();                                                       // Un-comment to take snapshot (see BRT_AN_014)

    /*while(1)
    {
    }*/
}
void WriteDataToCMD(const uint8_t *ImgData, uint32_t TotalDataSize)
{
    // This code works by sending the data in a series of one or more bursts.
    // If the data is more than 1000 bytes, it is sent as a series of one or more bursts and then the remainder.
    // It uses a target value which specifies the last index (of the source data) for each chunk
    // e.g. if sending 1500 bytes, we set the target to 999 first and send 1000 bytes (image data index 0 to 999). Then we set the
    // target to 1499 and send the remainder of the data from image data index 1000 to 1499.

    uint16_t CurrentIndex = 0;
    uint16_t Target = 0;
    uint16_t MaxChunkSize = 1000;
    uint16_t CurrentChunk = 0;
    uint16_t EndIndex = 0;
    uint8_t IsLastChunk = 0;
    uint8_t PaddingCheck = 0;
    uint16_t Freespace = 0;

    EndIndex = TotalDataSize - 1;                                               // Determine last index since array index is 0 to (TotalDataSize - 1)

    while(CurrentIndex < EndIndex)                                              // While not all data is sent
    {
        if((EndIndex - CurrentIndex) > MaxChunkSize)                            // If more than ChunkSize bytes to send
        {
            Target = CurrentIndex + MaxChunkSize;                               // ... then add ChunkSize to the current target index to make new target
            IsLastChunk = 0;                                                    // ... and this is not the last chunk
        }
        else                                                                    // or if all remaining bytes can fit in one chunk
        {
            Target = EndIndex;                                                  // ... then add the amount of data to the current target
            IsLastChunk = 0xFF;                                                 // .. and this is the last chunk
        }

        Freespace = 0;                                                          // Wait until there is space
        while(Freespace < MaxChunkSize)
        {
            Freespace = CheckFreeSpace(cmdOffset);
        }

        CurrentChunk = 0;

        wr(RAM_CMD + cmdOffset);    											// Write to the next location in the FIFO

        while(CurrentIndex < Target)                                            // From current index value, keep sending and incrementing until we hit the new target
        {
            wr8(ImgData[CurrentIndex]);
            CurrentIndex ++;
            CurrentChunk ++;
        }

        if(IsLastChunk != 0)                                                    // If this is the last chunk of the data,
        {
        	wr8(ImgData[CurrentIndex]);                                  // ... send last data value ...
            CurrentIndex ++;
            CurrentChunk ++;
                                                                                // ... and then pad with 00s if necessary to make overall data size a multiple of 4 bytes

            PaddingCheck = (CurrentChunk) & 0x03;                               // Mask off the bottom 2 bits to see if non-zero (indicating not multiple 4))
            if (PaddingCheck == 0x03)
            {
            	wr8(0x00);                                               // Send 1 dummy byte to make up to multiple of 4
                CurrentChunk ++;
            }
            else if (PaddingCheck == 0x02)
            {
            	wr8(0x00);                                               // Send 2 dummy byte to make up to multiple of 4
            	wr8(0x00);
                CurrentChunk = (CurrentChunk + 2);
            }
            else if (PaddingCheck == 0x01)
            {
            	wr8(0x00);                                               // Send 3 dummy byte to make up to multiple of 4
            	wr8(0x00);
            	wr8(0x00);
                CurrentChunk = (CurrentChunk + 3);
            }
        }

        endwr();

        cmdOffset = IncCMDOffset(cmdOffset, (CurrentChunk));                // Calculate where end of data lies
        memwr32(REG_CMD_WRITE, cmdOffset);                           		    // and move write pointer to here
    }
}
void WriteDataRAMG(const uint8_t *ImgData, uint32_t DataSize, uint32_t DestAddress)
{
    uint16_t DataPointer = 0;
    uint16_t BitmapDataSize = 0;

    DataPointer = 0;

    wr(DestAddress);


    while(DataPointer < DataSize)
    {
    	wr8(ImgData[DataPointer]);                                       // Send data byte-by-byte from array
        DataPointer ++;
    }

    BitmapDataSize = DataSize - DataPointer;                                    // Add 3, 2 or 1 bytes padding to make it  a multiple of 4 bytes
    BitmapDataSize = BitmapDataSize & 0x03;                                     // Mask off the bottom 2 bits

    if (BitmapDataSize == 0x03)
    {
    	wr8(0x00);
    }
    else if (BitmapDataSize == 0x02)
    {
    	wr8(0x00);
    	wr8(0x00);
    }
    else if (BitmapDataSize == 0x01)
    {
        wr8(0x00);
        wr8(0x00);
        wr8(0x00);
    }

    endwr();                                                               // CS high after burst write of image data
}
uint8_t SendString(const char* string)
{
    uint32_t StringLength = 0;
    uint32_t length = strlen(string);
    uint8_t command_size = 0;

    StringLength = (length + 1);
    while(length --)                                                            // Send string data
    {
        wr8(*string);
        string ++;
    }
    wr8(0);                                                              // Append one null as ending flag
    command_size = (command_size + StringLength);

    // Pad to multiple of 4
    StringLength = StringLength & 0x03;                                         // Mask off the bottom 2 bits and see if multiple of 4
    if (StringLength == 0x03)
    {
    	wr8(0x00);
        command_size = (command_size + 1);
    }
    else if (StringLength == 0x02)
    {
    	wr8(0x00);
    	wr8(0x00);
        command_size = (command_size + 2);
    }
    else if (StringLength == 0x01)
    {
    	wr8(0x00);
    	wr8(0x00);
    	wr8(0x00);
        command_size = (command_size + 3);
    }
    return command_size;
}

uint16_t CheckFreeSpace(uint16_t CmdOffset)
{
    uint32_t ReadPointer = 0;
    uint16_t Fullness, Freespace;

    ReadPointer = rd32(REG_CMD_READ);                                		    // Check the graphics processor read pointer
    Fullness = ((CmdOffset - (uint16_t)ReadPointer) & 4095);                    // Fullness is difference between MCUs current write pointer value and the FT81x's REG_CMD_READ
    Freespace = (4096 - 4) - Fullness;                                          // Free Space is 4K - 4 - Fullness (-4 avoids buffer wrapping round)
    return Freespace;
}
void InflateImage(void)
{
    uint16_t Reg_Cmd_Write_Offset = 0;
    uint32_t End_Address = 0;

    // ###### Send INFLATE command followed by image data ######
    BeginCoProList();                                                   // Begin new co-processor list
    cmd_inflate(0);                                                         // Send the inflate command with destination parameter set to 0
    EndCoProList();                                                     // Finish the burst write
    //WriteDataToCMD(images_3BlackTachBlackBG, sizeof(images_3BlackTachBlackBG));    // Now send the data to the co-processor FIFO immediately after the command //Envoi du fichier compressé
    WriteDataToCMD(Disp_Back, sizeof(Disp_Back));
    AwaitCoProEmpty();                                                  // Ensure that all data was consumed correctly

    // ###### Optionally check where the end of the data is ######
    BeginCoProList();                                                   // New co-processor list
    cmd_getptr(0);                                                          // Command 'Get Pointer' with dummy 0x00000000 parameter
    EndCoProList();                                                     // Execute the command
    AwaitCoProEmpty();                                                  // Ensure that all data was consumed correctly

    Reg_Cmd_Write_Offset = rd16(REG_CMD_WRITE);                        // Check the current write pointer value
    Reg_Cmd_Write_Offset = ((Reg_Cmd_Write_Offset - 4) & 4095);        // Go back by 4 bytes to where the dummy values was placed, allowing for the possibility of the rollover
    End_Address = rd32((RAM_CMD + Reg_Cmd_Write_Offset));                // Read this value. The co-processor will have replaced it with the end address

    // ###### Now display the image ######
    BeginCoProList();                                                   // Begin new screen
    cmd_dlstart();                                                          // Tell co-processor to create new Display List
    cmd(CLEAR_COLOR_RGB(0, 0, 0));                                               // Specify color to clear screen to
    cmd(CLEAR(1,1,1));                                                           // Clear color, stencil, and tag buffer
    cmd(COLOR_RGB(255,255,255));                                                 // Specify colour of text
    cmd(BITMAP_HANDLE(5));                                                       // Tell FT81x the properties of the bitmap we will display. Handle set to 5
    cmd(BITMAP_SOURCE(0));
    cmd(BITMAP_LAYOUT(L4, 400, 480));                                        // 9 bits faible de 800 (divisé par 2 je sais pas pourquoi), 9 bits faible de 480
    //cmd(BITMAP_LAYOUT(ARGB1555, 400, 480));
    cmd(BITMAP_SIZE(NEAREST, REPEAT, REPEAT, 288, 480));                        //9 bits faible de 800 9 bits faible de 480
    cmd(BITMAP_LAYOUT_H(0, 0));
    cmd(BITMAP_SIZE_H(1, 0));													//bits 10 et 11 de 800, bits 10 et 11 de 480
    cmd(BEGIN(BITMAPS));                                                         // Place the bitmap (handle 5) at (100,100)
    cmd(VERTEX2II(0,0,5,0));
    cmd(END());

    // ###### Just for the demo, we print the ending address in dec and hex ######
    /*cmd(COLOR_RGB(255,255,255));                                                 // Use the Number command to print the end address
    cmd_number(300, 260, 30, 0, End_Address);
    cmd_setbase(16);                                                        // Set hex base and re-print the hex equivalent
    cmd_number(300, 300, 30, 0, End_Address);*/

    // ###### Now display the screen created above ######
    cmd(DISPLAY());                                                              // Tell EVE that this is end of list
    cmd_swap();                                                             // Swap buffers in EVE to make this list active
    EndCoProList();                                                     // Finish the co-processor list burst write
    AwaitCoProEmpty();                                                  // Wait until co-processor has consumed all commands

    //APP_SnapShot2PPM();                                                       // Un-comment to take snapshot (see BRT_AN_014)

   /* while(1)
    {
    }*/
}
void BeginCoProList(void)
{
	AwaitCoProEmpty();
	wr(RAM_CMD+cmdOffset);
}
void EndCoProList(void)
{
	endwr();
	memwr32(REG_CMD_WRITE,cmdOffset);
}
void WaitCmdFifoEmpty(void)
{
	unsigned int ReadPointer, WritePointer;

    do
    {
        ReadPointer = rd16(REG_CMD_READ);                              // Read the graphics processor read pointer
        WritePointer = rd16(REG_CMD_WRITE);                            // Read the graphics processor write pointer
    }while ((WritePointer != ReadPointer) && (ReadPointer != 0xFFF));           // Wait until the two registers match

}
unsigned long GetCurrentWritePointer(void)
{
	unsigned long WritePointer;

    WritePointer = rd32(REG_CMD_WRITE);                                // Read the graphics processor write pointer

    return WritePointer;                                                        // New starting point will be first location after the last command
}
void AwaitCoProEmpty(void)
{
	WaitCmdFifoEmpty();														// Await completion of processing
    cmdOffset = GetCurrentWritePointer();                                   // and record starting address for next screen update
}
unsigned int IncCMDOffset(unsigned int currentOffset,unsigned int commandSize)
{
	unsigned int newOffset;                                                       // Used to hold new offset

	newOffset = currentOffset + commandSize;                                    // Calculate new offset

	if(newOffset > 4095)                                                        // If new offset past top of buffer...
	{
		newOffset = (newOffset - 4096);                                         // ... roll over
	}

	return newOffset;

}



unsigned long ALPHA_FUNC(func FUNCTION,unsigned char REFERENCE)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x09<<24)|(FUNCTION<<8)|REFERENCE;
}
unsigned long BEGIN(Prim PRIMITIVE)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1F<<24)|PRIMITIVE;
}
unsigned long BITMAP_HANDLE(unsigned char HANDLE)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x05<<24)|HANDLE;
}
unsigned long BITMAP_LAYOUT(format FORMAT,unsigned int WIDTH, unsigned int HEIGHT)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x07<<24)|(FORMAT<<19)|(WIDTH<<9)|HEIGHT;
}
unsigned long BITMAP_LAYOUT_H(unsigned char WIDTH, unsigned char HEIGHT)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x28<<24)|(WIDTH<<2)|HEIGHT;
}
unsigned long BITMAP_SIZE(filter FILTER,wrap WRAPX,wrap WRAPY,unsigned int WIDTH,unsigned int HEIGHT)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x08<<24)|(FILTER<<20)|(WRAPX<<19)|(WRAPY<<18)|(WIDTH<<9)|HEIGHT;
}
unsigned long BITMAP_SIZE_H(unsigned char WIDTH,unsigned char HEIGHT)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x29<<24)|(WIDTH<<2)|HEIGHT;
}
unsigned long BITMAP_SOURCE(unsigned long ADDRESS)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x01<<24)|ADDRESS;
}
unsigned long BITMAP_TRANSFORM_A(unsigned long A)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x15<<24)|A;
}
unsigned long BITMAP_TRANSFORM_B(unsigned long B)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x16<<24)|B;
}
unsigned long BITMAP_TRANSFORM_C(unsigned long C)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x17<<24)|C;
}
unsigned long BITMAP_TRANSFORM_D(unsigned long D)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x18<<24)|D;
}
unsigned long BITMAP_TRANSFORM_E(unsigned long E)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x19<<24)|E;
}
unsigned long BITMAP_TRANSFORM_F(unsigned long F)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1A<<24)|F;
}
unsigned long BLEND_FUNC(ConstantValue SOURCE,ConstantValue DESTINATION)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0B<<24)|(SOURCE<<3)|DESTINATION;
}
unsigned long CALL(unsigned int DESTINATION)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1D<<24)|DESTINATION;
}
unsigned long CELL(unsigned char CELL)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x06<<24)|CELL;
}
unsigned long CLEAR(bool C,bool S,bool T)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x26<<24)|(C<<2)|(S<<1)|T;
}
unsigned long CLEAR_COLOR_A(unsigned char ALPHA)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0F<<24)|ALPHA;
}
unsigned long CLEAR_COLOR_RGB(unsigned char RED,unsigned char BLUE, unsigned char GREEN)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2 << 24)|(RED << 16)|(BLUE << 8)|GREEN;
}
unsigned long CLEAR_STENCIL(unsigned char S)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x11<<24)|S;
}
unsigned long CLEAR_TAG(unsigned char T)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x12<<24)|T;
}
unsigned long COLOR_A(unsigned char ALPHA)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x10<<24)|ALPHA;
}
unsigned long COLOR_MASK(bool R,bool G,bool B,bool A)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x20<<24)|(R<<3)|(G<<2)|(B<<1)|A;
}
unsigned long COLOR_RGB(unsigned char RED,unsigned char BLUE, unsigned char GREEN)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x04<<24)|(RED<<16)|(BLUE<<8)|GREEN;
}
unsigned long DISPLAY(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return 0;
}
unsigned long END(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x21<<24);
}
unsigned long JUMP(unsigned int DESTINATION)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1E<<24)|DESTINATION;
}
unsigned long LINE_WIDTH(unsigned int WIDTH)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0E<<24)|WIDTH;
}
unsigned long MACRO(bool M)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x25<<24)|M;
}
unsigned long NOP(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2D<<24);
}
unsigned long PALETTE_SOURCE(unsigned long ADDRESS)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2A<<24)|ADDRESS;
}
unsigned long POINT_SIZE(unsigned int SIZE)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0D<<24)|SIZE;
}
unsigned long RESTORE_CONTEXT(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x23<<24);
}
unsigned long RETURN(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x24<<24);
}
unsigned long SAVE_CONTEXT(void)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x22<<24);
}
unsigned long SCISSOR_SIZE(unsigned int WIDTH,unsigned int HEIGHT)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1C<<24)|(WIDTH<<12)|HEIGHT;
}
unsigned long SCISSOR_XY(unsigned int X,unsigned int Y)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1B<<24)|(X<<11)|Y;
}
unsigned long STENCIL_FUNC(func FUNCTION,unsigned char REFERENCE,unsigned char MASK)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0A<<24)|(FUNCTION<<16)|(REFERENCE<<8)|MASK;
}
unsigned long STENCIL_MASK(unsigned char MASK)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x13<<24)|MASK;
}
unsigned long STENCIL_OP(StencilAction SFAIL,StencilAction SPASS)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x0C<<24)|(SFAIL<<3)|SPASS;
}
unsigned long TAG(unsigned char S)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x03<<24)|S;
}
unsigned long VERTEX2F(unsigned long X,unsigned long Y)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x1<<30)|(X<<15)|Y;
}
unsigned long VERTEX2II(unsigned int X,unsigned int Y,unsigned char HANDLE,unsigned char CELL)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2<<30)|(X<<21)|(Y<<12)|(HANDLE<<7)|CELL;
}
unsigned long VERTEX_FORMAT(unsigned char FRAC)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x27<<24)|FRAC;
}
unsigned long VERTEX_TRANSLATE_X(unsigned long X)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2B<<24)|X;
}
unsigned long VERTEX_TRANSLATE_Y(unsigned long Y)
{
	//cmdOffset = IncCMDOffset(cmdOffset, 4);
	return (0x2C<<24)|Y;
}

/*Widgets*/

void cmd_dlstart(void)
{
	wr32(CMD_DLSTART);
	cmdOffset = IncCMDOffset(cmdOffset,4);
}
void cmd_swap(void)
{
	wr32(CMD_SWAP);
	cmdOffset = IncCMDOffset(cmdOffset,4);
}
void cmd_coldstart(void)
{
	wr32(CMD_COLDSTART);
	cmdOffset = IncCMDOffset(cmdOffset,4);
}
void cmd_interrupt(uint32_t ms)
{
	wr32(CMD_INTERRUPT);
	wr32(ms);
	cmdOffset = IncCMDOffset(cmdOffset,8);
}
void cmd_append(uint32_t ptr,uint32_t num)
{
	wr32(CMD_APPEND);
	wr32(ptr);
	wr32(num);
	cmdOffset = IncCMDOffset(cmdOffset,12);
}
void cmd_regread(uint32_t ptr,uint32_t result)
{
	wr32(CMD_REGREAD);
	wr32(ptr);
	wr32(result);
	cmdOffset = IncCMDOffset(cmdOffset,12);
}
void cmd_memwrite(uint32_t ptr, uint32_t num)
{
	wr32(CMD_MEMWRITE);
	wr32(ptr);
	wr32(num);
	cmdOffset = IncCMDOffset(cmdOffset,12);
}
void cmd_inflate(uint32_t ptr)
{
	wr32(CMD_INFLATE);
	wr32(ptr);
	cmdOffset = IncCMDOffset(cmdOffset,8);
}
void cmd_loadimage(unsigned char ptr,Option options)////uint32_t
{
	wr32(CMD_LOADIMAGE);
	wr32(ptr);
	wr32(options);
	cmdOffset = IncCMDOffset(cmdOffset,12);
}
void cmd_mediafifo (uint32_t ptr,uint32_t size)
{
	wr32(CMD_MEDIAFIFO);
	wr32(ptr);
	wr32(size);
	cmdOffset = IncCMDOffset(cmdOffset,12);
}
void cmd_playvideo (Option opts)
{
	wr32(CMD_PLAYVIDEO);
	wr32(opts);
	cmdOffset = IncCMDOffset(cmdOffset,8);
}
void cmd_videostart(void)
{
	wr32(CMD_VIDEOSTART);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
void cmd_videoframe(uint32_t dst,uint32_t ptr)
{
	wr32(CMD_VIDEOFRAME);
	wr32(dst);
	wr32(ptr);
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_memcrc(uint32_t ptr,uint32_t num,uint32_t result)
{
	wr32(CMD_MEMCRC);
	wr32(ptr);
	wr32(num);
	wr32(result);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_memzero(uint32_t ptr,uint32_t num)
{
	wr32(CMD_MEMZERO);
	wr32(ptr);
	wr32(num);
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_memset(uint32_t ptr,uint32_t value,uint32_t num)
{
	wr32(CMD_MEMSET);
	wr32(ptr);
	wr32(value);
	wr32(num);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_memcpy(uint32_t dest,uint32_t src,uint32_t num)
{
	wr32(CMD_MEMCPY);
	wr32(dest);
	wr32(src);
	wr32(num);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_button(int16_t x,int16_t y,int16_t w,int16_t h,int16_t font,Option options,const char* string)
{
	uint32_t command_size = 0, StringLength = 0;

	wr32(CMD_BUTTON);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32((((uint32_t)options<<16)|(font & 0xffff)));
	command_size = (command_size + 16);

	StringLength = SendString(string);
	command_size = (command_size + StringLength);

	cmdOffset = IncCMDOffset(cmdOffset, command_size);
}
void cmd_clock(int16_t x,int16_t y,int16_t r,Option options,uint16_t h,uint16_t m,uint16_t s,uint16_t ms)
{
	wr32(CMD_CLOCK);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)options<<16)|(r & 0xffff)));
	wr32((((uint32_t)m<<16)|(h & 0xffff)));
	wr32((((uint32_t)ms<<16)|(s & 0xffff)));
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_fgcolor(uint32_t c)
{
	wr32(CMD_FGCOLOR);
	wr32(c);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_bgcolor(uint32_t c)
{
	wr32(CMD_BGCOLOR);
	wr32(c);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_gradcolor(uint32_t c)
{
	wr32(CMD_GRADCOLOR);
	wr32(c);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_gauge(int16_t x,int16_t y,int16_t r,Option options,uint16_t major,uint16_t minor,uint16_t val,uint16_t range)
{
	wr32(CMD_GAUGE);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)options<<16)|(r & 0xffff)));
	wr32((((uint32_t)minor<<16)|(major & 0xffff)));
	wr32((((uint32_t)range<<16)|(val & 0xffff)));
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_gradient(int16_t x0,int16_t y0,uint32_t rgb0,int16_t x1,int16_t y1,uint32_t rgb1)
{
	wr32(CMD_GRADIENT);
	wr32((((uint32_t)y0<<16)|(x0 & 0xffff)));
	wr32(rgb0);
	wr32((((uint32_t)y1<<16)|(x1 & 0xffff)));
	wr32(rgb1);
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_progress(int16_t x,int16_t y,int16_t w,int16_t h,Option options,uint16_t val,uint16_t range)
{
	wr32(CMD_PROGRESS);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32((((uint32_t)val<<16)|(options & 0xffff)));
	wr32(range);
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_scrollbar(int16_t x,int16_t y,int16_t w,int16_t h,Option options,uint16_t val,uint16_t size,uint16_t range)
{
	wr32(CMD_SCROLLBAR);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32((((uint32_t)val<<16)|(options & 0xffff)));
	wr32((((uint32_t)range<<16)|(size & 0xffff)));
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_slider(int16_t x,int16_t y,int16_t w,int16_t h,Option options,uint16_t val,uint16_t range)
{
	wr32(CMD_SLIDER);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32((((uint32_t)val<<16)|(options & 0xffff)));
	wr32(range);
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_dial(int16_t x,int16_t y,int16_t r,Option options,uint16_t val)
{
	wr32(CMD_DIAL);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)options<<16)|(r&0xffff)));
	wr32(val);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_toggle(int16_t x,int16_t y,int16_t w,int16_t font,Option options,uint16_t state,const char* string)
{
	uint32_t length = strlen(string);
	uint32_t command_size = 0, StringLength = 0;

	wr32(CMD_TOGGLE);
	wr32(((uint32_t)y<<16)|(x & 0xffff));
	wr32(((uint32_t)font<<16)|(w & 0xffff));
	wr32(((uint32_t)state<<16)|options);
	command_size = (command_size + 16);

	StringLength = SendString(string);
	command_size = (command_size + StringLength);

	cmdOffset = IncCMDOffset(cmdOffset, command_size);
}
void cmd_text(int16_t x,int16_t y,int16_t font,Option options,const char* string)
{
	uint32_t command_size = 0;
	uint32_t StringLength = 0;

	wr32(CMD_TEXT);
	wr32(((uint32_t)y<<16)|(x & 0xffff));
	wr32(((uint32_t)options<<16)|(font & 0xffff));
	command_size = (command_size + 12);

	StringLength = SendString(string);
	command_size = (command_size + StringLength);

	cmdOffset = IncCMDOffset(cmdOffset, command_size);
}
void cmd_setbase(uint32_t base)
{
	wr32(CMD_SETBASE);
	wr32(base);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_number(int16_t x,int16_t y,int16_t font,Option options,int32_t n)
{
	wr32(CMD_NUMBER);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)options<<16)|(font & 0xffff)));
	wr32(n);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_loadidentity(void)
{
	wr32(CMD_LOADIDENTITY);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
void cmd_setmatrix(void)
{
	wr32(CMD_SETMATRIX);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
void cmd_getmatrix(int32_t a,int32_t b,int32_t c,int32_t d,int32_t e,int32_t f)
{
	wr32(CMD_GETMATRIX);
	wr32(a);
	wr32(b);
	wr32(c);
	wr32(d);
	wr32(e);
	wr32(f);
	cmdOffset = IncCMDOffset(cmdOffset, 28);
}
void cmd_getptr(uint32_t result)
{
	wr32(CMD_GETPTR);
	wr32(result);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_getprops(uint32_t ptr, uint32_t width, uint32_t height)
{
	wr32(CMD_GETPROPS);
	wr32(ptr);
	wr32(width);
	wr32(height);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_scale(int32_t sx,int32_t sy)
{
	wr32(CMD_SCALE);
	wr32(sx);
	wr32(sy);
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_rotate(int32_t a)
{
	wr32(CMD_ROTATE);
	wr32(a);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_translate(int32_t tx,int32_t ty)
{
	wr32(CMD_TRANSLATE);
	wr32(tx);
	wr32(ty);
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_setrotate(uint32_t r)
{
	wr32(CMD_SETROTATE);
	wr32(r);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_spinner(int16_t x,int16_t y,uint16_t style,uint16_t scale)
{
	wr32(CMD_SPINNER);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)scale<<16)|(style & 0xffff)));
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_screensaver(void)
{
	wr32(CMD_SCREENSAVER);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
void cmd_sketch(int16_t x,int16_t y,uint16_t w,uint16_t h,uint32_t ptr,uint16_t format)
{
	wr32(CMD_SKETCH);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32(ptr);
	wr32(format);
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_stop(void)
{
	wr32(CMD_STOP);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
void cmd_setfont(uint32_t font,uint32_t ptr)
{
	wr32(CMD_SETFONT);
	wr32(font);
	wr32(ptr);
	cmdOffset = IncCMDOffset(cmdOffset, 12);
}
void cmd_setfont2(uint32_t font,uint32_t ptr,uint32_t firstchar)
{
	wr32(CMD_SETFONT2);
	wr32(font);
	wr32(ptr);
	wr32(firstchar);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_setscratch(uint32_t handle)
{
	wr32(CMD_SETSCRATCH);
	wr32(handle);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_track(int16_t x,int16_t y,int16_t w,int16_t h,int16_t tag)
{
	wr32(CMD_TRACK);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	wr32(tag);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_snapshot(uint32_t ptr)
{
	wr32(CMD_SNAPSHOT);
	wr32(ptr);
	cmdOffset = IncCMDOffset(cmdOffset, 8);
}
void cmd_snapshot2(uint32_t fmt,uint32_t ptr,int16_t x,int16_t y,int16_t w,int16_t h)
{
	wr32(CMD_SNAPSHOT2);
	wr32(fmt);
	wr32(ptr);
	wr32((((uint32_t)y<<16)|(x & 0xffff)));
	wr32((((uint32_t)h<<16)|(w & 0xffff)));
	cmdOffset = IncCMDOffset(cmdOffset, 20);
}
void cmd_setbitmap(uint32_t addr,uint16_t fmt,uint16_t width,uint16_t height)
{
	wr32(CMD_SETBITMAP);
	wr32(addr);
	wr32((((uint32_t)width<<16)|(fmt & 0xffff)));
	wr32(height);
	cmdOffset = IncCMDOffset(cmdOffset, 16);
}
void cmd_logo(void)
{
	wr32(CMD_LOGO);
	cmdOffset = IncCMDOffset(cmdOffset, 4);
}
