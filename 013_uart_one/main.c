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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
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
