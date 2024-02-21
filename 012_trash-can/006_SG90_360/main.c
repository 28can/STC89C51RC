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
	//1. 配置定时器0工作模式位16位计时
	TMOD = 0x01;
	//2. 给初值，定一个0.5出来
	TL0=0x33;
	TH0=0xFE;
	//3. 开始计时
	TR0 = 1;
	TF0 = 0;
	//4. 打开定时器0中断
	ET0 = 1;
	//5. 打开总中断EA
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
	Delay300ms();//让硬件稳定一下
	Time0Init(); //初始化定时器
	jd = 1;      //初始角度是0度，0.5ms,溢出1就是0.5，高电平
	sg90_con = 1;//一开始从高电平开始
	//每隔两秒切换一次角度
	while(1){
		jd = 3; //90度 1.5ms高电平
		cnt = 0; 
		Delay2000ms();
		jd = 1; //0度
		cnt = 0;
		Delay2000ms();
	}
}

void Time0Handler() interrupt 1
{
	cnt++;  //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL0=0x33;
	TH0=0xFE;
	//控制PWM波
	if(cnt < jd){
		sg90_con = 1;
	}else{
		sg90_con = 0;
	}
	/*周期*/
	if(cnt == 40){//爆表40次，经过了20ms
		cnt = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
		sg90_con = 1;//重回高电平
	}
		
}