#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"//_nop_
//*LED���Ŷ���*/
sbit ledOne    = P3^7;
sbit ledTwo    = P3^6;
/*���ģ�����Ŷ���*/
sbit Echo      = P1^6;
sbit Trig      = P1^5;
/*������Ŷ���*/
sbit sg90_con  = P1^1;

int jd;
int cnt = 0;
/*�ӳ�150����*/
void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/*�ӳ�����*/
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
/*�ӳ�300ms*/
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

/*�ӳ�10ms*/
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

/*��ʱ��0��ʼ��*/
void Time0Init()
{
	//1. ���ö�ʱ��0����ģʽλ16λ��ʱ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
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
/*��ʱ��1��ʼ��*/
void Time1Init(){
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	TMOD |= 0x10;			//���ö�ʱ��ģʽ
	TL1 = 0x00;				//���ö�ʱ��ʼֵ
	TH1 = 0x00;				//���ö�ʱ��ʼֵ
}
/*��ʼ���*/
void StartHC(){
	Trig=0;
	Trig=1;
	Delay10ms();
	Trig=0;
}
/*���*/
double get_distance(){
	double time;
	//��ʱ������
	TL1 = 0x00;				//���ö�ʱ��ʼֵ
	TH1 = 0x00;
	StartHC();
	while(Echo==0);//����ȥ
	TR1=1;//������ʱ����ʱ
	while(Echo==1);//������
	TR1=0;//ֹͣ��ʱ
	time=(TH1*256+TL1)*1.085;//us
	return (time*0.034/2);//0.034cm/us:�ٶ�
}
/*����*/
void OpenDusbin(){
	jd = 3; //90�� 1.5ms�ߵ�ƽ
	cnt = 0; 
	Delay2000ms();
}
/*����*/
void OffDusbin(){
	jd = 1; //0��
	cnt = 0;
	Delay150ms();
}
/*����*/
void OpenStatusLight(){
	ledOne=0;
	ledTwo=1;
}
/*�ص�*/
void OffStatusLight(){
	ledOne=1;
	ledTwo=0;
}

void main()
{
	double distance;
	
	Time0Init();
	Time1Init();
	
//	initSG90_0();
	while(1){
		distance=get_distance();
		if(distance<10){
			OpenStatusLight();
			OpenDusbin();
		}else{
			OffStatusLight();
			OffDusbin();
		}
	}
}


/*��ʱ��0�ж�*/
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