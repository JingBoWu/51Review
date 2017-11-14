#include <reg52.h>
#include <intrins.h>
unsigned char led = 0xFF;
//unsigned int i , j , k;
//unsigned char k;

void delay(unsigned int i)
{
  unsigned int j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--)
		_nop_();
}
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}



void main()
{
	P1 = 0xFF;
	
	while(1)
	{
		led = led << 1;
		if(led == 0) 
		{
			  led = 0xff;
		}
		//delay(1);	
		//Delay1000ms();
		Delay1ms()	;

		P1 = led;
	}

}
