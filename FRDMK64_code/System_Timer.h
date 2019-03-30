#ifndef SOURCES_SYSTEM_TIMER_H_
#define SOURCES_SYSTEM_TIMER_H_

/*
 * Created By: Joshua Bell
 * Description: Function convert UART communication time from type char to int
 * Parameters: a is a number between 0-9, count keeps track of largest base 10 number, current number is the return number
 * Returns: Integer time in seconds
 */
int lookUpTable(char a,int count, int currentNum);

/*
 * Created By: Matthew MacLeannan
 * Description: Function waits for a time to spray input 
 * Parameters: None
 * Returns: Integer time to release spray
 */
int getSprayTime();

#endif
