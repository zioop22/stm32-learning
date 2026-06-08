//#include "stm32f10x.h"                  // Device header

//unsigned int Encoder_Count;

//void Encoder_Init()
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);

//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_Pin_0);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_Pin_1);
//	
//	EXTI_InitTypeDef	EXTI_InitStruct;
//	EXTI_InitStruct.EXTI_Line =EXTI_Line0 | EXTI_Line1;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger =EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStruct);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	
//}

//unsigned int Get()
//{
//	unsigned int Temp;
//	Temp = Encoder_Count;
//	Encoder_Count =0;
//	return Temp;
//	
//}
//void EXTI0_IRQHandler()
//{
//	if(EXTI_GetITStatus(EXTI_Line0) ==SET)
//	{
//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
//		{
//			Encoder_Count--;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line0);
//	}
//	
//}
//void EXTI1_IRQHandler()
//{
//	if(EXTI_GetITStatus(EXTI_Line1) ==SET)
//	{
//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
//		{
//			Encoder_Count++;
//		}

//		EXTI_ClearITPendingBit(EXTI_Line1);
//	}
//	
//}




#include "stm32f10x.h"

// 必须改成有符号！！
volatile int Encoder_Count = 0;

void Encoder_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_Pin_0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_Pin_1);
	
	EXTI_InitTypeDef	EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line =EXTI_Line0 | EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger =EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef  NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// 获取值（有符号）
int Get()
{
	int Temp;
	Temp = Encoder_Count;
	Encoder_Count =0;
	return Temp;
}

// A相 PB0 中断 ↓↓↓ 这里修复了！
void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 1)
		{
			Encoder_Count--;  // 反转
		}
		else
		{
			Encoder_Count++;  // 正转 (向右)
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

// B相 PB1 中断
void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
		{
			Encoder_Count--;  // 反转
		}
		else
		{
			Encoder_Count++;  // 正转 (向右)
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}



