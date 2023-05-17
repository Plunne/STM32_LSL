#include "lsl_config.h"

/* Init */
void LSL_CONFIG_Init(void)
{
    /***************
     *     ADC     *
     ***************/

    // POTAR
    LSL_CONFIG_Pinout(&POTAR, GPIOA, 5, ADC_MODE);
    LSL_CONFIG_Pinout(&POTAR2, GPIOA, 6, ADC_MODE);

    /*******************
     *     DIGITAL     *
     *******************/

    // LED
    LSL_CONFIG_Pinout(&LED, GPIOB, 7, OUTPUT_MODE);

    // Button
    LSL_CONFIG_Pinout(&Button, GPIOC, 13, INPUT_MODE);

    /*****************
     *     USART     *
     *****************/

}

/* Pinout */
void LSL_CONFIG_Pinout(LSL_Pinout_t* pinout, GPIO_TypeDef* PORTx, uint8_t pin, uint8_t mode)
{
    /* Setup Pinout */
    pinout->PORTx = PORTx;
    pinout->pin = pin;
    pinout->mode = mode;

    /* Init Pinout */
    LSL_PINOUTS_InitPinout(pinout);
}