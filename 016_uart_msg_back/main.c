#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"
/*LED引脚*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*延迟10毫秒*/
void Delay10ms(){		//@11.0592MHz
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}
/*延迟1000毫秒*/
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
	SCON = 0x50;		//选择串口工作方式1，使能REN
	TMOD &= 0xF0;
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		
	TH1 = 0xFD;		//设定9600波特率
	TR1 = 1;		//启动定时器1
}
/*发送字符*/
void sendByte(char data_msg){
	SBUF =data_msg;
	//Delay10ms();
	while(!TI);
	TI = 0;
}
/*发送字符串*/
void sendString(char* str){
	while(*str != '\0'){
		sendByte(*str);
		str++;
	}
}
void main(){
	char cmd;
	ledOne = 1;
	UartInit();
	while(1){
		Delay1000ms();
		sendString("hello world!\r\n");
		/*查询RI的值*/
		if(RI == 1){
			RI = 0;
			cmd = SBUF;
			if(cmd == 'o'){
				ledOne = 0;
			}
			if(cmd == 'c'){
				ledOne = 1;
			}
		}
	}
}
