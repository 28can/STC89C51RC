//������������ʱ�����ӳ�ʱ�����޷�ʵ�о������룬����ģ����ƾ���
#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"

#define J_ON 1
#define J_OFF 0
/*led*/
sbit ledOne = P3^7;//led1
sbit ledTwo = P3^6;//led2
/*�񶯴�����*/
sbit vibrate = P3^3;//D0
/*�̵���*/
sbit switcher = P1^1;//in
/*ң��*/
sbit D0_ON = P1^2;//D0
sbit D1_OFF = P1^3;//D1

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
	int mark=0;
	while(1){
		if(D0_ON==1){//���뾯��ģʽ
			switcher=0;//��ʾ���뾯��ģʽ
			Delay2000ms();
			switcher=1;
			mark=J_ON;
		}
		if(D1_OFF==1){//�������ģʽ
			switcher=0;//��ʾ�������ģʽ
			Delay2000ms();
			switcher=1;
			mark=J_OFF;
		}
		if(mark){//����ģʽ��
			if(vibrate==0){//���������
				switcher=0;//����
			}else{
				switcher=1;
			}
		}
	}
}