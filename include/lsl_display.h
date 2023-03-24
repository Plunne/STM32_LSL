#ifndef __LSL_DISPLAY_H
#define __LSL_DISPLAY_H

#include "lsl_io.h"

#define DIODE_NB    7

enum DiodeCOM { anode, cathode };

/* 7 Segments */
uint8_t LSL_DISPLAY_Get7Seg(uint8_t number);
void LSL_DISPLAY_Display7Seg(LSL_Pinout *diode, uint8_t number, enum DiodeCOM common);
void LSL_DISPLAY_Display7SegAnodeCathode(LSL_Pinout *diode, uint8_t number, enum DIGITAL_STATE stateA, enum DIGITAL_STATE stateB);

#endif // __LSL_DISPLAY_H