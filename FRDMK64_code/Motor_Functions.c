#include "fsl_device_registers.h"
#include "DAC_Functions.h"


void setMotorSpeed(int dig){
	convert_DAC(dig);
}
