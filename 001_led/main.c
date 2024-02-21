#include "reg52.h"//—°‘ÒInter 8052±‡“Î
#include "intrins.h"
/*LED“˝Ω≈*/
sbit ledOne = P3^7;
sbit ledTwo = P3^6;
void main()
{
	ledOne = 0;
	ledTwo = 0;
}