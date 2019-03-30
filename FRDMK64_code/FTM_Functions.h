
//FTM_Header file
#ifndef SOURCES_FTM_FUNCTIONS_H_
#define SOURCES_FTM_FUNCTIONS_H_

/*Created By: Matthew MacLennan
* Description: Initializes the FTM module for FTM0_CH0 on PTC1 (header J1_5). Configures FTM0 for rising edge input capture.
* Input Paramaters: None
* Return: None
*/ 
void init_FTM();

/*Created By: Matthew MacLennan
* Description: Create delay to wait t seconds
* Input Paramaters: t is time in seconds and PULSE_LENGTH is used to manipulate delay time
* Return: None
*/ 
void delay(int t, int PULSE_LENGTH);

#endif
