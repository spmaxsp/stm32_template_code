/**
 * @file gpio.c
 * @brief ???
*/

// TEMPLATE CODE
// sets up a GPIO_PIN as Digital-Output
// This serves just as a Starting-Point and needs further modifications

#include "gpio.h"

void GPIO_Init(void)
{
    /*Reset GPIO pin Output Level */
    LL_GPIO_ResetOutputPin(GPIO_PORT, GPIO_PIN);

    /*Configure LED GPIO pins */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);

}

void SetGPIO(int32_t state)
{
    if (state == LED_ON)
    {
        LL_GPIO_SetOutputPin(GPIO_PORT, GPIO_PIN);
    }
    else
    {
        LL_GPIO_ResetOutputPin(GPIO_PORT, GPIO_PIN);
    }
}