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

#include "fsl_device_registers.h"

void UART0_Intertface_Init(){

	//Step 1: Use sim module to enable UART0 and PORTB
	// Use sim module to enable UART0
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	// Use sim module to enable PORTB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	//Step 2: Use the port mudle to enable pins
	// Use the port module to enable pin 16 for UART0_RX
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	// Use the port module to enable pin 17 for UART0_TX
	PORTB_PCR17 |= PORT_PCR_MUX(3);

	//Step 3: Use the UART module to configure UART0 for use with terminal serial communication
	//Disable transmit enable and recieve enable
	UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	//Configure UART0 for 8 bits and Disable parity
	UART0_C1 = 0b00000000;

	//set the baud rate to 9600;
	UART0_BDH = 0;
	UART0_BDL = 0x88;

	// Enable transmit and recieve
	UART0_C2 |= UART_C2_TE_MASK;
	UART0_C2 |= UART_C2_RE_MASK;
}

void initTimer(){
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

void putChar(char character){
	// Read the UART0_TDRE until its a 1
	while(!(UART0_S1 & 0x80));
	//Send data
	UART0_D = character;
}

char getChar(){
	// Read UART0_RDRF until 1
	while(!(UART0_S1 & 0x20));
	// Set val equal to recieved data
	char val = UART0_D;
	return val;
}

void putString(char * string){

	//Iterate through the string until null character is found
	do{
		// Print each char out individually
		putChar(*string);
	}while(*string++);

}

int lookUpTable(char a,int count, int currentNum){
	int i = (int)a;
	switch(i){
	case 0x30:
		i = 0;
		break;
	case 0x31:
		i = 1;
		break;
	case 0x32:
		i = 2;
		break;
	case 0x33:
		i = 3;
		break;
	case 0x34:
		i = 4;
		break;
	case 0x35:
		i = 5;
		break;
	case 0x36:
		i = 6;
		break;
	case 0x37:
		i = 7;
		break;
	case 0x38:
		i = 8;
		break;
	case 0x39:
		i = 9;
		break;
	}

	if(count == 0){
		return i;
	}else{
		return (currentNum * 10) + i;
	}
}

int getSprayTime(){
	//Get a char from serial terminal
	int count = 0;
	int time = 0;
	char a = getChar();
	while(a != '.'){
		if(a=='0' || a=='1' || a=='2' || a=='3' || a=='4' || a=='5' || a=='6' || a=='7' || a=='8' || a=='9'){
			time = lookUpTable(a,count,time);
		}
		a = getChar();
		count++;
	}

	return time;
}

void myDelay(int t, int PULSE_LENGTH){
	t = t * PULSE_LENGTH;
	FTM0_C0V |= 1000;
	int delayThreshold = t;
	int count = 0;
	//Loop while we havnt reached the
	//value to be counted to
	while(count < delayThreshold){
		if(FTM0_MOD == FTM0_C0V){
			FTM0_C0V = 0;
			count++;
		}else{
			FTM0_C0V += 1000;
		}
	}
}

int main(void)
{
	//Variables
	int timeToSpray = 0;
	const int PULSE_LEGNTH_CONST = 0x560e;

	// Initializes the board
	UART0_Intertface_Init();

	//Initialize time and LED to display timer done
	initTimer();

	while(1){
		//Get the time in seconds when the spray should be triggered
		timeToSpray = getSprayTime();

		// Test string to send over serial communication
		char* test = "The number was received!";

		GPIOB_PCOR = 0x01<<22;//Turn On LED
		myDelay(timeToSpray,PULSE_LEGNTH_CONST);
		GPIOB_PSOR = 0x01<<22;//Turn off LED

		// Should display the contents of test string to the putty terminal
		putString(test);
	}


    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
