#ifndef __SPEED_H__
#define __SPEED_H__

#include "delay.h"
#include "reg51.h"

sbit LEDRed	=		P2^4;		//测距指示灯，亮表示正在测距，灭表示测距完成
sbit Trig		=		P1^7;		//HC-SR04触发信号输入
sbit Echo		=		P1^6;		//HC-SR04回响信号输出


float MeasuringDistance();
void speed_init();
float DistanceStatistics();

#endif
