/**
 * @file uart.h
 * @brief ???
*/

// TEMPLATE CODE
// sets up UART using DMA for RX and blocking calls for TX
// See the comments in uart.c for more information

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_dma.h"

/* Exported types ------------------------------------------------------------*/
void UART_IRQHandler(void);

void UART_Init(void);
void UART_TX_Blocking(uint8_t *tx_buff, uint32_t tx_size);

#endif /* __UART_H__ */