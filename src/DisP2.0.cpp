/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif


#include <stdbool.h>
#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
#include "PinsConfig.h"
#include "interrupt.h"
#include "Timers.h"
#include "GPIO.h"
#include "PinsConfig.h"
#include "SPI.h"
#include "LCD.h"
#include "RTC.h"
#include "I2C.h"
#include "DisP.h"

//#include <predef.h>
#include <stdio.h>
#include <ctype.h>
//#include <startnet.h>
//#include <autoupdate.h>
//#include <dhcpclient.h>
//#include <smarttrap.h>
//#include <taskmon.h>
//#include <NetworkDebug.h>
//#include <pins.h>
//#include <pin_irq.h>
//#include <multichanneli2c.h>
//#include <constants.h>
//#include <HiResTimer.h>
//#include "IMUSetupAndSample.h"
#include "MPU9250.h"
//#include "Boot_Settings.h"

//#define IMU_TIMER 3

//const char *AppName = "IMU Example";

//MPU9250 imu; //Default constructor does nothing

extern struct Master{
	char OwnAdr;//adresse du slave
	unsigned char *TxBuffer;//pointeur vers le message à envoyer
	int TxLen;//taille du message à envoyer
}I2CMaster;

extern struct Interrupt{
	bool STT;
	bool LCD;
	bool RTC;
	bool InitDone;
}Flag;

unsigned char DummyPK[10] = {0xAF};
int Dummy;
int DummyCPT;


int main(void) {

	SystemCoreClockUpdate();
    Board_Init();
    Board_LED_Set(0, true);
    Init_Pins();	//pour mettre les PINSEL FOIPIN etc etc. (usage futur)
    //Init_RIT();
    Init_ST();
    Init_SPI();
    //Init_RTC();
    Init_I2C();

    Init_Interrupts();

    //Init_SSD1306V2();

    DisP_Init();


    //Init_SSD1306();

    //Init_LCD1604();

    //I2C_AdrLookup();
    //I2C_SendData(DummyPK);
    //I2C_Send(DummyPK,LCDAdr);

    //ConsoleGetItems();



    //Sleep(500);
    //DisP_Example();
   //Sleep(5000);
    //DisP_Test1();
	//DisP_4Points();
	//Sleep(500);
	//DisP_Template1();
	//Sleep(5000);

	InflateImage();
	Sleep(2000);

	//DisP_Background();



	//Re-construct MPU9250 object
	//passing in -1 assigns the next free HiResTimer to the imu
	//imu = MPU9250(IMU_TIMER); //ignore warning that 'imu' set and not used

	//Initialize and calibrate IMU
	//IMUSetup();

	//Create RTOS task that updates the IMU at a specified update rate
	//IMURun();



    while(1)
    {
		for(uint16_t i = 0;i<9000;i+=82)
		{

			Disp_RPM2(i);
			//ConvertedBitmap();
			Sleep(17);//pour avoir 60frames/sec environ
		}
    }

    /*while(1)
    {

   	   	  OSTimeDly(TICKS_PER_SECOND);
    }*/
    return 0 ;
}
