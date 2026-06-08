#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "Delay.h"

int main(void)
{
	unsigned int i;

	OLED_Init();
	PWM_Init();
	while(1)
	{
		// 渐亮
		for(i = 0; i < 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		// 渐暗
		for(i = 99; i > 0; i--)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
	}
}
