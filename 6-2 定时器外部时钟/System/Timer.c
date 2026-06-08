#include "stm32f10x.h"                  // Device header


void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef GPIO_InitSructure;
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);

	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	//时基部分
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//开启更新中断到NVIC的通路
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel =TIM2_IRQn ;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority =2 ;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
}
uint16_t Timer_GetCounter()
{
	return TIM_GetCounter(TIM2);
}

/*
void TIM2_IRQHandler()
{
	//更新中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}
*/




