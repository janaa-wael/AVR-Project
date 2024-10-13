/*
 * LDR.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */
#include "LDR.h"
#include "../../MCAL/ADC/adc.h"
#include "../../LIB/std_types.h"



uint16 LDR_getLightIntensity(void)
{
	uint8 light_intensity_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	//light_intensity_value = ((float)adc_value/ADC_MAXIMUM_VALUE)*100;
	light_intensity_value = (uint8)(((uint32)adc_value*SENSOR_MAX_VALUE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
	//light_intensity_value = 100 - (adc_value / 1023.0)*100;
	return light_intensity_value;
}

