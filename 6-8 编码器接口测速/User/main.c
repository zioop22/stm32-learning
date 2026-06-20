#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "Timer.h"
#include "OLED.h"
#include "Delay.h"

//int16_t Speed;        // 速度（每秒脉冲数）
//int16_t LastCount;    // 上一次计数值

int main(void)
{
    OLED_Init();
    Encoder_Init();
//    Timer_Init();

    OLED_ShowString(1, 1, "Speed:");

    while(1)
    {
        OLED_ShowSignedNum(2, 1, Encoder_Get(), 5);
        Delay_ms(1000);  // 100ms刷新一次
    }
}

// TIM2 每秒中断一次，计算速度
//void TIM2_IRQHandler()
//{
//    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//    {
//        int16_t CurrentCount = (int16_t)Encoder_Get();
//        Speed = CurrentCount - LastCount;  // 差值 = 每秒脉冲数
//        LastCount = CurrentCount;
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//    }
//}
