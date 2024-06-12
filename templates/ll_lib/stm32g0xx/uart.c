/**
 * @file uart.c
 * @brief ???
*/

// TEMPLATE CODE
// sets up UART using DMA for RX and blocking calls for TX
// optional: use CharMatch to trigger an interrupt on a specific character (e.g. '\n')
// Requires the following to be defined/replaced:
// - USART: the USART peripheral to use
// - RX_TX_PORT: the GPIO port for the RX and TX pins
// - RX_PIN: the RX pin
// - TX_PIN: the TX pin
// - USART_BAUDRATE: the baudrate to use

// * USART_IRQHandler needs to be mapped to the correct interrupt handler

#include "uart.h"

// extern uint8_t dma_Buffer[DMA_MEMBUFFER_SIZE];

void USART_IRQHandler(void)   // Interrupt for UI_USART
{
  //LL_USART_ClearFlag_CM(USART);
}

void UART_Init(void)
{
  /*USART GPIO Configuration */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = RX_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init( RX_TX_PORT, &GPIO_InitStruct );

  GPIO_InitStruct.Pin = TX_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init( RX_TX_PORT, &GPIO_InitStruct );
  
  /* USART RX Interrupt Configuration */
  //LL_USART_EnableIT_CM(       UI_USART );      // Enable Character Match Interrupt for "\n"    
  //LL_USART_ConfigNodeAddress( UI_USART, LL_USART_ADDRESS_DETECT_7B, '\n' );

  /* USART Initialization */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = USART_BAUDRATE;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init( USART, &USART_InitStruct );

  /* USART Disable FIFO mode */
  LL_USART_SetTXFIFOThreshold( USART, LL_USART_FIFOTHRESHOLD_1_8 );
  LL_USART_SetRXFIFOThreshold( USART, LL_USART_FIFOTHRESHOLD_1_8 );
  LL_USART_DisableFIFO(        USART );

  /* USART Async Mode */
  LL_USART_ConfigAsyncMode(USART);

  /* USART DMA Enable */
  LL_USART_EnableDMAReq_RX(USART);

  /* USART Enable */
  LL_USART_Enable(USART);

  /* Polling USART1 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART))) || (!(LL_USART_IsActiveFlag_REACK(USART))))
  {
  }
}

void UART_TX_Blocking(uint8_t *tx_buff, uint32_t tx_size)
{
  uint32_t i = 0;
  for (i = 0; i < tx_size; i++)
  {
    while (!LL_USART_IsActiveFlag_TXE(USART));
    LL_USART_TransmitData8(USART, tx_buff[i]);
  }
  while (!LL_USART_IsActiveFlag_TC(USART));
}