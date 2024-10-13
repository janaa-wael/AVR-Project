/*
 * FLAME_SENSOR.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#include "FLAME_SENSOR.h"
#include "../../LIB/std_types.h"

void FlameSensor_init(void)
{
	GPIO_setupPinDirection(FLAME_SENSOR_PORT,FLAME_SENSOR_PIN,LOGIC_HIGH);
	GPIO_writePin(FLAME_SENSOR_PORT,FLAME_SENSOR_PIN,LOGIC_LOW);
}

uint8 FlameSensor_getValue(void)
{
	return GPIO_readPin(FLAME_SENSOR_PORT,FLAME_SENSOR_PIN);
}

