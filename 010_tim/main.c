#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
//sfr AUXR =0x8E;
void Timer0Init(void)		//10毫秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xDC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}
void delay_10ms(){
	/*配置tim的工作模式*/
	TMOD=0x01;//00000001的16进制
	/*给初始值，如定10ms*/
	TL0=0x00;TH0=0xDC;
	/*开始计时*/
	TR0=1;
	TF0=0;
}
void main()
{
	int count=0;//计数
	Timer0Init();
	while(1){
		if(TF0==1){//爆表
			TF0=0;//不用中断，软件清零
			count++;
			TL0=0x00;TH0=0xDC;//重新给初值
			if(count==100){//爆表100次，经过1s
				count=0;//清零
				ledOne=!ledOne;//翻转led
			}
		}
	}
}