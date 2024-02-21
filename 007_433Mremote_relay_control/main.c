#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
sbit D0_ON = P1^2;
sbit D1_OFF = P1^3;
sbit switcher = P1^1; //in接线
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
	while(1){
		if(D0_ON==1){ //按键A按下，高电平
			switcher=0; //继电器导通
		}
		if(D1_OFF==1){ //按键B按下，高电平
			switcher=1; //继电器不导通
		}
	}
}