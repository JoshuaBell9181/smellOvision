
#include "fsl_device_registers.h"
#include "Switch_Functions.h"
#include "UART_Functions.h"

void init_FTM(){

	/**
	 * Timer Initialization
	 */
	//Initialize timer for FTM0
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	//Initialize timer for PortA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Set PortA PCR3 to FTM0_CH0
	PORTA_PCR3 |= PORT_PCR_MUX(3);

	//Turn Write Protection Off
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;

	//Make sure the FTM0 Status Control Register is 0
	FTM0_SC = 0;

	//Set the Prescale Factor to Divide By 128
	FTM0_SC |= 0x07;

	//Set the Clock Source Selection to System Clock
	FTM0_SC |= 0x01;

	//Set the Modulo value
	FTM0_MOD = 27000;

	//Set MSB=1 and ELSnB=1
	//This means Mode is Output Compare and
	//Configuration is Toggle Output on Match
	FTM0_C0SC |= 0x28;
}

void delay(int t, int PULSE_LENGTH){
	t = t * PULSE_LENGTH;
	char status = 'c';
	int pressed = 0;
	pressed = GPIOC_PDIR & 0x00000040;
	FTM0_C0V |= 1000;
	int delayThreshold = t;
	int count = 0;
	//Loop while we havnt reached the
	//value to be counted to
	while(count < delayThreshold){

		if(pressed){
			if(FTM0_MOD == FTM0_C0V){
				FTM0_C0V = 0;
				count++;
			}else{
				FTM0_C0V += 1000;
			}
			pressed = GPIOC_PDIR & 0x00000040;
		} else{
			status = 'p';
			putChar(status);
			for(int i =0; i <1000000;i++);
			pressed = switch_pressed();
			status = 'c';
			putChar(status);
		}

	}

}


