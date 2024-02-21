#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
//sfr AUXR =0x8E;
void Timer0Init(void)		//10����@11.0592MHz
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0xDC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}
void delay_10ms(){
	/*����tim�Ĺ���ģʽ*/
	TMOD=0x01;//00000001��16����
	/*����ʼֵ���綨10ms*/
	TL0=0x00;TH0=0xDC;
	/*��ʼ��ʱ*/
	TR0=1;
	TF0=0;
}
void main()
{
	int count=0;//����
	Timer0Init();
	while(1){
		if(TF0==1){//����
			TF0=0;//�����жϣ��������
			count++;
			TL0=0x00;TH0=0xDC;//���¸���ֵ
			if(count==100){//����100�Σ�����1s
				count=0;//����
				ledOne=!ledOne;//��תled
			}
		}
	}
}