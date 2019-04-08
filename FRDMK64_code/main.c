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
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "fsl_device_registers.h"

double PI = 3.1415926535897932384;
typedef float complex cplx;


void UARTx_GPIOx_Init(){
	//Select UART0 and PORTB
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//Select port B16 alt3 and port B17 alt3
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_MUX(3);
	//Disable transmit/receive so we can change settings
	UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	//Set Baud rate TO 9600
	UART0_BDH = 0;
	UART0_BDL = 0x88;
	//Re-enable UART0 transmit/receive
	UART0_C2 |= UART_C2_TE_MASK ;
	UART0_C2 |= UART_C2_RE_MASK;
	//Mux enable the blue LED
	PORTB_PCR21 |= PORT_PCR_MUX(1);
	GPIOB_PDDR |= 1 << 21;
 	GPIOB_PSOR = 0x01 << 21;
}

void ADC_Init(){
	/////////////////////////////////////////////////////
	//Enable the clock to the ATD0 module
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Setting clock, sample timing, and conversion mode
	ADC0_CFG1 |= 0x67;

	//Set continuous mode enable
	ADC0_SC3 |= 0X8;
	//Set ADCH to 17 (pin E24)
	//ADC0_SC1A |= 0x11;
	/////////////////////////////////////////////////////
}

void DAC_Init(){
	SIM_SCGC2 |= 0x1000;
	DAC0_C0 |= 0xF0;						 //Enable DAC?
}

void UARTx_Putchar(char N){
	while(!(UART0_S1 & UART_S1_TDRE_MASK)){} //TDRE = transmit data register empty flag
	UART0_D = N;							 //Set UART0 data register equal to N
}

void UARTx_Putstring(char* str){
	int i = 0;
	while(str[i] != 0){
		UARTx_Putchar(str[i++]);			 //Continue to print characters of the string until
	}										 //the whole string has been printed
}

int ADCx_Convert(){
 	//int temp = 0;				//Temporary variable
	int z = 0;					//Return variable
	//temp = ADC0_RA;				//Set temp to value in ADC data register
	//while((ADC0_RA == temp)){};	//Wait until the data in the ADC register changes
	z = ADC0_RA;				//After a change, return the new ADC data
	return z;
}
void DACconvert(int voltage){
	DAC0_DAT0L = (voltage&&0x0FF);
	DAC0_DAT0H = ((voltage&0xF00)>>8);
}

 void UARTx_Getchar(){
	while(!(UART0_S1 & UART_S1_RDRF_MASK)){} //RDRF = Receive Data Register Full flag
	return;
}



int main(void){
                                                                                                 	UARTx_GPIOx_Init();					 	 //Initialize UART & GPIO
	ADC_Init();								 //Initialize the ADC
	DAC_Init();								 //Initialize the DAC
	int y;
	UARTx_Putstring("Start");				 //Print the string "Start" to Putty
	UARTx_Putchar(10);
	UARTx_Putchar(13);
	ADC0_SC1A &= 0x11;						 //Begin ADC conversion (channel 17)

	GPIOB_PCOR = 0x01 << 21;				 //Turn on blue LED
	DAC0_DAT0L = 0;
	DAC0_DAT0H = 0;
	float iterator[40000];
	for(int i = 0; i<40000; i++){
		iterator[i] = 0.001;
	}
	while(1){
		//for(int i = 0;i<40000;i++){
			//y = 5*sin(2*PI*60*iterator[i]);
		//}

		y = ADCx_Convert();
		DACconvert(y);

		//GPIOB_PSOR = 0x01 << 21;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
/*
printf("Logged energies: \n");
for(int j = 0; j < 12;j++){
	//printf("%f\n", energies[0][j]);
}
printf("DCT coeffs: \n");
for(int j = 0; j < 12;j++){
	//printf("%f\n", energies[0][j]);
}
//printf("MFCC coeffs: \n");
/*
FILE *f = fopen("H:\2019 Winter\Embedded\Templates\one.txt", "w");
int j = 250;
float py = 3.14;
fprintf(f, "Integer: %d, float: %f\n", j, py);
fclose(f);
*/

/*int ae_load_file_to_memory(const char *filename, char **result)
{
	int size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		*result = NULL;
		return -1; // -1 means file opening fail
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);
	if (size != fread(*result, sizeof(char), size, f))
	{
		free(*result);
		return -2; // -2 means file reading fail
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}
*/



