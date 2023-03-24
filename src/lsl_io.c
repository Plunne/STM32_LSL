#include "lsl_io.h"

void LSL_IO_InitGPIO(LSL_Pinout *pinout) {

    for (unsigned int i=0; i < (sizeof(*pinout)/sizeof(pinout[0])); i++) { // For each Pinout from the array
    
        LSL_PINOUTS_InitPinout(&pinout[i]); // Set GPIO RCC & Mode
    }
}