#include "reg52.h"

sbit sg90_con = P1^1;
int jd;
int cnt = 0;


void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

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


void Time0Init()
{
	//1. ���ö�ʱ��0����ģʽλ16λ��ʱ
	TMOD = 0x01;
	//2. ����ֵ����һ��0.5����
	TL0=0x33;
	TH0=0xFE;
	//3. ��ʼ��ʱ
	TR0 = 1;
	TF0 = 0;
	//4. �򿪶�ʱ��0�ж�
	ET0 = 1;
	//5. �����ж�EA
	EA = 1;
}

void Delay300ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 3;
	j = 26;
	k = 223;
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
	Delay300ms();//��Ӳ���ȶ�һ��
	Time0Init(); //��ʼ����ʱ��
	jd = 1;      //��ʼ�Ƕ���0�ȣ�0.5ms,���1����0.5���ߵ�ƽ
	sg90_con = 1;//һ��ʼ�Ӹߵ�ƽ��ʼ
	//ÿ�������л�һ�νǶ�
	while(1){
		jd = 3; //90�� 1.5ms�ߵ�ƽ
		cnt = 0; 
		Delay2000ms();
		jd = 1; //0��
		cnt = 0;
		Delay2000ms();
	}
}

void Time0Handler() interrupt 1
{
	cnt++;  //ͳ�Ʊ���Ĵ���. cnt=1��ʱ�򣬱�����1
	//���¸���ֵ
	TL0=0x33;
	TH0=0xFE;
	//����PWM��
	if(cnt < jd){
		sg90_con = 1;
	}else{
		sg90_con = 0;
	}
	/*����*/
	if(cnt == 40){//����40�Σ�������20ms
		cnt = 0;  //��100�α�ʾ1s��������cnt��0��ʼ��������һ�ε�1s
		sg90_con = 1;//�ػظߵ�ƽ
	}
		
}