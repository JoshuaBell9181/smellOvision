#include "UART_Functions.h"

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
