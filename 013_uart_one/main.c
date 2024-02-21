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
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
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
