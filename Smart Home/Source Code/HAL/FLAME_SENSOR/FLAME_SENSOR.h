/*
 * FLAME_SENSOR.h
 *
 *  Created on: Oct 6, 2024
 *      Author: hp
 */

#ifndef HAL_FLAME_SENSOR_FLAME_SENSOR_H_
#define HAL_FLAME_SENSOR_FLAME_SENSOR_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

#define FLAME_SENSOR_PORT	PORTD_ID
#define FLAME_SENSOR_PIN	PIN2_ID

void FlameSensor_init(void);
uint8 FlameSensor_getValue(void);

#endif /* HAL_FLAME_SENSOR_FLAME_SENSOR_H_ */
