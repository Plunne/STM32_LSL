#ifndef __LSL_DIGITAL_H
#define __LSL_DIGITAL_H

#include "lsl_pinouts.h"

enum DIGITAL_STATE {LOW, HIGH, TOGGLE};

/* Input */
uint8_t LSL_DIGITAL_Read(LSL_Pinout *pinout);

/* Output */
void LSL_DIGITAL_Write(LSL_Pinout *pinout, enum DIGITAL_STATE mode);
void LSL_DIGITAL_Set(LSL_Pinout *pinout);
void LSL_DIGITAL_Clear(LSL_Pinout *pinout);
void LSL_DIGITAL_Toggle(LSL_Pinout *pinout);

#endif // __LSL_DIGITAL_H