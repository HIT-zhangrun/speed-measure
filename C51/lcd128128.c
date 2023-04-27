/*****************************************************
*@filename: 			lcd128128.c
*@description: 		显示页面控制
*@author: 				ZhangRun
*@version：				v1.0
*@date：					2021/6/17
*@note: 
****************************************************/
#include "lcd128128.h"
#include "zimo.h"


uint_16 	lcdadress;						//lcd地址
uint_8 		lcdh,lcdl;						//lcd地址高低

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
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
			cd=1;      								// 选择指令通道，准备读取通道状态
			rd=0;      								//读有效
			state=P0;
			rd=1;
		}
		while((state&0x03)!=0x03);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void setadr(void)           			//设定地址子程序
{
   lcdh=lcdadress/256;
   lcdl=lcdadress-lcdh*256;
   wrcode2(lcdl,lcdh,0x24);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode0(uint_8 h)						//无参数指令写入子程序
{
		busycheck();
		cd=1;      										//选择指令通道
    P0=h;
		wr=0;
		wr=1;
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode1(uint_8 i,uint_8 h)		//单参数指令写入子程序
{  
	 wrdata(i);
	 wrcode0(h);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrcode2(uint_8 i,uint_8 j,uint_8 h)//双参数指令写入子程序
{
		wrdata(i);            							//第一个参数写入
	  wrdata(j);           								//第二个参数写入
	  wrcode0(h);
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void wrdata(uint_8 j)
{
		busycheck();
		cd=0;     													//选择数据通道
		P0=j;
		wr=0;
		wr=1;
}

/*****************************************************
*@param: 				
*@return: 
*@function: 			LCD初始化
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
*@function: 			LCD初始化
*@author: 				ZhangRun
*@date: 					2021/6/17
*@note: 
****************************************************/
void lcd_init()//LCD初始化
{     
		uint_16 i;
		wrcode2(0x04,0x00,0x22);
		wrcode2(0x00,0x00,0x40);		//文本区首地址设置（D1,D2,40H），0X0000
	  wrcode2(0x1e,0x00,0x41);		//文本区宽度设置（D1,D2,41H），16字节每行
	  wrcode2(0x00,0x08,0x42);		//图形区首地址设置（D1,D2,42H)，0x0800
	  wrcode2(0x1e,0x00,0x43);		//图形区宽度(D1,D2,43H),30字节每行
    wrcode0(0x80);         			//显示方式设置，内部字符发生器有效，逻辑或合成
	  wrcode0(0x9c);							//显示开关指令，
	  wrcode0(0xa3);							//光标形状选择，8点*7行
	  wrcode2(0x00,0x08,0x24);		//移地址指针(D1,D2,24H),清图形区
	 	wrcode0(0xb0);          		//自动写设置,准备清零
    for(i=0;i<2048;i++)     		//128*128共2048个字节，清屏
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
		disptupian(tupian,16,128,0,0); //清空
		disptupian(jiansu,16,32,0,0); 
		disptupian(xiansu,16,96,32,0);  
		delay1ms(1000);
		disptupian(tupian,16,128,0,0); //清空
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