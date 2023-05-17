#ifndef LSL_CONFIG_H
#define LSL_CONFIG_H

/* Extra Includes */
#include "lsl_utils.h"

/* Abstraction Layer Includes */
#include "lsl_adc.h"
#include "lsl_digital.h"

/* Libraries Level Includes */

/* Analog */
LSL_Pinout_t POTAR;
LSL_Pinout_t POTAR2;

/* Digital */
LSL_Pinout_t LED;                 // LED
LSL_Pinout_t Button;

/* USART */

/* Config Features */
void LSL_CONFIG_Init(void);
void LSL_CONFIG_Pinout(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode);

#endif // LSL_CONFIG_H