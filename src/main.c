#include "main.h"
#include "lsl_init_regs.h"
#include "lsl_utils.h"
#include "lsl_io.h"
#include "lsl_display.h"

int main(void) {

	/* Init Registers */
	LSL_Init_Registers();

	/* Init ADC7/1 */
	LSL_ANALOG_ADC_Start(ADC1, 2);

	/* Select channel sequence */
	LSL_ANALOG_ADC_SetSequence(ADC1, 2, POTAR.pin);

	/* Calibrate ADC */
	LSL_ANALOG_ADC_Calibrate(ADC1);

	/* Init Variables */
	uint16_t adc_value = 0;

	/* Super Loop */
	while (1) {

		LSL_ANALOG_ADC_Read(ADC1); // Get blank ADC Data because we have set an empty ADC input as first sequence (increment to next ADC conv)
		adc_value = LSL_ANALOG_ADC_Read(ADC1); // Get ADC Data without MSB Bits 12 -> 15 (because it's a 12bits ADC not 16)
		
		// Delay
		LSL_DIGITAL_Write(&LED, TOGGLE);
		LSL_UTILS_DelayMs(adc_value); 					// Delay (Be careful sw_cpt value depends of this delay)
	}
	
	return 0;
}