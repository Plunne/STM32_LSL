#include "lsl_timer.h"

/* Init */
void LSL_TIMER_Init(LSL_TIMER_Handler* TIMER_Handler) {

    /* Enable Timer RCC */
    if (TIMER_Handler->timer == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if (TIMER_Handler->timer == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIMER_Handler->timer == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if (TIMER_Handler->timer == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    /* Timer prescaling division */
	TIMER_Handler->timer->PSC = TIMER_Handler->prescaler - 1; 	// divide clock source frequency by TIMER_Handler->prescaler

	/* Timer max count value */
	TIMER_Handler->timer->ARR = TIMER_Handler->counter - 1; 	// interrupt every TIMER_Handler->counter

	/* Update prescaler and counter limit */
	TIMER_Handler->timer->EGR |= TIM_EGR_UG;
	
	/* Enable Interrupts */
	TIMER_Handler->timer->DIER |= TIM_DIER_UIE;

    /* Enable interrupt TIMER_Handler->event */
	NVIC_EnableIRQ(TIMER_Handler->event);
	
	/* Start Timer */
	TIMER_Handler->timer->CR1 |= TIM_CR1_CEN;
}

/* Update */
void LSL_TIMER_Update(LSL_TIMER_Handler* TIMER_Handler, uint32_t count) {

	TIMER_Handler->counter = count; 						// Interrupt every TIMER_Handler->counter
	TIMER_Handler->timer->ARR = TIMER_Handler->counter - 1; // Interrupt every TIMER_Handler->counter
}