#include "reg52.h"//选择Inter 8052编译
#include "intrins.h"//_nop_
//*LED引脚定义*/
sbit ledOne    = P3^7;
sbit ledTwo    = P3^6;
/*测距模块引脚定义*/
sbit Echo      = P1^6;
sbit Trig      = P1^5;
/*舵机引脚定义*/
sbit sg90_con  = P1^1;
/*按键*/
sbit SW1       = P2^1;
/*振动传感器*/
sbit vibrate   = P3^2;
/*蜂鸣器引脚*/
sbit beep       =P2^0;
int jd;//角度
char jd_back;//记录上一次角度
int cnt             = 0;//爆表计数
char mark_vibrate   = 0;//震动传感器标志位
/*延迟150毫秒*/
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
/*延迟两秒*/
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
/*延迟300ms*/
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

/*延迟10ms*/
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

/*定时器0初始化*/
void Time0Init()
{
	//1. 配置定时器0工作模式位16位计时
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
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
/*定时器1初始化*/
void Time1Init(){
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0x00;				//设置定时初始值
	TH1 = 0x00;				//设置定时初始值
}
/*开始测距*/
void StartHC(){
	Trig=0;
	Trig=1;
	Delay10ms();
	Trig=0;
}
/*测距*/
double get_distance(){
	double time;
	//定时器清零
	TL1 = 0x00;				//设置定时初始值
	TH1 = 0x00;
	StartHC();
	while(Echo==0);//波出去
	TR1=1;//启动定时器计时
	while(Echo==1);//波回来
	TR1=0;//停止计时
	time=(TH1*256+TL1)*1.085;//us
	return (time*0.034/2);//0.034cm/us:速度
}
/*角度初始位*/
void initSG90_0(){
	jd       = 1;
	cnt      = 0;
	sg90_con = 1;
	
}
/*开盖*/
void OpenDusbin(){
	char n;
	jd    = 3; //90度 1.5ms高电平
	if(jd_back !=jd){
		cnt   = 0; 
		beep  = 0;
		for (n=0; n< 2; n++){
			Delay150ms();
		}
		beep  = 1;
		Delay2000ms();
	}
	jd_back = jd;
}
/*关盖*/
void OffDusbin(){
	jd = 1; //0度
	jd_back = jd;
	cnt = 0;
	Delay150ms();
}
/*开灯*/
void OpenStatusLight(){
	ledOne=0;
	ledTwo=1;
}
/*关灯*/
void OffStatusLight(){
	ledOne=1;
	ledTwo=0;
}
/*打开外部中断0*/
void EX0_Init(){
	EX0 = 1;
	IT0 = 0;//低电平触发
}
void main()
{
	double distance;
	
	Time0Init();
	Time1Init();
	
	EX0_Init();
	initSG90_0();
	while(1){
		distance=get_distance();
		if(distance<10 || SW1==0 || mark_vibrate==1){
			OpenStatusLight();
			OpenDusbin();
			mark_vibrate = 0;
		}else{
			OffStatusLight();
			OffDusbin();
		}
	}
}


/*定时器0中断*/
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
/**/
void EX0_Handler() interrupt 0
{
	mark_vibrate  =1;
}