#ifndef SOURCES_UART_FUNCTIONS_H_
#define SOURCES_UART_FUNCTIONS_H_

/*
 * Created By: Matthew MacLennan
 * Description: Function to initialize the UART module
 * Parameters: None
 * Returns: None
 */
void init_UART();

/*
 * Created By: Joshua Bell
 * Description: Function to put a character out to serial communication
 * Parameters: Character to be outputted on the serial communication
 * Returns: None
 */
void putChar(char character);

/*
 * Created By: Matthew MacLennan
 * Description: Function to read a character from the serial communication
 * Parameters: None
 * Returns: The character that is read from the serial communication
 */
char getChar();

/*
 * Created By: Joshua Bell
 * Description: Function to put a new line onto the serial communication
 * Parameters: None
 * Returns: None
 */
void putString(char * string);

#endif
