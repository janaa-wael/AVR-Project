/*
 * LED.h
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "../../MCAL/GPIO/gpio.h"

#define LED_RED_ID 			0
#define LED_GREEN_ID	 	1
#define LED_BLUE_ID 		2


#define LED_RED_PORT	PORTB_ID
#define LED_RED_PIN		PIN5_ID

#define LED_GREEN_PORT	PORTB_ID
#define LED_GREEN_PIN	PIN6_ID

#define LED_BLUE_PORT	PORTB_ID
#define LED_BLUE_PIN	PIN7_ID




void LEDS_init(void);

void LED_on(uint8 id);

void LED_off(uint8 id);

#endif /* HAL_LED_LED_H_ */
