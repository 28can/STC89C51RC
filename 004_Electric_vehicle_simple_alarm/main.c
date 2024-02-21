//警报按键按下时，在延迟时间内无法实行警报代码，即振动模块控制警报
#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"

#define J_ON 1
#define J_OFF 0
/*led*/
sbit ledOne = P3^7;//led1
sbit ledTwo = P3^6;//led2
/*振动传感器*/
sbit vibrate = P3^3;//D0
/*继电器*/
sbit switcher = P1^1;//in
/*遥控*/
sbit D0_ON = P1^2;//D0
sbit D1_OFF = P1^3;//D1

void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main()
{
	int mark=0;
	while(1){
		if(D0_ON==1){//进入警报模式
			switcher=0;//提示进入警报模式
			Delay2000ms();
			switcher=1;
			mark=J_ON;
		}
		if(D1_OFF==1){//解除警报模式
			switcher=0;//提示解除警报模式
			Delay2000ms();
			switcher=1;
			mark=J_OFF;
		}
		if(mark){//警报模式下
			if(vibrate==0){//如果发生震动
				switcher=0;//警报
			}else{
				switcher=1;
			}
		}
	}
}