#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
sbit vibrate = P3^3;//D0接线
sbit switcher = P1^1;//in接线
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
	if(vibrate==0){
		switcher=0;
		Delay2000ms();
		switcher=1;//高电平，继电器N0和com接通
	}else{
		switcher=1;
	}
}