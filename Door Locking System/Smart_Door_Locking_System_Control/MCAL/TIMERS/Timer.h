/*
 * TIMER.h
 *
 *  Created on: Oct 6, 2024
 *      Author: hp
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_
#include "../../LIB/common_macros.h"
#include "../../LIB/std_types.h"

typedef enum {
	TIMER0,
	TIMER1,
	TIMER2
}Timer_ID_Type;

typedef enum {
	NO_CLK_SRC,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_128,
	PRESCALER_256,
	PRESCALER_1024,
	EXT_SRC_FALLING,
	EXT_SRC_RISING
}Timer_ClockType;

typedef enum {
	NORMAL_MODE,
	PWM_PHASE_CORRECT_MODE,
	CTC_MODE,
	FAST_PWM_MODE
}Timer_ModeType;

typedef enum {
	NORMAL,
	TOGGLE,
	CLEAR,
	SET
}Timer_Output_Mode;

typedef enum {
	NORMAL_WGM_MODE,
	PWM_PHASE_CORRECT_8,
	PWM_PHASE_CORRECT_9,
	PWM_PHASE_CORRECT_10,
	CTC_OCR1A,
	FAST_PWM_8,
	FAST_PWM_9,
	FAST_PWM_10,
	PWM_PHASE_AND_FREQ_CORRECT_ICR1,
	PWM_PHASE_AND_FREQ_CORRECT_OCR1A,
	PWM_PHASE_CORRECT_ICR1,
	PWM_PHASE_CORRECT_OCR1A,
	CTC_ICR1,
	FAST_PWM_ICR1,
	FAST_PWM_OCR1A
}Timer1_WGM_MODES;

typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue; /*it will be used in compare mode only*/
	Timer_Output_Mode timer_compare_match_output_mode;
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
	Timer1_WGM_MODES timer1_wgm_mode;
}Timer_ConfigType;



void PWM_Timer0_Start(uint8 duty_cycle);
void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* MCAL_TIMER_TIMER_H_ */
