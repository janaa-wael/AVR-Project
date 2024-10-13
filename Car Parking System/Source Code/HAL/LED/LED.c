/*
 * LED.c
 *
 *  Created on: Oct 13, 2024
 *      Author: hp
 */


#include "LED.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIB/std_types.h"
#include "../../LIB/common_macros.h"

void LED_Init(void)
{
	GPIO_setupPinDirection(LED_RED_PORT,LED_RED_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LED_GREEN_PORT,LED_GREEN_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LED_BLUE_PORT,LED_BLUE_PIN,PIN_OUTPUT);
}


void LED_On(uint8 LED_ID)
{
	if(LED_ID == LED_RED)
	{
		GPIO_writePin(LED_RED_PORT,LED_RED_PIN,LOGIC_HIGH);
	}
	else if(LED_ID == LED_GREEN)
	{
		GPIO_writePin(LED_GREEN_PORT,LED_GREEN_PIN,LOGIC_HIGH);
	}
	else if(LED_ID == LED_BLUE)
	{
		GPIO_writePin(LED_BLUE_PORT,LED_BLUE_PIN,LOGIC_HIGH);
	}

}
void LED_Off(uint8 LED_ID)
{
	if(LED_ID == LED_RED)
	{
		GPIO_writePin(LED_RED_PORT,LED_RED_PIN,LOGIC_LOW);
	}
	else if(LED_ID == LED_GREEN)
	{
		GPIO_writePin(LED_GREEN_PORT,LED_GREEN_PIN,LOGIC_LOW);
	}
	else if(LED_ID == LED_BLUE)
	{
		GPIO_writePin(LED_BLUE_PORT,LED_BLUE_PIN,LOGIC_LOW);
	}
}
