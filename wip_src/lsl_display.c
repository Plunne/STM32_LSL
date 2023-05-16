#include "lsl_display.h"

/* 7 Segments */
uint8_t LSL_DISPLAY_Get7Seg(uint8_t number) {

    switch(number)
    {
        case 0: return 0b00111111;
        case 1: return 0b00000110;
        case 2: return 0b01011011;
        case 3: return 0b01001111;
        case 4: return 0b01100110;
        case 5: return 0b01101101;
        case 6: return 0b01111101;
        case 7: return 0b00000111;
        case 8: return 0b01111111;
        case 9: return 0b01101111;
        case 10: return 0b10000000;
        default: return 0b01000000;
    }
}

void LSL_DISPLAY_Display7Seg(LSL_Pinout *diode, uint8_t number, LSL_DISPLAY_DiodeCOM common) {

    if (common == anode) LSL_DISPLAY_Display7SegAnodeCathode(diode, number, HIGH, LOW);         // If display has Common Anode
    else if (common == cathode) LSL_DISPLAY_Display7SegAnodeCathode(diode, number, LOW, HIGH);  // If display has Common Cathode

}

void LSL_DISPLAY_Display7SegAnodeCathode(LSL_Pinout *diode, uint8_t number, LSL_DIGITAL_State stateA, LSL_DIGITAL_State  stateB) {

    uint8_t segment = LSL_DISPLAY_Get7Seg(number); // Translate number to bits pattern

    for (int i=0; i < DIODE_NB; i++) { // For each diode

        LSL_DIGITAL_Write(&diode[i], stateA);       // LED i OFF
        if (segment & (1 << i)) {                   // Check if at bit i, Pattern bit is HIGH
            LSL_DIGITAL_Write(&diode[i], stateB);   // If pattern bit is HIGH, LED i ON
        } else {                                    // Else pattern dosen't match HIGH for LED
            LSL_DIGITAL_Write(&diode[i], stateA);   // LED i OFF
        }
    }
}