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

#include "fsl_device_registers.h"
#include "FTM_Functions.h"
#include "GPIO_Functions.h"
#include "FTM_Functions.h"
#include "LED_Functions.h"
#include "UART_Functions.h"
#include "System_Timer.h"
#include "Motor_Functions.h"
#include "Potentiometer_Functions.h"
#include "ADC_Functions.h"
#include "DAC_Functions.h"



void initialize_all(){
	init_FTM();
	init_GPIO();
	init_UART();
	init_ADC();
	init_DAC();
}

int main()
{
	//Variables
	int timeToSpray = 0;

	//Initialize modules
	initialize_all();

	while(1){
			//Get the time in seconds when the spray should be triggered
			timeToSpray = getSprayTime();

			// Test string to send over serial communication debugging purposes
			char* test = "The number was received!";

			LED_on();//Turn On LED
			delay(timeToSpray);
			int speed = getSpeed();
			LED_off();//Turn off LED

			speed = getSpeed();
			setMotorSpeed(speed);
			delay(5);
			setMotorSpeed(0);

			// Should display the contents of test string to the putty terminal
			putString(test);
		}

	return 0;
}
