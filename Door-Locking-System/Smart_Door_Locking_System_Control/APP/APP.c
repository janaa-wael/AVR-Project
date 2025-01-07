/*
 * APP.c
 *
 *  Created on: Nov 2, 2024
 *      Author: hp
 */
#include "APP.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/TIMERS/Timer.h"
#include "../HAL/EEPROM/external_eeprom.h"
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/MOTOR/motor.h"
#include "../HAL/PIR_SENSOR/pir.h"
#include "../LIB/common_macros.h"
#include "../MCAL/TWI/twi.h"
#include "../LIB/std_types.h"
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>

uint8 timer_flag;
uint8 pass[6];
uint8 repass[6];
uint8 g_timer2_ticks;

extern void (*(g_ptrs[3]))(void);
void (*a_ptr)(void) ;

void MCAL_INIT(void)
{
	UART_init(9600);
	//a_ptr = &Timer1_CallbackFunction;
	//Timer_setCallBack(a_ptr,TIMER1);
	SREG |= (1<<7);
	TWI_init();
}

void HAL_INIT(void)
{
	PIR_SENSOR_INIT();
	DcMotor_Init();
	Buzzer_init();
}


void SetupSystemPass(void)
{
	for(int i = 0 ; i < 5 ; i++)
		pass[i] = UART_recieveByte();
	pass[5] = '\0';
	UART_recieveByte();
	for(int i = 0 ; i < 5 ; i++)
		repass[i] = UART_recieveByte();
	repass[5] = '\0';
	_delay_ms(1000);
	if(strcmp(pass,repass) == 0)
		Buzzer_on();
	while(UART_recieveByte() != 'c');
	if(strcmp(pass,repass) == 0)
	{
		UART_sendByte('T');
		Save_Pass_In_EEPROM(pass);
	}
	else
		UART_sendByte('F');
	Buzzer_off();
}


void Receive_MainOptionChar(uint8* change_pass_flag)
{
	uint8 received_pass[6];
	uint8 i =0,wrong_pass_counter = 0;
	uint8 received_byte = UART_recieveByte();
	Timer_ConfigType Timer_Config = {0, 0, 0xFFFF, TIMER1, PRESCALER_1024, NORMAL_MODE, NORMAL_WGM_MODE};
	Timer_ConfigType* Timer_Ptr = &Timer_Config; // Assign the address to Timer_Ptr
	switch(received_byte)
	{
	case '+':
		do{
			if(wrong_pass_counter==3)
			{
				Buzzer_on();
				for(int i = 0 ; i < 60 ; i++)
					_delay_ms(1000);
				Buzzer_off();
				break;
			}
			for( i = 0 ; i < 5 ; i++)
			{
				received_pass[i] = UART_recieveByte();
			}
			received_pass[5] = '\0';
			while(UART_recieveByte() != 'c');
			//UART_sendPass(received_pass);

			if(Cmp_Received_Pass(received_pass))
			{

				UART_sendByte('T');
				Buzzer_on();
				_delay_ms(3000);
				Buzzer_off();
			}
			else
			{
				wrong_pass_counter++;
				UART_sendByte('F');
			}
		}while(strcmp(received_pass,pass) != 0);
		if(wrong_pass_counter==3)
		{
			wrong_pass_counter = 0;
			break;
		}
		DcMotor_Rotate(CLKWISE,255);
		_delay_ms(150000);

		//Timer_init(Timer_Ptr);
		//while(g_timer2_ticks < 1);
		//Timer_deInit(TIMER2);
		//g_timer2_ticks=0;
		DcMotor_Rotate(STOP,0);

		while(PIR_GET_READING() == 0);
		UART_sendByte('P');
		while(PIR_GET_READING() == 1);
		UART_sendByte('B');

		DcMotor_Rotate(ANTICLKWISE,255);
		_delay_ms(150000);
		//Timer_init(Timer_Ptr);
		while(g_timer2_ticks < 3);
		//Timer_deInit(TIMER2);
		DcMotor_Rotate(STOP,0);
		break;
	case '-':
		*change_pass_flag = 1;
		break;
	}
}
/*
void OpenDoor(void)
{
	//Timer_ConfigType* Timer_Ptr = {0,0,0xFFFF,TIMER1,PRESCALER_1024,NORMAL_MODE,NORMAL_WGM_MODE};
	DcMotor_Rotate(CLKWISE,255);
	//Timer_init(Timer_Ptr);
	a_ptr = &Timer1_CallbackFunction;
	Timer_setCallBack(a_ptr,TIMER0);
	while(timer_flag == 0);
	UART_sendByte('L');
	while(PIR_GET_READING() == 0)
	{
		UART_sendByte('N');
		_delay_ms(1);
	}
	while(PIR_GET_READING() == 1)
	{
		UART_sendByte('Y');
		_delay_ms(1);
	}
	if(PIR_GET_READING() == 0)
	{
		timer_flag = 0;
		UART_sendByte('C');
		DcMotor_Rotate(ANTICLKWISE,255);
		Timer_init(Timer_Ptr);
		while(timer_flag == 0);
	}
}*/

void Save_Pass_In_EEPROM(uint8* received_pass)
{
	for(int i = 0 ; i < 5 ; i++)
	{
		EEPROM_writeByte(0x01+i,received_pass[i]);
		_delay_ms(150);
	}
	EEPROM_writeByte(0x01+5,'\0');
}

uint8 Cmp_Received_Pass(uint8* rec_pass)
{
	for(int i = 0 ; i < 6 ; i++)
	{
		uint8 data;
		EEPROM_readByte(0x01+i,&data);
		if(rec_pass[i] != data)
			return 0;
		_delay_ms(100);
	}
	return 1;
}

void Timer1_CallbackFunction(void)
{
	g_timer2_ticks++;
}


void UART_sendPass(const uint8 *str)
{
	uint8 i = 0;
	while (i<5)
	{
		UART_sendByte(str[i++]);
		_delay_ms(1);
	}
}


