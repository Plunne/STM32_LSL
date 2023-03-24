#include "lsl_init_regs.h"

void LSL_Init_Registers(void) {

    LSL_Init_RCC();
    LSL_Init_GPIO();

}

void LSL_Init_RCC(void) {

	/* RCC Settings */

}

void LSL_Init_GPIO(void) {
    
	LSL_PINOUTS_InitPinout(&LED);
	LSL_PINOUTS_InitPinout(&POTAR);

}