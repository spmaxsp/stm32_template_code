/**
 * @file tim.h
 * @brief ???
*/

// TEMPLATE CODE
// Basic code for setting up a timer
// See the comments in tim.c for more information

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_tim.h"

/* Exported types ------------------------------------------------------------*/
void TIM_Init(void);
void TIM_Start(void);
void TIM_Stop(void);

#endif /* __TIM_H__ */