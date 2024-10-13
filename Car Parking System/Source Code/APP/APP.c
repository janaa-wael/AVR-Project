/*
 * APP.c
 *
 *  Created on: Oct 13, 2024
 *      Author: hp
 */
#include "../HAL/LCD/lcd.h"
#include "../HAL/LED/LED.h"
#include "../HAL/ULTRASONIC_SENSOR/ultrasonic_sensor.h"
#include "../MCAL/ICU/icu.h"
#include "../LIB/common_macros.h"
#include "../LIB/std_types.h"
#include <avr/io.h>
#include <util/delay.h>

extern g_edgeCount, g_timeHigh;

void MCAL_Init()
{
	SREG |= (1<<7);
}

void HAL_Init(void)
{
	LCD_init();
	Ultrasonic_init();
	Buzzer_init();
	LED_Init();
}

void LCD_constant_msg(void)
{
	LCD_displayString("Distance=    cm");

}

void LCD_Print_Distance(void)
{
	LCD_moveCursor(0,9);
	uint16 distance = Ultrasonic_readDistance();
	LCD_intgerToString(distance);
	if(distance <= 5)
	{
		LCD_displayString("  ");
		Buzzer_on();
		LCD_STOP_MSG();
		TURN_ALL_LEDS_ON();
		_delay_ms(200);
		TURN_ALL_LEDS_OFF();
		_delay_ms(200);
	}
	else if(distance <= 10)
	{
		if(distance != 10)
			LCD_displayString("  ");
		else
			LCD_displayCharacter(' ');
		LCD_REMOVE_STOP_MSG();
		TURN_ALL_LEDS_ON();
		Buzzer_off();
	}
	else if(distance <= 15)
	{
		LCD_displayCharacter(' ');
		LED_On(LED_RED);
		LED_On(LED_GREEN);
		LED_Off(LED_BLUE);
		Buzzer_off();
		LCD_REMOVE_STOP_MSG();
	}
	else if(distance <= 20)
	{
		LCD_displayCharacter(' ');
		LED_On(LED_RED);
		LED_Off(LED_GREEN);
		LED_Off(LED_BLUE);
		Buzzer_off();
		LCD_REMOVE_STOP_MSG();
	}
	else if(distance > 20)
	{
		if(distance <= 99)
			LCD_displayCharacter(' ');

		TURN_ALL_LEDS_OFF();
		Buzzer_off();
		LCD_REMOVE_STOP_MSG();
		if(distance == 432)
			LCD_displayString("432");
	}

}

void TURN_ALL_LEDS_ON(void)
{
	LED_On(LED_RED);
	LED_On(LED_GREEN);
	LED_On(LED_BLUE);
}

void TURN_ALL_LEDS_OFF(void)
{
	LED_Off(LED_RED);
	LED_Off(LED_GREEN);
	LED_Off(LED_BLUE);
}

void LCD_STOP_MSG(void)
{
	LCD_moveCursor(1,6);
	LCD_displayString("STOP!");
	LCD_moveCursor(0,9);
}

void LCD_REMOVE_STOP_MSG(void)
{
	LCD_moveCursor(1,6);
	LCD_displayString("     ");
	LCD_moveCursor(0,9);
}
