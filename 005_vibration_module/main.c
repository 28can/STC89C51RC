#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
sbit vibrate = P3^3;//D0����
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
		ledOne=0;//����
		Delay2000ms();
	}else{
		ledOne=1;//���
	}
}