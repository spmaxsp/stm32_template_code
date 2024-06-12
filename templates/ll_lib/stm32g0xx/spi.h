/**
 * @file spi.h
 * @brief ???
*/

// TEMPLATE CODE
// sets up basic SPI interface
// See the comments in spi.c for more information

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_spi.h"

/* Exported types ------------------------------------------------------------*/
void SPI_Init(void);
void SPI_Transmit(uint16_t data);
uint16_t SPI_Receive();

#endif /* __SPI_H__ */
