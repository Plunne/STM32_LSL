#ifndef __LSL_PINOUTS_H
#define __LSL_PINOUTS_H

#include "stm32f103xb.h"

#define INPUT_MODE      0x8
#define OUTPUT_MODE     0x1
#define ADC_MODE        0x0

typedef struct {
    GPIO_TypeDef *PORTx;
    uint8_t pin;
    uint8_t mode;
}LSL_Pinout;

/* Enable */
void LSL_PINOUTS_Enable(GPIO_TypeDef *PORTx);

/* Mode */
void LSL_PINOUTS_SetMode(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode);
void LSL_PINOUTS_ClearMode(GPIO_TypeDef *PORTx, uint8_t pin);

/* Pinout */
void LSL_PINOUTS_SetPinout(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode);
void LSL_PINOUTS_InitPinout(LSL_Pinout *pinout);

#endif // __LSL_PINOUTS_H