#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"
/*LED����*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
/*�ӳ�10����*/
void Delay10ms(){		//@11.0592MHz
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}
/*�ӳ�1000����*/
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
	SCON = 0x50;		//ѡ�񴮿ڹ�����ʽ1��ʹ��REN
	TMOD &= 0xF0;
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		
	TH1 = 0xFD;		//�趨9600������
	TR1 = 1;		//������ʱ��1
}
/*�����ַ�*/
void sendByte(char data_msg){
	SBUF =data_msg;
	//Delay10ms();
	while(!TI);
	TI = 0;
}
/*�����ַ���*/
void sendString(char* str){
	while(*str != '\0'){
		sendByte(*str);
		str++;
	}
}
void main(){
	char cmd;
	ledOne = 1;
	UartInit();
	while(1){
		Delay1000ms();
		sendString("hello world!\r\n");
		/*��ѯRI��ֵ*/
		if(RI == 1){
			RI = 0;
			cmd = SBUF;
			if(cmd == 'o'){
				ledOne = 0;
			}
			if(cmd == 'c'){
				ledOne = 1;
			}
		}
	}
}