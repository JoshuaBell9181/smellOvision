#ifndef SOURCES_DAC_FUNCTIONS_H_
#define SOURCES_DAC_FUNCTIONS_H_

/*
 * Create By: Joshua Bell
 * Description: Function to initialize DAC0 module
 * Parameters: None
 * Returns: None
 */
void init_DAC();

/*
 * Created By: Joshua Bell
 * Description: Function to put a specific value on the DAC register
 * Parameters: The integer value to be sent out the DAC
 * Returns: None
 */
void convert_DAC(int dig);



#endif
