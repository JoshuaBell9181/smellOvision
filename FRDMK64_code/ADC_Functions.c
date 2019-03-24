#include "fsl_device_registers.h"


void init_ADC(){
	//Set mask bit for ADC0 on SCGc6
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

	//Set mask bit for Port E on SCGC5
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Set to ADC0_SE17 (Default, Alt 0)
	PORTE_PCR24 |= PORT_PCR_MUX(0);

	/*Sets fields in ADC0 Configuration Register 1
	 * ADLPC   =   0 : Normal Power Configuration
	 * ADIV    =  01 : (input clock)/2
	 * ADLSMP  =   0 : Short sample time
	 * MODE    =  10 : DIFF=0 10-bit conversion
	 * ADICLK  =  00 : Clock source = Bus clock
	 */
	ADC0_CFG1 |= 0x28;

	/* Sets fields in ADC0 Configuration Register 2
	 * MUXSEL  =  0  : ADxxa channels selected
	 * ADACKEN =  0  : Async clock output disabled
	 * ADHSC   =  0  : Normal conversion sequence
	 * ADLSTS  =  0  : Default longest sample time
	 */
	ADC0_CFG2 |= 0x00;

	/*
	 *Set fields in ADC0 Status and Control Register 2
	 * ADTRG  =  0   :  Select software trigger
	 * ACFE   =  0   :  Compare function disabled
	 * DMAEN  =  0   :  DMA function disabled
	 * REFSEL =  0   :  Voltage Reference = Vrefh, Vrefl
	 */
	ADC0_SC2 |= 0b00;

	/*
	 * Set fields in ADC0 Status and Control Register 3
	 * CAL   =  0  :  Do not start calibration
	 * ADC0  =  8  :  One conversion
	 */
	ADC0_SC3 |= 0b00;

	/*
	 * Set fields in ADC0 Status and Control Register 1 A
	 * AIEN  = 0  :  No interrupt
	 * DIFF  = 0  :  Single ended
	 * ADCH  = 10001 : Input Signal ADC0_SE17
	 */
	ADC0_SC1A |= 0b0010001;

}

int getADC(){

	//What for the coco to be 1 this flag tells us conversion complete(coco)
	//When coco = 0 then the conversion is not complete
	ADC0_RA;

	//while(1){

		//Set for channel 17
		ADC0_SC1A = 0x11;

		// Loop until coco is a 1
		while( !(ADC0_SC1A & 0x10)  ){}

		//Use this variable to look at the data register
		int test = ADC0_RA;

		return test;
	//}

}
