#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"

sbit ledOne = P3^7;
sbit ledTwo = P3^6;
int count=0;//����
void Timer0Init(){
	/*����tim�Ĺ���ģʽ*/
	TMOD=0x01;//00000001��16����
	/*����ʼֵ���綨10ms*/
	TL0=0x00;TH0=0xDC;
	/*��ʼ��ʱ*/
	TR0=1;
	TF0=0;
	/*�򿪶�ʱ���ж�*/
	ET0=1;//�򿪶�ʱ��0�ж�
	EA=1;//�����ж�
}
void main()
{
	Timer0Init();
	while(1){
	}
}
void Time0Handler() interrupt 1{
	//�������һ���ж�
//	TF0=0;//�����жϣ��������
	count++;
	TL0=0x00;TH0=0xDC;//���¸���ֵ
	if(count==100){//����100�Σ�����1s
		count=0;//����
		ledOne=!ledOne;//��תled
	}
}