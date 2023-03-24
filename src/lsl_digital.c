#include "lsl_digital.h"

/* Input */
uint8_t LSL_DIGITAL_Read(LSL_Pinout *pinout) {
    return (pinout->PORTx->IDR & (1 << pinout->pin));   // Read a digital input
}

/* Output */
void LSL_DIGITAL_Write(LSL_Pinout *pinout, enum DIGITAL_STATE mode) {
    
    switch (mode)
    {
    case LOW:
        LSL_DIGITAL_Clear(pinout);
        break;
    case HIGH:
        LSL_DIGITAL_Set(pinout);
        break;
    case TOGGLE:
        LSL_DIGITAL_Toggle(pinout);
        break;
    
    default:
        break;
    }
}

void LSL_DIGITAL_Set(LSL_Pinout *pinout) {
    pinout->PORTx->ODR |= (1 << pinout->pin);   // Set pinout HIGH
}

void LSL_DIGITAL_Clear(LSL_Pinout *pinout) {
    pinout->PORTx->ODR &= ~(1 << pinout->pin);  // Clear pinout LOW
}

void LSL_DIGITAL_Toggle(LSL_Pinout *pinout) {
    pinout->PORTx->ODR ^= (1 << pinout->pin);   // Toggle pinout (Swap HIGH/LOW)
}