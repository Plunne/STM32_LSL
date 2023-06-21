#include "lsl_usart.h"


/* Init */
void LSL_USART_Init(LSL_USART_Handler_t* USART_Handler)
{
	/* Enable USART Clock */
	if (USART_Handler->usart == USART1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 	// Enable clock USART1
	}
	else if (USART_Handler->usart == USART2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	// Enable clock USART2
	}
	else if (USART_Handler->usart == USART3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	// Enable clock USART3
	}
	else if (USART_Handler->usart == UART4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;	// Enable clock UART4
	}
	else if (USART_Handler->usart == UART5)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;	// Enable clock UART5
	}
	else if (USART_Handler->usart == USART6)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;	// Enable clock USART6
	}
	else if (USART_Handler->usart == UART7)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART7EN;	// Enable clock UART7
	}
	else if (USART_Handler->usart == UART8)
	{
		RCC->APB1ENR |= RCC_APB1ENR_UART8EN;	// Enable clock UART8
	}
	else
	{
		// Do Nothing
	}

	/* Setup USART */
	LSL_USART_Baudrate(USART_Handler->usart, USART_Handler->bauds, 16);
	LSL_USART_DataSize(USART_Handler->usart, USART_Handler->dataSize);
	LSL_USART_Parity(USART_Handler->usart, USART_Handler->parity);
	LSL_USART_Stop(USART_Handler->usart, USART_Handler->stop);
	
	/* Interrupt? */
	if (USART_Handler->event)
	{
		USART_Handler->usart->CR1 |= USART_CR1_RXNEIE;
		NVIC_EnableIRQ(USART_Handler->event);
	}
	
	/* Enable USART */
	LSL_USART_Enable(USART_Handler->usart, USART_Handler->direction);
}

/* Enable */
void LSL_USART_Enable(USART_TypeDef* USART, LSL_USART_Direction_t direction)
{
	USART->CR1 |= USART_CR1_UE;	// Enable USART
	
	USART->CR1 &= ~(USART_CR1_TE | USART_CR1_RE); 	// Clear Tx & Rx modes
	
	switch (direction)
	{
		case Tx:
			USART->CR1 |= USART_CR1_TE; // Enable Tx
			break;
		case Rx:
			USART->CR1 |= USART_CR1_RE; // Enable Rx
			break;
		case Tx_Rx:
			USART->CR1 |= USART_CR1_TE | USART_CR1_RE; 	// Enable Tx & Rx (TODO : Auto GPIO enabling)
			break;
		
		default:
			break;
	}

}

/* Baudrate */
void LSL_USART_Baudrate(USART_TypeDef* USART, uint32_t baudrate, uint8_t over)
{
	// Table used for Oversampling 8
	// MCU freq = 216MHz
	// LSL_USART216_OVER8_BAUD[x] = <MCU freq> / <Baudrate>
	uint16_t LSL_USART216_OVER8_BAUD[10] = {
		0xAFC4,	// 9600 Bauds
		0x57E2, // 19200 Bauds
		0x2BF1, // 38400 Bauds
		0x1D46, // 57600 Bauds
		0x0EA3, // 115200 Bauds
		0x0751, // 230400 Bauds
		0x03A4, // 461538.461 Bauds
		0x01D2, // 923076.923 Bauds
		0x0020, // 13 500 000 Bauds
		0x0010, // 27 000 000 Bauds
	};

	// Table used for Oversampling 16
	// MCU freq = 216MHz
	// LSL_USART216_OVER16_BAUD[x] = <MCU freq> / <Baudrate>
	uint16_t LSL_USART216_OVER16_BAUD[12] = {
		0x57E4,	// 9600 Bauds
		0x2BF2, // 19200 Bauds
		0x15F9, // 38400 Bauds
		0x0EA6, // 57600 Bauds
		0x0753, // 115200 Bauds
		0x03A9, // 230400 Bauds
		0x01D4, // 461538.461 Bauds
		0x00EA, // 923076.923 Bauds
		0x0036, // 4 000 000 Bauds
		0x0024, // 6 000 000 Bauds
		0x0015, // 10 285 714.286 Bauds
		0x0010, // 13 500 000 Bauds
	};

	switch (over)
	{
		case 8:
			LSL_USART_SetBaudrate(USART, LSL_USART216_OVER8_BAUD, baudrate);
			break;
		
		case 16:
			LSL_USART_SetBaudrate(USART, LSL_USART216_OVER16_BAUD, baudrate);
			break;
		
		default:
			break;
	}
}

void LSL_USART_SetBaudrate(USART_TypeDef* USART, uint16_t *baudTable, uint32_t baudrate)
{
	uint8_t i = 0;

	switch (baudrate)
	{
		case 9600: 		i = 0; break;
		case 19200: 	i = 1; break;
		case 38400: 	i = 2; break;
		case 57600: 	i = 3; break;
		case 115200:	i = 4; break;
		case 230400:	i = 5; break;
		case 461538:	i = 6; break;
		case 923076:	i = 7; break;
		case 13500000:	i = 8; break;
		case 27000000:	i = 9; break;
		default: break;
	}

    USART->BRR |= baudTable[i]; // Set Bauds Rate Register
}

/* Data Size */
void LSL_USART_DataSize(USART_TypeDef* USART, uint8_t data_size)
{
	switch (data_size)
	{
		case 7:
			USART->CR1 &= ~USART_CR1_M0;
			USART->CR1 |= USART_CR1_M1;
			break;
		case 8:
			USART->CR1 &= ~USART_CR1_M0;
			USART->CR1 &= ~USART_CR1_M1;
			break;

		case 9:
			USART->CR1 |= USART_CR1_M0;
			USART->CR1 &= ~USART_CR1_M1;
			break;
		
		default:
			break;
	}
}

/* Parity */
void LSL_USART_Parity(USART_TypeDef* USART, uint8_t parity)
{
	switch (parity)
	{
		case 0:
			USART->CR1 &= ~USART_CR1_PCE;	// Parity Control Disable (USART_CR1_PCE = 0)
			break;
		case 1:
			USART->CR1 |= USART_CR1_PCE;	// Parity Control Enable (USART_CR1_PCE = 1)
			USART->CR1 &= ~USART_CR1_PS;	// Parity Selection Even (USART_CR1_PS = 0)
			break;
		
		case 2:
			USART->CR1 |= USART_CR1_PCE;	// Parity Control Enable (USART_CR1_PCE = 1)
			USART->CR1 |= USART_CR1_PS;		// Parity Selection Odd (USART_CR1_PS = 1)
			break;

		default:
			break;
	}
}

/* Stop */
void LSL_USART_Stop(USART_TypeDef* USART, uint8_t stop)
{
	/* Clear stop bit(s) register */
	USART->CR2 &= ~USART_CR2_STOP;

	/* Set stop bit(s) */
	if (stop == 1)
	{
		USART->CR2 &= ~USART_CR2_STOP; 		// 1 Stop (USART_CR2_STOP = 0b00)
	}
	else if (stop == 2)
	{
		USART->CR2 &= ~USART_CR2_STOP_0;	// 2 Stop (USART_CR2_STOP = 0b10)
		USART->CR2 |= USART_CR2_STOP_1;		// 2 Stop (USART_CR2_STOP = 0b10)
	}
	else
	{
		// Do Nothing
	}
}

/* Transmit */
void LSL_USART_Tx(LSL_USART_Handler_t* USART_Handler, uint8_t data)
{
	USART_Handler->usart->TDR = (uint8_t) (data & 0xFF);
    while (!(USART_Handler->usart->ISR & USART_ISR_TC)) {}
}

/* Receive */
uint8_t LSL_USART_Rx(LSL_USART_Handler_t* USART_Handler)
{
    while (!(USART_Handler->usart->ISR & USART_ISR_RXNE)) {}
    return USART_Handler->usart->RDR & 0xFF;
}

/* Wait for interrupt */
void LSL_USART_Rxi(LSL_USART_Handler_t* USART_Handler)
{
	USART_Handler->usart->ISR &= ~USART_ISR_RXNE;
}