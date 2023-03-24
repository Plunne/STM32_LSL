#include "lsl_pinouts.h"

/* Enable */
void LSL_PINOUTS_Enable(GPIO_TypeDef *PORTx) {
    if (PORTx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable RCC for GPIOA
    else if (PORTx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable RCC for GPIOB
    else if (PORTx == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable RCC for GPIOC
    else if (PORTx == GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // Enable RCC for GPIOD
    else if (PORTx == GPIOE) RCC->APB2ENR |= RCC_APB2ENR_IOPEEN; // Enable RCC for GPIOE
}

/* Mode */
void LSL_PINOUTS_SetMode(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode) {
    if (pin < 8) PORTx->CRL |= (mode << (pin * 4)); // Set Mode for pins 0 -> 7
    else PORTx->CRH |= (mode << ((pin * 4) - 32));  // Set Mode for pins 8 -> 15
}

void LSL_PINOUTS_ClearMode(GPIO_TypeDef *PORTx, uint8_t pin) {
    if (pin < 8) PORTx->CRL &= ~(0xF << (pin * 4)); // Reset Mode for pins 0 -> 7
    else PORTx->CRH &= ~(0xF << ((pin * 4) - 32));  // Reset Mode for pins 8 -> 15
}

/* Pinout */
void LSL_PINOUTS_SetPinout(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode) {
    LSL_PINOUTS_Enable(PORTx);                      // Enable GPIO RCC
    LSL_PINOUTS_ClearMode(PORTx, pin);              // Reset GPIO Mode
    LSL_PINOUTS_SetMode(PORTx, pin, mode);          // Set GPIO Mode
}

void LSL_PINOUTS_InitPinout(LSL_Pinout *pinout) {
    LSL_PINOUTS_SetPinout(pinout->PORTx, pinout->pin, pinout->mode); // Set GPIO RCC & Mode
}