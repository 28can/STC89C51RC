#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"//_nop_
//*LED���Ŷ���*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*���ģ�����Ŷ���*/
sbit Echo =P1^6;
sbit Trig =P1^5;
void TimStart(){
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x00;				//���ö�ʱ��ʼֵ
	TH0 = 0x00;				//���ö�ʱ��ʼֵ
//	TF0 = 0;				//���TF0��־
//	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void StartHC(){
	Trig=0;
	Trig=1;
	Delay10ms();
	Trig=0;
}
void main()
{
	while(1){
		double time;
		double distance;
		TimStart();
		StartHC();
		while(Echo==0);//����ȥ
		TR0=1;//������ʱ����ʱ
		while(Echo==1);//������
		TR0=0;//ֹͣ��ʱ
		time=(TH0*256+TL0)*1.085;//us
		distance=time*0.034/2;//0.034cm/us:�ٶ�
		if(distance<10){
			ledOne=0;
			ledTwo=1;
		}else{
			ledOne=1;
			ledTwo=0;
		}
		//��ʱ������
		TL0 = 0x00;				//���ö�ʱ��ʼֵ
		TH0 = 0x00;
	}
}