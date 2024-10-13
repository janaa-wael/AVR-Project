/*
 * TIMER.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */
#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"
#include <avr/io.h>

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCCR0 = (1<<WGM01) | (1<<WGM00) |  (1<<COM01) | (1<<CS02) | (1<<CS00);
	DDRB |= (1<<3);
	OCR0 = duty_cycle;
}
