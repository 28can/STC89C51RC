#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
int count=0;//计数
void Timer0Init(){
	/*配置tim的工作模式*/
	TMOD=0x01;//00000001的16进制
	/*给初始值，如定10ms*/
	TL0=0x00;TH0=0xDC;
	/*开始计时*/
	TR0=1;
	TF0=0;
	/*打开定时器中断*/
	ET0=1;//打开定时器0中断
	EA=1;//打开总中断
}
void main()
{
	Timer0Init();
	while(1){
	}
}
void Time0Handler() interrupt 1{
	//爆表进入一次中断
//	TF0=0;//不用中断，软件清零
	count++;
	TL0=0x00;TH0=0xDC;//重新给初值
	if(count==100){//爆表100次，经过1s
		count=0;//清零
		ledOne=!ledOne;//翻转led
	}
}