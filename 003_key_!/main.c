#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h" 

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
sbit key1 = P2^1;
sbit key2 = P2^0;
void delay_50ms(){		//@11.0592MHz//�ӳ�50����
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do{
		do{
			while (--k);
		} while (--j);
	} while (--i);
}
void main()
{
	ledOne=1;
	while(1){
		if(key1==0){//����
			delay_50ms();
			if(key1==0){
				ledOne=!ledOne;//����
			}
		}
	}
}