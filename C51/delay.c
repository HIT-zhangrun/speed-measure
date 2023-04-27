/*****************************************************
*@filename: 			dely.c
*@description: 		延时函数
*@author: 				ZhangRun
*@version：				v1.0
*@date：					2021/6/17
*@note: 
****************************************************/
#include "delay.h"

/*****************************************************
*@param: 				
*@return: 
*@function: 			延时1ms
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void delay1ms(int t)
{
		int i,j;
		for(i=0;i<t;i++)
			for(j=0;j<120;j++)
				_nop_();
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			延时函数 20微秒 @12.000MHz
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void Delay20us()
{
		uint_8 i;
		_nop_();
		i = 7;
		while (--i);
}
