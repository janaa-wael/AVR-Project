/*
 * TIMER.c
 *
 *  Created on: Oct 6, 2024
 *      Author: hp
 */
#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "Timer.h"

void (*(g_ptrs[3]))(void);

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCCR0 = (1<<WGM01) | (1<<WGM00) |  (1<<COM01) | (1<<CS02) | (1<<CS00);
	DDRB |= (1<<3);
	OCR0 = duty_cycle;
}

void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	if(Config_Ptr->timer_ID == TIMER0)
	{
		if(Config_Ptr->timer_mode != FAST_PWM_MODE && Config_Ptr->timer_mode != PWM_PHASE_CORRECT_MODE)
			TCCR0 |= (1 << FOC0);

		TCCR0 |= (GET_BIT(Config_Ptr->timer_mode,0) << WGM00) | (GET_BIT(Config_Ptr->timer_mode,1) << WGM01);
		TCCR0 |= (Config_Ptr->timer_compare_match_output_mode) << COM00;
		TCCR0 |= (Config_Ptr->timer_clock << CS00);
		OCR0 = Config_Ptr->timer_InitialValue;

		if(Config_Ptr->timer_mode == CTC_MODE)
			TIMSK |= (1 << OCIE0);

		else if(Config_Ptr->timer_mode == NORMAL_MODE)
			TIMSK |= (1 << TOIE0);
	}
	else if(Config_Ptr->timer_ID == TIMER1)
	{
		// Set Compare Match Output Mode for OC1A
		TCCR1A |= (Config_Ptr->timer_compare_match_output_mode << COM1A0);

		// Set FOC1A if in CTC or Normal mode (not needed for PWM modes)
		if (Config_Ptr->timer_mode == CTC_MODE || Config_Ptr->timer_mode == NORMAL_MODE)
			TCCR1A |= (1 << FOC1A);

		// Set WGM bits for waveform generation mode
		TCCR1A |= (GET_BIT(Config_Ptr->timer1_wgm_mode, 0) << WGM10) |
				(GET_BIT(Config_Ptr->timer1_wgm_mode, 1) << WGM11);
		TCCR1B |= (GET_BIT(Config_Ptr->timer1_wgm_mode, 2) << WGM12) |
				(GET_BIT(Config_Ptr->timer1_wgm_mode, 3) << WGM13);

		// Set the clock prescaler
		TCCR1B |= Config_Ptr->timer_clock;

		// Set initial value and compare match value for Timer1
		TCNT1 = Config_Ptr->timer_InitialValue;
		OCR1A = Config_Ptr->timer_compare_MatchValue;

		// Enable interrupt based on timer mode
		if (Config_Ptr->timer_mode == CTC_MODE)
			TIMSK |= (1 << OCIE1A);  // Enable Compare Match A interrupt
		else if (Config_Ptr->timer_mode == NORMAL_MODE)
			TIMSK |= (1 << TOIE1);   // Enable Overflow interrupt
	}
	else if(Config_Ptr->timer_ID == TIMER2)
	{
		TCCR2 |= (Config_Ptr->timer_clock << 0) | (Config_Ptr->timer_mode << COM20);
		TCCR2 |= (GET_BIT(Config_Ptr->timer_mode,1) << WGM21) | (GET_BIT(Config_Ptr->timer_mode,0) << WGM20);
		if(Config_Ptr->timer_mode == CTC_MODE || Config_Ptr->timer_mode == NORMAL_MODE)
		{
			TCCR2 |= (1 << FOC2);
		}
		TCNT2 = Config_Ptr->timer_InitialValue;
		OCR2 = Config_Ptr->timer_compare_MatchValue;
	}
}
void Timer_deInit(Timer_ID_Type timer_type)
{
	if(timer_type == TIMER0)
	{
		TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // Stop Timer0
		TIMSK &= ~(1 << TOIE0);
		TIMSK &= ~(1 << OCIE0);
	}
	else if(timer_type == TIMER1)
	{
		TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Stop Timer1
		TIMSK &= ~(1 << TOIE1);
		TIMSK &= ~(1 << OCIE1A);
		TCNT1 = 0;
	}
	else if(timer_type == TIMER2)
	{
		TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Stop Timer2
		TIMSK &= ~(1 << TOIE2);
		TIMSK &= ~(1 << OCIE2);
	}
}
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	if(a_timer_ID == TIMER0)
	{
		g_ptrs[TIMER0] = a_ptr;
	}
	else if(a_timer_ID == TIMER1)
	{
		g_ptrs[TIMER1] = a_ptr;
	}
	else if(a_timer_ID == TIMER2)
	{
		g_ptrs[TIMER2] = a_ptr;
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_ptrs[TIMER0] != NULL)
		g_ptrs[TIMER0]();
}

ISR(TIMER0_OVF_vect)
{
	if(g_ptrs[TIMER0] != NULL)
		(*(g_ptrs[TIMER0]))();
}

ISR(TIMER1_COMP_vect)
{
	if(g_ptrs[TIMER1] != NULL)
		(*(g_ptrs[TIMER1]))();
}

ISR(TIMER1_OVF_vect)
{
	if(g_ptrs[TIMER1] != NULL)
		(*(g_ptrs[TIMER1]))();
}

ISR(TIMER2_COMP_vect)
{
	if(g_ptrs[TIMER2] != NULL)
		g_ptrs[TIMER2]();
}

ISR(TIMER2_OVF_vect)
{
	if(g_ptrs[TIMER2] != NULL)
		g_ptrs[TIMER2]();
}
