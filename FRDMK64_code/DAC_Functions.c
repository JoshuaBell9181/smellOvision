

#include "fsl_device_registers.h"
#include "DAC_Functions.h"


void init_DAC(){
	SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;  // Enable clock for DAC0

	//DAC0_C0 = 0b10100000
	DAC0_C0 |= DAC_C0_DACEN_MASK;   // enable DAC0
	DAC0_C0 &= ~(DAC_C0_DACRFS_MASK);   // vREF = DACREF_1
	DAC0_C0 |= ~(DAC_C0_DACTRGSEL_MASK);// select hardware trigger
	DAC0_C0 &= ~(DAC_C0_DACSWTRG_MASK); // DAC software trigger not valid
	DAC0_C0 &= ~(DAC_C0_LPEN_MASK);     // high power mode
	DAC0_C0 &= ~(DAC_C0_DACBWIEN_MASK); // The DAC buffer watermark interrupt is disabled
	DAC0_C0 &= ~(DAC_C0_DACBTIEN_MASK); // The DAC buffer read pointer top flag interrupt is disabled
	DAC0_C0 &= ~(DAC_C0_DACBBIEN_MASK); // The DAC buffer read pointer bottom flag interrupt is disabled

	// DAC0_C1 = 0b00000000
	DAC0_C1 &= ~(DAC_C1_DMAEN_MASK);     // disable DAM
	DAC0_C1 &= ~(DAC_C1_DACBFWM_MASK);   // 1 WORD
	DAC0_C1 &= ~(DAC_C1_DACBFMD_MASK);  // DAC BUFFER WORK MODE = NORMAL MODE
	DAC0_C1 &= ~(DAC_C1_DACBFEN_MASK);  // Buffer read pointer is disabled. The converted data is always the first word of the buffer

}

/*
 * Description: Function to put a specific value on the DAC register
 * Parameters: The integer value to be sent out the DAC
 * Returns: None
 */
void convert_DAC(int dig){
	int low_bits = dig & 0x00FF;  // isolate lower 8 bits
	DAC0_DAT0L = low_bits;       // write lower bits to DAC0
	int high_bits  = (dig & 0x0F00) >> 8;  // isolate upper 4 bits
	DAC0_DAT0H = high_bits;   // write upper bits to DAC0
}
