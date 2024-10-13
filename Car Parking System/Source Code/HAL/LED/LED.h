/*
 * LED.h
 *
 *  Created on: Oct 13, 2024
 *      Author: hp
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "../../MCAL/GPIO/gpio.h"

#define LED_RED			0
#define LED_GREEN		1
#define LED_BLUE		2

#define LED_RED_PORT		PORTC_ID
#define LED_GREEN_PORT		PORTC_ID
#define LED_BLUE_PORT		PORTC_ID

#define LED_RED_PIN			PIN0_ID
#define LED_GREEN_PIN		PIN1_ID
#define LED_BLUE_PIN		PIN2_ID

void LED_Init(void);
void LED_On(uint8 LED_ID);
void LED_Off(uint8 LED_ID);
#endif /* HAL_LED_LED_H_ */
