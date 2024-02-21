#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"
/*LED引脚*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*串口*/
//sfr AUXR = 0x8E;//声明
/*延迟1000秒*/
void Delay1000ms(){		//@11.0592MHz
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/*串口1初始化*/
void UartInit(void){		//9600bps@11.0592MHz
	AUXR = 0x01;
	SCON = 0x40;		//选择串口工作方式1
	TMOD &= 0xF0;
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		
	TH1 = 0xFD;		//设定9600波特率
	TR1 = 1;		//启动定时器1
}
/**/
void main(){
	char data_msg= 'a';
	UartInit();
	while(1){
		Delay1000ms();
		SBUF =data_msg;
	}
}
