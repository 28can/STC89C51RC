#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"
/*LED����*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*����*/
//sfr AUXR = 0x8E;//����
/*�ӳ�1000��*/
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
/*����1��ʼ��*/
void UartInit(void){		//9600bps@11.0592MHz
	AUXR = 0x01;
	SCON = 0x40;		//ѡ�񴮿ڹ�����ʽ1
	TMOD &= 0xF0;
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		
	TH1 = 0xFD;		//�趨9600������
	TR1 = 1;		//������ʱ��1
}
/**/
void main(){
	char data_msg= 'a';
	UartInit();
	while(1){
		Delay1000ms();
		SBUF =data_msg;
	}
}
