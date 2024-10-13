/*
 * LED.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */
#include "LED.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

void LEDS_init(void)
{
	GPIO_setupPinDirection(LED_RED_PORT, LED_RED_PIN, LOGIC_HIGH);
	GPIO_setupPinDirection(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_HIGH);
	GPIO_setupPinDirection(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_HIGH);
	GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_LOW);
	GPIO_writePin(LED_RED_PORT, LED_GREEN_PIN, LOGIC_LOW);
	GPIO_writePin(LED_RED_PORT, LED_BLUE_PIN, LOGIC_LOW);
}

void LED_on(uint8 id)
{
	if(id == LED_RED_ID)
	{
		GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_HIGH);
	}
	else if(id == LED_GREEN_ID)
	{
		GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_HIGH);
	}
	else if(id == LED_BLUE_ID)
	{
		GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_HIGH);
	}
}

void LED_off(uint8 id)
{
	if(id == LED_RED_ID)
	{
			GPIO_writePin(LED_RED_PORT, 	LED_RED_PIN,	LOGIC_LOW);
	}
		else if(id == LED_GREEN_ID)
	{
			GPIO_writePin(LED_GREEN_PORT,	LED_GREEN_PIN,	LOGIC_LOW);
	}
		else if(id == LED_BLUE_ID)
	{
			GPIO_writePin(LED_BLUE_PORT, 	LED_BLUE_PIN, 	LOGIC_LOW);
	}
}
