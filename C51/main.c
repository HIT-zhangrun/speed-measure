/*****************************************************
*@filename: 			main.c
*@description: 		实现校园车辆测速并显示
*@author: 				ZhangRun
*@version：				v1.0
*@date：					2021/6/17
*@note: 
****************************************************/

#include "reg51.h"
#include "intrins.h"
#include "absacc.h"
#include "lcd128128.h"
#include "delay.h"
#include "speed.h"


/*****************************************************
*@param: 				
*@return: 
*@function: 
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void main()
{
  	lcd_init();
		speed_init();//HC-SR04初始化
   	while(1)
		{
		display();
		}
}		 
