#include "lsl_clock.h"

/* Enable Clocks */
void LSL_CLOCK_EnableHSI(void) {

	RCC->CR |= RCC_CR_HSION; 			// Enable HSI (RCC_CR_HSION)
	while(!(RCC->CR & RCC_CR_HSIRDY)); 	// Wait for HSI enabling (RCC_CR_HSIRDY)
}

void LSL_CLOCK_EnablePLL(void) {

	RCC->CR |= RCC_CR_PLLON; 			// Enable PLL (RCC_CR_PLLON)
	while(!(RCC->CR & RCC_CR_PLLRDY)); 	// Wait for PLL enabling (RCC_CR_PLLRDY)
}

/* PLL Config */
void LSL_CLOCK_InitPLL(uint8_t multiplier) {

    LSL_CLOCK_MultiplierPLL(multiplier);	// Setup PLL Multiplier
    LSL_CLOCK_EnablePLL();					// Enable PLL
    LSL_CLOCK_Select(RCC_CFGR_SW_PLL);		// Select PLL Clock
}

void LSL_CLOCK_MultiplierPLL(uint8_t multiplier) {

    RCC->CFGR &= ~RCC_CFGR_PLLMULL_Msk;					// Clear PLL Multiplier register
    RCC->CFGR |= (multiplier << RCC_CFGR_PLLMULL_Pos);	// Set PLL Multiplier factor
}

/* Select Clock */
void LSL_CLOCK_Select(uint8_t clock) {

    // Set clock as source clock (RCC_CFGR_SW)
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= (clock << RCC_CFGR_SW_Pos);
	
	// Wait for clock enabling (RCC_CFGR_SWS)
	while (!(RCC->CFGR & (clock << 2)));
}

/* Prescaling */
void LSL_CLOCK_PrescaleAPB(uint8_t apb_clk, uint8_t prescale) {

    RCC->CFGR &= ~(0b111 << apb_clk);	// Clear RCC_CFGR_PPREx (1 for APB1, 2 for APB2)
    RCC->CFGR |= (prescale << apb_clk);	// Set prescaler for APBx clock (RCC_CFGR_PPREx)
}
