#include "stm32f10x.h"                  // Device header
#include "Delay.h"
unsigned char i;
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	while(1)
	{
//		GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0004);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0008);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0010);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0020);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0040);//0000 0000 0000 0001
//		Delay_ms(200);
//		GPIO_Write(GPIOA,~0x0080);//0000 0000 0000 0001
//		Delay_ms(200);
		for(i=0;i<8;i++)
		{
			GPIO_Write(GPIOA,~(0x0001<<i));//0000 0000 0000 0001
			Delay_ms(200);
		}
	}
	
}
