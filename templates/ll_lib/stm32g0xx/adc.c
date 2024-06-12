/**
 * @file adc.c
 * @brief ???
*/

// TEMPLATE CODE
// sets up an adc and sequencer for sampling two channels triggered by a timer
// This example is on the more complicated side and can be modified and in most cases even simplified

#include "adc.h"

void ADC_Init(void){

    /* ADC1 GPIO Configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = ANALOG_1_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(ANALOG_1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ANALOG_2_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(ANALOG_2_PORT, &GPIO_InitStruct);

    /* Initialize ADC */
    LL_ADC_InitTypeDef ADC_InitStruct = {0};
    ADC_InitStruct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
    ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
    LL_ADC_Init(ANALOG_ADC, &ADC_InitStruct);

    LL_ADC_REG_SetSequencerConfigurable(ANALOG_ADC, LL_ADC_REG_SEQ_CONFIGURABLE);

    /* Poll for ADC channel configuration ready */
    while (LL_ADC_IsActiveFlag_CCRDY(ANALOG_ADC) == 0)
    {
    }

    /* Clear flag ADC channel configuration ready */
    LL_ADC_ClearFlag_CCRDY(ANALOG_ADC);

    /* Configure ADC regular channel */
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
    ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_EXT_TIM2_TRGO;          // Triggered by Timer 2
    ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;      // Sequencer running the whole sequence
    ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;                // Sequencer is not restarted after sequence is finished
    ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
    ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
    LL_ADC_REG_Init(ANALOG_ADC, &ADC_REG_InitStruct);
    LL_ADC_SetOverSamplingScope(ANALOG_ADC, LL_ADC_OVS_DISABLE);
    LL_ADC_SetTriggerFrequencyMode(ANALOG_ADC, LL_ADC_CLOCK_FREQ_MODE_HIGH);
    LL_ADC_DisableIT_EOC(ANALOG_ADC);
    LL_ADC_DisableIT_EOS(ANALOG_ADC);

    /* Enable ADC internal voltage regulator */
    LL_ADC_EnableInternalRegulator(ANALOG_ADC);

    /* Configure Channels */
    LL_ADC_REG_SetSequencerRanks(ANALOG_ADC, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_6);
    LL_ADC_REG_SetSequencerRanks(ANALOG_ADC, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_8);
    
    /* Configure Sampling times */
    LL_ADC_SetSamplingTimeCommonChannels(ANALOG_ADC, LL_ADC_SAMPLINGTIME_COMMON_1, LL_ADC_SAMPLINGTIME_160CYCLES_5);
    LL_ADC_SetChannelSamplingTime(ANALOG_ADC, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_COMMON_1);
    LL_ADC_SetChannelSamplingTime(ANALOG_ADC, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_COMMON_1);

    /* Poll for ADC channel configuration ready */
    while (LL_ADC_IsActiveFlag_CCRDY(ANALOG_ADC) == 0)
    {
    }

    /* Enable ADC */
    LL_ADC_Enable(ANALOG_ADC);

    /* Wait for ADC ready */
    while (!LL_ADC_IsActiveFlag_ADRDY(ANALOG_ADC)) 
    {
    } 
}

void ADC_Start(void){
    LL_ADC_REG_StartConversion(ANALOG_ADC);
}

void ADC_Stop(void){
    LL_ADC_REG_StopConversion(ANALOG_ADC);
}