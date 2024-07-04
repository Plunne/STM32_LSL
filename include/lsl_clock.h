#ifndef LSL_CLOCK_H
#define LSL_CLOCK_H

#include "lsl_board.h"

/* Define PLL settings */
#define PLL_M_DIV_MIN   2
#define PLL_M_DIV_MAX   63
#define PLL_M_DIV2      2

#define PLL_N_x54       54      // 432 MHz after PLL M Prsc Div = 2 (For 216 MHz after Pstsc Div = 2)

#define PLL_P_DIV2      0b00
#define PLL_P_DIV4      0b01
#define PLL_P_DIV6      0b10
#define PLL_P_DIV8      0b11

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
void LSL_CLOCK_InitPLL(uint8_t dividerM, uint8_t multiplierN, uint8_t dividerP);
void LSL_CLOCK_PrescalePLL(uint8_t divider);
void LSL_CLOCK_UpscalePLL(uint8_t multiplier);
void LSL_CLOCK_PostscalePLL(uint8_t divider);

/* Selection */
void LSL_CLOCK_Select(uint8_t clock);

/* Prescaling */
void LSL_CLOCK_PrescaleAPB(uint8_t apb_clk, uint8_t prescale);

#endif // LSL_CLOCK_H