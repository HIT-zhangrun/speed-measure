/*****************************************************
*@filename: 			main.c
*@description: 		测速
*@author: 				ZhangRun
*@version：				v1.0
*@date：					2021/6/17
*@note: 
****************************************************/
#include "speed.h"

int  	count						=		0;

float DistanceValue		=		0.0;	//测量的距离值
float DistanceValue2	=		0.0;
uint_8 speed;
float SPEEDSOUND;								//声速


/*****************************************************
*@param: 				
*@return: 
*@function: 			测量距离
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
float MeasuringDistance()
{
		TH0=0;				//最大定时时间约65ms
		TL0=0;
		Trig=1;				//生成20us的脉冲宽度的触发信号
		Delay20us();
		Trig=0;
		while(!Echo);	//等待回响信号变高电平
		TR0=1;				//启动定时器0
		while(Echo);	//等待回响信号变低电平
		TR0=0;				//关闭定时器0
		return (SPEEDSOUND*(TH0*256.0+TL0))/2000;		//返回距离值(mm)
}
/*****************************************************
*@param: 				
*@return: 
*@function: 			HCSR04初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void speed_init()
{
		SPEEDSOUND=334.1+25*0.61;				
		Trig=0;	
		Echo=0;
		TMOD=0x01;
}
/*****************************************************
*@param: 				
*@return: 
*@function: 			测距的数值排序求平均
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
float DistanceStatistics()
{
		uint_8 i;
		float disData;
		for(i=0;i<7;i++)  						//连续测距
		{
			disData+=MeasuringDistance();	
			delay1ms(1);
		}
		return disData/7.0;
}

