#ifndef SOURCES_Switch_FUNCTIONS_H_
#define SOURCES_Switch_FUNCTIONS_H_

/*
 * Created By: Joshua Bell
 * Description: Function intialize SW2 for use on the FRDMK64 board
 * Parameters: None
 * Returns: None
 */
void switch_init();

/*
 * Created By: Joshua Bell
 * Description: Function wait until switch has been pressed
 * Parameters: None
 * Returns: int witch indicated a boolean value
 */
int switch_pressed();

#endif
