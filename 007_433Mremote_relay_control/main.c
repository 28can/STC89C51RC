#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
sbit D0_ON = P1^2;
sbit D1_OFF = P1^3;
sbit switcher = P1^1; //in����
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
		if(D0_ON==1){ //����A���£��ߵ�ƽ
			switcher=0; //�̵�����ͨ
		}
		if(D1_OFF==1){ //����B���£��ߵ�ƽ
			switcher=1; //�̵�������ͨ
		}
	}
}