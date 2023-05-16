#ifndef LSL_PINOUTS_H
#define LSL_PINOUTS_H

#include "lsl_board.h"

#define INPUT_MODE      0b00
#define OUTPUT_MODE     0b01
#define ADC_MODE        0b11
#define USART_TX        0b10    // AFIO Mode
#define USART_RX        0b10    // AFIO Mode

#define NO_PULL         0b00
#define PULL_UP         0b01
#define PULL_DOWN       0b10

#define PUSH_PULL       0
#define OPEN_DRAIN      1

#define OSPEED_LOW      0b00
#define OSPEED_MEDIUM   0b01
#define OSPEED_FAST     0b10
#define OSPEED_HIGH     0b11

typedef struct {
    GPIO_TypeDef *PORTx;
    uint8_t pin;
    uint8_t mode;
    uint8_t pupd;
    uint8_t otype;
    uint8_t ospeed;
}LSL_Pinout_t;

/* Enable */
void LSL_PINOUTS_Enable(GPIO_TypeDef *PORTx);

/* Mode */
void LSL_PINOUTS_SetMode(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode);
void LSL_PINOUTS_ClearMode(GPIO_TypeDef *PORTx, uint8_t pin);

/* Input/Output Configuration */
void LSL_PINOUTS_SetPullUpDown(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t pupd);
void LSL_PINOUTS_SetOutputType(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t otype);
void LSL_PINOUTS_SetOutputSpeed(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t ospeed);

/* Pinout */
void LSL_PINOUTS_SetPinout(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode);
void LSL_PINOUTS_InitPinout(LSL_Pinout_t *pinout);

/* Advanced */
void LSL_PINOUTS_Advanced(LSL_Pinout_t *pinout, uint8_t pupd, uint8_t otype, uint8_t ospeed);

#endif // LSL_PINOUTS_H