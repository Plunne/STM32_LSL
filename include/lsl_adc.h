#ifndef LSL_ADC_H
#define LSL_ADC_H

#include "lsl_pinouts.h"

#define NB_ADC_CHANNELS 16

typedef struct {
    ADC_TypeDef *adc;
    uint8_t resolution;
    uint8_t nbChannels;
    LSL_Pinout_t *adc_pinout[NB_ADC_CHANNELS];
    uint16_t adc_channel[NB_ADC_CHANNELS];

} LSL_ADC_Handler_t;

/* Init */
void LSL_ADC_Init(LSL_ADC_Handler_t* ADC_Handler);
void LSL_ADC_InitSingle(LSL_ADC_Handler_t* ADC_Handler);

/* Setup */
void LSL_ADC_Setup(ADC_TypeDef* adc);
void LSL_ADC_SetupDMA(ADC_TypeDef* adc, uint16_t data_size, uint32_t* data);

/* Resolution */
void LSL_ADC_SetResolution(ADC_TypeDef* adc, uint8_t resolution);

/* Conversions */
void LSL_ADC_SetConvNumber(ADC_TypeDef* adc, uint8_t nbConv);

/* Sequences */
void LSL_ADC_SingleSequence(ADC_TypeDef* adc, uint8_t sequence, uint8_t channel);
void LSL_ADC_MultipleSequences(LSL_ADC_Handler_t* ADC_Handler);

/* Calibration */
void LSL_ADC_Calibrate(ADC_TypeDef* adc);

/* Enable */
void LSL_ADC_Enable(ADC_TypeDef* adc);

/* Read */
uint16_t LSL_ADC_Read(LSL_ADC_Handler_t* ADC_Handler, LSL_Pinout_t* pinout);
uint16_t LSL_ADC_ReadSingle(LSL_ADC_Handler_t* ADC_Handler);
uint16_t LSL_ADC_ReadSingleMax(LSL_ADC_Handler_t* ADC_Handler, uint8_t max);
uint16_t LSL_ADC_ReadSingleRange(LSL_ADC_Handler_t* ADC_Handler, uint16_t min, uint16_t max);

#endif // LSL_ADC_H