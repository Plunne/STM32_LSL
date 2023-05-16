#ifndef LSL_ADC_H
#define LSL_ADC_H

#include "lsl_pinouts.h"

#define NB_ADC_CHANNELS 16

typedef struct {
    ADC_TypeDef *adc;
    uint8_t nbChannels;
    LSL_Pinout *adc_pinout[NB_ADC_CHANNELS];
    uint16_t adc_channel[NB_ADC_CHANNELS];

} LSL_ADC_Handler;

/* Init */
void LSL_ADC_Init(LSL_ADC_Handler* ADC_Handler);
void LSL_ADC_InitSingle(LSL_ADC_Handler* ADC_Handler);

/* Setup */
void LSL_ADC_Setup(ADC_TypeDef* ADC);
void LSL_ADC_SetupDMA(ADC_TypeDef* ADC, uint16_t data_size, uint32_t* data);

/* Covnersions */
void LSL_ADC_SetConvNumber(ADC_TypeDef* ADC, uint8_t nbConv);

/* Sequences */
void LSL_ADC_SingleSequence(ADC_TypeDef* ADC, uint8_t sequence, uint8_t channel);
void LSL_ADC_MultipleSequences(LSL_ADC_Handler* ADC_Handler);

/* Calibration */
void LSL_ADC_Calibrate(ADC_TypeDef* ADC);

/* Enable */
void LSL_ADC_Enable(ADC_TypeDef* ADC);

/* Read */
uint16_t LSL_ADC_Read(LSL_ADC_Handler* ADC_Handler, LSL_Pinout* pinout);
uint16_t LSL_ADC_ReadSingle(LSL_ADC_Handler* ADC_Handler);
uint16_t LSL_ADC_ReadSingleMax(LSL_ADC_Handler* ADC_Handler, uint8_t max);
uint16_t LSL_ADC_ReadSingleRange(LSL_ADC_Handler* ADC_Handler, uint16_t min, uint16_t max);

#endif // LSL_ADC_H