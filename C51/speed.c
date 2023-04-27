/*****************************************************
*@filename: 			main.c
*@description: 		����
*@author: 				ZhangRun
*@version��				v1.0
*@date��					2021/6/17
*@note: 
****************************************************/
#include "speed.h"

int  	count						=		0;

float DistanceValue		=		0.0;	//�����ľ���ֵ
float DistanceValue2	=		0.0;
uint_8 speed;
float SPEEDSOUND;								//����


/*****************************************************
*@param: 				
*@return: 
*@function: 			��������
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
float MeasuringDistance()
{
		TH0=0;				//���ʱʱ��Լ65ms
		TL0=0;
		Trig=1;				//����20us�������ȵĴ����ź�
		Delay20us();
		Trig=0;
		while(!Echo);	//�ȴ������źű�ߵ�ƽ
		TR0=1;				//������ʱ��0
		while(Echo);	//�ȴ������źű�͵�ƽ
		TR0=0;				//�رն�ʱ��0
		return (SPEEDSOUND*(TH0*256.0+TL0))/2000;		//���ؾ���ֵ(mm)
}
/*****************************************************
*@param: 				
*@return: 
*@function: 			HCSR04��ʼ��
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
*@function: 			������ֵ������ƽ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
float DistanceStatistics()
{
		uint_8 i;
		float disData;
		for(i=0;i<7;i++)  						//�������
		{
			disData+=MeasuringDistance();	
			delay1ms(1);
		}
		return disData/7.0;
}

