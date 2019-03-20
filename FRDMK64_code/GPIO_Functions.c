
#include "fsl_device_registers.h"
#include "GPIO_Functions.h"

void init_GPIO(){
	/**
	 * Button Initialization
	 */
	//Initialize timer for PortC
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//Set PortC PCR6 to PCR6
	PORTC_PCR6 |= PORT_PCR_MUX(1);
	//Set GPIOC Pin 6 Data Direction to input
	GPIOC_PDDR = 0;

	/**
	 * RED LED INITILIZATION
	 */
	//Set mask bit for PORTB on System Clock Gating
	//Control Register 5
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//Default for PORTB Pin Control Register 22 is 'Disabled'.
	PORTB_PCR22 |= PORT_PCR_MUX(1);
	//SET GIPOB Port Data Direction Register to
	//output (1) on pin 22.
	GPIOB_PDDR |= 0x01 << 22;
	GPIOB_PSOR = 0x01<<22;//Turn off LED
}
