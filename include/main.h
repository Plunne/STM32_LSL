#ifndef __MAIN_H
#define __MAIN_H

#include "lsl_pinouts.h"

static LSL_Pinout POTAR = { GPIOA, 7, ADC_MODE };
static LSL_Pinout LED = { GPIOA, 5, OUTPUT_MODE };

#endif // __MAIN_H