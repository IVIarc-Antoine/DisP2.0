/*
 * PinsConfig.cpp
 *
 *  Created on: 13 sept. 2019
 *      Author: Marc-Antoine
 */
#include "board.h"
#include <cr_section_macros.h>
#include "Clock.h"
#include "Macro.h"
#include "PinsFunctions.h"
//#include "PinsConfig.h"
#include "interrupt.h"
#include "Timers.h"
#include "GPIO.h"
#include "PinsConfig.h"
//#include "PWM.h"

void Init_Pins(void)
{
	/* affichage + on/off du moteur + Point décimal*/
	PINSEL4 = 0; // pour mettre tout le port 2 en GPIO (de p2.15 à 2.0)
	FIO2DIRL = 0x3FFF;//pour mettre p2.10-p2.8 et p2.5-p2.0 en output(0x73f) + p2.6 pour le ON/OFF1 + p2.7 pour le ON/OFF2(0x07FF) + P2.11 pour le S0 + P2.12 pour le S1 (0X1FFF) + P2.13pour le point en output(0x3FFF)
	//FIO2PIN1 = (FIO2PIN1 & 0XF8) | 0X07;//pour mettre s2 s1 s0 à 1 pour afficher sur le caractère de droite
	//FIO2PIN1 = 0x0;
	//FIO2PIN0 = (FIO2PIN0 & 0X00) | 0X00;//pour mettre seulement les p2.5-p2.0 à 0(0xC0) + p2.6 et p2.7 à 0 (0x00)
	FIO2PINL = 0b0001100000000000;//plus simple que lignes en haut (s0, s1 du MUX à 1)



	/*capture*/
	/*I2B(PINSEL3,20,F3);//Pour mettre P1.26 en GPIO (F3 = CAP0.0)
	I2B(PINSEL3,22,F3);//Pour mettre P1.27 en GPIO (F3 = CAP0.1)
	FIO1DIR3 = (FIO1DIR3 & 0x0C) | 0x00;//À la base les pins P1.26 et P1.27 sont déjà en inputs, mais c'est juste pour être certain
	I2B(PINMODE1,20,2);	//pour mettre la pin 1.26 flottante (autrement elle serait en pullup)*/


	/*PWM*/
	/*I2B(PINSEL7,18,F3);//P3.25 PWM1[2]
	I2B(PINSEL7,20,F3);//p3.26 PWM1[3]
	I2B(PINMODE7,18,2);//3.25 float
	I2B(PINMODE7,20,2);//3.26 float*/

	/*UART*/

	I2B(PINSEL9,24,F3);//TXD3 p4.28
	I2B(PINSEL9,26,F3);//RXD3 p4.29
	I2B(PINMODE9,24,2);//TXD3 open drain
	I2B(PINMODE9,26,2);//RXD3 open drain

	/*Désactiver les autres pins du UART3*/

	I2B(PINSEL0,0,F0);
	I2B(PINSEL0,2,F0);
	I2B(PINSEL1,18,F0);
	I2B(PINSEL1,20,F0);

	/*GPIO Interrupts*/
	/*I2B(PINSEL0,0,F0);//p0.0 GPIO
	I2B(PINSEL0,2,F0);//p0.1 GPIO
	I2B(PINSEL0,4,F0);//p0.2 GPIO
	I2B(PINSEL0,6,F0);//p0.3 GPIO
	I2B(PINSEL0,8,F0);//p0.4 GPIO
	I2B(PINSEL0,10,F0);//p0.5 GPIO
	I2B(PINSEL0,12,F0);//p0.6 GPIO

	FIO0DIR0 |= 0x70;// P0.6..P0.4 en output + P0.3..P0.0 en Input
	//pull up sur P0.3..P0.0 (déjà en pull up au reset)

	I2B(PINMODE0,0,0);//p0.0 pull up
	I2B(PINMODE0,2,0);//p0.1 pull up
	I2B(PINMODE0,4,0);//p0.2 pull up
	I2B(PINMODE0,6,0);//p0.3 pull up
	//I2B(PINMODE0,8,2);//p0.4 float
	//I2B(PINMODE0,10,2);//p0.5 float
	//I2B(PINMODE0,12,2);//p0.6 float (vérifier si ok de mettre un output en float...)

	ClearBit(4,FIO0PIN0);//output GPIO déja à 0 au reset
	ClearBit(5,FIO0PIN0);
	ClearBit(6,FIO0PIN0);*/

	/*GPIO Interrupt Capteurs IR*/
	/*I2B(PINSEL0,14,F0);//p0.7 GPIO
	I2B(PINSEL0,16,F0);//p0.8 GPIO
	I2B(PINMODE0,14,2);//p0.7 Float (pull down hardware)
	I2B(PINMODE0,16,2);//p0.8 Float (pull down hardware)*/

	/*SPI*/
	I2B(PINSEL0,30,F3);//P0.15 SCK
	I2B(PINSEL0,12,F0);//P0.6 Slave Select Master (GPIO)(DisP_PD)
	I2B(PINSEL0,14,F0);//P0.7 Slave Select Master (GPIO)(DisP)
	I2B(PINSEL0,16,F0);//P0.8 Slave Select Master (GPIO)(SDCard)
	I2B(PINSEL0,18,F0);//P0.9 Slave Select Master (GPIO)(none for now)
	I2B(PINSEL1,4,F3);//P0.18 MOSI
	I2B(PINSEL1,2,F3);//P0.17 MISO
	/*Pas de MISO sur le LCD*/
	//I2B(PINMODE0,30,0);// pull up sur SCK car on est en mode 3 (CPOL =1 , CPHA = 1) => Défini par le LCD (pas obligatoire mais évite des problèmes)
	I2B(PINMODE0,12,0);// pull up sur Slave Select car active low (on ne veut pas activer par accident)
	I2B(PINMODE0,14,0);// pull up sur Slave Select
	I2B(PINMODE0,16,0);// pull up sur Slave Select
	I2B(PINMODE0,18,0);// pull up sur Slave Select
	I2B(PINMODE1,4,2);// MOSI set en float
	I2B(PINMODE1,2,2);// MISO set en float
	SB(6,FIO0DIR);//P0.6 en output (GPIO)
	SB(7,FIO0DIR);//P0.7 en output (GPIO)
	SB(8,FIO0DIR);//P0.8 en output (GPIO)
	SB(9,FIO0DIR);//P0.9 en output (GPIO)



	/*ADC*/
	/*I2B(PINSEL1,14,F1);//P0.23 AD0.0 Temp 1
	I2B(PINSEL1,16,F1);//P0.24 AD0.1 Temp 2
	I2B(PINSEL1,18,F1);//P0.25 AD0.2 Gaz Inj 1
	I2B(PINSEL3,28,F3);//P1.30 AD0.4 Gaz Inj 2

	I2B(PINMODE1,14,2);//P0.23 AD0.0 Temp 1 float
	I2B(PINMODE1,16,2);//P0.24 AD0.1 Temp 2 float
	I2B(PINMODE1,18,2);//P0.25 AD0.2 Gaz Inj 1 float
	I2B(PINMODE3,28,2);//P1.30 AD0.4 Gaz Inj 2 float*/



	/*DAC*/
	/*I2B(PINSEL1,20,F2);//P0.26 AOUT Gauge
	I2B(PINMODE1,20,2);//P0.26 Float*/


	/*I2C*/


	/*//I2B(PINSEL1,22,F1);//P0.27 I2C SDA0
	I2B(PINSEL1,22,F0);//P0.27 GPIO (test)
	//I2B(PINSEL1,24,F1);//P0.28 I2C SCL0
	I2B(PINSEL1,24,F0);
	//I2B(PINMODE1,22,2);//P0.27 I2C SDA0 float
	I2B(PINMODE1,22,0);//P0.27 pull up (test)
	//I2B(PINMODE1,24,2);//P0.28 I2C SCL0 float
	I2B(PINMODE1,24,0);
	I2CPADCFG = 0x0;//pas de PINMODE_OD pour P0.27/P0.28, on utilise ce registre là au lieu

	SB(27,FIO0DIR);//P0.27 output (test)
	SB(28,FIO0DIR);

	I2B(PINSEL1,6,F0);//P0.19 GPIO (test)
	I2B(PINSEL1,8,F0);//P0.20 GPIO (test)
	I2B(PINMODE1,6,F0);//P0.19 GPIO (test)
	I2B(PINMODE1,8,F0);//P0.20 GPIO (test)

	SB(19,FIO0DIR);
	SB(20,FIO0DIR);*/


	I2B(PINSEL1,6,F3);//P0.19 I2C SDA1
	I2B(PINSEL1,8,F3);//P0.20 I2C SCL1
	I2B(PINMODE1,6,2);//P0.19 Float
	I2B(PINMODE1,8,2);//P0.20 Float

	SB(19,PINMODE_OD0);
	SB(20,PINMODE_OD0);

	/*Désactiver les ports qui ne sont pas utilisés*/
	I2B(PINSEL1,22,F0);//P0.27 GPIO
	I2B(PINSEL1,24,F0);//P0.28 GPIO
	I2B(PINSEL0,0,F0);//P0.0 GPIO
	I2B(PINSEL0,2,F0);//P0.1 GPIO
	I2B(PINSEL0,20,F0);//P0.10 GPIO
	I2B(PINSEL0,22,F0);//P0.11 GPIO



	/*CAN*/



}
void InitGPIO_Int(void)
{
	SB(15,PCONP);//PCGPIO
	I2B(PCLKSEL1,2,0);//cclk/4
	IO0IntEnF |= 0xF;//enable falling edge interrupt sur P0.3..P0.0 (falling edge car pull up à la base et niveau bas sur P0.6..P0.4)

	IO0IntEnR |= 0x180;//enable rising edge interrupt sur p0.7 et P0.8


}
