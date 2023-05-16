#ifndef LSL_DIGITAL_H
#define LSL_DIGITAL_H

#include "lsl_pinouts.h"
#include "lsl_utils.h"

typedef enum {LOW, HIGH, TOGGLE} LSL_DIGITAL_State_t;

/* Input */
uint8_t LSL_DIGITAL_Read(LSL_Pinout_t *pinout);

/* Output */
void LSL_DIGITAL_Write(LSL_Pinout_t *pinout, LSL_DIGITAL_State_t mode);
void LSL_DIGITAL_Set(LSL_Pinout_t *pinout);
void LSL_DIGITAL_Clear(LSL_Pinout_t *pinout);
void LSL_DIGITAL_Toggle(LSL_Pinout_t *pinout);

#endif // LSL_DIGITAL_H