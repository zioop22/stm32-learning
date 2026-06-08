#include "stm32f10x.h"                  // Device header


void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  TIM_InternalClockConfig(TIM2);
	
	//时基部分
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
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




