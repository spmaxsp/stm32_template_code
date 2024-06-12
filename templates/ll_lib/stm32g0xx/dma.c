/**
 * @file dma.c
 * @brief ???
*/

// TEMPLATE CODE
// sets up a DMA to copy data from a peripheral to a memory buffer
// Requires the following to be defined/replaced:
// - DMA: the DMA peripheral to use
// - DMA_CHANNEL: the DMA channel to use
// - DMA_REQUEST: the DMA request to use
// - DMA_MEMBUFFER_SIZE: the size of the memory buffer
// * LL_XXXXX_DMA_GetRegAddr() needs to be replaced with the correct function
// * DMA_IRQHandler needs to be mapped to the correct interrupt handler

#include "dma.h"

uint8_t dma_Buffer[DMA_MEMBUFFER_SIZE];

void DMA_IRQHandler(void)
{
  //LL_DMA_ClearFlag_TC1(DMA);
  //LL_DMA_ClearFlag_TE1(DMA);
}

void DMA_Init(void)
{
  /* DMA Init */
	LL_DMA_SetDataTransferDirection(DMA, DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY );
	LL_DMA_SetChannelPriorityLevel( DMA, DMA_CHANNEL, LL_DMA_PRIORITY_LOW );
	LL_DMA_SetMode(                 DMA, DMA_CHANNEL, LL_DMA_MODE_NORMAL );
	LL_DMA_SetPeriphIncMode(        DMA, DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT );
	LL_DMA_SetMemoryIncMode(        DMA, DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT );
	LL_DMA_SetPeriphSize(           DMA, DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE );
	LL_DMA_SetMemorySize(           DMA, DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE );
	LL_DMA_EnableIT_TE(             DMA, DMA_CHANNEL );
  LL_DMA_EnableIT_TC(             DMA, DMA_CHANNEL );

  /* DMA Request configuration */
    LL_DMA_SetPeriphRequest(        DMA, DMA_CHANNEL, DMA_REQUEST);

  /* DMA Register and Memory address configuration */
	LL_DMA_ConfigAddresses(         DMA, DMA_CHANNEL, 
                                      LL_XXXXX_DMA_GetRegAddr(), (uint32_t)dma_Buffer, 
                                      LL_DMA_DIRECTION_PERIPH_TO_MEMORY); 
	LL_DMA_SetDataLength(           DMA, DMA_CHANNEL, DMA_MEMBUFFER_SIZE); 
}

void DMA_Enable(void)
{
  /* Enable DMA Channel */
    LL_DMA_EnableChannel(DMA, DMA_CHANNEL);
}

void DMA_Disable(void)
{
  /* Disable DMA Channel */
    LL_DMA_DisableChannel(DMA, DMA_CHANNEL);
}

void DMA_Reset(void)
{
  /* Reset DMA Channel */
    LL_DMA_DisableChannel(DMA, DMA_CHANNEL);
    LL_DMA_ClearFlag_TE1(DMA);
    LL_DMA_ClearFlag_TC1(DMA);
    LL_DMA_SetDataLength(           DMA, DMA_CHANNEL, DMA_MEMBUFFER_SIZE); 
    LL_DMA_EnableChannel(DMA, DMA_CHANNEL);
}

uint32_t DMA_GetRevievedDataLength(void)
{
  return DMA_MEMBUFFER_SIZE - LL_DMA_GetDataLength(DMA, DMA_CHANNEL);
}
