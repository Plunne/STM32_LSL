#ifndef LSL_CLOCK_H
#define LSL_CLOCK_H

#include "lsl_board.h"

/* Define PLL settings */
#define PLL_x4      0b0010
#define PLL_x5      0b0011
#define PLL_x6      0b0100
#define PLL_x7      0b0101
#define PLL_x8      0b0110
#define PLL_x9      0b0111
#define PLL_x16     0b1111

/* Define APB settings */
#define APB1_CLK    8
#define APB2_CLK    11

#define APB_DIV0    0b000
#define APB_DIV2    0b100
#define APB_DIV4    0b101
#define APB_DIV8    0b110
#define APB_DIV16   0b111

/* Enable Clocks */
void LSL_CLOCK_EnableHSI(void);
void LSL_CLOCK_EnablePLL(void);

/* PLL */
void LSL_CLOCK_InitPLL(uint8_t multiplier);
void LSL_CLOCK_MultiplierPLL(uint8_t multiplier);

/* Selection */
void LSL_CLOCK_Select(uint8_t clock);

/* Prescaling */
void LSL_CLOCK_PrescaleAPB(uint8_t apb_clk, uint8_t prescale);

#endif // LSL_CLOCK_H