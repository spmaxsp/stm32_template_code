/**
 * @file adc.h
 * @brief ???
*/

// TEMPLATE CODE
// sets up an adc and sequencer for sampling two channels triggered by a timer
// See the comments in adc.c for more information


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_spi.h"

/* Exported types ------------------------------------------------------------*/
void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);

#endif /* __ADC_H__ */