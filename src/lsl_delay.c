#include "lsl_utils.h"

void LSL_UTILS_DelayMs(uint16_t d) {
	for (uint32_t i=0; i < (d * 5000); i++) {
		__asm("nop");
	};
}