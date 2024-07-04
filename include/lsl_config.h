#ifndef LSL_CONFIG_H
#define LSL_CONFIG_H

/* Extra Includes */
#include "lsl_utils.h"

/* Abstraction Layer Includes */
#include "lsl_adc.h"
#include "lsl_digital.h"
#include "lsl_usart.h"

/* Libraries Level Includes */

/* Analog */
LSL_Pinout_t POTAR;
LSL_Pinout_t POTAR2;

/* Digital */
LSL_Pinout_t LED;                 // LED
LSL_Pinout_t Button;

/* USART */
LSL_Pinout_t Serial_Tx;
LSL_Pinout_t Serial_Rx;

/* Config Features */
void LSL_CONFIG_Init(void);
void LSL_CONFIG_Pinout(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode, uint8_t pupd);
void LSL_CONFIG_AFIO(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode, uint8_t pupd, uint8_t otype, uint8_t ospeed, uint8_t afio);

#endif // LSL_CONFIG_H