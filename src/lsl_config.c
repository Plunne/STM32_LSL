#include "lsl_config.h"

/* Init */
void LSL_CONFIG_Init(void)
{
    /***************
     *     ADC     *
     ***************/

    // POTAR
    LSL_CONFIG_Pinout(&POTAR, GPIOA, 5, ADC_MODE, NO_PULL);
    LSL_CONFIG_Pinout(&POTAR2, GPIOA, 6, ADC_MODE, NO_PULL);

    /*******************
     *     DIGITAL     *
     *******************/

    // LED
    LSL_CONFIG_Pinout(&LED, GPIOB, 7, OUTPUT_MODE, NO_PULL);

    // Button
    LSL_CONFIG_Pinout(&Button, GPIOC, 13, INPUT_MODE, NO_PULL);

    /*****************
     *     USART     *
     *****************/

    // USART2
    LSL_CONFIG_AFIO(&Serial_Tx, GPIOD, 8, USART_TX, NO_PULL, PUSH_PULL, OSPEED_FAST, 0b0111);
    LSL_CONFIG_AFIO(&Serial_Rx, GPIOD, 9, USART_RX, NO_PULL, PUSH_PULL, OSPEED_FAST, 0b0111);
}

/* Pinout */
void LSL_CONFIG_Pinout(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode, uint8_t pupd)
{
    /* Setup Pinout */
    pinout->PORTx = PORTx;
    pinout->pin = pin;
    pinout->mode = mode;
    pinout->pupd = pupd;

    /* Init Pinout */
    LSL_PINOUTS_InitPinout(pinout);
}

/* AFIO */
void LSL_CONFIG_AFIO(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode, uint8_t pupd, uint8_t otype, uint8_t ospeed, uint8_t afio)
{
    LSL_CONFIG_Pinout(pinout, PORTx, pin, mode, pupd);

    pinout->otype = otype;
    pinout->ospeed = ospeed;

    LSL_PINOUTS_Advanced(pinout);

    if ((pin >= 0) && (pin <= 7))
    {
        PORTx->AFR[0] &= ~(0xf << (pin * 4));
        PORTx->AFR[0] |= ((0xf & afio) << (pin * 4));
    }
    else if ((pin >= 8) && (pin <= 15))
    {
        PORTx->AFR[1] &= ~(0xf << ((pin - 8) * 4));
        PORTx->AFR[1] |= ((0xf & afio) << ((pin - 8) * 4));
    }
    else
    {
        /* Do nothing */
    }
}