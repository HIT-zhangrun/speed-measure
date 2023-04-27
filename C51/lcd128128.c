/*****************************************************
*@filename: 			lcd128128.c
*@description: 		��ʾҳ�����
*@author: 				ZhangRun
*@version��				v1.0
*@date��					2021/6/17
*@note: 
****************************************************/
#include "lcd128128.h"
#include "zimo.h"


uint_16 	lcdadress;						//lcd��ַ
uint_8 		lcdh,lcdl;						//lcd��ַ�ߵ�

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void busycheck()
{
		uint_8 state;
		P0=0XFF;
		do
		{
			cd=1;      								// ѡ��ָ��ͨ����׼����ȡͨ��״̬
			rd=0;      								//����Ч
			state=P0;
			rd=1;
		}
		while((state&0x03)!=0x03);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void setadr(void)           			//�趨��ַ�ӳ���
{
   lcdh=lcdadress/256;
   lcdl=lcdadress-lcdh*256;
   wrcode2(lcdl,lcdh,0x24);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode0(uint_8 h)						//�޲���ָ��д���ӳ���
{
		busycheck();
		cd=1;      										//ѡ��ָ��ͨ��
    P0=h;
		wr=0;
		wr=1;
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode1(uint_8 i,uint_8 h)		//������ָ��д���ӳ���
{  
	 wrdata(i);
	 wrcode0(h);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode2(uint_8 i,uint_8 j,uint_8 h)//˫����ָ��д���ӳ���
{
		wrdata(i);            							//��һ������д��
	  wrdata(j);           								//�ڶ�������д��
	  wrcode0(h);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrdata(uint_8 j)
{
		busycheck();
		cd=0;     													//ѡ������ͨ��
		P0=j;
		wr=0;
		wr=1;
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void disptupian(uint_8 *p,uint_8 x,uint_8 y,uint_8 base,uint_8 pianyi)
{
		int i,j;
		for(i=0;i<y;i++)
		{
			lcdadress=base*30+pianyi+i*30+0x0800;
			setadr();
			for(j=0;j<x;j++)
			{
				wrcode1(*p,0xc0);
				p++;
			}
		}
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD��ʼ��
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void lcd_init()//LCD��ʼ��
{     
		uint_16 i;
		wrcode2(0x04,0x00,0x22);
		wrcode2(0x00,0x00,0x40);		//�ı����׵�ַ���ã�D1,D2,40H����0X0000
	  wrcode2(0x1e,0x00,0x41);		//�ı���������ã�D1,D2,41H����16�ֽ�ÿ��
	  wrcode2(0x00,0x08,0x42);		//ͼ�����׵�ַ���ã�D1,D2,42H)��0x0800
	  wrcode2(0x1e,0x00,0x43);		//ͼ�������(D1,D2,43H),30�ֽ�ÿ��
    wrcode0(0x80);         			//��ʾ��ʽ���ã��ڲ��ַ���������Ч���߼���ϳ�
	  wrcode0(0x9c);							//��ʾ����ָ�
	  wrcode0(0xa3);							//�����״ѡ��8��*7��
	  wrcode2(0x00,0x08,0x24);		//�Ƶ�ַָ��(D1,D2,24H),��ͼ����
	 	wrcode0(0xb0);          		//�Զ�д����,׼������
    for(i=0;i<2048;i++)     		//128*128��2048���ֽڣ�����
		{
    wrdata(0x00);
		}
    wrcode0(0xb2);
} 

void display()
{
		DistanceValue= DistanceStatistics();
		disptupian(HIT,16,128,0,0); 
		delay1ms(1000);
		disptupian(tupian,16,128,0,0); //���
		disptupian(jiansu,16,32,0,0); 
		disptupian(xiansu,16,96,32,0);  
		delay1ms(1000);
		disptupian(tupian,16,128,0,0); //���
		DistanceValue2=DistanceStatistics();
		speed=(int)((DistanceValue2-DistanceValue)/115);
		disptupian(nindesudu,16,32,0,0);
		switch(speed)
		{
			case	0:	
				disptupian(shu0,8,96,32,8);break;
			case	1:	
				disptupian(shu1,8,96,32,8);break;
			case	2:	
				disptupian(shu2,8,96,32,8);break;
			case	3:	
				disptupian(shu3,8,96,32,8);break;
			case	4:	
				disptupian(shu4,8,96,32,8);break;
			case	5:	
				disptupian(shu5,8,96,32,8);break;
			case	6:	
				disptupian(shu6,8,96,32,8);break;
			case	7:	
				disptupian(shu7,8,96,32,8);break;
			case	8:	
				disptupian(shu8,8,96,32,8);break;
			case	9:	
				disptupian(shu9,8,96,32,8);break;
			case	10:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	11:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	12:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	13:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	14:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	15:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	16:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	17:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	18:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	19:	
				disptupian(shu1,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	20:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	21:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	22:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	23:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	24:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	25:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	26:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	27:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	28:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	29:	
				disptupian(shu2,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	30:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	31:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	32:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	33:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	34:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	35:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	36:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	37:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	38:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	39:	
				disptupian(shu3,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	40:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	41:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	42:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	43:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	44:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	45:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	46:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	47:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	48:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	49:	
				disptupian(shu4,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	50:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	51:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	52:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	53:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	54:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	55:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	56:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	57:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	58:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	59:	
				disptupian(shu5,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	60:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	61:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	62:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	63:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	64:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	65:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	66:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	67:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	68:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	69:	
				disptupian(shu6,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	70:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	71:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	72:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	73:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	74:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	75:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	76:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	77:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	78:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	79:	
				disptupian(shu7,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	80:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	81:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	82:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	83:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	84:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	85:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	86:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	87:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	88:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	89:	
				disptupian(shu8,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			case	90:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu0,8,96,32,8);break;
			case	91:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu1,8,96,32,8);break;
			case	92:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu2,8,96,32,8);break;
			case	93:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu3,8,96,32,8);break;
			case	94:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu4,8,96,32,8);break;
			case	95:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu5,8,96,32,8);break;
			case	96:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu6,8,96,32,8);break;
			case	97:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu7,8,96,32,8);break;
			case	98:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu8,8,96,32,8);break;
			case	99:	
				disptupian(shu9,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
			default:
				disptupian(shu1,8,96,32,0);
				disptupian(shu9,8,96,32,8);break;
				}
			delay1ms(2000);
}