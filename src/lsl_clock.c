#include "lsl_clock.h"

/* Enable Clocks */
void LSL_CLOCK_EnableHSI(void)
{
	RCC->CR |= RCC_CR_HSION; 			// Enable HSI (RCC_CR_HSION)
	while(!(RCC->CR & RCC_CR_HSIRDY)); 	// Wait for HSI enabling (RCC_CR_HSIRDY)
}

void LSL_CLOCK_EnablePLL(void)
{
	RCC->CR |= RCC_CR_PLLON; 			// Enable PLL (RCC_CR_PLLON)
	while(!(RCC->CR & RCC_CR_PLLRDY)); 	// Wait for PLL enabling (RCC_CR_PLLRDY)
}

/* PLL Config */
void LSL_CLOCK_InitPLL(uint8_t dividerM, uint8_t multiplierN, uint8_t dividerP)
{
    LSL_CLOCK_PrescalePLL(dividerM);	    // Setup PLL Prescaler
    LSL_CLOCK_UpscalePLL(multiplierN);	    // Setup PLL Multiplier
    LSL_CLOCK_PostscalePLL(dividerP);	    // Setup PLL Postscaler
    LSL_CLOCK_EnablePLL();					// Enable PLL
    LSL_CLOCK_Select(RCC_CFGR_SW_PLL);		// Select PLL Clock
}

void LSL_CLOCK_PrescalePLL(uint8_t divider)
{
    if ( (divider >= PLL_M_DIV_MIN) && (divider <= PLL_M_DIV_MAX) )
    {
        RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;			        // Clear PLL M Prsc Divider register
        RCC->PLLCFGR |= (divider << RCC_PLLCFGR_PLLM_Pos);	    // Set PLL M Prsc Divider factor
    }
    else
    {
        /* Do nothing */
    }
}

void LSL_CLOCK_UpscalePLL(uint8_t multiplier)
{
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;			        // Clear PLL Multiplier register
    RCC->PLLCFGR |= (multiplier << RCC_PLLCFGR_PLLN_Pos);	// Set PLL Multiplier factor
}

void LSL_CLOCK_PostscalePLL(uint8_t divider)
{
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;			        // Clear PLL P Pstsc Divider register
    RCC->PLLCFGR |= (divider << RCC_PLLCFGR_PLLP_Pos);	    // Set PLL P Pstsc Divider factor
}

/* Select Clock */
void LSL_CLOCK_Select(uint8_t clock)
{
    // Set clock as source clock (RCC_CFGR_SW)
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= (clock << RCC_CFGR_SW_Pos);
	
	// Wait for clock enabling (RCC_CFGR_SWS)
	while (!(RCC->CFGR & (clock << 2)));
}

/* Prescaling */
void LSL_CLOCK_PrescaleAPB(uint8_t apb_clk, uint8_t prescale)
{
    RCC->CFGR &= ~(0b111 << apb_clk);	// Clear RCC_CFGR_PPREx (1 for APB1, 2 for APB2)
    RCC->CFGR |= (prescale << apb_clk);	// Set prescaler for APBx clock (RCC_CFGR_PPREx)
}
