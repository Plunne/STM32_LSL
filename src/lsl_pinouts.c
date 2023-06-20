#include "lsl_pinouts.h"

/* Enable */
void LSL_PINOUTS_Enable(GPIO_TypeDef *PORTx)
{
    if (PORTx == GPIOA) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; } // Enable RCC for GPIOA
    else if (PORTx == GPIOB) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; } // Enable RCC for GPIOB
    else if (PORTx == GPIOC) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; } // Enable RCC for GPIOC
    else if (PORTx == GPIOD) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; } // Enable RCC for GPIOD
    else if (PORTx == GPIOE) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; } // Enable RCC for GPIOE
    else if (PORTx == GPIOF) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; } // Enable RCC for GPIOF
    else if (PORTx == GPIOG) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; } // Enable RCC for GPIOG
    else if (PORTx == GPIOH) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN; } // Enable RCC for GPIOH
    else if (PORTx == GPIOI) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN; } // Enable RCC for GPIOI
    else if (PORTx == GPIOJ) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; } // Enable RCC for GPIOJ
    else if (PORTx == GPIOK) { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN; } // Enable RCC for GPIOK
    else {}
}

/* Mode */
void LSL_PINOUTS_ClearMode(GPIO_TypeDef *PORTx, uint8_t pin)
{
    PORTx->MODER &= ~(0b11 << (pin * 2)); // Set Mode for pins 0 -> 15
}

void LSL_PINOUTS_SetMode(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode)
{
    PORTx->MODER |= (mode << (pin * 2)); // Set Mode for pins 0 -> 15
}

/* Input/Output Configuration */
void LSL_PINOUTS_SetPullUpDown(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t pupd)
{
    PORTx->PUPDR &= ~(0b11 << (pin * 2));
    PORTx->PUPDR |= (pupd << (pin * 2));
}

void LSL_PINOUTS_SetOutputType(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t otype)
{
    PORTx->OTYPER &= ~(1 << pin);
    PORTx->OTYPER |= (otype << pin);
}

void LSL_PINOUTS_SetOutputSpeed(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t ospeed)
{
    PORTx->OSPEEDR &= ~(0b11 << (pin * 2));
    PORTx->OSPEEDR |= (ospeed << (pin * 2));
}

/* Pinout */
void LSL_PINOUTS_SetPinout(GPIO_TypeDef *PORTx, uint8_t pin, uint8_t mode)
{
    LSL_PINOUTS_Enable(PORTx);                      // Enable GPIO RCC
    LSL_PINOUTS_ClearMode(PORTx, pin);              // Reset GPIO Mode
    LSL_PINOUTS_SetMode(PORTx, pin, mode);          // Set GPIO Mode
}

void LSL_PINOUTS_InitPinout(LSL_Pinout_t *pinout)
{
    LSL_PINOUTS_SetPinout(pinout->PORTx, pinout->pin, pinout->mode);
}

/* Advanced */
void LSL_PINOUTS_Advanced(LSL_Pinout_t *pinout, uint8_t pupd, uint8_t otype, uint8_t ospeed)
{
    LSL_PINOUTS_SetPullUpDown(pinout->PORTx, pinout->pin, pinout->pupd);    // Set GPIO Pull Resistor
    LSL_PINOUTS_SetOutputType(pinout->PORTx, pinout->pin, pinout->otype);   // Set GPIO Output Type (output & AF only)
    LSL_PINOUTS_SetOutputSpeed(pinout->PORTx, pinout->pin, pinout->ospeed); // Set GPIO Output Speed (output & AF only)
}