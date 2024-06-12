/**
 * @file dma.h
 * @brief ???
*/

// TEMPLATE CODE
// sets up a DMA to copy data from a peripheral to a memory buffer
// See the comments in dma.c for more information

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA_H__
#define __DMA_H__

// #include "hw_config.h" // i like to define my hardware here

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_dma.h"
// #include "stm32g0xx_ll_usart.h" // replace with the correct peripheral header

/* Exported types ------------------------------------------------------------*/
void DMA_IRQHandler(void);

void DMA_Init(void);
void DMA_Enable(void);
void DMA_Disable(void);
void DMA_Reset(void);

uint32_t DMA_GetRevievedDataLength(void);

#endif /* __DMA_H__ */