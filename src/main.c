// #include "lsl_init.h"
#include "lsl_utils.h"
#include "lsl_init.h"

/* Globals */
// static int counter = 0;

/* Interrupts */
// void TIM2_IRQHandler(void);
// void USART2_IRQHandler(void);

/* Main */
int main(void)
{
	/* Init Registers */
	LSL_Init_Registers();

	/* Init Variables */

	/* User functions */

	/* Super Loop */
	while (1)
	{
		// LSL_DIGITAL_Write(&LED, LSL_DIGITAL_Read(&Button));

		LSL_DIGITAL_Write(&LED, HIGH);
		LSL_UTILS_DelayMs(LSL_ADC_Read(&LSL_INIT_ADC1, &POTAR));
		LSL_DIGITAL_Write(&LED, LOW);
		LSL_UTILS_DelayMs(LSL_ADC_Read(&LSL_INIT_ADC1, &POTAR2));
	}
	
	return 0;
}

/**********************
 *     Interrupts     *
 **********************/

// void TIM2_IRQHandler(void) {
	
// 	if (TIM2->SR & TIM_SR_UIF) {
		
// 		/* Interrupt instruction */
// 		counter = (1 + counter) % 10;
		
// 		/* Reset IRQ flag */
// 		TIM2->SR &= ~TIM_SR_UIF;
// 	}
// }

// void USART2_IRQHandler(void) {

// 	if (USART2->SR & USART_SR_RXNE) {

// 		/* Interrupt instruction */
// 		counter = 10;

// 		/* Reset IRQ flag */
// 		USART2->SR &= ~USART_SR_RXNE;
// 	}
// }