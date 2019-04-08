/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"
#include "fsl_device_registers.h"
#include "Switch_Functions.h"
#include "UART_Functions.h"

// begin the program

//Part One: Initialization of all hardware to be used

void init_FTM(){

	//initialize the flex timer

	//wake up timer to be assigned to the FTM module
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

	//Wake up timer to port A, as the FTM must be linked to a pin
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Setting Port A pin 3to be linked to the FTM module channel 0
	PORTA_PCR3 |= PORT_PCR_MUX(3);


	//Turn write protection mode off
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;

	//set pre-scale to divide by 1
	FTM0_SC = 0x0;

	// set mode to count to the max value (i.e. 2^16)
	FTM0_MOD |= 0xFFFF;


	return;
}


void delay(int time){
	// takes in a integer called time, will delay algorithm for 'time' seconds
	char status = 'c';
	int pressed = 0;
	pressed = GPIOC_PDIR & 0x00000040;
	int timer = time / 0.0031207;
	int  count2 = 0;

	// Turn clock on and begin counting
	FTM0_SC = 0x8;

	//while our count has not reached to zero, keep decrementing count
	while (count2 < timer){

		if(pressed){
			// check when the overflow flag is equal to one
			if ( FTM0_SC & (0x1 << 7) ){

					//increment the counter
					count2++;

					// Reseting the overflow flag to 0
					FTM0_SC &= ~(0x80);

			}//end if
		} else {
			status = 'p';
			putChar(status);
			for(int i =0; i <1000000;i++);
			pressed = switch_pressed();
			status = 'c';
			putChar(status);
		}

	}//end while

	//Turn the timer off
	FTM0_SC &= ~(0x8);


	return;
}// end myDelay



