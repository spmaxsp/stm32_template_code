/**
 * @file gpio.h
 * @brief ???
*/

// TEMPLATE CODE
// sets up a GPIO_PIN as Digital-Output
// See the comments in gpio.c for more information

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_gpio.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  LED_OFF = 0,
  LED_ON = 1
} LED_StateTypeDef;

void GPIO_Init(void);
void SetGPIO(int32_t state);

#endif /* __GPIO_H__ */