#include "reg52.h"//ѡ��Inter 8052����
#include "intrins.h"
/*LED����*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
void main()
{
	ledOne = 0;
	ledTwo = 0;
}