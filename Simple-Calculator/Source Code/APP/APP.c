/*
 * APP.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Jana Wael
 */
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../LIB/std_types.h"
#include <util/delay.h>
#include "APP.h"

sint64 whole_numbers[20] = {}, result = 0, operands_simplified[20] = {}, operations_simplified[20] = {};
uint8 operations[10] = {};
uint8 operations_counter = 0, whole_numbers_counter = 0;
sint64 old_num = 0;
uint8 input;

void HAL_Init(void)
{
	LCD_init();
	KEYPAD_voidInit();
}

void LCD_init_msg()
{
	LCD_displayString("Initializing");
	LCD_moveCursor(1,0);
	LCD_displayString("Calculator..");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
}

uint8 ConvertCharToInt(uint8 input)
{
	return (input-'0');
}

uint8 Get_Keypad_Input()
{
	uint8 input = 'x';
	while(input == 'x')
		input = KEYPAD_READ();
	return input;
}

void User_Formula_Input(void)
{
	uint8 prev_input=0,neg_flag = 0;
	while(1)
	{
		input =  Get_Keypad_Input();
		LCD_displayCharacter(input);
		if( (prev_input == '+' || prev_input == '*' || prev_input == '/') && input == '-')
		{
			neg_flag = 1;
			continue;
		}
		else if(prev_input == '-' && input == '-')
		{
			input = '+';
		}
		if(input == '+' || input == '-' || input == '/' || input == '*')
		{
			if(neg_flag)
			{
				operations[operations_counter++] = input;
				whole_numbers[whole_numbers_counter++] = -1*old_num;
				neg_flag = 0;
			}
			else
			{
				operations[operations_counter++] = input;
				whole_numbers[whole_numbers_counter++] = old_num;
			}
			old_num = 0;
		}
		else if(input == '=')
		{
			whole_numbers[whole_numbers_counter++] = old_num;
			old_num = 0;
			break;
		}
		else if(input == 'c')
		{
			User_Clearing_Screen();
		}
		else
		{
			old_num = old_num*10UL + ConvertCharToInt(input);
		}
		prev_input = input;
	}
	if(neg_flag)
	{
		whole_numbers[whole_numbers_counter-1] *= -1;
	}
}
sint64 Equation_Simplification()
{
	uint8 i = 0;

	for(;i<whole_numbers_counter;i++)
	{
		if(operations[i] == '/')
		{
			if(whole_numbers[i+1] == 0)
			{
				RunTimeErrorMsg();
				Reset_Arrays();
				return 'x';
			}
			if(operations[i+1] != '*' && operations[i+1] != '/')
			{
				whole_numbers[i] = whole_numbers[i]/whole_numbers[i+1];
				whole_numbers[i+1] = 0;
				operations[i] = '+';
			}
			else
			{
				whole_numbers[i+1] = whole_numbers[i]/whole_numbers[i+1];
				whole_numbers[i] = 0;
				operations[i] = '+';
			}
		}
		else if(operations[i] == '*')
		{
			if(operations[i+1] != '*' && operations[i+1] != '/')
			{
				whole_numbers[i] = whole_numbers[i]*whole_numbers[i+1];
				whole_numbers[i+1] = 0;
				operations[i] = '+';
			}
			else
			{
				whole_numbers[i+1] = whole_numbers[i]*whole_numbers[i+1];
				whole_numbers[i] = 0;
				operations[i] = '+';
			}
		}

	}
	return Second_Simplification();
}

sint64 Second_Simplification(void)
{
	uint8 operand_counter = 0;
	uint8 operation_counter = 0;
	sint64 res = whole_numbers[operand_counter++];
	while(operand_counter < whole_numbers_counter)
	{
		if(operations[operation_counter] == '-')
		{
			res -= whole_numbers[operand_counter++];
			operation_counter++;
		}
		else if(operations[operation_counter] == '+')
		{
			res += whole_numbers[operand_counter++];
			operation_counter++;
		}
	}
	return res;
}

void Print_Equation_Result()
{

	sint64 res = Equation_Simplification();
	if(res == 'x')
		return;
	LCD_moveCursor(1,0);
	LCD_intgerToString(res);
	Reset_Arrays();
	while(Get_Keypad_Input() != 'c');
	LCD_clearScreen();
}


void Reset_Arrays(void)
{
	memset(whole_numbers, 0, sizeof(whole_numbers));
	memset(operations, 0, sizeof(operations));
	whole_numbers_counter = 0;
	operations_counter = 0;
	old_num = 0;
}

void RunTimeErrorMsg(void)
{
	LCD_clearScreen();
	LCD_displayString("Error!! Can't");
	LCD_moveCursor(1,0);
	LCD_displayString("divide by zero!");
	_delay_ms(2000);
	LCD_clearScreen();
	Reset_Arrays();
}

void User_Clearing_Screen(void)
{
	LCD_clearScreen();
	Reset_Arrays();
	LCD_displayString("Clearing Screen..");
	_delay_ms(500);
	LCD_clearScreen();
}
