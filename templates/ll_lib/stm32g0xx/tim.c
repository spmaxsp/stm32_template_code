/**
 * @file tim.c
 * @brief ???
*/

// TEMPLATE CODE
// Basic code for setting up a timer
// This serves just as a Starting-Point and needs further modifications

#include "tim.h"

void TIM_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = 64;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 1000;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIMER, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIMER);
    LL_TIM_SetClockSource(TIMER, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_SetTriggerOutput(TIMER, LL_TIM_TRGO_UPDATE);
    LL_TIM_DisableMasterSlaveMode(TIMER);
}

void TIM_Start(void)
{
    LL_TIM_EnableCounter(TIMER);
}

void TIM_Stop(void)
{
    LL_TIM_DisableCounter(TIMER);
}