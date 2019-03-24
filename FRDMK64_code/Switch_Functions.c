#include "fsl_device_registers.h"

//Initialize the switch and LED
void switch_init(){

	// SIM module use PORTC module-for switch
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	// SIM module use PORTB module-for led
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// enable PTC6 for the sw
	PORTC_PCR6 |= PORT_PCR_MUX(1);

	// enable PTC6 for the LED
	PORTB_PCR22 |= PORT_PCR_MUX(1);

	// LED - output
	GPIOB_PDDR |= 0x01 << 22;


}

int switch_pressed(){
	int pressed = 0;
	pressed = GPIOC_PDIR & 0x00000040;
	return pressed;
}
