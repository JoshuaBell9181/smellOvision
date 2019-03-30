#include "fsl_device_registers.h"

void init_UART(){

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
