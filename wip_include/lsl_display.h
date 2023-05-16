#ifndef LSL_DISPLAY_H
#define LSL_DISPLAY_H

#include "lsl_digital.h"

#define DIODE_NB    8

typedef enum { anode, cathode } LSL_DISPLAY_DiodeCOM;

/* 7 Segments */
uint8_t LSL_DISPLAY_Get7Seg(uint8_t number);
void LSL_DISPLAY_Display7Seg(LSL_Pinout *diode, uint8_t number, LSL_DISPLAY_DiodeCOM common);
void LSL_DISPLAY_Display7SegAnodeCathode(LSL_Pinout *diode, uint8_t number, LSL_DIGITAL_State stateA, LSL_DIGITAL_State  stateB);

#endif // LSL_DISPLAY_H