#include "lsl_adc.h"

/* Init */
void LSL_ADC_Init(LSL_ADC_Handler_t* ADC_Handler)
{
	LSL_ADC_Setup(ADC_Handler->adc);
	LSL_ADC_SetResolution(ADC_Handler->adc, ADC_Handler->resolution);
	LSL_ADC_SetConvNumber(ADC_Handler->adc, ADC_Handler->nbChannels);
	LSL_ADC_MultipleSequences(ADC_Handler);
	LSL_ADC_Enable(ADC_Handler->adc);
	LSL_ADC_SetupDMA(ADC_Handler->adc, ADC_Handler->nbChannels, (uint32_t*) &ADC_Handler->adc_channel);
}

void LSL_ADC_InitSingle(LSL_ADC_Handler_t* ADC_Handler)
{
	LSL_ADC_Setup(ADC_Handler->adc);
	LSL_ADC_SetResolution(ADC_Handler->adc, ADC_Handler->resolution);
	LSL_ADC_SetConvNumber(ADC_Handler->adc, ADC_Handler->nbChannels);
	LSL_ADC_SingleSequence(ADC_Handler->adc, 1, ADC_Handler->adc_pinout[0]->pin);
	LSL_ADC_Enable(ADC_Handler->adc);
	LSL_ADC_Calibrate(ADC_Handler->adc);
}

/* Setup */
void LSL_ADC_Setup(ADC_TypeDef* adc)
{
	// Enable ADC
	if (adc == ADC1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// Enable ADC1
	}
	else if (adc == ADC2)
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;	// Enable ADC2
	}
	else
	{
		return;
	}

	// Set ADC Frequency (max allowed 16Mhz)
	ADC->CCR |= (0b10 << ADC_CCR_ADCPRE_Pos);

	// Set resolution here?

	// Enable scan mode
	adc->CR1 |= ADC_CR1_SCAN;
	
	// Enable continuous conversion
	adc->CR2 |= ADC_CR2_CONT;

	// Enable End of conversion selection
	adc->CR2 |= ADC_CR2_EOCS;

	// Data Alignment
	adc->CR2 &= ~ADC_CR2_ALIGN;
}

void LSL_ADC_SetupDMA(ADC_TypeDef* adc, uint16_t data_size, uint32_t* data)
{
	DMA_Stream_TypeDef* dma;

	if (adc == ADC1)
	{
		dma = DMA2_Stream0; // DMA for ADC1 is DMA2_Stream0 (check reference manual DMA Request mapping)
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; // Enable DMA Clock
	}
	else
	{
		return;
	}

	// Enable DMA
	adc->CR2 |= ADC_CR2_DMA;

	// Enable continuous DMA request
	adc->CR2 |= ADC_CR2_DDS;

	// DMA Settings
	dma->CR &= ~(0b11 << DMA_SxCR_DIR_Pos); // Set Peripheral read value to Memory
	dma->CR |= DMA_SxCR_CIRC; 				// Enable Circular mode for ADC
	dma->CR |= DMA_SxCR_MINC; 				// Enable Memory Increment to stack data in successive registers

	// Data registers sizes
	// 00 = 8b / 01 = 16b / 10 = 32b / 11 = reserved
	dma->CR |= (0b01 << DMA_SxCR_PSIZE_Pos); // Set Peripheral ADC Data Register value size (12bits -> 16bits)
	dma->CR |= (0b01 << DMA_SxCR_MSIZE_Pos); // Set Data Memory Acces size (12bits -> 16bits)

	// Set ADC1 (Channel 0) as channel for DMA2 stream
	dma->CR |= (0 << DMA_SxCR_CHSEL_Pos);

	// DMA Addresses
	dma->NDTR = data_size; 				// Captured value size (12bits -> 16bits)
	dma->PAR  = (uint32_t) &adc->DR;	// ADC Data register address
	dma->M0AR = (uint32_t) data;		// Data address to DMA Data Register

	// Start DMA
	dma->CR |= DMA_SxCR_EN; // Start DMA

	// External Trigger for ADC
	//adc->CR2 |= (0b111 << ADC_CR2_EXTSEL_Pos);	// Set SWSTART control
	//adc->CR2 |= (0b01 << ADC_CR2_EXTEN_Pos);	// Let DMA running ADC conversions
	//adc->CR2 |= ADC_CR2_SWSTART;  				// Start regular conversion by software
}

/* Resolution */
void LSL_ADC_SetResolution(ADC_TypeDef* adc, uint8_t resolution)
{
	adc->CR1 &= ~ADC_CR1_RES_Msk;

	switch (resolution)
	{
		case 6:
			adc->CR1 |= (0b11 << ADC_CR1_RES_Pos);
			break;
		
		case 8:
			adc->CR1 |= (0b10 << ADC_CR1_RES_Pos);
			break;
		
		case 10:
			adc->CR1 |= (0b01 << ADC_CR1_RES_Pos);
			break;
		
		case 12:
			adc->CR1 |= (0b00 << ADC_CR1_RES_Pos);
			break;
		
		default:
			break;
	}
}

/* Conversions */
void LSL_ADC_SetConvNumber(ADC_TypeDef* adc, uint8_t nbConv)
{		
	// If there is a number of conversion
	if (nbConv && (nbConv <= 16))
	{ 	
		nbConv--;
		
		// Set number of conversions for ADC
		adc->SQR1 &= ~ADC_SQR1_L_Msk;		// Clear number of conversions
		adc->SQR1 |= (nbConv << ADC_SQR1_L_Pos);	// Set number of conversions
	}
}

/* Sequences */
void LSL_ADC_SingleSequence(ADC_TypeDef* adc, uint8_t sequence, uint8_t channel)
{
	// Set conversion
	if ((sequence > 0) && (sequence <= 6))
	{
		adc->SQR3 &= ~(0x1F << (5 * (sequence - 1))); 	// Clear Sequence channel for the conversion (ADCx_SQR3_SQ1_6 = 0)
		adc->SQR3 |= (channel << (5 * (sequence - 1))); // Select ADC pin 1_6 for the conversion (ADCx_SQR3_SQ1_6 = pin)
	}
	else if ((sequence > 6) && (sequence <= 12))
	{
		adc->SQR2 &= ~(0x1F << (5 * (sequence - 1))); 	// Clear Sequence channel for the conversion (ADCx_SQR2_SQ6_12 = 0)
		adc->SQR2 |= (channel << (5 * (sequence - 1))); // Select ADC pin 7_12 for the conversion (ADCx_SQR2_SQ6_12 = pin)
	}
	else if ((sequence > 12) && (sequence <= 16))
	{
		adc->SQR1 &= ~(0x1F << (5 * (sequence - 1))); 	// Clear Sequence channel for the conversion (ADCx_SQR1_SQ13_16 = 0)
		adc->SQR1 |= (channel << (5 * (sequence - 1))); // Select ADC pin 13_16 for the conversion (ADCx_SQR1_SQ13_16) = pin)
	}
	else
	{
		// Do Nothing
	}
}

void LSL_ADC_MultipleSequences(LSL_ADC_Handler_t* ADC_Handler)
{
	for (int i=0; i < ADC_Handler->nbChannels; i++)
	{
		LSL_PINOUTS_InitPinout(ADC_Handler->adc_pinout[i]);
		LSL_ADC_SingleSequence(ADC_Handler->adc, i + 1, ADC_Handler->adc_pinout[i]->pin);
	}
}

/* Calibration */
void LSL_ADC_Calibrate(ADC_TypeDef* adc)
{
	//adc->CR2 |= ADC_CR2_CAL; 		// Calibrate ADC
	//while(adc->CR2 & ADC_CR2_CAL) {} 	// Waiting for calibration
}

/* Enable */
void LSL_ADC_Enable(ADC_TypeDef* adc)
{
	adc->CR2 |= ADC_CR2_ADON; // Run ADC (ADON)
}

/* Read */
uint16_t LSL_ADC_Read(LSL_ADC_Handler_t* ADC_Handler, LSL_Pinout_t* pinout)
{
	for (uint8_t i=0; i < NB_ADC_CHANNELS; i++)
	{
		if (pinout == ADC_Handler->adc_pinout[i])
		{
			return ADC_Handler->adc_channel[i];
		}
	}
	return 0;
}

uint16_t LSL_ADC_ReadSingle(LSL_ADC_Handler_t* ADC_Handler)
{
		// ADC1 Capture
		ADC_Handler->adc->CR2 |= ADC_CR2_ADON;			// Launch ADC capture
		while (!(ADC_Handler->adc->SR & ADC_SR_EOC)) {}	// Waiting for capture
		ADC_Handler->adc->SR &= ~ADC_SR_EOC;			// Reset end of conversion flag

		// ADC1 Data
		return (uint16_t)(ADC_Handler->adc->DR & ~(0xF << 12)); // Get ADC Data without MSB Bits 12 -> 15 (because it's a 12bits ADC not 16)
}

uint16_t LSL_ADC_ReadSingleMax(LSL_ADC_Handler_t* ADC_Handler, uint8_t max) {

	if (max)
	{
		return (LSL_ADC_ReadSingle(ADC_Handler) / (4092 / max));
	}

	return 0;
}


uint16_t LSL_ADC_ReadSingleRange(LSL_ADC_Handler_t* ADC_Handler, uint16_t min, uint16_t max) {

	if (max)
	{
		if((min < 0xffe) && (max < 0xfff))
		{
			return (min + (LSL_ADC_ReadSingle(ADC_Handler) / (4092 / (max - min))));
		}
	}

	return 0;
}