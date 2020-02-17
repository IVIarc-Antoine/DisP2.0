/*
 * Fonction.h
 *
 *  Created on: 2017-09-26
 *      Author: C-031
 */

#ifndef FONCTION_H_
#define FONCTION_H_

void RTCSetTime(char, char, char);
void RTCSetDate(char , char , int );
void InitRTC(void);
void InitClokAlarm(char, char, char);
void InitDateAlarm(char , char , int );
void RTCSetCalibration(char,char);
#endif /* FONCTION_H_ */
