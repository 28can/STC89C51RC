#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"//_nop_
//*LED引脚定义*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*测距模块引脚定义*/
sbit Echo =P1^6;
sbit Trig =P1^5;
void TimStart(){
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0x00;				//设置定时初始值
//	TF0 = 0;				//清除TF0标志
//	TR0 = 1;				//定时器0开始计时
}
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void StartHC(){
	Trig=0;
	Trig=1;
	Delay10ms();
	Trig=0;
}
void main()
{
	while(1){
		double time;
		double distance;
		TimStart();
		StartHC();
		while(Echo==0);//波出去
		TR0=1;//启动定时器计时
		while(Echo==1);//波回来
		TR0=0;//停止计时
		time=(TH0*256+TL0)*1.085;//us
		distance=time*0.034/2;//0.034cm/us:速度
		if(distance<10){
			ledOne=0;
			ledTwo=1;
		}else{
			ledOne=1;
			ledTwo=0;
		}
		//定时器清零
		TL0 = 0x00;				//设置定时初始值
		TH0 = 0x00;
	}
}