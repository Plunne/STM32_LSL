#include "lsl_usart.h"


/* Init */
void LSL_USART_Init(LSL_USART_Handler* USART_Handler) {

	/* Enable USART Clock */
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 		// Enable clock USART1
	if (USART_Handler->usart == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 		// Enable clock USART1
	else if (USART_Handler->usart == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable clock USART2
	else if (USART_Handler->usart == USART3) RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // Enable clock USART3

	/* Setup USART */
	LSL_USART_Baudrate(USART_Handler->usart, USART_Handler->bauds);
	LSL_USART_DataSize(USART_Handler->usart, USART_Handler->dataSize);
	LSL_USART_Parity(USART_Handler->usart, USART_Handler->parity);
	LSL_USART_Stop(USART_Handler->usart, USART_Handler->stop);
	
	/* Interrupt? */
	if (USART_Handler->event) {
		USART_Handler->usart->CR1 |= USART_CR1_RXNEIE;
		NVIC_EnableIRQ(USART_Handler->event);
	}
	
	/* Enable USART */
	LSL_USART_Enable(USART_Handler->usart, USART_Handler->direction);

}

/* Enable */
void LSL_USART_Enable(USART_TypeDef* USART, LSL_USART_Direction direction) {

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
void LSL_USART_Baudrate(USART_TypeDef* USART, uint32_t baudrate) {

	// Table used for USART1
	// MCU freq = 72MHz
	// LSL_USART72_BAUD[x][0] = <MCU freq> / (<Baudrate> * 16)
	// LSL_USART72_BAUD[x][1] = [decimals of "<MCU freq> / (<Baudrate> * 16)"] * 16
	uint16_t LSL_USART72_BAUD [5][2] = {
		{1875, 0},  // 2400 Bauds
		{468, 12},  // 9600 Bauds
		{234, 6},   // 19200 Bauds
		{78, 2},    // 57600 Bauds
		{39, 1}     // 115200 Bauds
	};

	// Table used for USART2 & USART3
	// MCU freq = 36MHz
	// LSL_USART36_BAUD[x][0] = <MCU freq> / (<Baudrate> * 16)
	// LSL_USART36_BAUD[x][1] = [decimals of "<MCU freq> / (<Baudrate> * 16)"] * 16
	uint16_t LSL_USART36_BAUD [5][2] = {
		{937, 8},   // 2400 Bauds
		{234, 6},   // 9600 Bauds
		{117, 3},   // 19200 Bauds
		{39, 1},    // 57600 Bauds
		{19, 8}     // 115200 Bauds
	};

	if (USART == USART1) LSL_USART_SetBaudrate(USART, *LSL_USART72_BAUD, baudrate);
	else if (USART == USART2) LSL_USART_SetBaudrate(USART, *LSL_USART36_BAUD, baudrate);
	else if (USART == USART3) LSL_USART_SetBaudrate(USART, *LSL_USART36_BAUD, baudrate);
	
}

void LSL_USART_SetBaudrate(USART_TypeDef* USART, uint16_t *baudTable, uint32_t baudrate) {

	uint8_t i = 0;

	switch (baudrate)
	{
		case 2400: 		i = 0; break;
		case 9600: 		i = 1; break;
		case 19200: 	i = 2; break;
		case 57600: 	i = 3; break;
		case 115200:	i = 4; break;
		default: break;
	}

    USART->BRR |= (baudTable[i*2] << 4) | (baudTable[i*2+1] << 0); // Set Bauds Rate Register DIV_Mantissa and DIV_fraction
    // USART->BRR |= ; // Set Bauds Rate Register DIV_Mantissa and DIV_fraction

}

/* Data Size */
void LSL_USART_DataSize(USART_TypeDef* USART, uint8_t data_size) {

	switch (data_size)
	{
	case 7:
	case 8:
		USART->CR1 &= ~USART_CR1_M;	// Disable 9 bits mode (Parity on 8th bit)
		break;

	case 9:
		USART->CR1 |= USART_CR1_M;	// Enable 9 bits mode (Parity on 9th bit or shall be disabled for 9 bits data)
		break;
	
	default:
		break;
	}
}

/* Parity */
void LSL_USART_Parity(USART_TypeDef* USART, uint8_t parity) {

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
void LSL_USART_Stop(USART_TypeDef* USART, uint8_t stop) {

	/* Clear stop bit(s) register */
	USART->CR2 &= ~USART_CR2_STOP;

	/* Set stop bit(s) */
	if (stop == 1) USART->CR2 &= ~USART_CR2_STOP; 			// 1 Stop (USART_CR2_STOP = 0b00)
	else if (stop == 2) USART->CR2 |= USART_CR2_STOP_1;		// 2 Stop (USART_CR2_STOP = 0b10)
}

/* Transmit */
void LSL_USART_Tx(LSL_USART_Handler* USART_Handler, uint8_t data) {

	USART_Handler->usart->DR = (uint8_t) (data & 0xFF);
    while (!(USART_Handler->usart->SR & USART_SR_TC));
}

/* Receive */
uint8_t LSL_USART_Rx(LSL_USART_Handler* USART_Handler) {

    while (!(USART_Handler->usart->SR & USART_SR_RXNE));
    return USART_Handler->usart->DR & 0xFF;
}

/* Wait for interrupt */
void LSL_USART_InterruptRx(LSL_USART_Handler* USART_Handler) {

	USART_Handler->usart->SR &= ~USART_SR_RXNE;
}