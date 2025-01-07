/*
 * ultrasonic_sensor.h
 *
 *  Created on: Oct 13, 2024
 *      Author: hp
 */

#ifndef HAL_ULTRASONIC_SENSOR_ULTRASONIC_SENSOR_H_
#define HAL_ULTRASONIC_SENSOR_ULTRASONIC_SENSOR_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

#define TRIG_PORT	PORTD_ID
#define TRIG_PIN	PIN7_ID

#define ECHO_PORT	PORTD_ID
#define ECHO_PIN	PIN6_ID

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);
uint16 Get_Periodic_Time();
#endif /* HAL_ULTRASONIC_SENSOR_ULTRASONIC_SENSOR_H_ */
