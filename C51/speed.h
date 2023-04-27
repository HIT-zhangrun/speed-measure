#ifndef __SPEED_H__
#define __SPEED_H__

#include "delay.h"
#include "reg51.h"

sbit LEDRed	=		P2^4;		//���ָʾ�ƣ�����ʾ���ڲ�࣬���ʾ������
sbit Trig		=		P1^7;		//HC-SR04�����ź�����
sbit Echo		=		P1^6;		//HC-SR04�����ź����


float MeasuringDistance();
void speed_init();
float DistanceStatistics();

#endif
