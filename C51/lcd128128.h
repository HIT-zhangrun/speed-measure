#ifndef __LCD128128_H__
#define __LCD128128_H__

#include "delay.h"
#include "reg51.h"
#include "speed.h"

sbit cd = P2^0;
sbit rd = P2^1;
sbit wr = P2^2;
sbit ce = P2^3;
extern int  		count;
extern float 		DistanceValue;		//测量的距离值
extern float 		DistanceValue2;
extern uint_8 	speed;
extern float 		SPEEDSOUND;				//声速

void busycheck();
void setadr(void);
void wrcode0(uint_8 h);
void wrcode1(uint_8 i,uint_8 h);
void wrcode2(uint_8 i,uint_8 j,uint_8 h);
void wrdata(uint_8 j);
void disptupian(uint_8 *p,uint_8 x,uint_8 y,uint_8 base,uint_8 pianyi);
void lcd_init();
void display();
#endif
