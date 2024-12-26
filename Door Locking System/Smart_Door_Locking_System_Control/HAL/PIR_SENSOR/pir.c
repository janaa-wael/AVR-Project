/*
 * pir.c
 *
 *  Created on: Nov 2, 2024
 *      Author: hp
 */

#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"
#include "pir.h"

void PIR_SENSOR_INIT()
{
	GPIO_setupPinDirection(PIR_PORT,PIR_PIN,PIN_INPUT);
}

uint8 PIR_GET_READING()
{
	return (GPIO_readPin(PIR_PORT,PIR_PIN));
}
