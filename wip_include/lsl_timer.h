#ifndef LSL_TIMER_H
#define LSL_TIMER_H

#include "lsl_clock.h"

typedef struct {
    TIM_TypeDef* timer;
    uint16_t prescaler;
    uint16_t counter;
    IRQn_Type event;
} LSL_TIMER_Handler;

/* Init */
void LSL_TIMER_Init(LSL_TIMER_Handler* TIMER_Handler);

/* Update */
void LSL_TIMER_Update(LSL_TIMER_Handler* TIMER_Handler, uint32_t count);

#endif // LSL_TIMER_H