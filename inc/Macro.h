/*
 * macro.h
 *
 *  Created on: 5 oct. 2017
 *      Author: mauclair
 */

#ifndef Macro_H_
#define Macro_H_

/******************************************************************************
 En qualifiant par volatile le type d'une variable, le programmeur
 prévient le compilateur que cette variable peut être modifiée par un moyen
 extérieur au programme. Ceci se produit lorsqu'on interagit avec des parties
 matérielles de la machine : coupleurs d'entrées-sorties généralement.
 Lorsqu'une variable est de type volatile le compilateur ne doit pas procéder
 aux optimisations qu'il réalise sur les variables normales.
 ******************************************************************************/
#define BITS_ZERO_ZERO 			0
#define ZZ						BITS_ZERO_ZERO
#define BITS_ZERO_ONE 			1
#define ZO						BITS_ZERO_ONE		
#define BITS_ONE_ZERO 			2
#define OZ						BITS_ONE_ZERO
#define BITS_ONE_ONE 			3
#define OO						BITS_ONE_ONE

#define	F0	0
#define	F1	1
#define	F2	2
#define	F3	3

#define SetBit(n,v)				v |= ( 1 << n )
#define SB(n,v)					SetBit(n,v)
#define ClearBit(n,v) 			v &= ~( 1 << n)
#define CB(n,v)					ClearBit(n,v)
#define ToggleBit(n,v)			v ^= (1 << n)


#define TestBit(n,v)  			((v & (1 << n)) > 0 ? 1:0)
#define TB(n,v)					TestBit(n,v)

#define ClearInterruptBit(n,v)					SetBit(n,v)
#define ClrIntBit(n,v)							ClearInterruptBit(n,v)
#define CIB(n,v)								ClrIntBit(n,v)
#define ClrTwoBits(n,v)							v &= ~( 3 << n ) //kill 2 bits 00 at position
#define C2B(n,v)								ClrTwoBits(n,v)
#define InitializeTwoBits(Vect,BitPos,Lev)		Vect = ClrTwoBits(BitPos,Vect);\
												Vect |= ( Lev << BitPos );
#define I2B(Vect,BitPos,Lev)					InitializeTwoBits(Vect,BitPos,Lev)



#endif /* Macro_H_ */
