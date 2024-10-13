/*
 * motor.c
 *
 *  Created on: Oct 6, 2024
 *      Author: Jana Wael
 */

#include "motor.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(IN1_PORT,IN1_PIN,LOGIC_HIGH);
	GPIO_setupPinDirection(IN2_PORT,IN2_PIN,LOGIC_HIGH);
	GPIO_setupPinDirection(EN1_PORT,EN1_PIN,LOGIC_HIGH);
	GPIO_writePin(EN1_PORT,EN1_PIN,LOGIC_LOW);
}

void DcMotor_Rotate(uint8 state, uint8 speed)
{
	if(state == CLKWISE)
	{
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_HIGH);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
		GPIO_writePin(EN1_PORT,EN1_PIN,LOGIC_HIGH);
		PWM_Timer0_Start(speed);
	}
	else if(state == ANTICLKWISE)
	{

		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_HIGH);
		GPIO_writePin(EN1_PORT,EN1_PIN,LOGIC_HIGH);
		PWM_Timer0_Start(speed);
	}
	else if(state == STOP)
	{
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_HIGH);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
		GPIO_writePin(EN1_PORT,EN1_PIN,LOGIC_LOW);
		PWM_Timer0_Start(0);
	}
}
