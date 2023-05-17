#ifndef LSL_INIT_H
#define LSL_INIT_H

#include "lsl_config.h"

/* Init All */
void LSL_Init_Registers(void);

/* Init Features */
void LSL_Init_RCC(void);
void LSL_Init_GPIO(void);
void LSL_Init_ADC(void);
void LSL_Init_USART(void);
void LSL_Init_TIMERS(void);

/* Analog Handler */
LSL_ADC_Handler LSL_INIT_ADC1;
/* USART Handler */
// LSL_USART_Handler LSL_INIT_USART2;

/* Timer Handler */
// LSL_TIMER_Handler LSL_INIT_TIMER2;

#endif // LSL_INIT_H