#ifndef __LSL_ANALOG_H
#define __LSL_ANALOG_H

#include "lsl_pinouts.h"

/* Input */
void LSL_ANALOG_ADC_Start(ADC_TypeDef* ADC, uint8_t nbChannels);
void LSL_ANALOG_ADC_SetSequence(ADC_TypeDef* ADC, uint8_t sequence, uint8_t channel);
void LSL_ANALOG_ADC_Calibrate(ADC_TypeDef* ADC);
uint16_t LSL_ANALOG_ADC_Read(ADC_TypeDef* ADC);

/* Output */
void LSL_ANALOG_Write(LSL_Pinout *pinout);

#endif // __LSL_DIGITAL_H