#include "lsl_init.h"

void LSL_Init_Registers(void)
{
    LSL_Init_RCC();
    LSL_Init_GPIO();
	LSL_Init_TIMERS();
}

void LSL_Init_RCC(void)
{
	/* RCC Setup */
	// LSL_CLOCK_EnableHSI();		// Enable High Speed Internal clock
	// LSL_CLOCK_InitPLL(PLL_x9);	// PLL Multiplier x9
}

void LSL_Init_GPIO(void)
{
	/* Config */	
	LSL_CONFIG_Init();
	LSL_Init_ADC();
	LSL_Init_USART();
}

void LSL_Init_ADC(void)
{
	// /* ADC Handler */
    // LSL_INIT_ADC1.adc              = ADC1;
    // LSL_INIT_ADC1.nbChannels       = 2;
    // LSL_INIT_ADC1.adc_pinout[0]    = &POTAR;
    // LSL_INIT_ADC1.adc_pinout[1]    = &POTAR2;

	// /* ADC Init */
	// LSL_ADC_Init(&LSL_INIT_ADC1);
}

void LSL_Init_USART(void)
{
	// /* USART Handler */
	// LSL_INIT_USART2.usart 		= USART2;
	// LSL_INIT_USART2.bauds 		= 9600;
	// LSL_INIT_USART2.dataSize 	= 8;
	// LSL_INIT_USART2.parity 		= 0;
	// LSL_INIT_USART2.stop 		= 1;
	// LSL_INIT_USART2.direction 	= Tx_Rx;
	// LSL_INIT_USART2.event 		= USART2_IRQn;

	// /* USART Init */
	// LSL_USART_Init(&LSL_INIT_USART2);
}

void LSL_Init_TIMERS(void)
{
	// /* Timers Handler */
	// LSL_INIT_TIMER2.timer = TIM2;
	// LSL_INIT_TIMER2.prescaler = 36000;
	// LSL_INIT_TIMER2.counter = 1000;
	// LSL_INIT_TIMER2.event = TIM2_IRQn;

	// /* Timers Init */
	// LSL_TIMER_Init(&LSL_INIT_TIMER2);
}