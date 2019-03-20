
#include "fsl_device_registers.h"
#include "GPIO_Functions.h"

void LED_on(){
	GPIOB_PCOR = 0x01<<22;//Turn On LED
}

void LED_off(){
	GPIOB_PCOR = 0x01<<22;//Turn On LED
}
