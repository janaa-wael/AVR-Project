/*
 * pir.h
 *
 *  Created on: Nov 2, 2024
 *      Author: hp
 */

#ifndef HAL_PIR_SENSOR_PIR_H_
#define HAL_PIR_SENSOR_PIR_H_

#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

#define PIR_PORT	PORTC_ID
#define PIR_PIN		PIN2_ID

void PIR_SENSOR_INIT(void);
uint8 PIR_GET_READING(void);
#endif /* HAL_PIR_SENSOR_PIR_H_ */
