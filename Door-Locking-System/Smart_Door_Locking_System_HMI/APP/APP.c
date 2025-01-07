/*
 * APP.c
 *
 *  Created on: Nov 1, 2024
 *      Author: hp
 */
#include "../LIB/common_macros.h"
#include "../LIB/std_types.h"
#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/UART/uart.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include <util/delay.h>
#include <avr/io.h>

uint8 pass[5];
uint8 re_pass[5];

void MCAL_INIT(void)
{
	UART_init(9600);
}

void HAL_INIT(void)
{
	LCD_init();
	KEYPAD_voidInit();
}

void Display_Welcome_Msg(void)
{
	LCD_displayString("Door Locking");
	LCD_moveCursor(1,4);
	LCD_displayString("System");
	_delay_ms(4000);
	LCD_clearScreen();
}


uint8 KEYPAD_USER_INPUT(void)
{
	uint8 input = 'x';
	while(input == 'x')
		input = KEYPAD_READ();
	return input;
}

void DISPLAY_CREATE_PASS_MSG(void)
{
	LCD_clearScreen();
	LCD_displayString("Plz enter pass:");
}

void DISPLAY_REENTER_PASS_MSG(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Reenter pass:");
}

void ENTER_PASS(uint8* password)
{
	uint8 counter = 0;
	uint8 input = KEYPAD_USER_INPUT();
	while(input != 'c')
	{
		LCD_displayCharacter(input);
		UART_sendByte(input);
		password[counter++] = input;
		input = KEYPAD_USER_INPUT();
	}
	password[counter] = '\0';
	UART_sendByte('c');
}


void CREATE_PASSWORD(void)
{
	DISPLAY_CREATE_PASS_MSG();
	LCD_moveCursor(1,0);
	ENTER_PASS(pass);
	DISPLAY_REENTER_PASS_MSG();
	LCD_moveCursor(1,0);
	ENTER_PASS(re_pass);
	LCD_clearScreen();
}


void SetUpSystemPassword(void)
{
	uint8* received_byte;
	CREATE_PASSWORD();
	LCD_clearScreen();
	LCD_displayString("Password Sent");
	received_byte = UART_recieveByte();
	if(received_byte == 'F')
	{
		LCD_clearScreen();
		LCD_displayString("False");
		_delay_ms(500);
		SetUpSystemPassword();
	}
	else if(received_byte == 'T')
	{
		LCD_clearScreen();
		LCD_displayString("True");

	}
}

void MainOptionsDisplay(uint8* change_pass_flag)
{
	uint8 choice, received_byte, wrong_pass_counter=0;
	uint8 user_pass[5];
	LCD_clearScreen();
	LCD_displayString("+: Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("-: Change pass");
	choice = KEYPAD_USER_INPUT();
	UART_sendByte(choice);
	_delay_ms(1);
	switch(choice)
	{
	case '+':
		do {
			if(wrong_pass_counter == 3)
			{
				UART_sendByte('L');
				LCD_clearScreen();
				LCD_displayString("System Locked!");
				for(int i = 0 ; i < 60 ; i++)
				_delay_ms(1000);
				LCD_clearScreen();
				break;
			}
			LCD_clearScreen();
			LCD_displayString("Plzz enter pass");
			LCD_moveCursor(1,0);
			ENTER_PASS(pass);
			received_byte = UART_recieveByte();
			if(received_byte == 'F')
			{
				wrong_pass_counter++;
				LCD_clearScreen();
				LCD_displayString("Incorrect pass");
				_delay_ms(500);
			}
		}while(received_byte == 'F');

		if(wrong_pass_counter==3)
		{
			wrong_pass_counter = 0;
			break;
		}
		UART_sendByte(received_byte);
		LCD_clearScreen();
		LCD_displayString("Opening Door");
		received_byte = UART_recieveByte();
		if(received_byte == 'P')
		{
			LCD_clearScreen();
			LCD_displayString("Wait for pple");
		}
		if(UART_recieveByte() == 'B')
		{
			LCD_clearScreen();
			LCD_displayString("Locking Door");
			_delay_ms(15000);
		}
		break;
	case '-':
		*change_pass_flag = 1;
		break;
	}

}
///////////////////////////////
void OpenDoor(void)
{

	UART_sendByte('O');
	if(UART_recieveByte() == 'L')
	{
		LCD_displayString("Door Unlocking");
		LCD_moveCursor(1,2);
		LCD_displayString("Please Wait");
	}
	_delay_ms(100);
	while(UART_recieveByte() == 'N');
	while(UART_recieveByte() == 'Y')
	{
		LCD_clearScreen();
		LCD_displayString("Wait for pple");
		LCD_moveCursor(1,3);
		LCD_displayString("to enter");

	}
}

void LockDoor(void)
{
	if(UART_recieveByte() == 'C')
	{
		LCD_clearScreen();
		LCD_displayString("Locking Door");

	}
}

void CHECK_PASSWORDS(void)
{
	if(UART_recieveByte() == 'F')
		CREATE_PASSWORD();
	else
	{
		LCD_clearScreen();
		LCD_displayString("Door is unlocking");
		if(UART_recieveByte() == 'O')
		{
			LCD_clearScreen();
			LCD_displayString("Wait for people");
		}
		while(UART_recieveByte() == 'O');
		if(UART_recieveByte() == 'C')
		{
			LCD_clearScreen();
			LCD_displayString("Door is locking");
			_delay_ms(15000);
		}

	}
}

void PASSWORD_REGISTRATION(void)
{
	uint8 received_byte;
	uint8 received_str[6];
	DDRD |= 1<<3;

	CREATE_PASSWORD();

	_delay_ms(1000);  // Ensure Control ECU has time to process
	//while (UART_recieveByte() != 'T');



	UART_receiveString(received_str);
	if(strcmp(received_str,"FALSE")==0)
	{
		LCD_clearScreen();
		LCD_displayString("False");
		_delay_ms(2000);
		PASSWORD_REGISTRATION();
	}
	else if(strcmp(received_str,"TRUE")==0)
	{
		LCD_clearScreen();
		LCD_displayString("True");
		_delay_ms(2000);

	}
}


/*void DOOR_LOCK_AND_UNLOCK(void)
{

}*/
