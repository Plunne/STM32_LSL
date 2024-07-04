// #include "lsl_init.h"
#include "lsl_utils.h"
#include "lsl_init.h"

/* Globals */
// static int counter = 0;

/* Interrupts */
// void TIM2_IRQHandler(void);
void USART3_IRQHandler(void);

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
		LSL_USART_Tx(&LSL_INIT_USART, 'A');
		LSL_UTILS_DelayMs(2000);
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

void USART3_IRQHandler(void) {

	if (USART3->ISR & USART_ISR_RXNE) {

		/* Interrupt instruction */
		// counter = 10;

		/* Reset IRQ flag */
		USART3->ISR &= ~USART_ISR_RXNE;
	}
}