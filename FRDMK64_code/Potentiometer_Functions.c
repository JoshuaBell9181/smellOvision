#include "fsl_device_registers.h"
#include "ADC_Functions.h"


int getSpeed(){
	//It is multiplied by 4 to scale our number for max output
	return getADC() * 4;
}
